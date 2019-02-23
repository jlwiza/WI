#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <gl/Gl.h>
#include <malloc.h>

#include "STB\stb_image\stb_image.cpp"
#include "GL/wglew.h"
#include "globalResources.h"

// i may use it, i dunno i thihnk were gonna go with the standard Graphics_vector thing  it 
// My locals or just think of these as private, so if i have a simple name like vector 



static HWND win;
struct Graphics_vector
{
	float x = 0;
	float y = 0;
};

// this isnt actually it but its close
GLfloat Graphics_width = 1000;
GLfloat Graphics_height = 1000;

// ot kist recenters the camera so 0,0 is on the top right really doesnt matter where 0,0 is but convention is um... nice
cameraPos CameraPos = {Graphics_width/2,Graphics_height/2};


static Graphics_vector circ;

static unsigned int CompileShader(unsigned int type, const char *source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source;
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
    
	//TODO:(JON)ERROR HANNDDDLLING 
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		const char* output;
		if (type == GL_VERTEX_SHADER)
		{
			output = "vertex shader Failed";
		} else
		{
			output = "fragment shader Failed";
            
		}
        
        // I tried to do an inline ternerary operation but it wouldnt let me with the const char, I dont know why, buut ill manage somehow
        
        // haha what the fuck does that even mean?
		
		//??? im just gonna need this eventually you can also you this to concatanate strings StringCbPrintf its in the strsafe
		//StringCbPrintf(message, sizeof(message), "%f", CameraPos.X);
		// OutputDebugStringA("Error \n");
		MessageBoxExA(win, message, output, MB_OK, 0);
		
		glDeleteShader(id);
		return 0;
        
        
	}
    
	return id;
}


