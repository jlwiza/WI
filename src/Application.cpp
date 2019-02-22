#pragma once
//#include "Application.h"

#include "Graphics.cpp"
#include "BezierResources.h"
#define M_PI 3.14159265358979323846
float tempAngle;
unsigned int tempShapeBoxesOutline;
intersection ixblock[20];
unsigned int ixblockcnt;
unsigned int fillQCnt;
float fillqueX[200];
float fillqueY[200];

//bezRef boneHead[20];
//bezRef boneHead2[20];

// I have made  a change
namespace whoKnows
{
    bool isTrue = false;
}

namespace whoKnowss
{
    bezRef someMoreCrap = {};
    
}



// god i really hope i didnt go through with that kind of operator overloading... its so confusing in practice... assignment should always just be a simple copy.. its too much mental realistate to do crap like that.

//TODO::z i dunno but i think this should probably be moved to the gpu but its nice convience thing right now

//
//float & composite::ySet::xxxxor=(float y)
//{
//	float ang = temporary_solution_angle;
//
//	float r = y * -sin(ang) + y * cos(ang);
//	return y;
//	// TODO: insert return statement here
//}

__int8 silly_source_hack = 0;

v2 drawPoint(float c, float s, v2 origin, v2 pt)
{
    
	v2 r = {};
	r.x = origin.x + pt.x * c + pt.y * s;
	r.y = origin.y + pt.x * s + pt.y * -c;
    
	return r;
}

// ok you know the goal let see if that simple formula can help me I know this will work but lets see if the

// itll probably just take in line and appstate
void drawLine(v2 pt1, v2 pt2, float width, v4 color, Application_State *AppState)
{
    
	float angle = atan2f(pt2.y - pt1.y, pt2.x - pt1.x);
	float a = pt2.y - pt1.y;
	float b = pt2.x - pt1.x;
	float l = sqrtf(a * a + b * b);
    
	float c = cosf(angle);
	float s = sinf(angle);
    
	v2 Xaxis = {l * c, l * s};
	v2 Yaxis = {l * -s, l * c};
    
	float points[12]{
		0.0f, -width / 2,
		l, -width / 2,
		l, width / 2,
		0.0f, -width / 2,
		l, width / 2,
		0.0f, width / 2};
	
    
	float *vertexbuffer = AppState->vertexBuffer;
	AppState->vertCount;
	unsigned int *cCnt = &AppState->colorCount;
	for (size_t i = 0; i < 12; i++)
	{
		v2 r1 = drawPoint(c, s, pt1, V2(points[i], points[i + 1]));
		i++;
		vertexbuffer[AppState->vertCount] = r1.x;
		AppState->vertCount += 1;
		vertexbuffer[AppState->vertCount] = r1.y;
		AppState->vertCount += 1;
        
		vertexbuffer[AppState->vertCount] = color.x;
		AppState->vertCount += 1;
		vertexbuffer[AppState->vertCount] = color.y;
		AppState->vertCount += 1;
		vertexbuffer[AppState->vertCount] = color.z;
		AppState->vertCount += 1;
		vertexbuffer[AppState->vertCount] = color.w;
		AppState->vertCount += 1;
		// we'll always have one more than we actually have
	}
    
	//AppState->colorBuffer[AppState->colorCount] = color.w
	//*cCnt += 1;
    
	AppState->numOfLines++;
}

// it needs four points to determine the mid point between the damn thing
// dont know why i didnt just need three though, christ this makes it hard though, maybe i should just go to the original draw line... hmmm..
// this is a dumb system how is this possible.. how can i create a line if there isnt a guarantee of having four points
// vc.y represents the left hand and vc.r represents the right hand one
void drawLine2(v2 pt1, v2 pt2,v2 pt3,v2 pt4, float width, v4 color, Application_State *AppState, v3 vc)
{
    
    float angle = atan2f(pt3.y - pt1.y, pt3.x - pt1.x);
	float a = pt2.y - pt1.y;
	float b = pt2.x - pt1.x;
	float l = sqrtf(a * a + b * b);
    
	float c = cosf(angle);
	float s = sinf(angle);
    
    angle = atan2f(pt4.y - pt2.y, pt4.x - pt2.x);
    
    float c1 = cosf(angle);
	float s1 = sinf(angle);
    
	v2 Xaxis = {l * c, l * s};
	v2 Yaxis = {l * -s, l * c};
    
	// the l/2 gives me the half way point between two points lines, I may need it to curve out something a bit more
    // first i think is rnomal, second is length and rnormal third is length and lnormal
    //  I think this ignores the midpoint.. clever but ultimately 
	
    // im just gonna override this and set
    float points[12]{
		0.0f, -width / 2,// |
		l/2, -width / 2,  //  rnormal point i think unless its 0 based 
		l/2, width / 2,   //  lnormal point
		0.0f, -width / 2, 
		l/2, width / 2,  // lnormal point
		0.0f, width / 2};
    // this shit actually goes on the implementation all this tells me is the direction 
    
    float pointsAlt[12] {
        0.0f, -vc.z / 2,// |
        l/2, -vc.z / 2,  //  rnormal point i think unless its 0 based 
        l/2, vc.y / 2,   //  lnormal point
        0.0f, -vc.z / 2, 
        l/2, vc.y / 2,  // lnormal point
        0.0f, vc.y / 2};
    
    if(!isnan(vc.x))
    {
        // the thing about it i have to figure out the lwidth and the 
        // if topSTays which we're just going to assume for right now just to make it easy 
        if(false){
            points[5] = pointsAlt[5];       
            points[9] = pointsAlt[9];       
            points[11] = pointsAlt[11];                   
        }else{
            points[1] = pointsAlt[1];       
            points[3] = pointsAlt[3];       
            points[7] = pointsAlt[7];                   
        }
    }
    
    float *vertexbuffer = AppState->vertexBuffer;
    AppState->vertCount;
    unsigned int *cCnt = &AppState->colorCount;
    
    for (size_t i = 0; i < 12; i++)
    {
        v2 r1;
        if(points[i] == 0.0f)
            r1 = drawPoint(c, s, pt1, V2(points[i], points[i + 1]));
        else
            r1 = drawPoint(c1, s1, pt3, V2(0.0f, points[i + 1]));
        // why didnt i just i+=2?
        i++;
        vertexbuffer[AppState->vertCount] = r1.x;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = r1.y;
        AppState->vertCount += 1;
        
        vertexbuffer[AppState->vertCount] = color.x;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.y;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.z;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.w;
        AppState->vertCount += 1;
        // we'll always have one more than we actually have
    }
    
    //AppState->colorBuffer[AppState->colorCount] = color.w
    //*cCnt += 1;
    
    AppState->numOfLines++;
}
// wow this is actually really really easy, except i dont know where the bezier is I may be better served getting a pointer the bezierCurvehandler, the frame and position of the first and second 

// I initially had the idea to move things around for cache performance considerations, I think that idea now is kinda short sighteed I may just wanna do it and keep track of al the links.. expensive yes but i think the other way is a shortcut thatll end up costing me more... but there is good knews I can make it a one dimensional array.. or i can make it a one dimensional array later.. and let me just trim a lot of the premature optimization crap out of the way


//FrameCurves is the number of reserved frames on each frame, its the first thing that I have to check to see if it works, also the from and to are [frms, "layer"]

// ok were just gonna seperate this out so it goes into a different 

void bezierTween(bezierCurve Blist[MAXFRMS][MAXBEZ],unsigned int *frames, int *frameCrves, int *from, int *to)
{
    
    // so were just gonna put some pointers and 0 in there because i just dont wanna deal with this mess... mmkkk
    // so this runs and swaps but iters frame frameCurves
    if(Blist[from[0]][frameCrves[from[0]]].numOfBPts != 0 && !Blist[from[0]][frameCrves[from[0]]].isInTween)
    {
        // were gonna do somet stuff
        bezierCurve swap = Blist[from[0]][from[1]];
        Blist[from[0]][from[1]] = Blist[from[0]][frameCrves[from[0]]];
        Blist[from[0]][frameCrves[from[0]]] = swap;
        Blist[from[0]][frameCrves[from[0]]].isInTween = true;
        frameCrves[from[0]] += 1;
        
    }else
    {
        // I dont think this would ever happen
        Blist[from[0]][frameCrves[from[0]]];
    }
    // I dont know what im going to 
    if(true)
    {
        bezierCurve swap = Blist[to[0]][to[1]];
        Blist[to[0]][to[1]] = Blist[to[0]][from[1]];
        Blist[to[0]][from[1]]= swap;
        Blist[to[0]][from[1]].isInTween = true;
        // I think this is write only makes sense i dont know 
        frameCrves[to[0]] += 1;
    }else
    {
        
        // I dont think this would ever happen
        Blist[to[0]][frameCrves[from[0]]];
    }
    
    bezierCurve lerpBeg;
    bezierCurve lerpEnd;
    
    //TODO::COMPACT THIS MESS i can do that by adding another variable that represents the from and to tween thingys and then I can put them in their appropriate place
    // so at this point we've probably done 
    // we ask which is  from or to and that one becomes 
    // im not sure if i should m
    // umm i should have just swapped these i dont know why i thought this would work, 
    // maybe i did this in a different day
    if(Blist[to[0]][from[1]].numOfBPts > Blist[from[0]][from[1]].numOfBPts)
    {
        // it just says the end is unchanged
        
        lerpBeg= Blist[to[0]][from[1]];
        lerpEnd = Blist[to[0]][from[1]];
        // and we have to calculate the beginning
        
        //weve matched them
        
        // now we have to fit the thing
        // it goes in two phases first we fit the damn thing in a one to one kinda thing
        
        // first thing to were gonna make an array of float arrays lp1 and lp2 they are [lerpBeg.numOfBPts][2], may or may not work i dunno
        //Blist[from[0]][from[0]]->numOfBPts
        // it should be 400 on both but that dumb
        
        // umm i could just turn this into a 1d array and it may be worth considering, since ill have to do these in batches but again right now clarity not quality
        float lp1[2][150];
        float lp2[2][150];
        
        // the first is the actual distance the second is 
        lp1[0][0] = 0.0f;
        lp1[1][0] =0.0f;
        lp2[0][0] = 0.0f;
        lp2[1][0] = 0.0f;
        // what happens is this wont work in the main one, for the distances, I probably have to recalculate it, honestly i doubt i need 1 to 1, but there it is formulas, so ofcourse this is temporary
        // I think ill do the lerp formula here for each individual, ehh I need it for ends so ill put it as part of the data, so this will come down the chain 
        //these should start with 0
        
        // its the total distance getter
        for(int i = 1; i <lerpEnd.numOfBPts; i++){
            lp1[0][i] = DistV2(lerpEnd.bezierPts[i-1], lerpEnd.bezierPts[i])+lp1[0][i-1];
        }
        
        for(int i = 1; i <lerpEnd.numOfBPts; i++ ){
            lp1[1][i] =lp1[0][i]/lp1[0][lerpEnd.numOfBPts - 1];
        }
        
        for(int i = 1; i <Blist[from[0]][from[1]].numOfBPts; i++){
            lp2[0][i] = DistV2(Blist[from[0]][from[1]].bezierPts[i-1], Blist[from[0]][from[1]].bezierPts[i]) + lp1[0][i - 1];
        }
        for(int i = 1; i <Blist[from[0]][from[1]].numOfBPts; i++){
            lp2[1][i] =lp2[0][i]/lp2[0][Blist[from[0]][from[1]].numOfBPts -1];
        }
        
        // after we do this were just gonna go through and test it probably tommorow, and debug it, honestly we could probably debug it today but you know... really good work today though 
        // this is the first pass
        for(int i = 0; i <lerpEnd.numOfBPts; i++ ){
            
            int cp = 0;
            for(int ii = 0; ii <Blist[from[0]][from[1]].numOfBPts; ii++ ){
                // we figure out which is the smallest difference
                if(fabsf(lp1[1][i] -lp2[1][ii]) < fabsf(lp1[1][i] -lp2[1][cp]) ){
                    cp = ii;
                }
                
            }
            lerpBeg.bezierPts[i] = Blist[from[0]][from[1]].bezierPts[cp];
            lerpBeg.controlPts[i*2] = Blist[from[0]][from[1]].bezierPts[cp];
            lerpBeg.controlPts[i*2+1] = Blist[from[0]][from[1]].bezierPts[cp];
            // this is where we fit that point onto the smaller part
            // after its gone through and realized its the one with the smalles 
        }
        // for testing really
        
        int tl = to[0] - from[0];
        
        
        
        // so before this just check the volume and flip if it fails, you just run it through and if the volume ever isnt in between flip it, the volume should always be between the two, though you have to make the vertical and horizontals, have a thickness of one, so you just check if it has a 0 volume, if it does check its height, and width, and use whichever isnt 0 to be the volume, 
        
        for(int j = 1; j< tl; j++){
            
            frames[from[0]+j-1] += 1;
            Blist[from[0] + j][from[1]] = lerpEnd;
            
            
            for(int i = 0; i <lerpEnd.numOfBPts; i++ ){
                
                v2 mp1 = lerpV2(lerpBeg.bezierPts[i], lerpEnd.bezierPts[i], (float)j/tl);
                
                Blist[from[0] + j][from[1]].bezierPts[i] =mp1;
                Blist[from[0] + j][from[1]].controlPts[i*2] = mp1;
                Blist[from[0] + j][from[1]].controlPts[i*2+1] = mp1;
                // after its gone through and realized its the one with the smalles 
            }
        }
        
        // were gonna use lp1 because were in the beg
        //then afterwards we place the remainder points that distance in there, I have to look up how to split the bezier, and get that point, I should probably test it at that point... nah i think im just gonna do this thing the whole way through then debug it, just seems dumber. or i could do it and place the new point at zero that might be fun 
        
    }else
    {
    }
    //frameCrves[to[0]] += 1;
    
    
}

