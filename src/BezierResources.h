#pragma once

//GLOBAL VARIABLES...TODO::should probably delete eventually
bezRef shapeBoxes[1000];
bezRef colRects[100];
unsigned int numOfShapeBoxes;
boxRef glbDim = {};
float G_bezDivision = 1.0f / 10.0f;

// TODO:: get rid of this its just a hack to get the ordering working make a .h someplace maybe
void createFitBoxes(bezRef ctest, bezRef *c2, unsigned int numOfBoxes, Application_State *AppState);


// I made this y width because i am all kinds of stupid 

// its made like this with the weirdness of having height at the end because it assumes a square since i probably modified this thibng
bezRef chkBox[4];
void paintRectangle(float x, float y, float width, v4 color, Application_State *AppState, float height = 0)
{
	if (height == 0)
	{
		height = width;
	}
    
    
	float *vertexbuffer = AppState->tvertexBuffer;
    
	for (int i = 0; i < 6; i++)
	{
		float bx = width / 2;
		float by = height / 2;
        
		switch (i)
		{
            case 0:
            {
                bx *= -1.0f;
                by *= -1.0f;
                break;
            }
            
            case 1:
            {
                bx *= 1.0f;
                by *= 1.0f;
                break;
            }
            case 2:
            {
                bx *= -1.0f;
                by *= 1.0f;
                break;
            }
            case 3:
            {
                bx *= -1.0f;
                by *= -1.0f;
                break;
            }
            case 4:
            {
                bx *= 1.0f;
                by *= -1.0f;
                break;
            }
            case 5:
            {
                bx *= 1.0f;
                by *= 1.0f;
                break;
            }
            
		}
        
		vertexbuffer[AppState->tvertCount] = x + bx;
		AppState->tvertCount += 1;
		vertexbuffer[AppState->tvertCount] = y + by;
		AppState->tvertCount += 1;
        
		vertexbuffer[AppState->tvertCount] = color.x;
		AppState->tvertCount += 1;
		vertexbuffer[AppState->tvertCount] = color.y;
		AppState->tvertCount += 1;
		vertexbuffer[AppState->tvertCount] = color.z;
		AppState->tvertCount += 1;
		vertexbuffer[AppState->tvertCount] = color.w;
		AppState->tvertCount += 1;
        
        
        
	}
    
}

void paintRectangle(bezRef *bx, v4 color, Application_State *AppState)
{
    float width = (bx->xh - bx->xl);
    float height = (bx->yh - bx->yl);
    
    paintRectangle(bx->xl+ width/2, bx->yl+ height/2,width, color,AppState,height);
    
}



namespace testCode
{
    
	// code refactoring so i can hopefully just get real filling working 
	void adjustBox(bezRef *box, bezRef *c2, unsigned int *numOfBoxes,Application_State *AppState, int isBoxSet = false)
	{
        
        
        // either this or createbox then look in there and 
		const int up = 1;
		const int left = 2;
		const int down = 3;
		const int right = 4;
        static int lowest = 0;
		bezRef *ctest = box;
		int vcnt = *numOfBoxes;
        
		bezRef testiBox;
        
        static bool checkbox = false;
        
        if(!isBoxSet){
            
            // this is why i hate coming back to code after a while, you spend the whole time trying to remember what the fuck you were trying to do, oh well.
            
            for (unsigned int i = 0; i < *numOfBoxes; i++)
            {
                if (c2[lowest].yl < c2[i].yl)
                {
                    // it mkes sense but its weird
                    lowest = i;
                }
                
            }
            
            ///box->yh = c2[0].yh;
            int highest = 0;
            for (unsigned int i = 0; i < *numOfBoxes; i++)
            {
                
                if (c2[highest].yh > c2[i].yh)
                {
                    
                    
                    // this 
                    highest = i;
                }
            }
            
            box->yl = c2[highest].yh;
            
            c2[highest] =  c2[*numOfBoxes - 1];
            *numOfBoxes -=1;
            
        }
        
        trace("box yl: %f box yh: %.f", box->yl, box->yh);
        // this has a possibility of not working 
        unsigned int lbox = 0;
        
        // will probably need saving but its fine for now
        int st = false;
        
        
        // im thinking of making all the boxes on one pass for that level
        // that corresponds with the left most
        //this seems to go through the boxes 
        for (unsigned int i = 0; i < *numOfBoxes; i++)
        {
            
            // this wouldnt be col Volumes im not sure where the box yl
            if (box->yl >= c2[i].yl && box->yl<=  c2[i].yh)
            {
                //trace("box yl: %d box yh: %d", box->yl,box->yh );
                if(!st){
                    lbox = i;
                    st = true;
                    continue;
                }
                if(c2[lbox].xh > c2[i].xh){
                    lbox = i;
                }
            }
        }
        
        box->xl = c2[lbox].xh;
        box->yh = c2[lbox].yh;
        // the fuck is this?
        
        
        
        //NOTE:: there is a possible problem when the boxes are staggered and the left most box should always be stricken from consideration thats what were doing, and we can do that in pairs if there is no gap we do not care about that box
        // this may have some unforseen problems i dunno It could be real tough.. we shall see
        
        
        bezRef colVolumes[50];
        int ncnt = 0;
        // okay so in here we need to make sure we get the lower value 
        for (int i = 0; i < *numOfBoxes; i++)
        {
            if (box->yl < c2[i].yh && box->yh >= c2[i].yl)
            {
                colVolumes[ncnt] = c2[i];
                ncnt++;
            }
        }
        
        
        box->yh = colVolumes[0].yh;
        int boyh = -1;
        for (unsigned int i = 1; i < ncnt; i++)
        {
            
            if(colVolumes[i].yh < box->yh)
            {
                boyh = i;
                box->yh = colVolumes[i].yh;
            }
            
        }
        
        vcnt = 0;
        // okay so in here we need to make sure we get the lower value 
        for (int i = 0; i < ncnt; i++)
        {
            if (box->yl < colVolumes[i].yh && box->yh > colVolumes[i].yl)
            {
                colVolumes[vcnt] = colVolumes[i];
                vcnt++;
            }
        }
        
        //Assert(vcnt > 1)
        
#if 0
        bool isInit = false;
        
        // in the final i could and should just be able to grab the final 
        for (unsigned int i = 1; i < vcnt; i++)
        {
            // we only do this because we need to, there is a lot of superfluous work because of this, but its fine for testing 
            // we want the first 
            if(!isInit && colVolumes[i].xl > box->xl){
                box->xh = colVolumes[i].xl;
                isInit = true;
            }else if (colVolumes[i].xl < box->xh && colVolumes[i].xl > box->xl)
            {
                // this sometimes catches the one underneath, so we have to get the highest first before getting into this
                box->xh = colVolumes[i].xl;
            }
        }
#endif
        // so before the line we want to get 
        // i think i only check for the highest yh because its contiguous, the highest yl will also be the highest yh value, except it has the benefit of excluding my current yl, because its yh would be the value above it
        
        
        
        // im gonna quickly sort them from left to right honestly its usually gonna be small shouldnt matter 
        
        // its a quick and dirty bubble sort, usually its sorting two thats the most common case so i may not even have to use a better sorting algorithm since half the time they may already be sorted, or itll be one change anyway
        bezRef swap;
        for (int c = 0 ; c < vcnt - 1; c++)
        {
            for (int d = 0 ; d < vcnt - c - 1; d++)
            {
                if (colVolumes[d].xl > colVolumes[d+1].xl) /* For decreasing order use < */
                {
                    swap       = colVolumes[d];
                    colVolumes[d]   = colVolumes[d+1];
                    colVolumes[d+1] = swap;
                }
            }
        }
        
        
        
        v4 color = {};
        //box->yh = box->yl +1.0f;
        for (unsigned int i = 1; i < vcnt; i+=2)
        {
            box->xl = colVolumes[i-1].xh;
            box->xh = colVolumes[i].xl;
            paintRectangle(box,color,AppState);
            
        }
        
        // maybe i put a const before? no idea but it never should have worked
        // i may have fixed this but the change didnt take.. its happened before 
        // is this an infinite loop???
        //for(int i = 0; i < 1; i++){
        //createFitBoxes(*box,c2,8,AppState);
        //box->yl = box->yh;
        //testCode::adjustBox(box,c2,8,AppState,true);
        //}
        
        int eight = 8;
    }
    
