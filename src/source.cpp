#include <windows.h>
#include "globalResources.h"
#include "Application.cpp"
#define GLEW_STATIC
#include <GL/glew.h>


/// ok got imgui working umm didnt expect that i can keep that there to help make my ui, then ill probably end up deleting it at the end

struct IOcomp
{
	v2 MouseP;
	float PenPressure;
	bool isPen;
	bool MouseDown[3];
};

IOcomp io = {};

struct winContext
{
    
	HWND window;
	HDC context;
};

static void Fatal(const char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	//vprintf(msg, args);
	va_end(args);
	ExitProcess(1);
}

// I'd have this seperated out but this is some weird openGl windows talking shit to get it started, oh and vsync
// ok im gonna try some shit
void windowsGL_init(winContext *context)
{
    
    
	HWND window = context->window;
	HDC windowDC = context->context;
	PIXELFORMATDESCRIPTOR pixelFrmat = {};
    
	pixelFrmat.nSize = sizeof(pixelFrmat);
	pixelFrmat.nVersion = 1;
	pixelFrmat.iPixelType = PFD_TYPE_RGBA;
	pixelFrmat.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pixelFrmat.cColorBits = 32;
	pixelFrmat.cAlphaBits = 8;
	pixelFrmat.iLayerType = PFD_MAIN_PLANE;
	
    
    int suggestedPixelFrmatIndex = ChoosePixelFormat(windowDC, &pixelFrmat);
	
    
    
    PIXELFORMATDESCRIPTOR suggestedPixelFrmat;
	DescribePixelFormat(windowDC, suggestedPixelFrmatIndex, sizeof(suggestedPixelFrmat), &suggestedPixelFrmat);
	SetPixelFormat(windowDC, suggestedPixelFrmatIndex, &suggestedPixelFrmat);
    
	
	HGLRC OpenGLRC = wglCreateContext(windowDC);
	
    
    
	if (wglMakeCurrent(windowDC, OpenGLRC))
	{
        // still flickering wonder why... hmmm..
        wglSwapInterval =(wgl_swap_interval_ext *)wglGetProcAddress("wglSwapIntervalEXT");
        if(wglSwapInterval){
            wglSwapInterval(1);
        }
        
        if (glewInit() != GLEW_OK)
		{
			// so eventually when i decide to get rid of glew this is where we will start
            // why did i want to get rid of glew? hmmm..
			OutputDebugStringA("Error \n");
		} else
		{
            
            
			OutputDebugStringA("Success \n");
			//OutputDebugString(glGetString(GL_VERSION));
		}
		
        
        
        
	} else
	{
		//I dunno
	}
	ReleaseDC(window, windowDC);
}




//extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WindowProc(HWND   hwnd, UINT   msg, WPARAM wParam, LPARAM lParam)
{
    
    
	//if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
    //return true;
	const WORD wid = GET_POINTERID_WPARAM(wParam);
	POINTER_INFO piTemp = {};
	GetPointerInfo(wid, &piTemp);
	if (piTemp.pointerType == PT_PEN)
    {
        UINT32 entries = 0;
        UINT32 pointers = 0;
        
        POINTER_PEN_INFO penInfo; //= {};
        GetPointerFramePenInfoHistory(wid, &entries, &pointers, &penInfo); // how many
        
        
        
        BOOL check = GetPointerPenInfo(wid,
                                       &penInfo
                                       );
		
        
        
        if (penInfo.pressure > 0)
        {
            // dont know if this will work but yeah 
            io.PenPressure = (float)penInfo.pressure / 1024.0f;
            io.MouseP = V2(penInfo.pointerInfo.ptPixelLocation.x, penInfo.pointerInfo.ptPixelLocation.y);
            io.isPen = true;
            //it reports pressure from 0 to 1024
            int nonsense = 12;
        }else{
            
            io.PenPressure = 0.0f;
            io.MouseP = V2(penInfo.pointerInfo.ptPixelLocation.x, penInfo.pointerInfo.ptPixelLocation.y);
            io.isPen = false;
            //it reports pressure from 0 to 1024
            // the fuck is nonsense... sounds like nonsense
            int nonsense = 12;
            
        }
        // TODO, allocate space needed for the info, process the data in a loop to retrieve it, test pointerInfo.pointerFlags for down/up/update.
        
    }
    
	switch (msg)
	{
        
        
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
        {
            int button = 0;
            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONDBLCLK) button = 0;
            if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONDBLCLK) button = 1;
            if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONDBLCLK) button = 2;
            io.MouseDown[button] = true;
            return 0;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        {
            int button = 0;
            if (msg == WM_LBUTTONUP) button = 0;
            if (msg == WM_RBUTTONUP) button = 1;
            if (msg == WM_MBUTTONUP) button = 2;
            io.MouseDown[button] = false;
            return 0;
        }
        
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
            
        }
        
        default:
        {
            
            
            return DefWindowProc(hwnd, msg, wParam, lParam);
            break;
        }
        
	}
}