void STATICDrawLine(v2 pt1, v2 pt2, float width, v4 color, Application_State *AppState)
{
    
    float angle = atan2f(pt2.y - pt1.y, pt2.x - pt1.x);
    float a = pt2.y - pt1.y;
    float b = pt2.x - pt1.x;
    float l = sqrtf(a * a + b * b);
    
    float c = cosf(angle);
    float s = sinf(angle);
    
    v2 Xaxis = {l * c, l * s};
    v2 Yaxis = {l * -s, l * c};
    
    float points[12]{
        0.0f, -width / 2,
        l, -width / 2,
        l, width / 2,
        0.0f, -width / 2,
        l, width / 2,
        0.0f, width / 2};
    
    float *vertexbuffer = AppState->tvertexBuffer;
    unsigned int *vcnt = &AppState->tvertCount;
    for (size_t i = 0; i < 12; i++)
    {
        v2 r1 = drawPoint(c, s, pt1, V2(points[i], points[i + 1]));
        i++;
        vertexbuffer[*vcnt] = r1.x;
        *vcnt += 1;
        vertexbuffer[*vcnt] = r1.y;
        *vcnt += 1;
        
        vertexbuffer[*vcnt] = color.x;
        *vcnt += 1;
        vertexbuffer[*vcnt] = color.y;
        *vcnt += 1;
        vertexbuffer[*vcnt] = color.z;
        *vcnt += 1;
        vertexbuffer[*vcnt] = color.w;
        *vcnt += 1;
        // we'll always have one more than we actually have
    }
    
    //AppState->colorBuffer[AppState->colorCount] = color.w
    //*cCnt += 1;
    
    AppState->numOfLines++;
}

void DrawBezBox(bezRef bf, v4 color, Application_State *AppState)
{
    //just a thought but if i draw these bezboxes as im drawing the line I may have something  itd also help me limit the size of the line but for now since I know Im only working with one I can use it right here but I think that's an excellent idea
    float stp = G_bezDivision;
    v2 *controlPts = bf.bCurve->controlPts;
    v2 *bezierPts = bf.bCurve->bezierPts;
    v2 vIter[35];
    __int8 cnt = 0;
    // add the total heat
    
    int t = (bf.t2 - bf.t1) / stp;
    // this wont work because it assumes it ends at the same place that i have the end of the curve
    bool islsOne = false;
    for (float u = bf.t1; u < bf.t2; u += stp)
    {
        v2 v = vIter[cnt];
        
        v.x = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[0].x + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[0].x + 3.0f * (1.0f - u) * u * u * controlPts[1].x + (u * u * u) * bezierPts[1].x;
        
        v.y = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[0].y + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[0].y + 3.0f * (1.0f - u) * u * u * controlPts[1].y + (u * u * u) * bezierPts[1].y;
        if (u == 0)
        {
            
            v = vIter[cnt + 1];
            
            v.y = bf.yh;
            if (u + stp < bf.t2)
            {
                v.x = bf.xl + 1 / t * cnt + 1;
            }
            else
            {
                islsOne = true;
                v.x = bf.xh;
            }
            
            v = vIter[cnt + 2];
            
            v.y = bf.yh;
            v.x = bf.xl + 1 / t * cnt;
            cnt += 3;
        }
        else
        {
            v = vIter[cnt + 1];
            
            v.y = bf.yh;
            v.x = bf.xl + 1 / t * cnt;
            
            vIter[cnt + 2] = vIter[cnt - 3];
            
            vIter[cnt + 3] = vIter[cnt];
            v = vIter[cnt + 4];
            
            v.y = bf.yh;
            v.x = bf.xl + 1 / t * cnt + 1;
            
            v = vIter[cnt + 5];
            
            v.y = bf.yh;
            v.x = bf.xl + 1 / t * cnt;
            
            cnt += 6;
        }
    }
    
    float u = bf.t2;
    v2 v = vIter[cnt];
    
    v.x = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[0].x + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[0].x + 3.0f * (1.0f - u) * u * u * controlPts[1].x + (u * u * u) * bezierPts[1].x;
    
    v.y = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[0].y + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[0].y + 3.0f * (1.0f - u) * u * u * controlPts[1].y + (u * u * u) * bezierPts[1].y;
    
    v = vIter[cnt + 1];
    
    v.y = bf.yh;
    v.x = bf.xh;
    
    vIter[cnt + 2] = vIter[cnt - 3];
    
    cnt += 3;
    
    float *vertexbuffer = AppState->vertexBuffer;
    for (size_t i = 0; i < cnt; i++)
    {
        v2 r1 = vIter[i];
        vertexbuffer[AppState->vertCount] = r1.x;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = r1.y;
        AppState->vertCount += 1;
        
        vertexbuffer[AppState->vertCount] = color.x;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.y;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.z;
        AppState->vertCount += 1;
        vertexbuffer[AppState->vertCount] = color.w;
        AppState->vertCount += 1;
        // we'll always have one more than we actually have
    }
}

//lort is leading or trailing
void DrawBez(bezierCurve *bCurve, unsigned int *pts, bHelper *BHandler)
{
    bool *isTrailing = &BHandler->isTrailing;
    v2 *controlPts = bCurve->controlPts;
    v2 *bezierPts = bCurve->bezierPts;
    v2 *rwpts = bCurve->rawPts;
    unsigned int *tPts = pts;
    bool someCrap = true;
    //dangerzone
    
    float oldHeat = 0;
    // not sure what ii
    unsigned int ii_;
    unsigned int noChange = 0;
    unsigned int count = 0;
    v2 delta0 = {};
    v2 delta1 = {};
    
    float *deltax;
    float *deltay;
    
    unsigned int b = bCurve->numOfBPts - 2;
    unsigned int c = b * 2;
    if (c == 2)
    {
        int sl = 3;
    }
    static v2 activeCntrl = controlPts[c + 0];;
    // i just dont know if im gonna want anything else besides leading or trailing bezier sooo... yeah
    if (*isTrailing)
    {
        deltax = &delta1.x;
        deltay = &delta1.y;
        //activeCntrl = controlPts[c + 1];
    }
    else
    {
        deltax = &delta0.x;
        deltay = &delta0.y;
        
    }
    bool isChange = true;
    v2 bestChange = {};
    float frst = BHandler->start;
    float lst = (int)*tPts;
    while (someCrap && count <= 8 * 12 * 4)
    {
        count++;
        // just a safety precaution
        delta0 = {};
        delta1 = {};
        // im thinking switching by count... maybe
        
        switch (noChange)
        {
            
            case 0:
            {
                *deltax = 0.0f;
                *deltay = 0.0f;
                break;
            }
            
            case 1:
            {
                *deltax = -1.0f;
                *deltay = -1.0f;
                break;
            }
            case 2:
            {
                *deltax = 0.0f;
                *deltay = -1.0f;
                break;
            }
            case 3:
            {
                *deltax = 1.0f;
                *deltay = -1.0f;
                break;
            }
            case 4:
            {
                *deltax = 1.0f;
                *deltay = 0.0f;
                break;
            }
            case 5:
            {
                *deltax = 1.0f;
                *deltay = 1.0f;
                break;
            }
            case 6:
            {
                *deltax = 0.0f;
                *deltay = 1.0f;
                break;
            }
            case 7:
            {
                *deltax = -1.0f;
                *deltay = 1.0f;
                break;
            }
            case 8:
            {
                *deltax = -1.0f;
                *deltay = 0.0f;
                break;
            }
        }
        float heat = 0.0f;
        float stp = G_bezDivision;
        // anyway a lot of this will be changed... not sure how though 
        // add the total heat
        //seems like i limited to two points.. heh.. weird
        for (float u = 0; u <= 1; u += stp)
        {
            
            v2 v = {};
            // not sure but i will do it here 
            v.x = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[b + 0].x + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[c + 0].x + delta0.x + 3.0f * (1.0f - u) * u * u * controlPts[c + 1].x + delta1.x + (u * u * u) * bezierPts[b + 1].x;
            
            v.y = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[b + 0].y + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[c + 0].y + delta0.y + 3.0f * (1.0f - u) * u * u * controlPts[c + 1].y + delta1.y + (u * u * u) * bezierPts[b + 1].y;
            
            
            if(u == 0){
                bCurve->xl  = v.x;
                bCurve->xh  = v.x;
                bCurve->yl  = v.y;
                bCurve->yh  = v.y;
                
            }
            
            if(bCurve->xl > v.x)
                bCurve->xl  = v.x;
            if(bCurve->xh < v.x)
                bCurve->xh = v.x;
            if(bCurve->yl > v.y)
                bCurve->yl = v.y;
            if(bCurve->yh < v.x)
                bCurve->yh = v.x;
            
            
            //ill wanna use my own transformation thingy or i could just get it from the point method i made i dunno yet
            
            // this is what gets fed to the line creator thing?? so if there is a problem itlll show up here
            float lesq = 0;
            for (unsigned int i = frst; i < lst; i++)
            {
                // its just a quick distance approximation it should be fine since im just approximating
                // ok if i have 10 points and i have 30 points
                float a = v.x - rwpts[i].x;
                float b = v.y - rwpts[i].y;
                
                float f = ((a * a + b * b));
                if (i == BHandler->start)
                {
                    lesq = f;
                }
                else if (f < lesq)
                {
                    lesq = f;
                }
            }
            
            heat += lesq;
        }
        if (oldHeat)
        {
            
            if (oldHeat > heat)
            {
                isChange = true;
                oldHeat = heat;
                bestChange.x = activeCntrl.x + *deltax / 4;
                bestChange.y = activeCntrl.y + *deltay / 4;
            }
            
            if (noChange == 8)
            {
                if (isChange && count < 20000)
                {
                    activeCntrl.x = bestChange.x;
                    activeCntrl.y = bestChange.y;
                    v2 tgtPt = activeCntrl;
                    v2 * bp = bezierPts;
                    controlPts[c + 0] = bp[b +0] + (0.0f/3.0f)*(tgtPt - bp[b+0]); 
                    controlPts[c+1] =  bp[b +1] + (0.0f/3.0f)*(tgtPt - bp[b+1]); 
                    
                    
                    
                    isChange = false;
                    noChange = 0;
                    
                    oldHeat = 0;
                    
                    // i dont know what this is doing but if your doing clean up try do your best to kill this
                    if (false &&deltax == &delta0.x)
                    {
                        controlPts[c + 1] = rwpts[*tPts - 1];
                    }
                }
                else
                {
                    
                    // this is where we wanna trace out the heat
                    // because this is the closest we could get after all the iterations, we may  to do as a percentage and make sure we only start counting when we are over ten points
                    if (*pts <= 10)
                    {
                        BHandler->posCount = 0;
                        BHandler->lowestHeat = 200.0f;
                    }
                    
                    //trace("heat = %f difference = %f  %d \n",heat, heat - BHandler->oldestHeat, BHandler->posCount);
                    //OutputDebugStringA(message);
                    
                    //trace("\n \n Whiste %f \n\n\n \n", BHandler->lhtPoint);
                    
                    /*if (heat - bCurve->oldestHeat > 4.0f)
                    bCurve->posCount += 1;
                    else if(heat - bCurve->oldestHeat < 0.0f)
                    bCurve->posCount = 0;
                    */
                    if (heat > 120.0f)
                        BHandler->posCount += 1;
                    else if (heat - BHandler->oldestHeat < 0.0f)
                        BHandler->posCount = 0;
                    
                    if (BHandler->posCount == 5 && BHandler->lowestHeat < 120.0f && false)
                    {
                        //these are the end time
                        *isTrailing = !*isTrailing;
                        bCurve->numOfBPts += 1;
                        BHandler->start = *pts - 2;
                        controlPts[(bCurve->numOfBPts - 2) * 2] = rwpts[BHandler->start];
                        controlPts[(bCurve->numOfBPts - 2) * 2 + 1] = rwpts[BHandler->start + 1];
                        //OutputDebugStringA(mes);
                    }
                    
                    // ok were gonna try this instead after ten tpts were gonna keep track of the lowest point
                    // also were gonna see if our heat is above 200 for now we go back to the point were it was the lowest.. should work.. i think heck i dunno but we'll try it out
                    
                    BHandler->oldestHeat = heat;
                    if (heat < BHandler->lowestHeat)
                    {
                        BHandler->lowestHeat = heat;
                        BHandler->lhtPoint = *pts;
                    }
                    // ok the data says this should work and we can get a fixed zone model going
                    // and then later see if we can increase the space using math
                    // Im guessing we could use rate of increase between oldest heat and heat
                    
                    if (count >= 20000 && false)
                    {
                        //controlPts[0].x = 0.0f;
                        //controlPts[0].y = 0.0f;
                    }
                    someCrap = false;
                }
                
                // this is where we would tell it to switch
                continue;
            }
            noChange++;
        }
        else
        {
            // i think this is initialization.. not sure but probably
            bCurve->ixCount = 0;
            
            bestChange.x = activeCntrl.x;
            bestChange.y = activeCntrl.y;
            oldHeat = heat;
            if (BHandler->oldestHeat < 0.0f)
                BHandler->oldestHeat = heat;
            noChange = 1;
        }
    }
}

bool iBoxCollisions(bezRef c1, bezRef *c2, unsigned int numOfBoxes, unsigned int *cCnt = 0)
{
    
    for (int i = 0; i < numOfBoxes; i++)
    {
        if (c1.xl < c2[i].xh &&
            c2[i].xl < c1.xh &&
            c1.yl < c2[i].yh &&
            c2[i].yl < c1.yh)
        {
            *cCnt = i;
            return true;
        }
    }
    
    return false;
}