	void oldadjustBox(bezRef *box, bezRef *c2, unsigned int *numOfBoxes,Application_State *AppState, int isBoxSet = false)
	{
        
        
        // either this or createbox then look in there and 
		const int up = 1;
		const int left = 2;
		const int down = 3;
		const int right = 4;
        static int lowest = 0;
		bezRef *ctest = box;
		int vcnt = *numOfBoxes;
        
		bezRef testiBox;
        
        static bool checkbox = false;
        
		// so this is the first step we wanna make sure that its the top box  we find it
        if(!isBoxSet){
            
            
            for (unsigned int i = 0; i < *numOfBoxes; i++)
            {
                if (c2[lowest].yl < c2[i].yl)
                {
                    // it mkes sense but its weird
                    lowest = i;
                }
                
            }
            
            ///box->yh = c2[0].yh;
            int highest = 0;
            for (unsigned int i = 0; i < *numOfBoxes; i++)
            {
                
                if (c2[highest].yh > c2[i].yh)
                {
                    
                    
                    // this 
                    highest = i;
                }
            }
            
            box->yl = c2[highest].yh;
            
            c2[highest] =  c2[*numOfBoxes - 1];
            *numOfBoxes -=1;
            
        }else if (checkbox){
            int highest = 0;
            for (unsigned int i = 0; i < *numOfBoxes; i++)
            {
                
                if (box->yl > c2[i].yl)
                {
                    highest = i;
                }
                
                box->yl = c2[highest].yl;
                checkbox = false;
            }
        }
        trace("box yl: %f box yh: %.f", box->yl, box->yh);
        // this has a possibility of not working 
        unsigned int lbox = 0;
        
        // will probably need saving but its fine for now
        int st = false;
        for (unsigned int i = 0; i < *numOfBoxes; i++)
        {
            
            // this wouldnt be col Volumes
            if (box->yl >= c2[i].yl && c2[i].yh> box->yl)
            {
                //trace("box yl: %d box yh: %d", box->yl,box->yh );
                if(!st){
                    lbox = i;
                    st = true;
                    continue;
                }
                if(c2[lbox].xh > c2[i].xh){
                    lbox = i;
                }
            }
        }
        
        box->xl = c2[lbox].xh;
        box->yh = c2[lbox].yh;
        // the fuck is this?
        for (unsigned int i = 0; i < *numOfBoxes; i++)
        {
            
        }
        
        
        
        //NOTE:: there is a possible problem when the boxes are staggered and the left most box should always be stricken from consideration thats what were doing, and we can do that in pairs if there is no gap we do not care about that box
        // this may have some unforseen problems i dunno It could be real tough.. we shall see
        
        
        bezRef colVolumes[50];
        vcnt = 0;
        
        for (int i = 0; i < *numOfBoxes; i++)
        {
            if (box->yl < c2[i].yh && c2[i].yl < box->yh)
            {
                colVolumes[vcnt] = c2[i];
                vcnt++;
            }
        }
        
        
        // we should figure out the simple case first, because if we can optimize and figure out for the simple case we'll do really well because thankfully the simple case is the common case
        //
        box->xh = colVolumes[0].xl;
        // in the final i could and should just be able to grab the final 
        for (unsigned int i = 1; i < vcnt; i++)
        {
            // we only do this because we need to, there is a lot of superfluous work because of this, but its fine for testing 
            if (colVolumes[i].xl > box->xh)
            {
                box->xh = colVolumes[i].xl;
            }
        }
        
        box->yh = colVolumes[0].yh;
        int boyh = -1;
        for (unsigned int i = 1; i < vcnt; i++)
        {
            
            if(colVolumes[i].yh < box->yh)
            {
                boyh = i;
                box->yh = colVolumes[i].yh;
            }
            
        }
        
        if(boyh != -1)
        {
            for (unsigned int i = 1; i < *numOfBoxes; i++)
            {
                if(&colVolumes[boyh] == &c2[i])
                {
                    c2[i] = c2 [*numOfBoxes - 1];
                    *numOfBoxes -=1;
                    break;
                }
                
            }
        }
        
        
        if(box->yh == c2[lbox].yh)
        {
            c2[lbox] = c2 [*numOfBoxes - 1];
            *numOfBoxes -=1;
            
        }
        
        
        if (box->yh == c2[lowest].yh)
        {
            checkbox = true;
        }
        
        //box->yh = box->yl +1.0f;
        v4 color = {};
        paintRectangle(box,color,AppState);
        
        
        // maybe i put a const before? no idea but it never should have worked
        // i may have fixed this but the change didnt take.. its happened before 
        // is this an infinite loop???
        //for(int i = 0; i < 1; i++){
        //createFitBoxes(*box,c2,8,AppState);
        //box->yl = box->yh;
        //testCode::adjustBox(box,c2,8,AppState,true);
        //}
        
        int eight = 8;
    }
    
    void addPointTotVert(v2 pt, v4 color, Application_State *AState)
    {
        float *vertexbuffer = AState->tvertexBuffer;
        
        vertexbuffer[AState->tvertCount] = pt.x;
        AState->tvertCount += 1;
        vertexbuffer[AState->tvertCount] = pt.y;
        AState->tvertCount += 1;
        
        vertexbuffer[AState->tvertCount] = color.x;
        AState->tvertCount += 1;
        vertexbuffer[AState->tvertCount] = color.y;
        AState->tvertCount += 1;
        vertexbuffer[AState->tvertCount] = color.z;
        AState->tvertCount += 1;
        vertexbuffer[AState->tvertCount] = color.w;
        AState->tvertCount += 1;
    }
    // i honestly dont know if itll be void or not, were gonna assume four points for easy expansion
    
    int boundinglineFill(bezRef bb, v2 *pts, Application_State *AState, unsigned int numPoints = 4)
    {
        
        v4 color = {};
        
        // if im gonna do this i have to save the place of this but i dont
        // need to at first just so i can do like a position += 6 to get to where i need to be and then change the alpha a +2 to change the color
        // i  am may return just an int
        int position = AState->tvertCount;
        if (pts[0].x != bb.xl && pts[0].y != bb.yl)
        {
            addPointTotVert(pts[1], color, AState);
            addPointTotVert(pts[0], color, AState);
            addPointTotVert(V2(bb.xl, bb.yl), color, AState);
        }
        addPointTotVert(pts[1], color, AState);
        addPointTotVert(V2(bb.xl, bb.yl), color, AState);
        addPointTotVert(V2(pts[1].x, bb.yl), color, AState);
        
        addPointTotVert(pts[2], color, AState);
        addPointTotVert(pts[1], color, AState);
        addPointTotVert(V2(pts[1].x, bb.yl), color, AState);
        
        addPointTotVert(pts[2], color, AState);
        addPointTotVert(V2(pts[1].x, bb.yl), color, AState);
        addPointTotVert(V2(pts[2].x, bb.yl), color, AState);
        
        addPointTotVert(pts[3], color, AState);
        addPointTotVert(pts[2], color, AState);
        addPointTotVert(V2(pts[2].x, bb.yl), color, AState);
        
        if (pts[3].x != bb.xh && pts[3].y != bb.yl)
        {
            addPointTotVert(pts[3], color, AState);
            addPointTotVert(V2(pts[2].x, bb.yl), color, AState);
            addPointTotVert(V2(pts[3].x, bb.yl), color, AState);
        }
        //im just gonna be super explicit right now ill change it after
        
#if 0
        unsigned int i;
        
        for (i = 1; i < numPoints - 1; i++)
        {
            addPointTotVert(pts[i + 1], color, AState);
            addPointTotVert(pts[i], color, AState);
            addPointTotVert(V2(pts[i].x, bb.yl), color, AState);
            
            addPointTotVert(pts[i + 1], color, AState);
            addPointTotVert(V2(pts[i].x, bb.yl), color, AState);
            addPointTotVert(V2(pts[i + 1].x, bb.yl), color, AState);
        }
        
        addPointTotVert(pts[i + 1], color, AState);
        addPointTotVert(pts[i], color, AState);
        addPointTotVert(V2(pts[i].x, bb.yl), color, AState);
        
        if (pts[i + 1].x != bb.xh && pts[i + 1].y != bb.yl)
        {
            addPointTotVert(pts[i + 1], color, AState);
            addPointTotVert(V2(pts[i].x, bb.yl), color, AState);
            addPointTotVert(V2(pts[i + 1].x, bb.yl), color, AState);
            
        }
        
#endif
        
        return position;
    }
    
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
                