unsigned int buffer;
static unsigned int CreateShader(const char *vertexShader, const char *fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
    
	glDetachShader(program, fs);
	glDetachShader(program, vs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

// not sure if i should pass the appState through this as well hmmm.. i think id rather have a Application_Update function and this acts as the render part of the thing



//I need to agnostazise hwind and pixel format description and device context but thats not that much work so yeah.. upwards and onwards





//YAY i might call a function for this crap but i dunno this really only gets called the first time I dont know why this would be here, more realistically it would be on mouse down
// but since putting it on mouse down is dumb since it would update needlessly i would end up putting it in an update method anywhoo, so yeah , but we'll still limit the draw calls, doesnt seem to me itll matter but everything besides drawing should be something like 60 48 fps and then after that.. this drunk programming is not a good idea... aWWESSSOOMMMEE
// anyway as i was saying 60 to 48 fps when drawing but then when im just hanging out down the street doing the same old thing, i did last week ill just do 30 fps for the drawing and not a thing too dooo, but talk to youuuuuuuududududududududududu...


// ok but the first thing we gotta do is get a triangle strip no sensitivity curved bezier line so first a rectangle strip bezier, then 2, then we should be close enough to know how its done.. mmmk?


// so this actually would be called from the uh thingy... yeah i still need to understand how to handle loops and variables, do they just stick around maybe i should alloc and delete them? i dunno.. seriously i feel like i should know the answer to this by now... weird

// i may change this to something like triangle updater??

void Graphics_update(float vBuffer[], unsigned int numberOfTriangles)
{
    
	// yo image
    
	
	// this should definitely be temperorary till i get a real thing but you know 
	
    
    
	const char *vertexShader = R"(
   #version 330 core
   //layout(location = 0)in vec4 position;
   //layout(location = 3)in vec2 texCoord;
   layout(location = 0)in vec4 pos2;
   layout(location = 1) in vec4 vertexColor;			
   
   out vec4 fragmentColor;
   //out vec2 v_textCoord;
   // eventually it will probably need to be a vec4 so I made the cameraOffset a vec4
   uniform vec2 u_cameraOffset;
   uniform vec2 u_scrnDim;
   
   
   void main(){
  //	v_textCoord = texCoord;
  
   /*float in1;
   float in2;
   in1 = position.x/(u_scrnDim.x/2);
   in2 = position.y/(u_scrnDim.y/2);*/
   
   
   vec4 realignment2 = vec4((u_cameraOffset.x+pos2.x)/(u_scrnDim.x/2), -((u_cameraOffset.y+pos2.y)/(u_scrnDim.y/2)), pos2.zw);
   gl_Position = realignment2;
   fragmentColor = vertexColor;
   })";
    
    
    
    
	const char *fragmentShader = 
#include "FragmentShader.shader";
		// TODO: ok so what im doing next is creating a triangle, then two triangles, then i can create a method that creates triangle, or more specifically rectangles, and then we are pretty much off to the races and can copy our old code, even though it is scary, we are gonna cheat in the undo department by doing that same dumb shit that photoshop does, itll just
		// make things simpler for a little bit, then we'll worry about the performance considerations and a much better undo scheme
		// but i think it should be fine for a while, and bits of it will always be there
		// i dont know why but 
    
		// ok so im just gonna see if i can get imgui to compile and run i really dont care what version works so lets have at it shaaaall we, oh im also scared about mouse input if i screwed something up but since the message loop is firing else i wouldnt be able to exit i dont think so 
		unsigned int shader = CreateShader(vertexShader, fragmentShader);
    
	
    
	//Texture shit
    
	//stbi_set_flip_vertically_on_load(1);
	
	//	glActiveTexture()
    
    
	// i commented this to free it
	
    
    
	// its literaly just the size of the array
	// it looks weird just putting six but uh
	unsigned int vertsperTriangle = 3;
	unsigned int indecesPerTriangle = 2;
	unsigned int vTimesI = vertsperTriangle * indecesPerTriangle;
    
	//so were gonna pull out some values here to see if we cant make some dummy values to automate this based on
	// triangle vertices that we'll pass in then 
    
	float *vertices = vBuffer;
    
	// i think for now till it becomes a time to clean this up we'll just use this for textures, then well change to texture strips and all that when time comes, but for now party like its 1999
    
	// um what to do what to doooooo... we finished the stuff to make it sane, hmm.... 
    
	
	
    
	
	
	glGenBuffers(1, &buffer);
	//
    
    //I PUT SOME ALPHA STUFF DID NOT TEST
    // it just works.. just like that.. weird.
    glEnable(GL_ALPHA_TEST);
	
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 3*vTimesI * numberOfTriangles * sizeof(float), vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
    
    
	
	
	glVertexAttribPointer(1, 4, GL_FLOAT, true, sizeof(float) * 6, (const void*)(sizeof(float)*2));
	glEnableVertexAttribArray(1);
	glBindVertexArray(1);
    
	
	
    
    glUseProgram(shader);
	
    
	int location = glGetUniformLocation(shader, "u_scrnDim");
	glUniform2f(location, Graphics_width, Graphics_height);
    
	location = glGetUniformLocation(shader, "u_cameraOffset");
	glUniform2f(location, -CameraPos.X, -CameraPos.Y);
    
	
	glDeleteProgram(shader);
    
}

void DrawGLShapes(unsigned int numOflines)
{
    glDrawArrays(GL_TRIANGLES, 0, numOflines);
    
}

void Graphics_Render(unsigned int numOflines)
{
    
	// this is broken ish its good for example but when i set up how the mouse will input i need to bring some of the set up code out to the loop, but 
	// only playing it once it gets changed i think, or it might be more i dunno i think we'll just guess try it out then see where it may take us
	__int16 vertsperTriangles = 3;
	unsigned int numOfTriangles = numOflines*2*vertsperTriangles;
    
	// i have no idea what the width is but for now i will give you what the demensions are on start up and you can go from there
    
	// i think this may be it soo yeah why not
    
    
    
    
	glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
	glClearDepth(10.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// hmm i was gonna use the projection formula, but its a library that i dont think i need to put on so i will just write it myself and not use that crap
    
	// so game plan is get the stb the png get the ui library, then get the projection, stop it from using opengl crazy coordinates too, so just inverse it then i can write some quick bezier code first a line, then two lines, then the whole damn thing, ok then we
    
    // jeez the beautiful level of naivity of that comment is something else.. just write a line or two than it'll be great yeah
    
	// i just gotta get the projection thing down and then i can get the stb and whatnot
	//what we need to do eventually is just  reposition the origin and flip the y in the view port so it makes sense, but thats not crazy important can do that later w just need stb and imgui
	// apparently my viewport game is weak so it makes seem strange even though they are not... wasted 3 hours trying to fix a problem that wasnt even there... LAAAAAADAGGAHAAHHAMME
	glViewport(1, -395, Graphics_width, Graphics_height);
    
	//glMatrixMode(GL_ident);
	DrawGLShapes(numOflines);
	
	//glDrawElements(GL_TRIANGLES, 3,);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	//glBindVertexArray(0);
    
	glEnd();
    
	glDeleteBuffers(1, &buffer);
	//glDeleteVertexArrays(1, &buffer);
    
    
}

void Graphics_UpdateTexture()
{
	float positions[12];
	float textCoords[12];
	int slot = 0;
    // what?! why is it just vertex shader fragment shader? Ill have to write this up so its not fucking retarded.. maybe i dummied this
	const char *vertexShader = "Vertex shader";
    const char *fragmentShader = "Fragment shader";
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	unsigned int textureHandler = 1;
	unsigned int buffers[2];
	// not sure about this type but i dont think itll matter
	unsigned int numberOfTriangles = 1;
    
    
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureHandler);
    
    
	unsigned int vertsperTriangle = 3;
	unsigned int indecesPerTriangle = 2;
	unsigned int vTimesI = vertsperTriangle * indecesPerTriangle;
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vTimesI * numberOfTriangles * sizeof(float), positions, GL_STATIC_DRAW);
    
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
    
    
    
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, vTimesI * numberOfTriangles * sizeof(float), textCoords, GL_STATIC_DRAW);
    
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(1);
    
    
	int location = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(location, 0);
}
void Graphics_initTexture()
{
    
	int testIWidth, testIheight, fileChannels;
    // how do i learn the texture's width? I dont need it obviously but itd be nice
	float image_width = 644;
	float image_height = 608;
    
    
	//I'll have to come back to this to deal with textures but that wont be for a while, it should be easy since i got the first one but opengl fucking sucks
	//we'll just set this up make it easy then we'll make it an arbirary size
	//unsigned int numOftriangles = 2;
	float positions[] = {
		0.0f,0.0f,
		image_width, 0.0f,
		image_width,image_width,
		0.0f,0.0f,
		image_width,image_width,
		0.0f, image_width
        
	};
    
    // its always gonna be this i never want part of a texture... except well maybe i do sometimes, if i want to texture pack... hmmm
	float textCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};
    
    unsigned char *textureTest = stbi_load("RES/myImage.png", &testIWidth, &testIheight, &fileChannels, 4);
	if (textureTest == 0)
		OutputDebugStringA("Error failed to load Image \n");
    
	unsigned int textureHandler;
	glGenTextures(1, &textureHandler);
	glBindTexture(GL_TEXTURE_2D, textureHandler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, testIWidth, testIheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureTest);
    
}

void Graphics_FreeTexture()
{
	/*if (textureTest)
 {
 stbi_image_free(&textureTest);
 }*/
	//glDeleteTextures(1, &shader);
}




// just learning some of the c family notes::



//bool, char, unsigned char, signed char, __int8	        1 byte
//__int16, short, unsigned short, wchar_t, __wchar_t	    2 bytes

//float, __int32, int, unsigned int, long, unsigned long	4 bytes


//double, __int64, long double, long long	                8 bytes

//if pArray is the array, type pArray, 10 in the watch window.

#if 0
v2 tgtPt = AppState->bezierCurves[0].controlPts[0];
v2 *cp = AppState->bezierCurves[0].controlPts;
v2 *bp = AppState->bezierCurves[0].bezierPts;

cp[0] = bp[0] + (2.0f/3.0f)*(tgtPt - bp[0]); 
cp[1] = bp[1] + (2.0f/3.0f)*(tgtPt - bp[1]); 

#endif