#pragma once
#include "Math.h"
#include <time.h>


// just some debug stuff

clock_t start, end, total;

//start = clock();
//end = clock();

// its windows specific but string shit is umm needed

#define LW_WINDOWS_DEBUG

#ifdef LW_WINDOWS_DEBUG
#include <strsafe.h>
// Id prefer to use this one 


typedef BOOL WINAPI wgl_swap_interval_ext(int interval);
wgl_swap_interval_ext *wglSwapInterval;




#define trace(string,...) {char message[150]; StringCbPrintfA((STRSAFE_LPSTR)message, sizeof(message),(STRSAFE_LPCSTR)string, __VA_ARGS__);\
    OutputDebugStringA(message);\
}
// its just more explicit and you have to define the message above
#define Etrace(message,string,...) StringCbPrintf((STRSAFE_LPCSTR)message, sizeof(message),(STRSAFE_LPCSTR)string, __VA_ARGS__)

// not necessary but uh yeah there you go
#define Assert(expression)  if(!(expression)) {DebugBreak();}

#else
#define Assert(expression) if(!(expression)) {*(int *)0 = 0;}
#define trace(x,...) 
#define Etrace(x,y,...) 
#endif

//im gonna keep some of the windows code here but ill need to get rid of it at a certain point
#define Kilos(Value) (Value * 1024)
#define Megs(Value) (Kilos(Value) * 1024)
#define Gigs(Value) (Megs(Value) * 1024)


bool BP = true;

const int MAXFRMS = 40;
const int MAXBEZ = 100;
const int TWEENBUTTON =1;

struct Application_Handler
{
	void *AppMemory;
	void *UndoSpace;
};

struct v2
{
	float x;
	float y;
};