                //so im gonna look through and see if the top left most box // is gonn scan right and see whats the closest box to the right that also passes throught the top if there isnt anything
                // it drops down now to the next highest being the heighest for the collision test thing, but you search the entire row, for the left most, when we look for the closest to the right you make sure its not touching you every time
                // ok that should work next we take those out of con
                
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
                            //unnecessary // not sure If I should put oldYmax check here or down beeelloow because I may want the absolute smallest, square I can make...
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
        }
        
    }
    
    
}//namespace testTempCode


float getBezX(void *Curve, BezierType type, unsigned int b_i, float t)
{
    
    v2 *controlPts;
    v2 *bezierPts;
    if (type == BezierCuveType)
    {
        bezierCurve *bCurve = (bezierCurve *)Curve;
        controlPts = bCurve->controlPts;
        bezierPts = bCurve->bezierPts;
    } else
    {
        bezRef *bCurve = (bezRef *)Curve;
        controlPts = bCurve->cntrlPts;
        bezierPts = bCurve->bezPts;
    }
    unsigned int c = b_i * 2;
    float x = (1.0f - t)*(1.0f - t)*(1.0f - t)*bezierPts[b_i + 0].x + 3.0f * (1.0f - t)*(1.0f - t)*t*controlPts[c + 0].x + 3.0f * (1.0f - t)*t*t*controlPts[c + 1].x + (t*t*t)*bezierPts[b_i + 1].x;
    return x;
}

float getBezY(void *Curve, BezierType type, unsigned int b_i, float t)
{
    
    v2 *controlPts;
    v2 *bezierPts;
    if (type == BezierCuveType)
    {
        bezierCurve *bCurve = (bezierCurve *)Curve;
        controlPts = bCurve->controlPts;
        bezierPts = bCurve->bezierPts;
    } else
    {
        bezRef *bCurve = (bezRef *)Curve;
        controlPts = bCurve->cntrlPts;
        bezierPts = bCurve->bezPts;
    }
    
    unsigned int c = b_i * 2;
    
    //(1−t)^3P1 + 3(1−t)^2tP2 +3(1−t)t^2P3 + t^3P4
    float y = (1.0f - t)*(1.0f - t)*(1.0f - t)*bezierPts[b_i + 0].y + 3.0f * (1.0f - t)*(1.0f - t)*t*controlPts[c + 0].y + 3.0f * (1.0f - t)*t*t*controlPts[c + 1].y + (t*t*t)*bezierPts[b_i + 1].y;
    
    float x = (1.0f - t)*(1.0f - t)*(1.0f - t)*bezierPts[b_i + 0].y + (t*t*t)*bezierPts[b_i + 1].y + 3 * (t*t)*(1.0f - t)*controlPts[c + 1].y + 3 * (1.0f - t)*(1.0f - t)*t*controlPts[c].y;
    
    return y;
}

v2 getBezV2(void *bCurve, BezierType type, unsigned int b_i, float t)
{
    return V2(getBezX(bCurve, type, b_i, t), getBezY(bCurve, type, b_i, t));
}



v2 * splitBezref(bezRef bCurve, float t)
{
    unsigned int b_i = 0;
    v2 *cntrl = bCurve.cntrlPts;
    v2 *bez = bCurve.bezPts;
    
    
    
    
    unsigned int b = b_i;
    unsigned int c = b * 2;
    // were gonna need to change the code that actuallly deals with this
    
    v2 p1 = lerpV2(bez[b], cntrl[c], t);
    v2 p2 = lerpV2(cntrl[c], cntrl[c + 1], t);
    v2 p3 = lerpV2(cntrl[c + 1], bez[b + 1], t);
    
    v2 lBez = lerpV2(p1, p2, t);
    v2 rBez = lerpV2(p2, p3, t);
    v2 nBez = lerpV2(lBez, rBez, t);
    //pt 1 and pt 3 are ofcourse the left and right new control points respectively
    v2 r[5] = { nBez, lBez, rBez,p1,p3 };
    return r;
}



bool boxCollisionBez(bezierCurve c1, bezierCurve c2)
{
    if (c1.xl < c2.xh &&
        c1.xh > c2.xl &&
        c1.yl < c2.yh &&
        c1.yh> c2.yl)
    {
        return true;
    }
    
    return false;
}

bool PointInBox(v2 c1, boxRef c2)
{
    if (c1.x < c2.xh &&
        c1.x > c2.xl &&
        c1.y < c2.yh &&
        c1.y > c2.yl)
    {
        return true;
    }
    
    return false;
}

bool PointInBox(v2 c1, bezierCurve c2)
{
    if (c1.x < c2.xh &&
        c1.x > c2.xl &&
        c1.y < c2.yh &&
        c1.y> c2.yl)
    {
        return true;
    }
    
    return false;
}

bool bezboxCollisionRef(bezRef c1, bezRef c2)
{
    
    if (c1.xl <= c2.xh &&
        c2.xl <= c1.xh &&
        c1.yl <= c2.yh &&
        c2.yl <= c1.yh)
    {
        return true;
    }
    
    return false;
    
}


// returns four values x low , xhigh, ylow, yhigh i think this is the same as bbref so i could just combine em but who knows i honestly dont see how i could of changed it but there might be some references ill clean those up and consolidate em in do course 



float * findBBbez(bezierCurve *bCurve, unsigned int b_i)
{
    v2 *cntrl = bCurve->controlPts;
    v2 *bez = bCurve->bezierPts;
    
    unsigned int cnt = b_i * 2;
    
    float a = 3 * bez[b_i + 0].x - 9 * cntrl[cnt + 1].x + 9 * cntrl[cnt + 0].x - 3 * bez[b_i + 0].x;
    float b = 6 * bez[b_i + 0].x - 12 * cntrl[cnt + 0].x + 6 * cntrl[cnt + 1].x;
    float c = 3 * cntrl[cnt + 0].x - 3 * bez[b_i + 0].x;
    float disc = b * b - 4 * a * c;
    float xl = bez[b_i + 0].x;
    float xh = bez[b_i + 0].x;
    if (bez[b_i + 1].x < xl) xl = bez[b_i + 1].x;
    if (bez[b_i + 1].x > xh) xh = bez[b_i + 1].x;
    if (disc >= 0)
    {
        float t1 = (-b + sqrtf(disc)) / (2 * a);
        
        if (t1 > 0 && t1 < 1)
        {
            float x1 = getBezX(bCurve, BezierReferenceType, 0, t1);
            if (x1 < xl) xl = x1;
            if (x1 > xh) xh = x1;
        }
        
        float t2 = (-b - sqrtf(disc)) / (2 * a);
        if (t2 > 0 && t2 < 1)
        {
            float x2 = getBezX(bCurve, BezierReferenceType, 0, t2);
            if (x2 < xl) xl = x2;
            if (x2 > xh) xh = x2;
        }
    }
    
    
    a = 3 * bez[b_i + 0].y - 9 * cntrl[cnt + 1].y + 9 * cntrl[cnt + 0].y - 3 * bez[b_i + 0].y;
    b = 6 * bez[b_i + 0].y - 12 * cntrl[cnt + 0].y + 6 * cntrl[cnt + 1].y;
    c = 3 * cntrl[cnt + 0].y - 3 * bez[b_i + 0].y;
    disc = b * b - 4 * a * c;
    float yl = bez[b_i + 0].y;
    float yh = bez[b_i + 0].y;
    if (bez[b_i + 1].y < yl) yl = bez[b_i + 1].y;
    if (bez[b_i + 1].y > yh) yh = bez[b_i + 1].y;
    if (disc >= 0)
    {
        float t1 = (-b + sqrtf(disc)) / (2 * a);
        
        if (t1 > 0 && t1 < 1)
        {
            float x1 = getBezY(bCurve, BezierReferenceType, 0, t1);
            if (x1 < yl) yl = x1;
            if (x1 > yh) yh = x1;
        }
        
        float t2 = (-b - sqrtf(disc)) / (2 * a);
        if (t2 > 0 && t2 < 1)
        {
            float x2 = getBezY(bCurve, BezierReferenceType, 0, t2);
            if (x2 < yl) yl = x2;
            if (x2 > yh) yh = x2;
        }
    }
    
    float r[4] = { xl, xh, yl, yh };
    return r;
}