// this is where we f11 and stop at the first line on the program
int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR commandLine, int cmdShow)
{
    
    
	WNDCLASSA windClass = {};
	windClass.hInstance = instance;
	windClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windClass.lpfnWndProc = WindowProc;
	windClass.lpszClassName = "Paint Stuff";
	windClass.style = CS_OWNDC | CS_BYTEALIGNCLIENT;
    
	RECT rect = { 0,0,800,600 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
    
	HWND windowHandle;
	HDC dc;
	// very wrong should rename
	winContext myContext = {};
    
    
	if (RegisterClassA(&windClass))
	{
		windowHandle = CreateWindowExA(0, windClass.lpszClassName, "PaintCrap", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 0, 0, instance, 0);
		dc = GetDC(windowHandle);
		if (windowHandle)
		{
			myContext.context = dc;
			myContext.window = windowHandle;
			// so this doesnt need my appstate since its just graphics stuff, but whatevs
			// but i think application init will probably end up including graphics init or something doesnt really matter 
			windowsGL_init(&myContext);
			ShowWindow(windowHandle, cmdShow);
            
		} else
		{
			return -1;
		}
	} else
	{
        
	}
    
    
    
	Application_Handler Buffer;
	Buffer.AppMemory = (void *)calloc(1,Megs(600));
    
    
    
    
	Application_State *AppState = (Application_State *)Buffer.AppMemory;
    
	AppState->GfxNeedsUpdate = true;
    
    //TODO:: if your loading from a closed state this would be the place to load this
    AppState->currFrame =1; 
    AppState->maxbezPerFrame =100; 
	
	AppState->mode = Drawing;
    
	MSG msg;
	msg.message = WM_NULL;
	
    
	
	while (msg.message != WM_QUIT)
	{
        
        
		
		int a;
		a = 4;
		RECT clientRect;
		GetClientRect(windowHandle, &clientRect);
		int windowWidth = clientRect.right - clientRect.left;
		int windowHeight = clientRect.bottom - clientRect.top;
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		} else
		{
			POINT tempMouse;
            GetCursorPos(&tempMouse);
            ScreenToClient(windowHandle, &tempMouse);
            io.MouseP = V2(tempMouse.x, tempMouse.y);
            if (!io.isPen)
            {
                io.PenPressure =(float)io.MouseDown[0];
            }
            AppState->mousePos = io.MouseP;
			AppState->PenPressure = io.PenPressure;
            if(AppState->PenPressure){
                // i dont think i should put this here but i am dumb so you know
                AppState->canFill = true;
            }
            char message[700];
            /*StringCbPrintf(message, sizeof(message), "x = %f,y = %f  \n",AppState->mousePos.x, AppState->mousePos.y);
OutputDebugStringA(message);*/
            trace("PEN PRESSURE %f", AppState->PenPressure);
            
            
            start = clock();
            
            
            Application_Update(AppState);
            
            end = clock();
            double total_t = (double)(end - start)/CLOCKS_PER_SEC;
            //trace("\n\n\nExit program time = %f \n\n\n\n\n", total_t);
            
            
			
            
            
			SwapBuffers(dc);
            
            
		}
        
	}
    
    
	return 0;
}
//cntrl shift p 