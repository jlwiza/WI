namespace testCodetest {
	
void bezierIntersection(bezierCurve *b1, bezierCurve *b2)
{


	// just have to make this true so it runs later ill make a full box for beziers
	if (boxCollisionBez(*b1, *b2) || true)
	{
		// this is where it gets a bit complicated so were just gonna pretend there is only one intersection 
		// first we find which sub bez has it

		// so now before this we have to check for collisions between between each of the bezrefs from group one to group 2

		// i think we may be fine with just 2 here
		
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



					// probably wont need these since we'll do it two at atime
					brf1Cnt += 2;
					brf2Cnt += 2;

				}
			}


// YOU CAN START NOWWWW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
//FROM HERERERERERE

		}
		newbrf1cnt = brf1Cnt;
		newbrf2cnt = brf2Cnt;

		if (brf1Cnt == 0) return;

		bool isFinished = false;

		while (!isFinished)
		{ 
			
			newbrf1cnt = 0;
			newbrf2cnt = 0;

			bezRef oldbref1[1000];
			// I capped this at 400 dont know if that was right, but i did, so uhh yeah 

			// i can replace it here its just constantly going to a different thing
			memcpy(oldbref1, bref1, sizeof*bref1);
			bezRef oldbref2[1000];

			memcpy(oldbref2, bref2,  sizeof*bref2);
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

						// well that explains why it doesnt work for multiple ones, anyway it doesnt matter its a bad algorithm just gonna fix it a bit more
						if (isFinished)
						{
							// to make this work on multiple ones i just have to increment it but this should work

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

							return;
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


					bref1[0] = b1left;
					bref1[1] = b1Right;
					// TODO:: if this works make sure to clean all this stuff up because its a mess since I just wanted to see if the change in algorithm would... yknow what, what am I defending this for.. its crap fix it
					newbrf1cnt = 2;
					break;


					}

				}

				

			}

		}


	}



}
}