float * findBBbezRef(bezRef *bCurve)
{
    v2 *cntrl = bCurve->cntrlPts;
    v2 *bez = bCurve->bezPts;
    
    unsigned int b_i = 0;
    unsigned int cnt = b_i * 2;
    
    float a = 3 * bez[b_i + 0].x - 9 * cntrl[cnt + 1].x + 9 * cntrl[cnt + 0].x - 3 * bez[b_i + 0].x;
    float b = 6 * bez[b_i + 0].x - 12 * cntrl[cnt + 0].x + 6 * cntrl[cnt + 1].x;
    float c = 3 * cntrl[cnt + 0].x - 3 * bez[b_i + 0].x;
    float disc = b * b - 4 * a * c;
    float xl = bez[b_i + 0].x;
    float xh = bez[b_i + 0].x;
    if (bez[b_i + 1].x < xl) xl = bez[b_i + 1].x;
    if (bez[b_i + 1].x > xh) xh = bez[b_i + 1].x;
    if (disc >= 0)
    {
        float t1 = (-b + sqrtf(disc)) / (2 * a);
        
        if (t1 > 0 && t1 < 1)
        {
            float x1 = getBezX(bCurve, BezierReferenceType, 0, t1);
            if (x1 < xl) xl = x1;
            if (x1 > xh) xh = x1;
        }
        
        float t2 = (-b - sqrtf(disc)) / (2 * a);
        if (t2 > 0 && t2 < 1)
        {
            float x2 = getBezX(bCurve, BezierReferenceType, 0, t2);
            if (x2 < xl) xl = x2;
            if (x2 > xh) xh = x2;
        }
    }
    
    
    a = 3 * bez[b_i + 0].y - 9 * cntrl[cnt + 1].y + 9 * cntrl[cnt + 0].y - 3 * bez[b_i + 0].y;
    b = 6 * bez[b_i + 0].y - 12 * cntrl[cnt + 0].y + 6 * cntrl[cnt + 1].y;
    c = 3 * cntrl[cnt + 0].y - 3 * bez[b_i + 0].y;
    disc = b * b - 4 * a * c;
    float yl = bez[b_i + 0].y;
    float yh = bez[b_i + 0].y;
    if (bez[b_i + 1].y < yl) yl = bez[b_i + 1].y;
    if (bez[b_i + 1].y > yh) yh = bez[b_i + 1].y;
    if (disc >= 0)
    {
        float t1 = (-b + sqrtf(disc)) / (2 * a);
        
        if (t1 > 0 && t1 < 1)
        {
            float x1 = getBezY(bCurve, BezierReferenceType, 0, t1);
            if (x1 < yl) yl = x1;
            if (x1 > yh) yh = x1;
        }
        
        float t2 = (-b - sqrtf(disc)) / (2 * a);
        if (t2 > 0 && t2 < 1)
        {
            float x2 = getBezY(bCurve, BezierReferenceType, 0, t2);
            if (x2 < yl) yl = x2;
            if (x2 > yh) yh = x2;
        }
    }
    
    float r[4] = { xl, xh, yl, yh };
    return r;
}


// the split happens at b_i+1 thats the new bezier point
void splitBezAtT(bezierCurve *bCurve, unsigned int b_i, float t)
{
    v2 *cntrl = bCurve->controlPts;
    v2 *bez = bCurve->bezierPts;
    
    unsigned int b = b_i;
    unsigned int c = b * 2;
    
    /*bez[b].x = 0.0f;
 bez[b].y = 100.0f;
 
 // m = 50,50
 cntrl[c].x = 100.0f;//lbez 100,25
 cntrl[c].y = 0.0f;//nBez 150, 25
 //m 150,0
 cntrl[c+1].x = 200.0f;//rbez 200,25
 cntrl[c+1].y = 0.0f;
 //m 250,50
 bez[b + 1].x = 300.0f;
 bez[b + 1].y = 100.0f;
 */
    // it seems silly that i need a b_i, the t should determine that, but 
    // maybe i didnt want to keep track of that
    
    
    v2 tpt = getBezV2(bez, BezierCuveType, b_i, t);
    v2 p1 = lerpV2(bez[b], cntrl[c], t);
    v2 p2 = lerpV2(cntrl[c], cntrl[c + 1], t);
    v2 p3 = lerpV2(cntrl[c + 1], bez[b + 1], t);
    v2 lBez = lerpV2(p1, p2, t);
    v2 rBez = lerpV2(p2, p3, t);
    
    // nBez.x should equal 150 
    v2 nBez = lerpV2(lBez, rBez, t);
    // looks like this is a shift
    for (unsigned int k = bCurve->numOfBPts; k > b + 1; k--)
    {
        bez[k] = bez[k - 1];
    }
    bez[b + 1] = nBez;
    
    
    // if something goes wrong its probably here
    for (unsigned int k = bCurve->numOfBPts * 2; k > c + 1; k--)
    {
        cntrl[k] = cntrl[k - 1];
    }
    // yeah just gotta check make sure I does this right pretty easy to inspect though so shouldnt be too much of a problem
    for (unsigned int k = bCurve->numOfBPts * 2; k > c + 2; k--)
    {
        cntrl[k] = cntrl[k - 1];
    }
    cntrl[c + 1] = lBez;
    cntrl[c + 2] = rBez;
    cntrl[c] = p1;
    cntrl[c + 3] = p3;
    
    bCurve->numOfBPts += 1;
    
    
    
}

// it would be multiples of 2 I may just incorporate this with the intersection since there is redunancy but that's way too clever so not right now, how id do it, is i would do this first before feeding it into the bezier, that way doing less splits, its pretty easy if you actually do it that way


//TODO:: This is broken, or rather it just sends back extra bezierRefs after the number of splits i want back, im not entirely sure there is a clean solution to spliting it but i may just forgo spliting them all together and just get the points and draw lines from the bpoints inside
// yeah it may just be best not to use this at all in the future

void splitBezier(bezierCurve *bz, int splits, bezRef *bref1)
{
    
    bezRef b1 = {};
    b1.bezPts[0] = bz->bezierPts[0];
    b1.bezPts[1] = bz->bezierPts[1];
    b1.cntrlPts[0] = bz->controlPts[0];
    b1.cntrlPts[1] = bz->controlPts[1];
    
    bezRef br1;
    unsigned int iter = (int)ceil(sqrt(splits));
    unsigned int iter2 = splits;
    
    for(size_t i = 0; i < bz->numOfBPts; i++)
    {
        b1.bezPts[0] = bz->bezierPts[i];
        b1.bezPts[1] = bz->bezierPts[i+1];
        b1.cntrlPts[0] = bz->controlPts[i*2];
        b1.cntrlPts[1] = bz->controlPts[i*2+1];
        
        unsigned int newbrf1cnt = 0;
        unsigned int brf1Cnt = 1;
        
        // test this one
        //Im gonna come back to this when it has to do multiple ones confused becaue what the hell
        bezRef oldbref1[1000];
        
        b1.t1 = 0.0f;
        b1.t2 = 1.0f;
        
        oldbref1[0] = b1;
        // i think this should work i gotta test it though, god i did such a slow job 
        
        for (size_t ii = 0; ii < iter; ii++)
        {
            // this refers to the splits 
            for (size_t i2 = 0; i2 < brf1Cnt + 1; i2++)
            {
                br1 = oldbref1[i2];
                float md1 = lerpf(br1.t1, br1.t2, 0.5f);
                //here i would be like newBrfCnt instead, and after im done I make the new the old and set the new to zero
                v2 *m_l_r = splitBezref(br1, 0.5f);
                bezRef b1left = br1;
                bezRef b1Right = br1;
                b1left.bezPts[1] = m_l_r[0];
                b1left.cntrlPts[1] = m_l_r[1];
                b1Right.bezPts[0] = m_l_r[0];
                b1Right.cntrlPts[0] = m_l_r[2];
                b1left.cntrlPts[0] = m_l_r[3];
                b1Right.cntrlPts[1] = m_l_r[4];
                // dont do anything to this value
                b1left.t1 = br1.t1;
                b1left.t2 = md1;
                // dont do anything to this value.. delete on copy
                b1Right.t2 = br1.t2;
                b1Right.t1 = md1;
                
                
                float *dim = findBBbezRef(&b1left);
                b1left.xl = dim[0];
                b1left.xh = dim[1];
                b1left.yl = dim[2];
                
                b1left.yh = dim[3];
                
                b1left.bCurve = bz;
                //ok i rememebr doing this and ading a note maybe i did it in vs and thats why it didnt stick but im gonna put this here again 
                
                
                
                dim = findBBbezRef(&b1Right);
                b1Right.xl = dim[0];
                b1Right.xh = dim[1];
                b1Right.yl = dim[2];
                b1Right.yh = dim[3];
                
                
                
                b1Right.bCurve = bz;
                //*** thats just the splitting 
                
                
                
                bref1[newbrf1cnt+16*i] = b1left;
                bref1[newbrf1cnt+16*i + 1] = b1Right;
                
                newbrf1cnt += 2;
            }
            
            
            // newbrf1cnt should be there instead of 16, yknow
            memcpy(oldbref1, bref1+16*i, 16 * sizeof*bref1);
            brf1Cnt = newbrf1cnt;
            newbrf1cnt = 0;
            
        }
    }
    
}