bool boxCollisions(bezRef c1, bezRef *c2, unsigned int numOfBoxes)
{
    
    for (int i = 0; i < numOfBoxes; i++)
    {
        if (c1.xl < c2[i].xh &&
            c2[i].xl < c1.xh &&
            c1.yl < c2[i].yh &&
            c2[i].yl < c1.yh)
        {
            
            return true;
        }
    }
    
    return false;
}

// i dunno what im gonna do with new color but its there

// cool i know how to make this i just havent, because i dont know if its necessaryz, im just
bool isboxflushCheck(bezRef testSquare, bezRef *collisionVolumes, unsigned int *numOfBoxes)
{
    return false;
}

// I have reverse list somewhere but I dunno so Im gonna make it here and just comment it out I dont think it was a full on function anyway i think it was just inside something

void reverseBezRefList(bezRef *list, int length)
{
    
    // TODO:: this is way too small
    bezRef tempList[90];
    unsigned int t = 0;
    for (int c = length; c <= 1; c--)
    {
        tempList[t] = list[c - 1];
        t++;
    }
}

void sortBezrefBoxes(bezRef *c2, unsigned int n)
{
    // Im pretty sure they retainted their  t1 and t2 so we can sort them on their t's
    int c, d, t;
    
    for (c = 0; c < n; c++)
    
        for (c = 1; c <= n - 1; c++)
    {
        d = c;
        
        while (d > 0 && c2[d - 1].t1 > c2[d].t1)
        {
            t = c2[d].t1;
            c2[d] = c2[d - 1];
            c2[d - 1].t1 = t;
            
            d--;
        }
    }
}

// I feel like alot of this is gonna get worryingly annoying ordering reordering
//Ive never felt this way before but there is a real messy ness to this that bothers the bejeezes out of me i really wanna go over and kill some of the repeating parts, maybe it was a little difficult to get it down in my head which is weird since it wasnt that bad of a problem...hmm
// Might wanna put these in order first I dunno Ill do something but yeah put the beziers in order because Im depending on that
void createFitBoxes(bezRef ctest, bezRef *c2, unsigned int numOfBoxes, Application_State *AppState)
{
    
    bezRef ogTest = ctest;
    int vcnt = 0;
    
    bezRef colVolumes[40];
    
    unsigned int nOb = numOfBoxes;
    bool isFinished = false;
    float oldYmin = ctest.yh;
    
    while (!isFinished)
    {
        vcnt = 0;
        for (int i = 0; i < nOb; i++)
        {
            // dont know how I knew it should be noninclusive but awesome
            if (ctest.xl < c2[i].xh &&
                c2[i].xl < ctest.xh &&
                ctest.yl < c2[i].yh &&
                c2[i].yl < ctest.yh)
            {
                
                // do some true shit here true;
                colVolumes[vcnt] = c2[i];
                vcnt++;
                
                // so cool now we have the collision volumes that I  to know
            }
        }
        
        //TODO:: ok im assuming
        
        // so now I just  to do the code to check what the size of the volume should be repeatedly adding rects, THIS WILL BREAK, but maybe i can fix it i dunno
        
        //TODO:: very potential error here should fix i just put this because i didnt want to check if wasnt initialized yet
        bezRef testiBox;
        bool isTestBox = false;
        float oldymax = ctest.yh;
        
        for (unsigned int i = 0; i < vcnt && !isTestBox; i++)
        {
            
            
            //
            
            if (colVolumes[i].xl <= ctest.xl && ctest.yl >= colVolumes[i].yl)
            {
                isTestBox = true;
                // if we found one were gonna check again and again
                //untill there is a gap at the end using this colVolume as our new testing zone thing
                
                testiBox = colVolumes[i];
                
                // all this does is make sure if there are any back to back
                for (unsigned int s = 0; s < vcnt && testiBox.xh < ctest.xh; s++)
                {
                    // there is the potential error over here that the low or mid box in here would be ignored to fix you just check if it collides with anything inside
                    if (colVolumes[s].xl == testiBox.xh && ctest.yl >= colVolumes[s].yl)
                    {
                        
                        testiBox = colVolumes[s];
                        
                        if (oldymax > colVolumes[s].yh)
                            oldymax = colVolumes[s].yh;
                        
                        break;
                    }
                }
            }
        }
        // now we're down to two options either the box is flush with the edge/greater or we have a gap either way we either draw box and just reshape the ctest and start again
        // this is gonna see if there is a gap
        
        bool isGap = false;
        bezRef mabox = {};
        
        mabox.xl = ctest.xh;
        mabox.xh = ctest.xh + 1.0f;
        
        if (!isTestBox)
        {
            testiBox = {};
            testiBox.xl = ctest.xl - 1.0f;
            testiBox.xh = ctest.xl;
            testiBox.yl = ctest.yl;
        }
        // im just looking for the closest lefti and seeing if there is a gap going good so far
        for (unsigned int s = 0; s < vcnt; s++)
        {
            if (colVolumes[s].xl >= testiBox.xh && testiBox.yl <= colVolumes[s].yh)
            {
                isGap = true;
                
                if (colVolumes[s].xl < mabox.xl)
                    mabox = colVolumes[s];
            }
            
            // were not gonna deal with this possibility of it coming from below yet... but we will
            if (oldymax > colVolumes[s].yl && colVolumes[s].yl > ctest.yl)
            {
                
                oldymax = colVolumes[s].yl;
            }
            
            if (oldymax > colVolumes[s].yh && colVolumes[s].yh > ctest.yl)
            {
                oldymax = colVolumes[s].yh;
            }
        }
        
        // ok so i have the idea that i have made this wanna make so at this point
        //hmm it feels like here we could check if we had any in that row and just find the highest
        
        //jeez this is some reaaly reeaaly bad code AAAAAAHHHAHAHAHAAHHH!!!!
        if (testiBox.xh < ctest.xh)
        {
            isGap = true;
        }
        
        if (isGap)
        {
            
            // to make this really work it should before this test through all the boxes again and see if there are
            static float wierdcheck = 0.0f;
            
            v4 weirdColor = {wierdcheck, 0.0f, wierdcheck, 1.0f};
            //wierdcheck+=50.5f;
            bezRef bxy = {};
            bxy.xl = testiBox.xh;
            bxy.xh = mabox.xl;
            bxy.yl = ctest.yl;
            bxy.yh = oldymax;
            
            float boxsize = bxy.xh - bxy.xl;
            float yboxsize = bxy.yh - bxy.yl;
            float t = bxy.xl + boxsize / 2;
            float d = bxy.yl + yboxsize / 2;
            paintRectangle(t, d, boxsize, weirdColor, AppState, yboxsize);
            
            // and we want to check if its at the end so it doesn go through it again for no reason
            //if (bxy.xh == ctest.xh)	{
            ctest.yl = oldymax;
            
            if (oldymax == ctest.yh)
                isFinished = true;
            //}
            
            //then add this box into the fray
            
            c2[nOb] = bxy;
            nOb += 1;
            
        }
        else
        {
            
            // ok if we're in the not is gap category there
            
            if (oldymax < ctest.yh)
            {
                ctest.yl = oldymax;
            }
            else
            {
                isFinished = true;
            }
        }
        // the if we're flush oldyMax  indicates how we need to change ctest.yh to oldYmax if oldYmax is vertically flush than we are done and it restart
    }
    
    //this is like the vertical gap handler I wanna get the first bit working first because this should be completely unnecessary in the v, if there are no verticle gaps this would be unnecessary we also need to have our ctest sensible, other
}

void adjustBox(unsigned int dir, bezRef *box, bezRef *c2, unsigned int *numOfBoxes, bezRef *output)
{
    const int up = 1;
    const int left = 2;
    const int down = 3;
    const int right = 4;
    
    bezRef *ctest = box;
    int vcnt = 0;
    
    bezRef *colVolumes = output;
    
    switch (dir)
    {
        case up:
        {
            for (int i = 0; i < *numOfBoxes; i++)
            {
                if (box->xl < c2[i].xh &&
                    c2[i].xl < box->xh)
                {
                    colVolumes[vcnt] = c2[i];
                    vcnt++;
                }
            }
            
            box->yl = box->yh;
            
            bezRef testiBox;
            
            for (unsigned int i = 0; i < vcnt; i++)
            {
                
                // why did i do this??? not sure hmm
                if (true) //colVolumes[i].xl <= box->xl)
                {
                    //isTestBox = true;
                    //Im stuck im thinking how this should be implemented, its weird for a simple case its obvious you just do the up but there are clear cases where the thing may buldge
                    // i think im gonna work till 2 then work and try not to kill myself...UGGGHGHGHGHGHGHGHGHGGHH
                    // so the idea is kinda umm you just do all the boxes regardless of
                    // umm so i just make the thing that makes sense
                    // it makes a box and i just have to now make sure the boxes center isnt to the left hand side
                    
                    // i should probably have to check flushness cus i can see this just not making anything or getting stuck in an infinite loop.. hmm
                    // ok so first were gonna check if anything is flush but we dont have to because
                    // we look for the closest
                    // so were gonna look for each that is equal
                    
                    // oh jeez its so obvious now its because the box yl starts higher than the original problem soo we need to start it equal to the the box.yh
                    if (box->yl >= colVolumes[i].yh)
                    {
                        box->yl = colVolumes[i].yh;
                        
                        // so were gonna use this to figure out if its left right or otherwise
                    }
                }
                
                // i think we can do all that shit right here like a left most to right most thinga madgig
            }
            // this is starting to look like more work than just seeing what's outside and deleting that... hmm 
            // well this code is here if the occasion should ever require it
            if (box->yl == box->yh)
            {
                bezRef flushVols[35];
                unsigned int count = 0;
                for (unsigned int i = 0; i < vcnt; i++)
                {
                    
                    //TODO:: umm were just gonna assume the simplest case with 2 if we have anymore than 2 we'll throw an error and handle that, its just right now its not necessary
                    if (box->yl == colVolumes[i].yh)
                    {
                        flushVols[count] = colVolumes[i]; 
                        count++;
                        //if this breaks then its time to handle this but i should be fine for a while
                        Assert(count<1)
                    }
                }
            }
            
            break;
        }
        case left:
        {
            
            break;
        }
        case down:
        {
            
            break;
        }
        case right:
        {
            
            break;
        }
        default:
        break;
    }
}

void floodFill(float x, float y, v4 oldcolor, v4 newcolor, unsigned int *shpeBoxes, Application_State *AppState)
{
    
    if (!AppState->canFill)
    {
        return;
    }
    // this is the bounds if i fill outside the bounds i should kill stop filling, it just gets complicated because filling, is a process that goes through stuff so to get it working right is gonna take some finagaling, that i really not too super stoked on doing
    
    // i also dont know where im gonna get the bounds am I just gonna keep the max's and mins? or do I just calculate them here... hmm probably
    static boxRef bounds = {0, 1024, 0, 1024};
    // oh its simple just turn on a canFill variable or something and have that turn
    if (AppState->canFill &&
        x < bounds.xl ||
        x > bounds.xh ||
        y < bounds.yl || y > bounds.yh)
    {
        AppState->canFill = false;
    }
    
    // TODO::this is dumb and I should put count in someplace but I am feeling tired and dumb
    static int count = 0;
    if (count < 0 && oldcolor.x != 0)
        return;
    
    oldcolor.x = 1.0f;
    if (count == 0)
    {
        AppState->paintCrap[0] = {};
        static bool isdone = false;
        
        if (!isdone)
        {
            bezRef *boxes;// = AppState->shapeBoxHandler;
            
            for (unsigned int i = 0; i < *shpeBoxes; i++)
            {
                
                v4 weirdColor = {0.5f, i / 4.0f, i / 4.0f, 1.0f};
                
                float boxsize = boxes[i].xh - boxes[i].xl;
                float yboxsize = boxes[i].yh - boxes[i].yl;
                float t = boxes[i].xl + boxsize / 2;
                float d = boxes[i].yl + yboxsize / 2;
                paintRectangle(t, d, boxsize, weirdColor, AppState, yboxsize);
                // not sure why this is here i thought this.. i dunno really doesnt matter i dont think
                tempShapeBoxesOutline = *shpeBoxes;
            }
            isdone = true;
        }
    }
    float bwdth = AppState->boxsize;
    bezRef box = {x - bwdth / 2, x + bwdth / 2, y - bwdth / 2, y + bwdth / 2};
    
    //TODO:: its likely to not move a pixel when create a bezier point so it would be wise not to use this for its creation, instead use a fixed amount, that way i can also regulate the size of the triangles to some extent, its fine for beginning testing get the point accross type shit though
    glbDim.yh = 600.0f;
    
    //if (!boxCollisions(box, AppState->shapeBoxHandler, *shpeBoxes) && y - bwdth / 2 > glbDim.yl && x - bwdth / 2 > glbDim.xl && x + bwdth / 2 < glbDim.xh && y + bwdth / 2 < glbDim.yh)
    if(false){
        
        count++;
        if (count > 1600)
        {
            
            AppState->paintCrap[0] = x;
            AppState->paintCrap[1] = y;
            AppState->paintCrap[2] = newcolor.x;
            AppState->paintCrap[3] = newcolor.y;
            AppState->paintCrap[4] = newcolor.z;
            AppState->paintCrap[5] = newcolor.w;
            //seems redundant dont know what i was doijng here i think some of this looks hackey and i may have done some of this as a work around im not sure
            AppState->numOfBoxHndler = *shpeBoxes;
            count = -1;
            
            return;
            
        }
        
        paintRectangle(x, y, bwdth, newcolor, AppState);
        //AppState->shapeBoxHandler[*shpeBoxes] = box;
        *shpeBoxes += 1;
        
        floodFill(x + bwdth, y, oldcolor, newcolor, shpeBoxes, AppState);
        floodFill(x, y + bwdth, oldcolor, newcolor, shpeBoxes, AppState);
        floodFill(x - bwdth, y, oldcolor, newcolor, shpeBoxes, AppState);
        floodFill(x, y - bwdth, oldcolor, newcolor, shpeBoxes, AppState);
    }
    else
    {
        // check if flush combine the two but anyway for now its fine
        static int newerBetterMostDefinitelyTemporaryCounter = 0;
        //if (boxCollisions(box, AppState->shapeBoxHandler, tempShapeBoxesOutline) && y - bwdth / 2 > glbDim.yl && x - bwdth / 2 > glbDim.xl && x + bwdth / 2 < glbDim.xh && y + bwdth / 2 < glbDim.yh && newerBetterMostDefinitelyTemporaryCounter < 100)
        {
            newerBetterMostDefinitelyTemporaryCounter++;
            
            unsigned int direction = 1;
            
            // why did i want colRects dont i make another  Rect... arrrghhhghhghghggh.. anyway ill manage lets see what happens
            //What im gonna do instead is eventually split it up... betweeen the fill boxes and the countour boxes
            //adjustBox(direction, &box, AppState->shapeBoxHandler, shpeBoxes, colRects);
            //createFitBoxes(box, AppState->shapeBoxHandler, *shpeBoxes, AppState);
            
            
            
            
            
        }
        trace("\n\n\n ma count %d \n\n\n\n", newerBetterMostDefinitelyTemporaryCounter);
    }
    
    //paintSquare(x, y, newcolor, AppState);
}