inline v2 operator+(v2 a , v2 b){
    
	v2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

inline v2 operator-(v2 a, v2 b){
	v2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

inline v2 operator*(v2 a, v2 b){
	v2 r;
	r.x = a.x*b.x;
	r.y = a.y*b.y;
	return r;
}

inline v2 operator/(v2 a, v2 b){
	v2 r;
	r.x = a.x/b.x;
	r.y = a.y/b.y;
	return r;
}

inline v2 operator*(float a, v2 b){
	v2 r;
	r.x = a*b.x;
	r.y = a*b.y;
	return r;
}



namespace testingName
{
    struct vev
    {
        float jon;
        float away;
    };
} // namespace testingName
// fix this i really shouldnt even need to send this over

v2 lerpV2(v2 p1, v2 p2, float t)
{
	v2 lerp = {};
	lerp.x = (1 - t) * p1.x + t * p2.x;
	lerp.y = (1 - t) * p1.y + t * p2.y;
	return lerp;
}

float lerpf(float p1, float p2, float t)
{
	float lerp = {};
	lerp = (1 - t) * p1 + t * p2;
	return lerp;
}

float DistV2(v2 p1, v2 p2)
{
    float c = sqrtf((p2.x - p1.x)*(p2.x - p1.x)+(p2.y - p1.y)*(p2.y - p1.y));
    return c;
}


struct v3
{
	float x, y, z;
};
struct cameraPos
{
	// i dunno i just put this here if i wanted to put more shit here really no reason to make it like i did but
	union {
		v3 pos;
		float X, Y, Z;
	};
};

struct boxRef
{
	float xl;
	float xh;
	float yl;
	float yh;
};

struct v4
{
	float x;
	float y;
	float z;
	float w;
};

// not sure if i should define bezierCurves in its primitive or just data, I imagine keeping it flat with just data may not only be more versitile but more useful... I dunno because keeping it as a simple primitive i dont do things automagically, because in here all i do is give it the number of bezier points and it defines everything else... no jon with this system i could change it to the other system, this just takes the data and processes it in the simplest input, it doesnt automagically do anything
struct bezierCurve;
struct EdgeBoxes;

struct intersection
{
    // im not sure if im ever gonna need the b_i or t at this point.. yeah for kutting, then again if need be i can cut from scratch, since cutting is suh a rare 
    // TODO:: OPTIMIZE PRIME
    // b_i is the the bpoint
    __int8 b_i;
    bool isCutting;
    int b_t;
    int crsAngle;
    
    // t is the exact value 
    float t;
    v2 pt;
    intersection *pair;
    
    bezierCurve *bCurve;
	//I would never need to know 
    // but for what im testing its 
};


// yeah this is some oop nonesense going into this very dumb
// should be like maybe even a 400 v2 array then store th ix's, but we'll see if we need to kill stuff to get to the so so good 60fps I think its completely and uderly doable even under high hmm a bezier is just just a collection of points I really shouldnt store all this here, so innefecient
//TODO:: destroy this, but its useful to think abut it like this so we'll see what our load is first then start killing a bunch of this, we have like 800 useless floats and 350 useless ix's that do nothing but take up space
// TODO:: StUDy its this just make this work, not too bad i hope
struct bezierCurve
{
    bool isEnd;
    bool isBeg;
	bool isInTween;
    unsigned int numOfBPts;
	unsigned int ixCount;
	float yl;
	float yh;
	float xl;
	float xh;
    // dont know what these bools are bt consider them fro
    
	// i dunno if i should do this i feel like im presupposing the problem when i do this ehh whatever
	v2 *rawPts;
    EdgeBoxes *edges;
    intersection ix[350];
    v2 bezierPts[400];
	v2 controlPts[400];
	// there are some definite optimizations that need to be made, its weird how obvious some of these fixes are now like I can dramatically decrease the size of this bahemous relatively trivially, bezierpoints cntrl points, should be 
    //TODO:: there is no reason to keep the edges around thats just way past dumb make sure to fix that 
    // TODO:: this shit should move out of this cuz its dumb to have multiple instances of this when i just use it when Im drawing
    
	// im gonna leave this because i may wanna refer to the raw points later, why? no idea but i feel like i made it for a reason
	// i honestly dont think i do C
	//TODO::Consider deleting this, wastes a shitton of space
};


// im thnking this is a pointless data hogging description 
// the nature of this has changed and i dont know where im actually gonna need the demensions or a lot of this
//TODO:: get rid of bezRef its a datahogging waste of space
struct bezRef
{
    
	float xl;
	float xh;
	float yl;
	float yh;
	float t1;
	float t2;
    
	// this is dumb but im gonna get rid of it anyway i think so yeah go hog
	union {
		v2 v;
		float x, y;
	};
	// the bcurve is a reference to the original bezier may not need it since were using it as a box
	bezierCurve *bCurve;
	v2 bezPts[2];
	v2 cntrlPts[2];
	// we use this original bezRefI to find out how far along we are in it
	int b_i;
};


struct EdgeBoxes
{
    bezRef *edges;
    unsigned int size;
    bezierCurve *curve;
    
};
//TODO:: GET RID OF BOOLS in structs
struct bHelper
{
	unsigned int posCount;
	unsigned int start;
	bool isTrailing;
    
	float oldestHeat;
	float lowestHeat;
	float lhtPoint;
    
	v2 *rawPts;
};
// i dont think i use this consider deleting it
struct line
{
	v2 pt1;
	v2 pt2;
	v4 color = {0.0f, 0.0f, 0.0f, 0.0f};
};

struct shape
{
	// if its smaller than a pixel dont bother drawing it
	float xl, xh, yl, yh;
	v4 color;
	// bezier Curves are expensive and I may be potentially doubling up data, so Im goint to reference a bezier and then create it if its intersection is not at the end, wow, this is why flash didnt do dynamic intersections, it would take an entire rewrite of the system... jeez, if i didnt have dynamic intersections it would always definitely be one of the beziers
    
    // an int before would have worked but now were gonna put it as a pointer.. because its less expensive i dont have to do a two tear thing, and its not often shapes get used as a group.. so yeah 
    
    // this is probably going to become the start of the two teir system ive been thinking of mmmk?
	bezierCurve *bezierCurves[50];
	// i think if it goes more than that, it should be like oh your going into insane levels of detail, which i shouldnt disuage, I should make this fail more often then
};

// just transfer over to this if thats the case
struct largeShape
{
	float xl, xh, yl, yh;
	v4 color;
	bezierCurve *bezierCurves[100];
	// i think if it goes more than that, it should be like oh your going into insane levels of detail, which i shouldnt disuage, I should make this fail more often then
	//TODO:: bezier curve has a low number which should be typical, but there may be circumstances when your making large shapes,
};

//this i nowhere near enough i can see one taking up that much space but itll give me an idea of how to get some interesting questions
// TODO:: Kill this when do i use this ridiculous mess, its completely unnecessary, kill it, SERIOUSLY WTF
struct lineSegment
{
	float triangleVerts[4000000];
	float triangleColors[400];
};

inline v2 V2(float x, float y)
{
	v2 r;
	r.x = x;
	r.y = y;
	return r;
}


inline v3 V3(float x, float y, float z)
{
	v3 r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;
}

inline float dot(v2 a, v2 b)
{
	float result = a.x * b.x + a.y * b.y;
	return result;
}

enum Mode : unsigned char
{
	Drawing = 0,
	Editing,
    Filling,
    Selection
};

struct Application_State
{
    
    //  C++ is funny it partially implements features, like you can initialize a variable in a struct, but not if you pull it from the heap... but only if its on the stack.. which makes it next to useless.. its like thanks for the almost convienence 
    int currFrame = 1;
    unsigned int maxbezPerFrame = 0;
    // a better name would have been bezes in frame or something
    unsigned int frames[3000];
	__int32 BaseHeapAddress;
	bool canFill = true;
	bool GfxNeedsUpdate = true;
	unsigned int numOfLines;
	unsigned int vertCount;
	unsigned int tvertCount;
	unsigned int colorCount;
	unsigned int lineQue;
	unsigned int numOftempPoints;
	unsigned int numOfBeziers;
    float posAnglecnt;
	int twnframeCurves[50];
    // which beziers were last selected on the frame, we can change it to layer that can be either a shape or a bezier later
	int hotBeziers[MAXFRMS];
    v2 rawPoints[30000];
	Mode mode;
	v2 mousePos;
	float boxsize;
	float PenPressure;
	float PenMoveAngle;
	float bezDiv;
	unsigned int numOfBoxHndler;
	//lines lines[15];
	bezierCurve *selection[30];
    bezRef shapeBoxHandler[50][200];
	//bezRef shapeBoxHandler2[500];
	//bezRef shapeBoxHandler3[500];
	EdgeBoxes EdgeBoxes[50];
    unsigned int numOfEdgeBoxes;
    // im just 
    
    // TODO::vertex buffer will be the permanent one, very little is temporary in the drawing of the thing, its gonna take some rewriting to get that right though
    // DONT KNOW WHY THIS IS DONT CARE KILL ONE OF THESE
    float vertexBuffer[6000000];
	// right now tVertex buffer acts as the permanent one but that will change
	float tvertexBuffer[6000000];
	float paintCrap[7];
	//float colorBuffer[200000];
	// honestly this is really the only data that remains
	shape AppShapes[90000];
    // 40 represents the number of 
	bezierCurve bezierCurves[MAXFRMS][MAXBEZ];
    
	bHelper bezierHandler;
};

enum BezierType
{
	BezierCuveType,
	BezierReferenceType
};

// namespace testTempCode start 45 end 50 


// i got 28 lines last time
// oh at this point i was cleaning up how so it only iterates two


// okay here's what were gonna do dirt bag
// where gonna scrap this because first this is just based on a stupid premise i have no idea why someone would use this so were gonna do something I think a little bit smarter since we've already gonna through the trouble of.. you know if i never looked this shit up i feel like i would of just done a better job, like this box finding algorithm... isn't it a bit dumb, Im really thinking of scrapping everything i learned and just do it the way i would have done it had i never looked that stuff up.. anyway it works for now except yeah I looked back on this shit and its just so dumb it's so much more work than you need to do , its got a crazy amount of iterations, its completely context unaware, its kinda frustrating because its so much more difficult too.. like wtf? its so much more work, so much more complicated, and its so much slower