// so now that we've moved this whats next oh I wanna make beziers based on
// i think i can do it in three minutes  lets give it to 1:16 i shaved it to 4 but well fuck anyway moving on 
// im just thinking putting the t in here and just running it, pff I dont know anything else should take like a minute if that 
void newsplitBezier(bezierCurve *bz, unsigned int *splits, bezRef *bref1)
{
    
    bezRef b1 = {};
    
    unsigned int iter = (int)ceil(sqrt(*splits));
    unsigned int iter2 = *splits;
    unsigned int newbrf1cnt = 0;
    
    for(size_t i = 0; i < bz->numOfBPts; i++)
    {
        
        b1.bezPts[0] = bz->bezierPts[i];
        b1.bezPts[1] = bz->bezierPts[i+1];
        b1.cntrlPts[0] = bz->controlPts[i*2];
        b1.cntrlPts[1] = bz->controlPts[i*2+1];
        
        if (b1.bezPts[0].x < b1.bezPts[1].x)
        { b1.xl = b1.bezPts[0].x; b1.xh = b1.bezPts[1].x;}
        else
        {b1.xh = b1.bezPts[0].x;	b1.xl = b1.bezPts[1].x;}
        if (b1.bezPts[0].y < b1.bezPts[1].y)
        {b1.yl = b1.bezPts[0].y; b1.yh = b1.bezPts[1].y; }
        else
        {b1.yh = b1.bezPts[0].y; b1.yl = b1.bezPts[1].y;}
        
        b1.t1 = (float)i/(bz->numOfBPts -1);
        b1.t2 = (float)(i+1)/(bz->numOfBPts -1);
        
        b1.bCurve = bz;
        //ok i rememebr doing this and ading a note maybe i did it in vs and thats why it didnt stick but im gonna put this here again 
        
        // cancel the fill and just draw out the boxes work from there
        
        bref1[i] = b1;
        
        
    }
    *splits = bz->numOfBPts -1;
    
    // newbrf1cnt should be there instead of 16, yknow
    
}