namespace testCode{
    
    void imaginaryFill(Application_State *Appstate, intersection *one = 0, intersection *two = 0)
    {
        // when i move this to flood i wont need to have a ix fill pair loop it would just iterate throught the points in the bezier, itll literally just do this once every time it finds a collision so there wouldnt be a ixblock or ixbloxk count
        for(int i =0; i <ixblockcnt; i+=2)
        {
            
            bezierCurve *bez = ixblock[i].bCurve;
            int low, high;
            if(ixblock[i].b_i <ixblock[i+1].b_i)
            {
                low = ixblock[i].b_i+1;
                high = ixblock[i+1].b_i+1;
                
            }else
            {
                low = ixblock[i+1].b_i+1;
                high = ixblock[i].b_i+1;
            }
            
            
            for(int i1 =low; i1 <high; i1++ )
            {
                v2 v = {};
                
                int divs = 12;
                fillQCnt = divs;
                // really should be an int
                
                for(int i2 =low; i2 <high; i2++ )
                {
                    
                    for(int i2 = 0; i2 < divs; i2++){
                        float t = i2*(1/divs);
                        fillqueY[i2]= (1.0f - t) * (1.0f - t) * (1.0f - t) * bez->bezierPts[i2].x + 3.0f * (1.0f - t) * (1.0f - t) * t * bez->controlPts[i2*2].x + 3.0f * (1.0f - t) * t * t * bez->controlPts[i2*2+1].x + (t * t * t) * bez->bezierPts[i2+1].x;
                    }
                    // sort then swap 
                    
                    for(int i2 = 0; i2 < divs; i2++){
                        float t = i2*(1/divs);
                        fillqueX[i2] = (1.0f - t) * (1.0f - t) * (1.0f - t) * bez->bezierPts[i2].y + 3.0f * (1.0f - t) * (1.0f - t) * t * bez->controlPts[i2*2].y + 3.0f * (1.0f - t) * t * t *bez->controlPts[i2*2+1].y + (t * t * t) * bez->bezierPts[i2+1].y;
                    }
                    //sort then swap
                }
                
            }
        }
        
        
    }
    
}

// i dunno if i use this but uhh cutting is here CUT CUUTER CUTTING
void ChopEnd(int bz_i, bezierCurve *curve)
{
    // so we need to do stuff here
    bool isLess;
    if(bz_i < curve->ix[0].b_i)
    {
        int ix = curve->ix[0].b_i;
        // otherwise were splitting the bezier into two its realy not that hard but uhh not right now
        for(int i = ix; i < curve->numOfBPts; i++)
        {
            curve->bezierPts[i - ix] = curve->bezierPts[i];
            curve->controlPts[2*i - ix] = curve->controlPts[2*i];
            curve->controlPts[2*i+1 - ix] = curve->controlPts[2*i+1];
        }
        curve->numOfBPts = curve->numOfBPts - ix;
        
        for(int i = 0; i < curve->ixCount; i++)
        {
            curve->ix[i].b_i -= ix;
        }
        
    }else if(bz_i > curve->ix[curve->ixCount - 1].b_i)
    {
        int ix = curve->ix[curve->ixCount - 1].b_i;
        // all we do is just change the length to equal the last one
        curve->numOfBPts = curve->numOfBPts - ix;
    }
    // id at this point split the bezier so it can serve as the last or first point 
    
}


bezRef *fmix = (bezRef *)calloc(7000,sizeof(bezRef));
unsigned int fmixSize;

// now the problem is im not sure that i can get the edgeBoxes, actually if its edgeBox centric, a lil weird but whatevs, so lets test it and see if it works
void Fmixer(float btL, float btH,EdgeBoxes e,  Application_State *AppState)
{
    float swap = 0;
    if(btL > btH)
    {
        swap = btL;
        btL = btH;
        btH = swap;
    }
    
    // so remember in the final wouldnt do this, itd be a function and itd say i want the boxes from t1 to 
    
    
    for (int i = 0; i < e.size; i++)
    {
        if (e.edges[i].t1 >= btL && e.edges[i].t2 <= btH)
        {
            fmix[fmixSize] = e.edges[i];
            fmixSize++;
        }
    }
    
    
    // I took away the lyH stuff here as well
    
    
    
}


void convienceFillFunction(Application_State *AppState)
{
    
    
    bezRef box = {};
    box.yl = box.yh; // it may be lYH.. i dunno 
    
    
    for (unsigned int i = 0; i < fmixSize; i++)
    {
        
        v4 weirdColor = {0.5f, i / 4.0f, i / 4.0f, 1.0f};
        float boxsize = fmix[i].xh - fmix[i].xl+ .000000001;
        float yboxsize = fmix[i].yh - fmix[i].yl+.0000000001;
        float t = fmix[i].xl + boxsize / 2;
        float d = fmix[i].yl + yboxsize / 2;
        paintRectangle(t, d, boxsize, weirdColor, AppState, yboxsize);
        
        //tempShapeBoxesOutline = *shpeBoxes;
    }
    
    
    // took away fillque stuff because um yeah 
    //return;
    testCode::adjustBox(&box, fmix,&fmixSize, AppState, false);
    
    //createFitBoxes(box, fmix,fcnt, AppState);
    // }
    
    for(int i = 0; i < 45; i++){
        
        //createFitBoxes(box, fmix,fcnt, AppState);
        
        box.yl = box.yh;
        testCode::adjustBox(&box, fmix,&fmixSize, AppState, true);
        
    }
    
    
}

// so the goal is for simple shapes it should just work fine... I can add to it so that when there are multiple ways to get to a place I can figure out which would be the ways Id rather it go
struct traversedIX
{
    __int8 dir = 0;
    // represents if Ive gone 0 for neither direction left right or both
    intersection *ix;
};



bool checkIx(bezierCurve *bCurve, int  b_t)
{
    
    bool res;
    
    
    
    
    return res;
}


// TODO:: get rid of APPSTATE L1 diff Im gonna wanna return the array of shpaes or something 
void shapeChecker(bezierCurve *bez, int b_t, traversedIX *tvd)
{
    // im gonna leave this i probably wont need this but this is what it should look like
    //bezierCurve *b_next = &AppState->bezierCurves[AppState->currFrame][b];
    
    bezierCurve *b_next = bez;
    
    b_t = 0;
    intersection *begIx = &bez->ix[b_t];
    
    
#if 0
    newsplitBezier(&AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1], splits[1], boneHead2);
#endif
    
    // I think on the thing before Im o
    
    // i think this was maybe test code?
    // I keep ALL THE EDGES!?!??!?!!!
    
    // not sure i wanna pass appstate in here im just not sure if itll work there is a good chance itll fail
    //Fmixer(bez->ix[b_t].t, b_t->ix[b_t+1].t,b1, AppState);
    intersection *orig = &b_next->ix[b_t];
    
    
    
    // i also represents the count.. not the best naming but uh sue me?
    int i = 0; 
    bool isFinished;
    while(!isFinished){
        
        b_t = tvd[i].ix->b_t;
        switch(tvd[i].dir)
        {
            
            
            // it gets tricky to actually get the path.. but i should be able to
            // since the final traversed
            
            //open path 
            case 0:
            {
                
                if(checkIx(tvd[i].ix->bCurve, b_t -1))
                {
                    
                    tvd[i].dir = 2;
                    tvd[i+1].ix = &tvd[i].ix->bCurve->ix[b_t -1];
                    tvd[i+1].dir =1; 
                    tvd[i+2].ix = tvd[i+1].ix->pair;
                    i +=2;
                    
                }
                else if(checkIx(tvd[i].ix->bCurve, b_t +1)){
                    
                    tvd[i].dir = 3;
                    tvd[i+1].ix = &tvd[i].ix->bCurve->ix[b_t +1];
                    tvd[i+1].dir =2; 
                    tvd[i+2].ix = tvd[i+1].ix->pair;
                    i +=2;
                    
                    
                }else{
                    i--;
                }
                
                // check if it can go lower... if you can procede to next point, find its partner and add that one to the to the que(set it to the next i ) .ix and also it sets this previous one to 2 it but the one with the partner that one you set to 1 since the only direction it can go is only more low,
                //otherwise we try to go right/ we set it to 0 if we cant go that way and its not the same thing since we've checkd but we set the current one to 3, the higher one if  we can add that one and we set it 2 since we can only go higher and we set its partner to be the next i and also we give it the address of the damn thing  like some kinda bizarro linked list
                // if we can go higher or lower we set it to 3
                break;
                
            }
            // only left is open hmm there would never be a situation that i would know this, because the moment i get to the path I try left and if left isnt open I try right // so it ne
            
            case 1:
            {
                
                if(checkIx(tvd[i].ix->bCurve, b_t -1))
                {
                    
                    tvd[i].dir = 3;
                    tvd[i+1].ix = &tvd[i].ix->bCurve->ix[b_t -1];
                    tvd[i+1].dir =1; 
                    tvd[i+2].ix = tvd[i+1].ix->pair;
                    i +=2;
                    
                }else{
                    i --;
                }
                
                // just go lower if we can, and we set it to 3 the next one we set to 1, and set up its partner set it up to be the next i to have the partner as its pointer
                break;
            }
            
            case 2:
            {
                
                
                if(checkIx(tvd[i].ix->bCurve, b_t +1)){
                    
                    tvd[i].dir = 3;
                    tvd[i+1].ix = &tvd[i].ix->bCurve->ix[b_t +1];
                    tvd[i+1].dir =2; 
                    tvd[i+2].ix = tvd[i+1].ix->pair;
                    i +=2;
                }else{
                    i--;
                }
                // we are going to look if we can go higher, if  we can't we set this value to 3 and go back in the array.. we really dont need to set it to  if we can go higher we set it to three and set the one to 2 since we are going to search the partner set that up same as before
                break;
            }
            case 3:
            {
                i--;
                // if we are 3 we set i we just decrement the value
                break;
            }
            // no default either but 
            default:
            {
                
                // we just wanna break the program if that doesnt fly 
                Assert(0);
                
                break;
            }
            
            
        }
        
        if(tvd[i].ix == begIx && tvd[i].dir != 3){
            
            isFinished = true;
        }else{
            
            // this is failure but im not sure what I want to do for failure at this point... it just means there was no way for it to make it passed.. for real we'd might just wanna make sure it's begIx[0].dir == 3; otherwise we should check if we can go left.. though that may not be true
            
        }
    }
    
    
    while( b_next->ix[b_t+1].pair != orig)
    {
        
        //TODO:: this is dumb and wasteful but whatever, it goes through every intersection to find the next highest, itll probably just work out since its filling but its so fucking dumb
        b_next = b_next->ix[b_t+1].pair->bCurve;
        // b_t is the of the i'th intersection
        b_t =  b_next->ix[b_t].b_t;
        
        EdgeBoxes b2 =*b_next->edges;
        //Fmixer(b_next->ix[b_t].t, b_next->ix[b_t+1].t,b2, AppState);
        
    }
    
}