void bezierIntersection(bezierCurve *b1, bezierCurve *b2)
{
    
    
    // just have to make this true so it runs later ill make a full box for beziers
    if (boxCollisionBez(*b1, *b2) || true)
    {
        // this is where it gets a bit complicated so were just gonna pretend there is only one intersection 
        // first we find which sub bez has it
        
        bezRef bref1[1000];
        unsigned int newbrf1cnt = 0;
        unsigned int newbrf2cnt = 0;
        unsigned int brf1Cnt = 0;
        bezRef bref2[1000];
        unsigned int brf2Cnt = 0;
        for (size_t i = 0; i < b1->numOfBPts - 1; i++)
        {
            int c = i * 2;
            // were gonna assume there is only one intersection
            bezRef br1 = bref1[brf1Cnt];
            br1 = {};
            br1.bCurve = b1;
            br1.b_i = i;
            br1.bezPts[0] = b1->bezierPts[i];
            br1.bezPts[1] = b1->bezierPts[i + 1];
            br1.cntrlPts[0] = b1->controlPts[c];
            br1.cntrlPts[1] = b1->controlPts[c + 1];
            float *dim = findBBbezRef(&br1);
            br1.xl = dim[0];
            br1.xh = dim[1];
            br1.yl = dim[2];
            br1.yh = dim[3];
            for (size_t ii = 0; ii < b2->numOfBPts - 1; ii++)
            {
                bezRef br2 = bref2[brf2Cnt];
                br2 = {};
                br2.bCurve = b2;
                br2.b_i = ii;
                br2.bezPts[0] = b2->bezierPts[ii];
                br2.bezPts[1] = b2->bezierPts[ii + 1];
                br2.cntrlPts[0] = b2->controlPts[c];
                br2.cntrlPts[1] = b2->controlPts[c + 1];
                dim = findBBbezRef(&br2);
                br2.xl = dim[0];
                br2.xh = dim[1];
                br2.yl = dim[2];
                br2.yh = dim[3];
                if (bezboxCollisionRef(br1, br2))
                {
                    // this is interesting the next loops i dont need to do all that initial setup because i will have created it in here
                    float md1 = lerpf(0.0f, 1.0f, 0.5f);
                    
                    //here i would be like newBrfCnt instead, and after im done I make the new the old and set the new to zero
                    v2 *m_l_r = splitBezref(br1, 0.5f);
                    bezRef b1left = br1;
                    bezRef b1Right = br1;
                    b1left.bezPts[1] = m_l_r[0];
                    b1left.cntrlPts[1] = m_l_r[1];
                    b1Right.bezPts[0] = m_l_r[0];
                    b1Right.cntrlPts[0] = m_l_r[2];
                    b1left.cntrlPts[0] = m_l_r[3];
                    b1Right.cntrlPts[1] = m_l_r[4];
                    // dont do anything to this value
                    b1left.t1 = 0;
                    b1left.t2 = md1;
                    // dont do anything to this value.. delete on copy
                    b1Right.t2 = 1;
                    b1Right.t1 = md1;
                    
                    
                    dim = findBBbezRef(&b1left);
                    b1left.xl = dim[0];
                    b1left.xh = dim[1];
                    b1left.yl = dim[2];
                    b1left.yh = dim[3];
                    
                    dim = findBBbezRef(&b1Right);
                    b1Right.xl = dim[0];
                    b1Right.xh = dim[1];
                    b1Right.yl = dim[2];
                    b1Right.yh = dim[3];
                    
                    
                    bref1[brf1Cnt] = b1left;
                    bref1[brf1Cnt + 1] = b1Right;
                    
                    float md2 = lerpf(0.0f, 1.0f, 0.5f);
                    
                    
                    m_l_r = splitBezref(br2, 0.5f);
                    bezRef b2left = br2;
                    bezRef b2Right = br2;
                    b2left.bezPts[1] = m_l_r[0];
                    b2left.cntrlPts[1] = m_l_r[1];
                    b2Right.bezPts[0] = m_l_r[0];
                    b2Right.cntrlPts[0] = m_l_r[2];
                    b2left.cntrlPts[0] = m_l_r[3];
                    b2Right.cntrlPts[1] = m_l_r[4];
                    // dont do anything to this value
                    b2left.t1 = 0;
                    b2left.t2 = md1;
                    // dont do anything to this value.. delete on copy
                    b2Right.t2 = 1;
                    b2Right.t1 = md1;
                    
                    dim = findBBbezRef(&b2left);
                    b2left.xl = dim[0];
                    b2left.xh = dim[1];
                    b2left.yl = dim[2];
                    b2left.yh = dim[3];
                    
                    dim = findBBbezRef(&b2Right);
                    b2Right.xl = dim[0];
                    b2Right.xh = dim[1];
                    b2Right.yl = dim[2];
                    b2Right.yh = dim[3];
                    
                    
                    bref2[brf2Cnt] = b2left;
                    bref2[brf2Cnt + 1] = b2Right;
                    
                    
                    
                    
                    brf1Cnt += 2;
                    brf2Cnt += 2;
                    
                }
            }
            
            
            
            
        }
        newbrf1cnt = brf1Cnt;
        newbrf2cnt = brf2Cnt;
        
        if (brf1Cnt == 0) return;
        
        bool isFinished = false;
        
        while (!isFinished)
        {
            brf1Cnt = newbrf1cnt;
            brf2Cnt = newbrf2cnt;
            newbrf1cnt = 0;
            newbrf2cnt = 0;
            
            bezRef oldbref1[1000];
            // I capped this at 400 dont know if that was right, but i did, so uhh yeah 
            memcpy(oldbref1, bref1, 400*sizeof(bezRef));
            bezRef oldbref2[1000];
            
            memcpy(oldbref2, bref2,  400*sizeof(bezRef));
            for (size_t i = 0; i < brf1Cnt; i++)
            {
                if (brf1Cnt > 10)
                {
                    bool test = true;
                }
                bool didCollide = false;
                bezRef br1 = oldbref1[i];
                for (size_t ii = 0; ii < brf2Cnt; ii++)
                {
                    
                    bezRef br2 = oldbref2[ii];
                    
                    trace("\nbr1 t1 = %f, t2 = %f ", br1.t1, br1.t2);
                    
                    trace("vs  br2 t1 = %f, t2 = %f  ", br2.t1, br2.t2);
                    
                    if (bezboxCollisionRef(br1, br2))
                    {
                        OutputDebugStringA("Collision!");
                        
                        // this is interesting the next loops i dont need to do all that initial setup because i will have created it in here
                        didCollide = true;
                        
                        
                        //LAST TIME ON DRAGON BALL Z::::: I dunno it seems to work some of the time and then it'll get to zero collisions, the fact that it happens rarely makes me wanna take traces out to inspect whats happening
                        
                        
                        float md2 = lerpf(br2.t1, br2.t2, 0.5f);
                        
                        
                        v2* m_l_r = splitBezref(br2, 0.5f);
                        bezRef b2left = br2;
                        bezRef b2Right = br2;
                        //all these with mlr are wrong lets see how pervasive this problem is
                        b2left.bezPts[1] = m_l_r[0];
                        b2Right.bezPts[0] = m_l_r[0];
                        b2left.cntrlPts[1] = m_l_r[1];
                        b2left.cntrlPts[0] = m_l_r[3];
                        b2Right.cntrlPts[0] = m_l_r[2];
                        b2Right.cntrlPts[1] = m_l_r[4];
                        // dont do anything to this value
                        b2left.t1 = br2.t1;
                        b2left.t2 = md2;
                        // dont do anything to this value.. delete on copy
                        b2Right.t1 = md2;
                        b2Right.t2 = br2.t2;
                        
                        float *dim = findBBbezRef(&b2left);
                        b2left.xl = dim[0];
                        b2left.xh = dim[1];
                        b2left.yl = dim[2];
                        b2left.yh = dim[3];
                        
                        if (dim[1] - dim[0] < 1.0f && dim[3] - dim[2] < 1.0)
                        {
                            
                            isFinished = true;
                        }
                        
                        
                        if (isFinished)
                        {
                            // to make this work on multiple ones i just have to increment it but this should work
                            trace("\n we split")
                            
                                if (br1.bCurve->ixCount > 0)
                            {
                                if (fabs(br1.bCurve->ix[br1.bCurve->ixCount].t - br1.bCurve->ix[br1.bCurve->ixCount].t) < 0.1f)
                                {
                                    isFinished = false;
                                    break;
                                }
                            }
                            intersection *inx = &br1.bCurve->ix[br1.bCurve->ixCount];
                            inx->t = br1.t1;
                            inx->b_i = br1.b_i;
                            
                            inx = &br2.bCurve->ix[br2.bCurve->ixCount];
                            
                            inx->t = br2.t1;
                            inx->b_i = br2.b_i;
                            
                            br1.bCurve->ixCount += 1;
                            br2.bCurve->ixCount += 1;
                            
                            splitBezAtT(br1.bCurve, br1.b_i, br1.t1);
                            splitBezAtT(br2.bCurve, br2.b_i, br2.t1);
                            
                            static unsigned int counting = 0;
                            
                            if (counting < 2)
                            {
                                isFinished = false;
                                counting++;
                                break;
                            } else
                            {
                                return;
                            }
                        }
                        
                        
                        
                        dim = findBBbezRef(&b2Right);
                        b2Right.xl = dim[0];
                        b2Right.xh = dim[1];
                        b2Right.yl = dim[2];
                        b2Right.yh = dim[3];
                        
                        
                        bref2[newbrf2cnt] = b2left;
                        bref2[newbrf2cnt + 1] = b2Right;
                        // this is very unclean, but lets see if it works ugggh fuck me, but basically what this is that it prevents it from splitting the same bezier twice by taking it out of consideration, since it has already been split
                        
                        /*for (int j = ii; j< brf2Cnt - 1; j++) oldbref2[j] = oldbref2[j+ 1];
        brf2Cnt -= 1;
        ii--;*/
                        
                        newbrf2cnt += 2;
                        
                    }
                    
                }
                
                if (didCollide)
                {
                    float md1 = lerpf(br1.t1, br1.t2, 0.5f);
                    
                    //here i would be like newBrfCnt instead, and after im done I make the new the old and set the new to zero
                    v2 *m_l_r = splitBezref(br1, 0.5f);
                    bezRef b1left = br1;
                    bezRef b1Right = br1;
                    b1left.bezPts[1] = m_l_r[0];
                    b1Right.bezPts[0] = m_l_r[0];
                    b1left.cntrlPts[0] = m_l_r[3];
                    b1left.cntrlPts[1] = m_l_r[1];
                    b1Right.cntrlPts[0] = m_l_r[2];
                    b1Right.cntrlPts[1] = m_l_r[4];
                    // dont do anything to this value
                    b1left.t1 = br1.t1;
                    b1left.t2 = md1; 
                    // dont do anything to this value.. delete on copy
                    b1Right.t1 = md1;
                    b1Right.t2 = br1.t2;
                    
                    float *dim = findBBbezRef(&b1left);
                    b1left.xl = dim[0];
                    b1left.xh = dim[1];
                    b1left.yl = dim[2];
                    b1left.yh = dim[3];
                    
                    dim = findBBbezRef(&b1Right);
                    b1Right.xl = dim[0];
                    b1Right.xh = dim[1];
                    b1Right.yl = dim[2];
                    b1Right.yh = dim[3];
                    
                    
                    bref1[newbrf1cnt] = b1left;
                    bref1[newbrf1cnt + 1] = b1Right;
                    
                    newbrf1cnt += 2;
                }
                
            }
            
        }
        
        
    }
    
    
    
}

v2 lineIntersect(v2 a, v2 b, v2 c, v2 d, bool absCoord = false){
    
    v2 r = b - a;
    v2 s = d - c;
    
    float p = r.x * s.y - r.y * s.x;
    float u = ((c.x - a.x)* r.y - (c.y - a.y)* r.x)/p;
    float t = ((c.x - a.x)* s.y - (c.y - a.y)* s.x)/p;
    // if you wanna know its coordinates, its hizeer a + t*r
    
    // REMEMBER this through me for a loop for a while, u, is for the second one, and t is for the first... u is where it intersects the second one and t the first, EDIT() THIS IS WRONG I DONT KNW WHAT I MEANT/ALREADY FIXED IT, hence the weird u, tm instead of t,u
    
    //
    
    if(!absCoord)
    {return V2(u,t);
    }else{
        if(u <= 1.0f && u  >= 0.0f && t <= 1.0f && t >= 0.0f)
            return a + (t*r);
        else
            return V2(NAN,NAN);
    }
    
    
}
namespace testCode {
    
    
    // this returns the the u for the virst line and the t for the second it should be between 0 and 1 ill put the 
    
    
    v2 lineIntersect(bezRef b1, bezRef b2){
        
        return lineIntersect(b1.bezPts[0],b1.bezPts[1],b2.bezPts[0], b2.bezPts[1]);
    }
    
    
    void bezierIntersection(bezRef *b1, bezRef *b2)
    {
        
        v2 it =  lineIntersect(b1->bezPts[0], b1->bezPts[1], b2->bezPts[0], b2->bezPts[1]);
        if(it.x >= 0.0f && it.x <= 1.0 && it.y >= 0.0f && it.y <= 1.0f){
            
            // for most i can probably just end it here
            v2 *b1Pts;
            v2 *b2Pts;
            v2 v = {};
            v2 *bPts[2];
            bPts[0] = b1Pts;
            bPts[1] = b2Pts;
            bezRef *b[2];
            b[0] = b1;
            b[1] = b2;
            unsigned int nlines = 3;
            for(size_t f = 0; f < 2; f++){
                
                for(unsigned int i = 0; i < nlines +1; i++){
                    
                    float u = i*(1/3);
                    
                    v.x = (1.0f - u) * (1.0f - u) * (1.0f - u) * b[f]->bezPts[0].x + 3.0f * (1.0f - u) * (1.0f - u) * u * b[f]->cntrlPts[0].x + 3.0f * (1.0f - u) * u * u * b[f]->cntrlPts[1].x + (u * u * u) * b[f]->bezPts[1].x;
                    
                    v.y = (1.0f - u) * (1.0f - u) * (1.0f - u) * b[f]->bezPts[0].y + 3.0f * (1.0f - u) * (1.0f - u) * u * b[f]->cntrlPts[0].y + 3.0f * (1.0f - u) * u * u * b[f]->cntrlPts[1].y + (u * u * u) * b[f]->bezPts[1].y;
                    
                    bPts[f][i] = v; 
                }
            }
            
            for (size_t i = 0; i < 3; i++)
            {
                
                for (unsigned int ii = 0; ii < 3; ii++)
                {
                    v2 it = lineIntersect(b1Pts[i], b1Pts[i+1], b2Pts[ii], b2Pts[ii+1]);
                    if (it.x >= 0.0f && it.x <= 1.0 && it.y >= 0.0f && it.y <= 1.0f)
                    {
                        // then just figure out where it is based loosely on where its i's are
                        // and just put the is finished thing here
                        
                        
                        
                        intersection *inx = &b1->bCurve->ix[b1->bCurve->ixCount];
                        inx->t = b1->t1;
                        inx->b_i = b1->b_i;
                        
                        inx = &b2->bCurve->ix[b2->bCurve->ixCount];
                        
                        inx->t = b2->t1;
                        inx->b_i = b2->b_i;
                        
                        b1->bCurve->ixCount += 1;
                        b2->bCurve->ixCount += 1;
                        
                        splitBezAtT(b1->bCurve, b1->b_i, b1->t1);
                        splitBezAtT(b2->bCurve, b2->b_i, b2->t1);
                        
                        return;
                        
                    }
                }
            }
            
        }
    }
    
    v2 pointFromBez(float t, v2 *bezPts, v2 *cntrlPts)
    {
        
        v2 v = {};
        
        
        v.x = (1.0f - t) * (1.0f - t) * (1.0f - t) * bezPts[0].x + 3.0f * (1.0f - t) * (1.0f - t) * t * cntrlPts[0].x + 3.0f * (1.0f - t) * t * t * cntrlPts[1].x + (t * t * t) * bezPts[1].x;
        
        v.y = (1.0f - t) * (1.0f - t) * (1.0f - t) * bezPts[0].y + 3.0f * (1.0f - t) * (1.0f - t) * t * cntrlPts[0].y + 3.0f * (1.0f - t) * t * t *cntrlPts[1].y + (t * t * t) * bezPts[1].y;
        
        return v; 
        
    }
    