bool ValueCheck(Application_State *AppState)
{
    v4 something = {0.0f, 1.0f, 0.0f};
    bool isNewPoint = false;
    // its a silly patch because its unitialized  to fix that, I cant think of any but there may be cause to delete everything from the screen so yeah... options
    
    bezRef b1left = {};
    b1left.bezPts[1] = V2(0.0f, 0.0f);
    b1left.bezPts[1] = V2(100.0f, 0.0f);
    b1left.cntrlPts[1] = V2(0.0f, 100.0f);
    b1left.cntrlPts[1] = V2(100.0f, 100.0f);
    
    
    float v = 0 * 4.0f;
    //TODO:: I should fix this, it s this for some reason, not sure why though
    drawLine(V2(v, 0.0f), V2(v, 600.0f), 8.0f, something, AppState);
    //			}
    //		}
    //#endif
    silly_source_hack++;
    if (silly_source_hack == 3)
        return false;
    else
    {
        
        
        static unsigned int iter = 0;
        
        if (AppState->paintCrap[0] != 0.0f)
        {
            float *pc = AppState->paintCrap;
            v4 other = {pc[2], pc[3], pc[4], pc[5]};
            floodFill(pc[0], pc[1], v4{}, other, &AppState->numOfBoxHndler, AppState);
        }
        
        {
            // the variables for the damn thing
            float curvePoints = 32;
            float u;
            // just incase it should be just u but who knows i could be wrong
            unsigned int pushCnt = 0;
            
            float _step = 1 / curvePoints;
            
            
            
            unsigned int *tPts = &AppState->numOftempPoints;
            static bool wasDown = false;
            
            // if i have a block of buttons dont be dumb just consolidate, but honestly thatd never be a performance bottleneck so forget i even said anything
            bool isAnglePositive;
            if(AppState->PenPressure > 0 )
            {
                boxRef buttons[2];
                int buttonLength = 1;
                buttons[0].xl = 0.0f;
                buttons[0].xh = 100.0f;
                buttons[0].yl = 0.0f;
                buttons[0].yh = 100.0f;
                
                buttons[TWEENBUTTON].xl = 0.0f;
                buttons[TWEENBUTTON].yl = 0.0f;
                buttons[TWEENBUTTON].xh = 100.0f;
                buttons[TWEENBUTTON].yh = 100.0f;
                
                for(int i = 0; i < buttonLength; i++){
                    
                    if(buttons[i].xl < AppState->mousePos.x && buttons[i].xh > AppState->mousePos.x &&
                       buttons[i].yl < AppState->mousePos.y && buttons[i].yh > AppState->mousePos.y){
                        wasDown = true;
                        // this return is just so it doesnt draw in here, I can assert a draw bounds in the thing later
                        return true;
                        
                    }
                }
            }
            
            
            // mouse up
            if(wasDown && AppState->PenPressure == 0.0f){
                
                // need to change the hit test but uh yeah 
                //if(HitTest(buttons[0], AppState->mousePos.x))
                if(AppState->mousePos.x < 100 && AppState->mousePos.y < 100){
                    
                    static bool swtch = false;
                    if(!swtch){
                        //this currFrame business needs to be refactored and cleaned up
                        AppState->currFrame += 1;
                    }else{
                        //dumb shit make sure to delete this
                        //
                        static bool played = false;
                        
                        if(!played){
                            int frme1[2] = {1,0};
                            int frme2[2] = {AppState->currFrame,0};
                            
                            bezierTween(AppState->bezierCurves,AppState->frames, AppState->twnframeCurves, frme1, frme2);
                            
                            played = true;
                        }
                        AppState->currFrame -= 1;
                    }
                    
                    if(AppState->currFrame > 3)
                    {
                        swtch = true;
                        
                    }
                    //if(AppState->mode == Drawing)
                    //AppState->mode = Filling;
                    //else if(AppState->mode == Filling)
                    //AppState->mode = Drawing;
                    
                }
                
                
                
                
                
            }
            if(AppState->PenPressure == 0.0f)
                wasDown = false;
            
            
            else if(AppState->mode == Filling && AppState->PenPressure > 0){
                // we definitely gonna move this to a function but for now its fine
                
                //were gonna assume that there are 2 for every bezier and they are ordered like that as well, i dont think it is though and youll need to adress that.. wow i see why you want to optimize while your going a long because i see the path to optimization and its a doozey but honestly all this code didnt take that long to write for now all that matters is that they are paired up
                
                //TODO:: CHECKPOINT
                //ok we just do the intersept inbetween double jumping and saving the intercept if the intersept is the lowest intersept it wins
                int ix;
                int b;
                // TODO:: this is hacky i was just being lazy 
                // in other words what this does is just check between intersections, so it creates essentially a line inbetween intersections and checks for that things collision because its impossible for it not to collide, what the rub is if you have multiple in that direction, you really have two options ask for the extremes of the line, and see if it goes underneath, the first intersection, then check 
                float ckTest = NAN;
                //ixblock[ixblockcnt - 1];
                // i should rename frame to something like beziersInFrame or something I can take it into that program that can do that 
                for(int bi = 0; bi < AppState->frames[AppState->currFrame -1] - 1; bi++){
                    
                    intersection *iblock = AppState->bezierCurves[AppState->currFrame][bi].ix;
                    for(int i; i < AppState->bezierCurves[AppState->currFrame][bi].ixCount; i+=2)
                    {
                        v2 ck =lineIntersect(iblock[i].pt, iblock[i+1].pt, AppState->mousePos, V2(AppState->mousePos.x,0));
                        
                        if(ckTest == NAN)
                            ckTest = ck.y;
                        if(ck.y < ckTest && ck.y > AppState->mousePos.y){
                            ckTest = ck.y;
                            ix = i;
                            b  = bi;
                        }
                        
                    }
                }
                
                int x = 0;
                //ixblock[x] =
                //AppState->bezierCurves[b].ix[ix];
                b = 0;
                ix = 0;
                EdgeBoxes b1 = *AppState->bezierCurves[AppState->currFrame][b].edges;
                
                bezierCurve *b_next = &AppState->bezierCurves[AppState->currFrame][b];
                
                int b_t = 0;
                
                Fmixer(b_next->ix[b_t].t, b_next->ix[b_t+1].t,b1, AppState);
                
                intersection *orig = &b_next->ix[b_t];
                
                // just figure out what the bez is and the inbetween ness it is around, I for now dont care about direction so long as its consistant
                
                
                //SNUFFLUGGULUS.. whatever
                //SNUFFLUGGULUS.. whateer
                
                
                // for this i can just get the first bezier and the first point itd be nice for testing.. ok good lets get swiffty 
                
                bezierCurve *bez;
                
                
                traversedIX tvd[50];
                
                shapeChecker(bez,  b_t,  tvd);
                
                
                while(b_next->ix[b_t+1].pair != orig)
                {
                    
                    //TODO:: this is dumb and wasteful but whatever, it goes through every intersection to find the next highest, itll probably jus work out since its filling but its so fucking dumb
                    b_next = b_next->ix[b_t+1].pair->bCurve;
                    
                    // b_t is the of the i'th intersection
                    b_t =  b_next->ix[b_t].b_t;
                    
                    
                    
                    EdgeBoxes b2 =*b_next->edges;
                    Fmixer(b_next->ix[b_t].t, b_next->ix[b_t+1].t,b2, AppState);
                    
                }
                
                
                convienceFillFunction(AppState);
                
                wasDown = false;
                AppState->mode =Drawing;
                // so heres what we know we know if we have two in the same order itll be 
                
                
                // god I love reading the past notes to myself
                
                // oh wow, this is interesting it makes the assumption that I only need to find any random one, because as soon as i find one,  should be able to go around, to its next intersection to make a completed shape if that thing works, which means I will be spending a lot of time tweaking the hell out of this shit, I may not even get this done tonight because I have a lot of self loathing... no i dont I dont know why i said that, maybe its because self loathing is hip, oh jon, you trying to be like the cool kids... yknow disagreeing with yourself like that is what eventually might lead to self loathing.... yeeesss.
                
                
                // okay were just gonna rewrite this, just because its actually pretty simple, we just make some really simple assumptions and then were gonna go from there 
                // ASS #1 every bezier only has two intersections
                //  ASS #2 they go in the same direction, so we'll just add em into the fmix and I think ill just be on my way, real quick simple dirty first test, its stupid but its really big
                
                // you might wanna order these in a clockwise, and ofcourse its radial around a given center point what have you 
                
                //Again this only works with perfectly behaved bez's but uh yeah, rock on 
                
                
                
#if 0
                bezRef *boneHead = AppState->shapeBoxHandler2;
                for(int bi = 0; bi < AppState->frames[AppState->currFrame -1]; bi++){
                    
                    bezRef rando[8] = {};
                    //TODO::REPLACE SPLIT BEZIER its waste hmm this is wrong, well it doesnt matter its a pointless algorithm 
                    splitBezier(&AppState->bezierCurves[bi], 8, rando);
                    memcpy(&boneHead[bi*8], rando, 8 * sizeof(bezRef));
                    
                    AppState->numOfBoxHndler = bi*8
                }
                
                v4 clor;
                
                floodFill(AppState->mousePos.x, AppState->mousePos.y, v4{}, clor, &AppState->numOfBoxHndler, AppState);
                
                
#endif
            }
            else if (AppState->mode == Selection && AppState->PenPressure > 0)
            {
                int cfm = AppState->currFrame;
                for(unsigned int i = 0; i < AppState->frames[AppState->currFrame -1]; i++)
                {
                    if(AppState->bezierCurves[cfm][i].yl  < AppState->mousePos.y && AppState->bezierCurves[cfm][i].yh >
                       AppState->mousePos.y && AppState->bezierCurves[cfm][i].xl  < AppState->mousePos.x && AppState->bezierCurves[cfm][i].xh >
                       AppState->mousePos.x)
                    {
                        
                        // ok thats done i think
                        for(int j = 0; j<AppState->bezierCurves[cfm][i].numOfBPts; j++){
                            
                            for(int jj = 0; jj< 3; jj++ ){
                                v2 p = getBezV2(&AppState->bezierCurves[cfm][i],BezierCuveType,j,jj);
                                // TODO(JON) nice and easy just get the squared distance soo i don't want this 
                                if(DistV2(p, AppState->mousePos) < 15.0f)
                                {
                                    
                                    AppState->selection[0][0] = cfm;
                                    AppState->selection[0][1] = i;
                                    
                                    //AppState->selection[AppState->selectionCnt][0] = cfm;
                                    //AppState->selection[AppState->selectionCnt][1] = i;
                                    AppState->selectionCnt++;
                                }
                            }
                        }
                    }
                }
                
            }
            else if (AppState->mode == Drawing && AppState->PenPressure > 0)
            {
                
                if (*tPts == 5)
                {
                    int e = 3;
                }
                
                v4 something = {0.0f, 1.0f, 0.0f};
                
                for (int i = 1; i < *tPts; i++)
                {
                    drawLine(AppState->rawPoints[i - 1], AppState->rawPoints[i], 2.0f, something, AppState);
                }
                if (*tPts == 0 || (*tPts > 0 && AppState->mousePos.x != AppState->rawPoints[*tPts - 1].x))
                {
                    
                    if (*tPts == 0)
                    {
                        AppState->bezierHandler = {};
                    }
                    
                    AppState->rawPoints[*tPts] = AppState->mousePos;
                    
                    isNewPoint = true;
                    
                    *tPts += 1;
                    
                    //TODO:: clean up this was too hard so i gave up dealing with angles is always stupid
                    
                    //NOTE:: if you click a word and hit cntrl+shift L you can change the name of all the variables of that same name
                    if (*tPts > 1)
                    {
                        float dx = AppState->rawPoints[*tPts - 1].x - AppState->rawPoints[*tPts - 2].x;
                        
                        float dy = AppState->rawPoints[*tPts - 1].y - AppState->rawPoints[*tPts - 2].y;
                        //trace("old = %f,new = %f, then the new - 0ld is %f  \n", AppState->PenMoveAngle*180 /M_PI, atan2f(dy, dx)*180/M_PI, -AppState->PenMoveAngle * 180 / M_PI + atan2f(dy, dx) * 180 / M_PI);
                        //	OutputDebugStringA(message);
                        if (atan2f(dy, dx) > AppState->PenMoveAngle)
                        {
                            
                            AppState->posAnglecnt += -AppState->PenMoveAngle * 180 / M_PI + atan2f(dy, dx) * 180 / M_PI;
                        }
                        AppState->PenMoveAngle = atan2f(dy, dx);
                    }
                    
                    __int8 cGrn = 9;
                    
                    //TODO:: DElete this
                    if (*tPts % cGrn == 0)
                    {
                        isAnglePositive = (AppState->posAnglecnt / cGrn >= 0);
                        
                        AppState->posAnglecnt = 0;
                        // I dont have to check for 0 becuase it cant be zero in this if block
                        
                        //I dont actually  this the only info i  is if its positive or negative
                        
                        //I think the only other thing is to see if its going positive in the x or negative in the x all that determines if you  a new point
                        
                        /*	if (isAnglePositive)
                        {
                        OutputDebugStringA("positive \n");
                        } else
                        {
                        OutputDebugStringA("negative\n");
                        }*/
                    }
                }
            }
            
            //computing intersection seems potentially expensive so do your best to compute intersection earlier, I dont know how that data or how often it will be used so id like to program it flat so i can rearrange it later
            
            // I dunno this is temp using rawpoints like that may accidently work and thatd be bad
            //
            if (AppState->PenPressure >= 0 && *tPts > 1 && AppState->mode == Drawing)
            {
                
                int cfm = AppState->currFrame;
                v2 *rwpts = AppState->rawPoints;
                // I think this should be fine for now, but in the future or later i want this in workingFrames
                unsigned int *nOb = &AppState->frames[AppState->currFrame -1];
                //this seems like the initializatio
                if (*tPts == 2 && isNewPoint)
                {
                    // this isnt a good place to put this but it works for temp stuf
                    
                    *nOb += 1;
                    // this clearly garbage
                    if (*nOb == 2)
                    {
                        *nOb;
                    }
                    v2 *controlPts = AppState->bezierCurves[cfm][*nOb - 1].controlPts;
                    controlPts[0] = AppState->rawPoints[0];
                    controlPts[1] = AppState->rawPoints[*tPts - 1];
                }
                
                //make sure cGrn is odd otherwise it wont work... i think
                
                // this should just output a change, and when that change is output i should uhh tell it to make a point, its coarse grain and feeble but should do a fairly shitty job so its good,
                
                v2 *bezierPts = AppState->bezierCurves[cfm][*nOb - 1].bezierPts;
                v2 *controlPts = AppState->bezierCurves[cfm][*nOb - 1].controlPts;
                
                // you'll have to increment this in the drawing where it sees you have more than two turns
                
                // TODO: this will have to move into the initialization since it will also be moved
                
                unsigned int *numOfBezPts = &AppState->bezierCurves[cfm][*nOb - 1].numOfBPts;
                
                
                
                //TODO::just incase i didnt put a note to get rid of all the static int that should definitely happen
                static int timeTicker = 0;
                
                timeTicker++;
                
                if (*tPts == 2)
                {
                    
                    *numOfBezPts = 2;
                }else{
                    
                    if(isNewPoint)
                    {
                        AppState->bezierHandler.start = *tPts -2;
                        *numOfBezPts+= 1;
                        
                        
                        controlPts[(*numOfBezPts - 1)*2 -1] = AppState->rawPoints[AppState->bezierHandler.start];
                        controlPts[(*numOfBezPts - 1)*2] = AppState->rawPoints[*tPts - 1];
                        
                    }
                }
                
                // this will always be something I dont know if this is true though
                //TODO:: I can probably get rid of it but its low concern
                bezierPts[*numOfBezPts - 2] = AppState->rawPoints[AppState->bezierHandler.start];
                bezierPts[*numOfBezPts - 1] = AppState->rawPoints[*tPts - 1];
                
                
                AppState->bezierCurves[cfm][*nOb - 1].rawPts = rwpts;
                
                //TODO:: Make sure you look for all the static ints and kill em
                
                
                
                // i think this is the way that it is done i dont know what im supposed to be doing but i thought
                
                //where in the world is the a
                // so its the angles of the leading or trailing bezier points that determine weather you should delete and combine, though honestly it doesnt matter its just a cleanliness thing
                
                // this probably should only be done when, well it really doesnt matter but i dont  to do this every frame
                
                //TODO::WORK ON
                start = clock();
                
                if (isNewPoint)
                    DrawBez(&AppState->bezierCurves[cfm][*nOb - 1], tPts, &AppState->bezierHandler);
                
                
                end = clock();
                double total_t = (double)(end - start)/CLOCKS_PER_SEC;
                trace("\n\n\nExit program time = %f \n\n\n\n\n", total_t);
                
            }
            
            if (AppState->PenPressure == 0 && *tPts > 0 && AppState->mode == Drawing)
            
            {
                
                
                
                
                // TODO: if your gonna save the point info you're gonna do it here
                //TODO:: WORK ON TODAY I changed my mind about the fill right there, Im gonna switch it up and see if i cant do a scanline and have it here.. hmm
                
                
                if (AppState->frames[AppState->currFrame -1] > 1)
                {
                    // go figure it actually goes in here 
                    
                    
                    
                    
                    //ok this is where we gotta start looking for our culprit
                    // we gotta find out wher
                    
                    // oh poops this code was made with certain assumptions all it does is find the intersections and wherever there is an intersetion those parts so to speak become live
                    
                    // so all i would need to do to get this generalized is find he intersection pairs and make sure they form a loop
                    // if it loops it should be fine so lets just generalize it first through finding the pairs its a bit of a maze searching too though that probaby wont be necessary since the pair will always be given to us, yeah this may be too general, lets just we'll always be given the pair and solve for it that way
                    
                    // we should be able to able to just do the do im just trying to remember if it can process whole beziers 
                    
                    
                    // most of this code underneath is rendered useless after thi
                    int cfm = AppState->currFrame;
                    
                    unsigned int *splits[2];
                    //testCode::imaginaryFill(AppState);
                    
                    //AppState->shapeBoxHandler[AppState->numOfEdgeBoxes].curve = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes];
                    
                    //splits[0] = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes].size;
                    
                    
                    
                    bezRef *boneHead;
                    
                    bezRef *boneHead2 = AppState->shapeBoxHandler[AppState->numOfEdgeBoxes];
                    
                    splits[1] = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes].size;
                    
                    AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1].edges = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes];
                    
                    AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1].edges->edges = AppState->shapeBoxHandler[AppState->numOfEdgeBoxes];
                    
                    AppState->EdgeBoxes[AppState->numOfEdgeBoxes].curve = &AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1];
                    
                    AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1].edges = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes];
                    
                    AppState->numOfEdgeBoxes +=1;
                    // it should always be two all this thing should be doing is ordering what goes where 
                    unsigned int cols = 0;
                    unsigned int crs = 0;
                    unsigned int cr = 0;
                    int bcnt;
                    bezRef bCols[10];
                    bezRef bCols2[10];
                    //v2 flts[2][3] = {0};
                    v2 *stuff;
                    
                    
                    //this isnt finished not by a long shot it has to check i vs i2 im gonna get rid of the splits before that though actually i dint have to i dont automatically look for closed shapes i figure out what i wanna fill first so this is fine
                    
                    // umm before we wanna check which ones even intersect to begin with and we'd do that here
                    
                    for(int bi = 0; bi < AppState->frames[AppState->currFrame -1] - 1; bi++){
                        
                        //TODO::REPLACE SPLIT BEZIER its waste hmm this is wrong, well it doesnt matter its a pointless algorithm 
                        // well wasted two days should have read this.. note to self, learn to read
                        
                        if(AppState->bezierCurves[cfm][bi].edges == NULL){
                            
                            splits[0] =&AppState->EdgeBoxes[AppState->numOfEdgeBoxes].size;
                            AppState->bezierCurves[cfm][bi].edges = &AppState->EdgeBoxes[AppState->numOfEdgeBoxes];
                            
                            boneHead = AppState->shapeBoxHandler[AppState->numOfEdgeBoxes];
                            
                            AppState->bezierCurves[cfm][bi].edges->edges = AppState->shapeBoxHandler[AppState->numOfEdgeBoxes];
                            
                            AppState->bezierCurves[cfm][bi].edges->curve = &AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1];
                            
                            
                            newsplitBezier(&AppState->bezierCurves[cfm][bi], splits[0], boneHead);
                            
                            AppState->numOfEdgeBoxes+=1;
                            
                        }else{
                            splits[0] = &AppState->bezierCurves[cfm][bi].edges->size;
                            boneHead = AppState->bezierCurves[cfm][bi].edges->edges;
                        }
                        if(*splits[1] == 0){
                            newsplitBezier(&AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1], splits[1], boneHead2);
                        }
                        int nPts = AppState->bezierCurves[cfm][bi].numOfBPts;
                        //TODO:: point aggregation, if there are subsequent points all less than a pixel apart count them as a single pixel
                        
                        //bezRef colbRef[10];
                        //splits *=2;
                        unsigned int i2 = 0;
                        
                        // ok im just gonna test the formula real quick
                        //v2 g = testCode::lineIntersect(V2(0.0f, 0.0f),V2(3.0f, 3.0f),
                        //V2(3.0f, 0.0f),
                        //V2(0.0f, 3.0f);
                        
                        // after this point i think this could be made a lot easier
                        unsigned int bez1s = *splits[0];
                        unsigned int bez2s = *splits[1];
                        //TODO:: JUST GET RID OF THE CONTROL POINTS I DONT KNOW WHY I EVEN PUT THEM IN THERE THEY SHOULD ACTUALLY DO 
                        for (int i = 0; i < bez1s; i++)
                        {
                            for(int i2 = 0; i2 < bez2s; i2++){
                                v2 v = testCode::lineIntersect(boneHead[i],boneHead2[i2]);
                                
                                if(v.x <= 1.0f && v.x >= 0.0f && v.y <= 1.0f && v.y >= 0.0f){
                                    
                                    bCols[crs] = boneHead[i];
                                    
                                    v2 midPt = v.y*(boneHead[i].bezPts[1] - boneHead[i].bezPts[0])+ boneHead[i].bezPts[0];
                                    chkBox[cr].xl = midPt.x;
                                    chkBox[cr].xh = midPt.x+5.0f;
                                    chkBox[cr].yl = midPt.y;
                                    chkBox[cr].yh = midPt.y+5.0f;
                                    //ix->pt = boneHead2[i2].bezPts[0] + delta;
                                    
                                    float dt = (boneHead[i].t2 - boneHead[i].t1)*v.x;
                                    
                                    bezRef *b1 =&boneHead[*splits[0]];
                                    
                                    // we need to stop this from being a bezpoint and i think
                                    // itll be fine, I only need the splits 
                                    b1->bezPts[0] = boneHead[i].bezPts[0];
                                    b1->bezPts[1] = midPt;
                                    b1->cntrlPts[0] = boneHead[i].bezPts[0];
                                    b1->cntrlPts[1] = midPt;
                                    
                                    
                                    if (b1->bezPts[0].x < b1->bezPts[1].x)
                                    { b1->xl = b1->bezPts[0].x; b1->xh = b1->bezPts[1].x;}
                                    else
                                    {b1->xh = b1->bezPts[0].x;	b1->xl = b1->bezPts[1].x;}
                                    if (b1->bezPts[0].y < b1->bezPts[1].y)
                                    {b1->yl = b1->bezPts[0].y; b1->yh = b1->bezPts[1].y; }
                                    else
                                    {b1->yh = b1->bezPts[0].y; b1->yl = b1->bezPts[1].y;}
                                    
                                    b1->t1 = boneHead[i].t1;
                                    b1->t2 =  boneHead[i].t1 + (boneHead[i].t2 - boneHead[i].t1)*v.x;
                                    
                                    b1->bCurve = &AppState->bezierCurves[cfm][bi];
                                    
                                    bezRef *b2 = &boneHead[*splits[0]+1];
                                    
                                    
                                    b2->bezPts[0] = midPt;
                                    b2->bezPts[1] = boneHead[i].bezPts[1];
                                    b2->cntrlPts[0] = midPt;
                                    b2->cntrlPts[1] = boneHead[i].bezPts[1];
                                    
                                    
                                    if (b2->bezPts[0].x < b2->bezPts[1].x)
                                    { b2->xl = b2->bezPts[0].x; b2->xh = b2->bezPts[1].x;}
                                    else
                                    {b2->xh = b2->bezPts[0].x;	b2->xl = b2->bezPts[1].x;}
                                    if (b2->bezPts[0].y < b2->bezPts[1].y)
                                    {b2->yl = b2->bezPts[0].y; b2->yh = b2->bezPts[1].y; }
                                    else
                                    {b2->yh = b2->bezPts[0].y; b2->yl = b2->bezPts[1].y;}
                                    
                                    
                                    b2->t1 = boneHead[i].t1 + (boneHead[i].t2 - boneHead[i].t1)*v.x;
                                    b2->t2 = boneHead[i].t2;
                                    
                                    b2->bCurve = &AppState->bezierCurves[cfm][bi];
                                    
                                    
                                    *splits[0] +=2;
                                    
                                    
                                    
                                    // ok so this is the intersection
                                    unsigned int crsI;
                                    {
                                        int cfm = AppState->currFrame;
                                        unsigned int *iCnt = &AppState->bezierCurves[cfm][bi].ixCount;
                                        crsI = AppState->bezierCurves[cfm][bi].ixCount;
                                        bool swapped = false;
                                        intersection ix = {};
                                        intersection swapIx;
                                        
                                        ix.bCurve = &AppState->bezierCurves[cfm][bi];
                                        // umm the b_i is a pointless thing now, it would be a pain in the ass to maintain and i dont think it serves any value
                                        v2 delta = v.x*(boneHead[i].bezPts[1] - boneHead[i].bezPts[0]);
                                        ix.pt = boneHead[i].bezPts[0] + delta;
                                        ix.t = boneHead[i].t1 + (boneHead[i].t2 - boneHead[i].t1)*v.x;
                                        
                                        ix.b_t = *iCnt;
                                        int i = 0;
                                        float oldT = -42.0f;
                                        if(*iCnt > 0)
                                            oldT =  AppState->bezierCurves[cfm][bi].ix[*iCnt-1].t;
                                        if(ix.t< oldT){
                                            swapIx = AppState->bezierCurves[cfm][bi].ix[*iCnt - i -1];
                                            AppState->bezierCurves[cfm][bi].ix[*iCnt - i - 1] = ix;
                                            AppState->bezierCurves[cfm][bi].ix[*iCnt - i] = swapIx;
                                            //AppState->bezierCurves[bi].ix[*iCnt - i].pair->pair = &AppState->bezierCurves[bi].ix[*iCnt - i - 1];
                                            AppState->bezierCurves[cfm][bi].ix[*iCnt - i - 1].b_t -=1;
                                            AppState->bezierCurves[cfm][bi].ix[*iCnt - i].b_t += 1;
                                            crsI -=1;
                                        }else{
                                            AppState->bezierCurves[cfm][bi].ix[*iCnt - i]  = ix;
                                        }
                                        
                                        *iCnt+=1;
                                        
                                        
                                    }
                                    // and here i would just replace the two bez refs and move on and calculate the t
                                    
                                    
                                    bCols2[crs] = boneHead2[i2];
                                    
                                    midPt= v.x*(boneHead2[i2].bezPts[1] - boneHead2[i2].bezPts[0])+ boneHead2[i2].bezPts[0];
                                    
                                    chkBox[cr+1].xl = midPt.x;
                                    chkBox[cr+1].xh = midPt.x+5.0f;
                                    chkBox[cr+1].yl = midPt.y;
                                    chkBox[cr+1].yh = midPt.y+5.0f;
                                    
                                    //
                                    dt = (boneHead2[i2].t2 - boneHead2[i2].t1)*v.y;
                                    
                                    
                                    b1 =&boneHead2[*splits[1]];
                                    
                                    
                                    b1->bezPts[0] = boneHead2[i2].bezPts[0];
                                    b1->bezPts[1] = midPt;
                                    b1->cntrlPts[0] = boneHead2[i2].bezPts[0];
                                    b1->cntrlPts[1] = midPt;
                                    
                                    
                                    if (b1->bezPts[0].x < b1->bezPts[1].x)
                                    { b1->xl = b1->bezPts[0].x; b1->xh = b1->bezPts[1].x;}
                                    else
                                    {b1->xh = b1->bezPts[0].x;	b1->xl = b1->bezPts[1].x;}
                                    if (b1->bezPts[0].y < b1->bezPts[1].y)
                                    {b1->yl = b1->bezPts[0].y; b1->yh = b1->bezPts[1].y; }
                                    else
                                    {b1->yh = b1->bezPts[0].y; b1->yl = b1->bezPts[1].y;}
                                    
                                    b1->t1 = boneHead2[i2].t1;
                                    
                                    b1->t2 = boneHead2[i2].t1 + (boneHead2[i2].t2 - boneHead2[i2].t1)*v.y;
                                    
                                    
                                    b2 = &boneHead2[*splits[1]+1];
                                    
                                    
                                    b2->bezPts[0] = midPt;
                                    b2->bezPts[1] = boneHead2[i2].bezPts[1];
                                    b2->cntrlPts[0] = midPt;
                                    b2->cntrlPts[1] = boneHead2[i2].bezPts[1];
                                    
                                    
                                    if (b2->bezPts[0].x < b2->bezPts[1].x)
                                    { b2->xl = b2->bezPts[0].x; b2->xh = b2->bezPts[1].x;}
                                    else
                                    {b2->xh = b2->bezPts[0].x;	b2->xl = b2->bezPts[1].x;}
                                    if (b2->bezPts[0].y < b2->bezPts[1].y)
                                    {b2->yl = b2->bezPts[0].y; b2->yh = b2->bezPts[1].y; }
                                    else
                                    {b2->yh = b2->bezPts[0].y; b2->yl = b2->bezPts[1].y;}
                                    
                                    
                                    b2->t1 = 
                                        boneHead2[i2].t1 + (boneHead2[i2].t2 - boneHead2[i2].t1)*v.y;
                                    int cfm = AppState->currFrame;
                                    
                                    b2->t2 = boneHead2[i2].t2;
                                    unsigned int end = AppState->frames[AppState->currFrame -1] -1;
                                    
                                    b1->bCurve = &AppState->bezierCurves[cfm][end];
                                    b2->bCurve = &AppState->bezierCurves[cfm][end];
                                    
                                    *splits[1] +=2;
                                    
                                    unsigned int *iCnt = &AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1].ixCount;
                                    intersection ix  = {}; 
                                    intersection swapIx; 
                                    
                                    ix.b_t = *iCnt;
                                    ix.bCurve = &AppState->bezierCurves[cfm][end];
                                    // umm the b_i is a pointless thing now, it would be a pain in the ass to maintain and i dont think it serves any value
                                    v2 delta = v.y*(boneHead2[i2].bezPts[1] - boneHead2[i2].bezPts[0]);
                                    ix.pt = boneHead2[i2].bezPts[0] + delta;
                                    ix.t = boneHead2[i2].t1 + dt;
                                    
                                    
                                    unsigned int crsI2 =*iCnt; 
                                    
                                    
                                    AppState->bezierCurves[cfm][bi].ix[crsI].pair = &AppState->bezierCurves[cfm][end].ix[*iCnt-1];
                                    
                                    ix.pair = &AppState->bezierCurves[cfm][bi].ix[crsI];
                                    
                                    //TODO::Im going to have to come back to this later but for now I wanna stay so far away 
                                    
                                    
                                    int i = 0;
                                    float oldT = -42.0f;
                                    if(*iCnt > 0)
                                        oldT =  AppState->bezierCurves[cfm][end].ix[*iCnt-1].t;
                                    if(ix.t< oldT){
                                        swapIx = AppState->bezierCurves[cfm][end].ix[*iCnt - i -1];
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i - 1] = ix;
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i] = swapIx;
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i].pair->pair = &AppState->bezierCurves[cfm][end].ix[*iCnt - i];
                                        
                                        
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i - 1].b_t -=1;
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i].b_t += 1;
                                        crsI2 -=1;
                                    }else{
                                        AppState->bezierCurves[cfm][end].ix[*iCnt - i]  = ix;
                                        AppState->bezierCurves[cfm][bi].ix[crsI].pair = &AppState->bezierCurves[cfm][end].ix[crsI2];
                                        
                                        AppState->bezierCurves[cfm][end].ix[crsI2].pair = &AppState->bezierCurves[cfm][bi].ix[crsI];
                                        
                                        
                                    }
                                    
                                    
                                    
                                    boneHead2[i2] = {};
                                    boneHead[i] = {};
                                    // hopefully this wasnt supposed to do anything
                                    &AppState->bezierCurves[cfm][AppState->frames[AppState->currFrame -1] -1].ix[*iCnt];
                                    *iCnt+=1;
                                    
                                    crs++;
                                    cr+=2;
                                }
                            }
                        }
                        
                        
                        
                        
                        
                        //TODO::TOO SIMPLE SORT IT ALSO SORTS ALL OF THEM
#if 0
                        int end_i = AppState->frames[AppState->currFrame -1];
                        for(int i = 0; i < end_i; i++){
                            bezierCurve *bc = &AppState->bezierCurves[i];
                            intersection swap;
                            int vcnt = bc->ixCount;
                            for (int c = 0 ; c < vcnt - 1; c++)
                            {
                                for (int d = 0 ; d < vcnt - c - 1; d++)
                                {
                                    if (bc->ix[d].t > bc->ix[d+1].t) /* For decreasing order use < */
                                    {
                                        swap       = bc->ix[d];
                                        bc->ix[d] =  bc->ix[d+1];
                                        
                                        bc->ix[d+1] = swap;
                                    }
                                }
                            }
                        }
                        
                        // ok were gonna do a bunch of code refactoring and shit so its gonna get a bit messy but the alternative is understanding code thats useless
                        if(crs > 0)
                        {// what the fuck is colts v2 colts[15];
                            //bcnt = splits;
                            
                            
                            for(int i = 0, b = 0; i < crs;b++, i++){
                                
                                
                                //long time no see sailor fs
                                // the v2 it gets back isnt a v2 its just an array of floats first being x next being y
                                
                                stuff= testCode::binarySIntersection(&bCols[i],&bCols2[i]);
                                // create the gnarley box thing
                                //[b];
                                memcpy(flts[b], stuff, 3 * sizeof(v2));
                                
                                
                                
                                
                                
                            }
                            
                            
                            
                        }