    v2 pointFromBez(float t, bezRef *bez){
        // check if thats right
        return pointFromBez(t, bez->bezPts, bez->cntrlPts);
    }
    
    
    v2 pointFromBez(float t, bezierCurve *bez){
        // check if thats right
        
        // TODO::Again this is just a hack itll be a lot more complicated adding all the points in the bezier in the final but for now
        
        // yeah figuring out the t of this badboy is gonna be a bitch... good luck friend
        return pointFromBez(t, bez->bezierPts, bez-> controlPts);
    }
    // DEPTRICATED APPARTENTLY I CHANGED THE ENTIRE STRUCTURE OF THE PROGRAM AND NOW IT MAKES SENSE WHY I KEPT THOSE BEZREFS, THOSE ARE MEANT TO STAY, THEY ACT AS HIT BOXES, THEY CAN BE REMADE REFERENCED OTHERWISE THEY ARE ADJUSTABLE AND NOT BOUND BY THINGS, ALSO I CAN GET A ROUGH DISTANCE OF THE DAMN THING
    v2 *binarySIntersection(bezRef *b1,bezRef *b2)
    {
        
        
        if ( true)
        {
            
            
            bezRef bref1[1000];
            unsigned int newbrf1cnt = 0;
            unsigned int newbrf2cnt = 0;
            unsigned int brf1Cnt = 0;
            bezRef bref2[1000];
            unsigned int brf2Cnt = 0;
            //int c = i * 2;
            // were gonna assume there is only one intersection
            bezRef br1 = *b1;
            bezRef br2 = *b2;
            
            // why would i clear   it if i set it to it, how is it suppose to do work
            //br1 = {};
            
            
            float md2 = lerpf(br2.t1, br2.t2, 0.5f);
            
            
            v2* m_l_r = splitBezref(br2, 0.5f);
            bezRef b2left = br2;
            bezRef b2Right = br2;
            //all these with mlr are wrong lets see how pervasive this problem is
            b2left.bezPts[1] = m_l_r[0];
            b2Right.bezPts[0] = m_l_r[0];
            b2left.cntrlPts[1] = m_l_r[1];
            b2left.cntrlPts[0] = m_l_r[3];
            b2Right.cntrlPts[0] = m_l_r[2];
            b2Right.cntrlPts[1] = m_l_r[4];
            // dont do anything to this value
            b2left.t1 = br2.t1;
            b2left.t2 = md2;
            // dont do anything to this value.. delete on copy
            b2Right.t1 = md2;
            b2Right.t2 = br2.t2;
            
            float *dim = findBBbezRef(&b2left);
            b2left.xl = dim[0];
            b2left.xh = dim[1];
            b2left.yl = dim[2];
            b2left.yh = dim[3];
            
            
            
            
            
            dim = findBBbezRef(&b2Right);
            b2Right.xl = dim[0];
            b2Right.xh = dim[1];
            b2Right.yl = dim[2];
            b2Right.yh = dim[3];
            
            
            bref2[0] = b2left;
            bref2[1] = b2Right;
            // this is very unclean, but lets see if it works ugggh fuck me, but basically what this is that it prevents it from splitting the same bezier twice by taking it out of consideration, since it has already been split
            
            /*for (int j = ii; j< brf2Cnt - 1; j++) oldbref2[j] = oldbref2[j+ 1];
        brf2Cnt -= 1;
        ii--;*/
            
            newbrf2cnt = 2;
            
            
            float md1 = lerpf(br1.t1, br1.t2, 0.5f);
            
            //here i would be like newBrfCnt instead, and after im done I make the new the old and set the new to zero
            m_l_r = splitBezref(br1, 0.5f);
            bezRef b1left = br1;
            bezRef b1Right = br1;
            b1left.bezPts[1] = m_l_r[0];
            b1Right.bezPts[0] = m_l_r[0];
            b1left.cntrlPts[0] = m_l_r[3];
            b1left.cntrlPts[1] = m_l_r[1];
            b1Right.cntrlPts[0] = m_l_r[2];
            b1Right.cntrlPts[1] = m_l_r[4];
            // dont do anything to this value
            b1left.t1 = br1.t1;
            b1left.t2 = md1; 
            // dont do anything to this value.. delete on copy
            b1Right.t1 = md1;
            b1Right.t2 = br1.t2;
            
            dim = findBBbezRef(&b1left);
            b1left.xl = dim[0];
            b1left.xh = dim[1];
            b1left.yl = dim[2];
            b1left.yh = dim[3];
            
            dim = findBBbezRef(&b1Right);
            b1Right.xl = dim[0];
            b1Right.xh = dim[1];
            b1Right.yl = dim[2];
            b1Right.yh = dim[3];
            
            
            bref1[0] = b1left;
            bref1[1] = b1Right;
            // TODO:: if this works make sure to clean all this stuff up because its a mess since I just wanted to see if the change in algorithm would... yknow what, what am I defending this for.. its crap fix it
            newbrf1cnt = 2;
            
            
            // START::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
            //FROM HERERERERERE
            
            brf1Cnt = 2;
            brf2Cnt = 2;
            //newbrf1cnt = brf1Cnt;
            //newbrf2cnt = brf2Cnt;
            // i dont know what this is and its probably wrong so im just gonna throw an error if it does it
            //if (brf1Cnt == 0) return;
            //Assert(brf1Cnt != 0);
            
            bool isFinished = false;
            
            while (!isFinished)
            { 
                
                newbrf1cnt = 0;
                newbrf2cnt = 0;
                
                bezRef oldbref1[10];
                // I capped this at 400 dont know if that was right, but i did, so uhh yeah 
                
                // i can replace it here its just constantly going to a different thing
                
                bezRef oldbref2[10];
                
                
                bezRef br1 = bref1[0];
                bezRef br2 = bref2[0];
                
                
                float lessSqr = (bref1[0].bezPts[0].x - bref2[0].bezPts[0].x)*(bref1[0].bezPts[0].x - bref2[0].bezPts[0].x) + (bref1[0].bezPts[0].y - bref2[0].bezPts[0].y)*(bref1[0].bezPts[0].y - bref2[0].bezPts[0].y);
                
                
                for (size_t i = 0; i < brf1Cnt; i++)
                {
                    
                    bool didCollide = false;
                    
                    
                    for (size_t ii = 0; ii < brf2Cnt; ii++)
                    {
                        // am i doing distance for this?
                        
                        float nlSqr = (bref1[i].bezPts[i].x - bref2[ii].bezPts[ii].x)*(bref1[i].bezPts[i].x - bref2[ii].bezPts[ii].x) + (bref1[i].bezPts[i].y - bref2[ii].bezPts[ii].y)*(bref1[i].bezPts[i].y - bref2[ii].bezPts[ii].y);
                        
                        if (nlSqr < lessSqr)
                        {
                            lessSqr = nlSqr;
                            br1 = bref1[i];
                            br2 = bref2[ii];
                        }
                        
                    }
                    
                }
                
                //not sure why i put this here but im pretty sure this isnt supposed to happen since things were working before hand.. hmm 
                //Assert(0);
                //	Assert(br1.t1 > 0.0f);
                //trace("\nbr1 t1 = %f, t2 = %f ", br1.t1, br1.t2);
                
                //trace("vs  br2 t1 = %f, t2 = %f  ", br2.t1, br2.t2);
                // weird i thought I did this before
                if (true)
                {
                    OutputDebugStringA("Collision!");
                    
                    // this is interesting the next loops i dont need to do all that initial setup because i will have created it in here
                    //	didCollide = true;
                    
                    
                    
                    
                    float md2 = lerpf(br2.t1, br2.t2, 0.5f);
                    
                    
                    v2* m_l_r = splitBezref(br2, 0.5f);
                    bezRef b2left = br2;
                    bezRef b2Right = br2;
                    //all these with mlr are wrong lets see how pervasive this problem is
                    b2left.bezPts[1] = m_l_r[0];
                    b2Right.bezPts[0] = m_l_r[0];
                    b2left.cntrlPts[1] = m_l_r[1];
                    b2left.cntrlPts[0] = m_l_r[3];
                    b2Right.cntrlPts[0] = m_l_r[2];
                    b2Right.cntrlPts[1] = m_l_r[4];
                    // dont do anything to this value
                    b2left.t1 = br2.t1;
                    b2left.t2 = md2;
                    // dont do anything to this value.. delete on copy
                    b2Right.t1 = md2;
                    b2Right.t2 = br2.t2;
                    
                    float *dim = findBBbezRef(&b2left);
                    b2left.xl = dim[0];
                    b2left.xh = dim[1];
                    b2left.yl = dim[2];
                    b2left.yh = dim[3];
                    
                    if (dim[1] - dim[0] < 1.0f && dim[3] - dim[2] < 1.0)
                    {
                        
                        isFinished = true;
                    }
                    
                    // well that explains why it doesnt work for multiple ones, anyway it doesnt matter its a bad algorithm just gonna fix it a bit more
                    if (isFinished)
                    {
                        // to make this work on multiple ones i just have to increment it but this should work
                        
                        int crsAngle1;
                        int crsAngle2;
                        {
                            float an1 = atan2f(br1.bezPts[0].y - br1.bezPts[0].y , br1.bezPts[0].x -br1.bezPts[0].x);
                            float an2 = atan2f(br2.bezPts[0].y - br2.bezPts[0].y , br2.bezPts[0].x -br2.bezPts[0].x);
                            crsAngle1 = int(an2 - an1);
                            crsAngle2 = int(an1 - an2);
                        }
                        
                        
                        intersection *inx = &br1.bCurve->ix[br1.bCurve->ixCount];
                        inx->t = br1.t1;
                        inx->b_i = br1.b_i;
                        
                        // not sure what bez points are but shouldnt matter
                        inx->pt = br1.bezPts[0];
                        inx->crsAngle = crsAngle1;
                        inx->isCutting = true;
                        
                        inx = &br2.bCurve->ix[br2.bCurve->ixCount];
                        static int iT = -1;
                        
                        // TODO:: get rid of iT i just wont work later it's a hack
                        // but when you change it, change the bezier
                        // so it wont need a b_i, just no its a split, just iterate over each of em so that, adding a point doesnt chnage the nature of the bezier, so i wont have to keep track of b_i's of each point because thats a huge amount of memory wasted for no reason
                        
                        
                        
                        //TODO:: OPTIMIZE PRIME i can combine these later since its more info then i need but for now its fin
                        iT++;
                        inx->t = br2.t1;
                        inx->b_i = iT;
                        inx->pt = br2.bezPts[0];
                        inx->crsAngle = crsAngle2;
                        inx->isCutting = true;
                        
                        
                        br1.bCurve->ixCount += 1;
                        br2.bCurve->ixCount += 1;
                        trace("\n\nsplit me up inside\n\n");
                        splitBezAtT(br1.bCurve,inx->b_i, br1.t1);
                        splitBezAtT(br2.bCurve, inx->b_i, br2.t1);
                        // itd be cleaner if i can return the t1 and t2 remember to do that sometime TODO: do it
                        v2 thing[3];
                        thing[0] = 
                            V2(br1.t1, br2.t1);
                        thing[1] = br1.bezPts[0];
                        thing[2] = br2.bezPts[0];
                        
                        return thing;
                    }
                    
                    
                    
                    dim = findBBbezRef(&b2Right);
                    b2Right.xl = dim[0];
                    b2Right.xh = dim[1];
                    b2Right.yl = dim[2];
                    b2Right.yh = dim[3];
                    
                    
                    bref2[0] = b2left;
                    bref2[1] = b2Right;
                    // this is very unclean, but lets see if it works ugggh fuck me, but basically what this is that it prevents it from splitting the same bezier twice by taking it out of consideration, since it has already been split
                    
                    /*for (int j = ii; j< brf2Cnt - 1; j++) oldbref2[j] = oldbref2[j+ 1];
        brf2Cnt -= 1;
        ii--;*/
                    
                    newbrf2cnt = 2;
                    
                    
                    float md1 = lerpf(br1.t1, br1.t2, 0.5f);
                    
                    //here i would be like newBrfCnt instead, and after im done I make the new the old and set the new to zero
                    m_l_r = splitBezref(br1, 0.5f);
                    bezRef b1left = br1;
                    bezRef b1Right = br1;
                    b1left.bezPts[1] = m_l_r[0];
                    b1Right.bezPts[0] = m_l_r[0];
                    b1left.cntrlPts[0] = m_l_r[3];
                    b1left.cntrlPts[1] = m_l_r[1];
                    b1Right.cntrlPts[0] = m_l_r[2];
                    b1Right.cntrlPts[1] = m_l_r[4];
                    // dont do anything to this value
                    b1left.t1 = br1.t1;
                    b1left.t2 = md1; 
                    // dont do anything to this value.. delete on copy
                    b1Right.t1 = md1;
                    b1Right.t2 = br1.t2;
                    
                    dim = findBBbezRef(&b1left);
                    b1left.xl = dim[0];
                    b1left.xh = dim[1];
                    b1left.yl = dim[2];
                    b1left.yh = dim[3];
                    
                    dim = findBBbezRef(&b1Right);
                    b1Right.xl = dim[0];
                    b1Right.xh = dim[1];
                    b1Right.yl = dim[2];
                    b1Right.yh = dim[3];
                    
                    
                    bref1[0] = b1left;
                    bref1[1] = b1Right;
                    // TODO:: if this works make sure to clean all this stuff up because its a mess since I just wanted to see if the change in algorithm would... yknow what, what am I defending this for.. its crap fix it
                    newbrf1cnt = 2;
                    
                    
                    
                }
                
                
                
            }
            
            
        }
        
        
        
    }
}