#endif
                    }
                    // so all it does on draw is here simply setting up and dividing the boxes on intersections, and setting up the t1 and t2
                    
                    //Assert(crs == 2);
                    //int b = -1;
                    // weree just   g dslfakjfs d;a
                    for(int i = 0, b = 0; i < crs; b++, i++){
                        
                        // the only difference here is we are going to assume three different lines, and will work with 2 
                        //long time no see sailor fs
                        // the v2 it gets back isnt a v2 its just an array of floats first being x next being y
                        
                        // create the gnarley box thing
                        //[b];
                        
                        
                        
                        
                        
                        // this is where we get the point as well i need to see what its doing and take out
                        
                        // this assumes they are being both probably being drawn left to right which
                        
                        // means TODO:: actually make this work for reeals
                        // i dont know if i should take this out of test yet, let me test it first then i can take it out of test
                        
                        // you might step in here and check it.. maybe.. but it should be splitting make sure thats doing that before you go into all this,
                        
                        //#if 0
                        
                        // so itd be instead 
                        
                        // and 
                        // i could determine the t1 and t2 but I dont think Im gonna get anything from it, so if I need it its here
                        
                        
                        // ok here is where we do the thing
                        
                        
                        //p1 = flts[b][2];
                        //testCode::pointFromBez(flts[b][0].y, &bCols2[i].bCurve);
                        
                        // we need to give it just the xl xh and yh yl nonesense
                        
                        
                        //boneHead2[bcnt] = brf2;
                        // i dont know why this isnt bcnt
                        //boneHead[bcnt+1] = brf;
                        
                        
                        
                        
                        
                    }
                    
                    
                    
                    // are these the bounds??!?! this is why i should do these all in one day oye veh  the naming here is super 
                    
                    //now we wanna 
                    
#if 0
                    
                    static bool randomStatusTemp = false;
                    
                    if(!randomStatusTemp){
                        
                        EdgeBoxes b1 = *AppState->bezierCurves[0].edges;
                        
                        
                        EdgeBoxes b2 = *AppState->bezierCurves[1].edges;
                        
                        
                        Fmixer(AppState->bezierCurves[0].ix[0].t, AppState->bezierCurves[0].ix[1].t,b1, AppState);
                        
                        Fmixer(AppState->bezierCurves[1].ix[0].t, AppState->bezierCurves[1].ix[1].t,b2, AppState);
                        convienceFillFunction(AppState);
                        randomStatusTemp = true;
                    }
                    
                    
                    float btL, btH, bt2L , bt2H;
                    unsigned int fcnt = 0;
                    
                    bezRef *fmix = (bezRef *)calloc(7000,sizeof(bezRef));
                    
                    // this orders the lowest t to the highest t using the x and y's its dumb because it makes it very confusing and Im never gonna do that again no matter how lazy i feel 
                    // id just need the intersection points, in order t1, and t2 for each individual to be added to the fmix
                    
                    // this would be in a for lop 
                    v2 flts[2];
                    
                    unsigned int end = AppState->frames[AppState->currFrame -1] -1;
                    AppState->bezierCurves[end];
                    
                    // it would be the two on the array that it gets in sequence, itd be this pair from the bez this pair from this bez etc etc
                    // so remember in the final wouldnt do this, itd be a function and itd say i want the boxes from t1 to t2 
                    
                    flts[0].x = AppState->bezierCurves[0].ix[0].t;
                    flts[1].x = AppState->bezierCurves[0].ix[1].t;
                    
                    flts[0].y = AppState->bezierCurves[end].ix[0].t;
                    flts[1].y = AppState->bezierCurves[end].ix[1].t;
                    
                    
                    if (flts[0].x <flts[1].x)
                    { btL = flts[0].x; btH = flts[1].x;}
                    else
                    {btL = flts[1].x; btH = flts[0].x;}
                    if (flts[0].y <flts[1].y)
                    { bt2L = flts[0].y; bt2H = flts[1].y;}
                    else
                    {bt2L = flts[1].y; bt2H = flts[0].y;}
                    
                    
                    for (int i = 0; i < *splits[1]; i++)
                    {
                        if (boneHead2[i].t1 >= bt2L && boneHead2[i].t2 <= bt2H)
                        {
                            fmix[fcnt] = boneHead2[i];
                            fcnt++;
                        }
                    }
                    
                    
                    
                    for (int i = 0; i < splits[0]; i++)
                    {
                        if (boneHead[i].t1 >= btL && boneHead[i].t2 <= btH)
                        {
                            fmix[fcnt] = boneHead[i];
                            fcnt++;
                        }
                    }
                    
                    float lYh = fmix[0].yh;
                    // and then we're just gonna figure out the lowest yh
                    for (int i = 0; i < fcnt; i++)
                    {
                        if(fmix[i].yh < lYh){
                            lYh = fmix[i].yh;
                        }
                    }
                    
                    // then all you gotta do is call scanline fill 
                    // ive totally forgotten what im supposed to to do with this box, i think i get it where it startts? UGGGH i wish i didnt comment out the first thing i did pOOOOOOOOPpss
                    
                    bezRef box = {};
                    box.yl = box.yh; // it may be lYH.. i dunno 
                    // i think i may had to call adjust box first or something but my brain hurts and Im sure you can figure it out later I need a well earned rest for getting to the goal of the week I hate vscode 
                    // why did they keep taking pointers man
                    
                    bezRef *boxes =fmix;
                    
                    for (unsigned int i = 0; i < fcnt; i++)
                    {
                        
                        v4 weirdColor = {0.5f, i / 4.0f, i / 4.0f, 1.0f};
                        float boxsize = boxes[i].xh - boxes[i].xl+ .000000001;
                        float yboxsize = boxes[i].yh - boxes[i].yl+.0000000001;
                        float t = boxes[i].xl + boxsize / 2;
                        float d = boxes[i].yl + yboxsize / 2;
                        paintRectangle(t, d, boxsize, weirdColor, AppState, yboxsize);
                        
                        //tempShapeBoxesOutline = *shpeBoxes;
                    }
                    
                    
                    
                    for(unsigned int i = 0; i<fillQCnt; i+=2)
                    {
                        if(fillqueX[i] > fillqueX[i+1]){
                            float swap = fillqueX[i];
                            fillqueX[i] = fillqueX[i+1];
                            fillqueX[i+1] = swap;
                        }
                    }
                    
                    
                    for(unsigned int i = 0; i<fillQCnt; i+=2)
                    {
                        if(fillqueY[i] > fillqueY[i+1]){
                            float swap = fillqueY[i];
                            fillqueY[i] = fillqueY[i+1];
                            fillqueY[i+1] = swap;
                        }
                    }
                    
#if 0
                    for(unsigned int i = 0; i<fillQCnt; i+=2)
                    {
                        fmix[i].xl= fillqueX[i];
                        fmix[i].xh= fillqueX[i+1];
                        fmix[i].yl= fillqueY[i];
                        fmix[i].yh= fillqueY[i+1];
                        
                    } 
#endif
                    testCode::adjustBox(&box, fmix,&fcnt, AppState, false);
                    
                    //createFitBoxes(box, fmix,fcnt, AppState);
                    // }
                    
                    for(int i = 0; i < 45; i++){
                        
                        //createFitBoxes(box, fmix,fcnt, AppState);
                        
                        box.yl = box.yh;
                        testCode::adjustBox(&box, fmix,&fcnt, AppState, true);
                        
                    }
                    
#endif
                }
                // TODO:: this is where we made the test code for the filling, I have to add multiple intersections and multiple splits aswell see how that works with more than just one bezier going through, however you feel like testing it man
                static bool testplayed = false;
                int cfm = AppState->currFrame;
                if (AppState->frames[AppState->currFrame -1] == 1 && !testplayed)
                { // remember to check to see if the thing is clamped
                    testplayed = true;
                    bezierCurve b1 = AppState->bezierCurves[cfm][0];
                    
                    AppState->bezierCurves[0];  
                    numOfShapeBoxes = 16;
                    //splitBezier(&br1, 16,  shap dsf eBoxes);
                    //splitBezier(&AppState->bezierCurves[0], 16, AppState->shapeBoxHandler);
                    glbDim.xl = AppState->bezierCurves[cfm][0].bezierPts[0].x;
                    glbDim.xh = AppState->bezierCurves[cfm][0].bezierPts[1].x;
                    
                    // ok i want the shape boxes but i want to put the the shape boxes into the bezier itself.. or maybe not that may be a bad idea but itll work for a while till i decide to optimize it, i think optimizing early will make it harder to program so yeah stuff
                    
                    // bezRef box = {};
                    // testCode::adjustBox(&box, AppState->shapeBoxHandler,&numOfShapeBoxes, AppState);
                    
                    // createFitBoxes(box,AppState->shapeBoxHandler,&numOfShapeBoxes,AppState);
                    
                    
                    // for (int i = 0; i < 7; i++)
                    // {
                    
                    
                    // 	box.yl = box.yh;
                    // 	testCode::adjustBox(&box, AppState->shapeBoxHandler, &numOfShapeBoxes, AppState, true);
                    
                    // 	createFitBoxes(box, AppState->shapeBoxHandler, &numOfShapeBoxes, AppState);
                    // }
                    
                    //	AppState->boxsize = 15.0f;
                    //floodFill(300.0f, 240.0f, {}, {256.0f, 256.0f, 0.0f}, &numOfShapeBoxes, AppState);
                }
                
                *tPts = 0;
                AppState->bezierHandler = {};
            }
            
            // ok where do i think i am i think i am at a point where the damn thing should work after a bit of work, with testing and iterating i can get it drawing probably before the end of the day, which is why i like working with errors // its stupidly unoptimized but ive layed tout the data in the easiest way to poke at it and try and change what is going on... so
            // geting the damn thing fixed and working i think i can get that by the days end.. optimistically even with the fancy corners, which arent even necessary i have some ideas round that ... okay
            
            // it should definitey draw with you, because surprises are dumb, makes it much easier not only to draw but also debug
            // ok so you have two turns per bezier pts, you can and have the option of creating a new point at one turn if you feel its neccesary but it
            // should be fine
            
            // I think im in a lazy mood thats alright i wanna do
            // a two pronged attack on this lets look at the microarchetecture course
            // and this simultaneously this is mostly set i think i just have to compile it and it will give me some problems that i  to solve
            // so cutting and filling are two biguns i  to solve to get a testible showable model
            
            // but yeah those are the two biggest of hurdles i think, cutting isnt bad but filling maybe difficult to visualize, and maybe hard to optimize.. and since ill be filling 100's if not thousands at the same time it may be a problem
            
            // TODO:: tell me if this is DUMB, because it smells like its dumb
            // this can stay here
            v2 curve[40000];
            
            // okay test code
            static float weirdTest = 100.0f;
            weirdTest++;
            //eventually will change it from all the beziers to just the beziers that  update and just put them at the end of some que or whatever doesnt matter
            size_t f =0;// AppState->currFrame -1;
            //TODO::rename frames indicates the number of beziers for now
            
            // so your gonna replace number of beziers with this
            //AppState->frames[0] = AppState->numOfBeziers;
            int nOb = AppState->frames[AppState->currFrame -1];
            int cfm = AppState->currFrame;
            for (f; f < nOb; f++)
            {
                
                v2 *bezierPts = AppState->bezierCurves[cfm][f].bezierPts;
                v2 *controlPts = AppState->bezierCurves[cfm][f].controlPts;
                unsigned int *numOfBezPts = &AppState->bezierCurves[cfm][f].numOfBPts;
                bool isBeg = AppState->bezierCurves[cfm][f].isBeg;
                
                bool isEnd = AppState->bezierCurves[cfm][f].isEnd;
                // this wont be for a while since i dont  direct beziers for now
                //
                
                // hmm if the thing hasnt changed i dont have to redraw thae damn thing
                // but i can honestly think about that later, but good to know
                // will definitely become usefull when it comes to optimize things
                int tu = -1;
                unsigned int ii;
                // we're probably gonna do another for loop here for all the bezier
                // thats crazy so it goes from 0 to one
                //TODO::FIGURE OUT WHY I DO THIS TWICE
                
                
                // realistically id have an array of these id imagine of which cuts which, but two is the max since you have three cuts otherwise your doing something more interesting
                float ixT = AppState->bezierCurves[cfm][f].ix[0].t;
                __int8 bi = AppState->bezierCurves[cfm][f].ix[0].b_i;
                float feta = AppState->bezierCurves[cfm][f].ix[0].crsAngle;
                
                // for testing 
                feta = 0.785398f;
                // hmm i just noticed i dont know actually the angle the feta is going to necesarily be coming in its not normalized or whatever.. umm we'll just wait for it to do something its not to complicated were just gonna ignore it and fake a circumstace
                
                // so what the fuck is going on 
                
                float tsize = 5.0f;
                
                v2 pt[4];
                if(f != 0 && AppState->bezierCurves[cfm][f].ix[0].isCutting){
                    tsize = 8.0f;
                    
                    
                    v2 v = AppState->bezierCurves[cfm][f].ix[0].pt;
                    
                    // put these in a loop
                    // the v stuff is whats wrong
                    pt[0].x = v.x+cosf(feta)*tsize;
                    pt[0].y = v.y+sinf(feta)*tsize;
                    pt[1].x = v.x+cosf(feta)*(-tsize);
                    pt[1].y = v.y+sinf(feta)*(-tsize);
                    
                    
                    
                }
                // not sure what to do on this one space seems to be an issue
                // its honestly probably a lot more than this
                // umm dont go nuts ill probably send a 
                float alteredBez[40000][3];
                int aCt = -1;
                alteredBez[0][0] = NAN;
                for (size_t i = 0; i < (size_t)*numOfBezPts - 1; i++)
                {
                    
                    ii = i * 2;
                    for (u = 0; u <= 1; u += _step)
                    {
                        v2 v = {};
                        tu++;
                        v.x = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[i].x + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[ii].x + 3.0f * (1.0f - u) * u * u * controlPts[ii + 1].x + (u * u * u) * bezierPts[i + 1].x;
                        v.y = (1.0f - u) * (1.0f - u) * (1.0f - u) * bezierPts[i].y + 3.0f * (1.0f - u) * (1.0f - u) * u * controlPts[ii].y + 3.0f * (1.0f - u) * u * u * controlPts[ii + 1].y + (u * u * u) * bezierPts[i + 1].y;
                        
                        //ill wanna use my own transformation thingy or i could just get it from the point method i made i dunno yet
                        
                        //lo
                        // what do we have to do now well we have to actually get the coloring working because that failed miserably
                        
                        // this calculates the normal which should ultimately be checked against every possible point 
                        
                        v2 dt = V2(v.x, v.y) - curve[tu-1];
                        
                        //TODO(): KILL tempsize;
                        float a = atan2f(dt.x,dt.y);
                        v2 nPt1; 
                        v2 nPt2;
                        nPt1.x = v.x+cos(a)*tsize;
                        nPt1.y = v.y+sin(a)*tsize;
                        nPt2.x = v.x+cos(a)*(-tsize);
                        nPt2.y = v.y+sin(a)*(-tsize);
                        v2 ix;
                        int lchecks = 1;
                        // i would check through the ix's pts which i would put in the thing, which remember you can shorten this but keep that for later
                        // will be AppState->bezierCurves[cfm][f].ix[i] dirived from points
                        for(int j = 0; j < lchecks; j++){
                            ix = V2((lineIntersect(pt[0], pt[1], v, nPt2)).x,
                                    (lineIntersect(pt[0], pt[1], v, nPt1)).x);
                            
                            // well i can only have 2 cuts and they can absolutely take the same line, and whichever would cut deeper would take precedent, also it could take the top one, and we'd handle for that too, i dont really have to though, since we can just assume thats not the case for now its
                            if(ix.x < 1.0f && ix.x  > -1.0f )
                            {
                                
                                aCt+=1;
                                alteredBez[aCt][0] = tu;
                                alteredBez[aCt][1] = ix.x*tsize;
                                alteredBez[aCt][2] = ix.y*tsize;
                            }
                            // not quite there but closer
                        }
                        
                        //if(bi == i){
                        // and isBroken check
                        //if(ixT >= u && ixT <= (u+_step))
                        //{
                        //}
                        //}
                        // this is what gets fed to the line creator thing?? so if there is a problem itlll show up here
                        curve[tu] = V2(v.x, v.y);
                        
                        v4 clor = {256.0f, 256.0f, 0.0f};
                        
                        drawLine(bezierPts[i], controlPts[ii], 2.0f, clor, AppState);
                        
                        drawLine(bezierPts[i + 1], controlPts[ii + 1], 2.0f, clor, AppState);
                    }
                    
                    // it would be how many tu's we have times, how many curves*beziers
                    v4 color = {1.0f, 0.0f, 1.0f, 0.0f};
                    // putting it inside a array to do this again is dumb 
                    // dont do it 
                    float size = 0;
                    int ends = 12;
                    // it should be something liek ix.i somhing * the divisions curvepoints then inx.pt is the point that you actually kill it.. seriously though past jon, phenominal you really made this easier for me, and just do the other angle minus your angle to get the relative angle of the slice... whhiich you check every preceding l/right and normal lines for an intersection, and wait till you get one, all the relative angle tells you is what direction you should start searching.
                    unsigned int stoptest = 50;
                    int min = 0;
                    // we have to create the fantom intereptpoint
                    v2 Ficept = V2(250.0f, 250.0f);
                    //for (size_t i = 0; i < tu - 1; i++)
                    for (size_t i = 0; i <  tu-1; i++)
                    {
                        // whih should be something like curve[0].x and blah blah shit like that
                        // in other words there is no discernable end in this it has no idea that one bezier ended or not, and it shouldnt all it needs to know is its preceding point in there 
                        // not sure why i have two 
                        ends= 1/5*(curvePoints*(int)(*numOfBezPts)) ;
                        float tgtSize = 5.0f;
						
                        // parently you dont get around the total length of the thing.. luckily i can calculate the the length and have the divs 
                        // so all we have to do is just guess let
                        if(!isBeg){
                            if(i < ends)
                                size+=tsize/ends;
                        }
                        if(!isEnd){
                            if(i > tu - ends)
                                size-=tsize/ends;
                        }
                        
                        v3 vc = V3(NAN,NAN,NAN);
                        if(!isnan(alteredBez[0][0]) && alteredBez[0][0] <= i)
                        {
                            for(int j = min; j <= aCt; j++)
                            {
                                if(alteredBez[j][0] == i)
                                {
                                    // the first point could effectively be a boolean
                                    // its a real waste i 
                                    
                                    
                                    vc = V3(feta,alteredBez[j][2],alteredBez[j][1]);
                                    min = j;
                                    break;
                                }
                                trace("%d",alteredBez[j][1]); 
                            }
                        }
                        // it just steps up 5 steps and steps down 5
                        // i think im going to be like do it normally unless i pass you a pair of points.. as completely unnormal as that is, I think it may just work better though with the straight normal drawline function
                        
                        //TODO::KERNING HERE, we'll do it dumb then we'll do special cases for really tight corners
                        drawLine2(curve[i], curve[i + 1],curve[i + 2],curve[i + 3], size, color, AppState,vc);
                        
                    }
                    // after which i can
                }
            }
            bool someValueToBedeterminedAtAlaterdateIntimesothatICanbetterdoMyjobInordertoknowIfthisValuesToBeUpdated = true;
            if (someValueToBedeterminedAtAlaterdateIntimesothatICanbetterdoMyjobInordertoknowIfthisValuesToBeUpdated)
                return true;
            
            return false;
            
            // this will probably be replaced with a draw lines, formula later which would literally just fill an array with these points
            if (AppState->numOfLines < AppState->lineQue)
            {
                // we draw lines then we
            }
            else
            {
                // then we check the opposite
            }
            
            return false;
        }
    }
}



void Application_Update(Application_State *AppState)
{
    
    AppState->GfxNeedsUpdate = ValueCheck(AppState);
    
    //AppState->vertCount = 360;
    float *Merged = AppState->vertexBuffer;
    float *b = AppState->tvertexBuffer;
    int mSize = AppState->vertCount + AppState->tvertCount;
    int aSize = AppState->vertCount;
    int bSize = AppState->tvertCount;
    
    //TODO::I changed i on the filling it should work but just make sure you test it
    for (int i = (AppState->currFrame -1)*5000, j = aSize; j < mSize && i < bSize; i++, j++)
    {
        Merged[j] = b[i];
    }
    AppState->vertCount = mSize;
    
    
    static bool gfxStart = true;
    
    // seems like we've decided not to draw anymore.. interesting choice
    if(gfxStart)
    {
        Graphics_initTexture();
        gfxStart = false;
    }else
    {
        //Graphics_UpdateTexture();
    }
    
    if (AppState->GfxNeedsUpdate)
    {
        // for now all we'll send down to the graphics update untill we start using the images is the colorbuffer and the pixeldata
        
        // just fix so if i dont have anything in the vertex buffer
        // dont update it oterwise i will get an error
        // its number of triangles, there are 6 floats per ever point and 3 points per ever triangle
        Graphics_update(AppState->vertexBuffer, AppState->vertCount / 18);
        // done know how long num of lines will work but uh yeah for now f yeah
        // hashtag applogic .. teehee, Im hip
    }
    
    // this is like a listener sees what the user is doing does all the internal logic and gets things set up to see if
    // it s to update the graphics, it updates variables, all that sort of good stuff
    // Update
    
    // Rendering
    
    //inbetweeen here we can send all the data about the updating and rendering, like s update, and update speed
    
    // RENDER
    
    Graphics_Render(AppState->vertCount);
    AppState->vertCount = 0;
    AppState->numOfLines = 0;
}
