/*
cool i can write in this thing and not have to worry about the multiple line wrapping thing that goes on which is nice.. oight

there are the problem sets i think if figure out the problem sets ill do a much better job

apparently architecture and microarchetecture are different, i wonder how

i hope he explains it...

he says architecture is an abstraction layer provided to the software through the hardware, its what the software thinks is the hardware so its like a fake machine for the programmers.. in the machine the ISA instruction space architecture 

so microarchetecture/organizations seems to be the specifics implementations of the computer

he says computer architecture is all about tradeoffs im not sure exactly what he means by that because he goes on to say that you can make big archetecture design decisions that will influence the microarchetecture but i dont understand how that is a tradeoff, i guess that "influence" is a bad one.. 
also its good to note that is a two way streak the design decisions you make down at the isa will also influence the big a archetecture

so in the ISA there are whats called execution semantics, i have no idea what the hell those are.. lets a finda outsa its the details, like say you have adding is taking two numbers putting them in a register thats not the whole picture there is more to it than that, ie io interrupts we have to say what happens when other shit happens

he says isa has to define how the inputs and the outputs work.. what the fuck does that mean? seems kinda vague to me.. if i ever go over this i need to investigate what he meant by this its 5:48 of some video

anyway ISA also defines the sizes of the data types you operate on, im guessing its like how a a char and a int8 are 1 byte and a int16 is 2 bytes? and and int is 4 bytes and a long is 8 bytes so basically 1 2 4 8 char short int and long, and ints in all of them represented in bits... hokay

hmm he seems to imply that the isa defines the interpertation of the data types which isnt what i thought, I thought that it was defined by.. well c guess not learn something new everyday

MicroArchetecture it does seem kinda dumb well cause it seems like the main purpose of the machine or the microArchitecture isnt to process data, but to service the programmer to make this faux computer.. it just smells like a lot of trouble waiting to happen but um lets move on 


it just seems to me like hardware seems to be made in service to the software.. which makes me uncomfortable, because then your making hardsoftware.. instead of just making hardware.. why cant they just make hardware, what would software look like if it were made for the hardware.. the actual hardware... hmmm

I dont know but what seems like a much more sane idea seems as if it would be to make hardware that processes data

so this ISA model started with IBM what happen was that IBM had like a bunch of computer lines, but you couldnt run the same software on one as you would on the other, so IBM decided to do was combine.. basically not that important they just wanted to simplify their line and they made it so they can change the actual imlementation details while they programed to the ISA important thing to note it was here when ibm decided that bytes should be 8 bits long before then people would call things bytes but they could be four bits 6 bits etc etc oh the name of the ISA was well let me take the full title IBM 360:  A general purpose register (GPR) machine

He says something about the binary coded decimal system but he trails off im not sure where he was going with that i dont know.. what he was going to say with that let me investigate okay it was called BCD its pretty simple but a little bit wasteful, the way it works is that you represent each decimal value with half a byte 0000 because its 8421 so what you have is say you want 32 you would write it like 0011 for the 3 and 0010 for the two and together you would have 00110010 and thats it thats bcd, I wonder how you represent decimal though well whatever

I wonder considering the speed of cpus wouldnt it be better to do math vertically?
well you already have this archetecture of cache right what if it acted like a waterfall, the computer never actually needs to know what its doing, so what if the memory is the only place that 

its interesting with the microarchitecture that was supporting the IBM 360 you have these two machines initially the model 30 and the model 70 for them to support it with vastly different archetecture they would do different things like the 30 had a 8 bit datapath while the 70 had a 64 bit while the 360 isa supported a 64 bit operation so the 30 had to do 8 of the 8 bit operations to support that.. interesting

ok lets just list some popular different ISA's man i really feel like i learned a ton i didnt even no what a mircoarchitecture was at the beginnning, or even how to spell it apparently, well there is the x86, Arm, powerpc, so really the takeaway is you cant run the same software on the different ISA's you know what this means but im just gonna say so yeah but of course you can have your own C implementation... which just seems to bring me to my original point, what the fuck is the point of it???!??!
// ok that was fun but mostly it was just saying and he did a tremendous job explaining the differences and the need for 

SUMMARY/TAKEAWAY for lesson one
yeah i really enjoyed that umm basically he just says well we have an ISA which is the instruction set architecture that is the big A or big architecture i have no idea why its considered to have the big A but this is the umbrella fake computer that your software runs on it defines what happens on this fake machine, and the fake machines constraints its the job of the microarchitecture to be the actual machine implementation and try to support the ISA, he talks about the history of ISA's the ISA was made by ofcourse IBM IBM had like a consumer suite a science suite and buisness whatever right but you had to write different softwares for each and you basically had to of made the damn thig to program the thing, unti lthe IBM 360 with that when they expanded they made the ISA he talks a bit about BCD  which is binary coded decimal i liked it i thought it was cool apparently it had some nice percision pretty easy you use 4 bits oh also this was when they codified byte to be 8 bits... solid anyway you use 4 bits to represent a digit 0-9 ooooohhhhhh kkkkkkkkdkdkdkdkdkdkdkdk what ya thinking jonathan so youd have something like 0100 0011 would be 43 and ofcourse you know the the drill its 8421 umm yeah that was most of it then he goes on to say you can have different microarchitecture with different ISA's and lists a few popular ones, arm x86 powerpc etc. if nothing else I learned how to spell Architecture hah.. nearly fucked that one up





which to me seems backwards but whatever I feel like it should be the computers job to i dunno just compute data not provide a platform to help the software, it just seems enabling to worse programmers and it makes hardware guys have to do heavy lifting for software guys, when it should be our job as the software guys to do heavy lifting, maybe there was a time when information wasnt as readily available but i think having at least a teir access to the 



ok he said were gonna start talking about machine models in that they are is what you need to build inside the ISA instruction set Architecture

ok he asks where to operands come from and where to they go? i think if im not mistaken its the registers and they get calculated in the ALU and back to main memory 

wow its kinda weird where you tune out cuz a lot of this stuff i easy i think he asks what type of instructions are allowed, it depends, the nes and what not could only do simple instructions im not even sure it could do multiplies, nowadays you have things that have... sin and cos? maybe 

haha i was wrong apparently you dont even have to have registers in your processor
he says you can use a stack instead, which im guessing just like a reguular stack in c does something similar?!?!?!????

oh so that makes sense instead of using a register what you can do is use a stack, you take the top two elements move em to the alu and operate on them from there.. its weird cuz i was under the impression thats what it did but that was the machine model.. but i dunno lets watch and find out

its so weird he just pops up a term and doesnt say anything else about it, i think i can do better all he really mentioned that one architecture is called an accumulator, where you have one named register and you have one in memory seems very similar to the way we do it, imma check up on the fish https://www.youtube.com/watch?v=Veas4VD5b54 this is more on the accumulator more the exact way its made which is kinda crazy 

soo.. it looks like what he's doing is just going through the different types of Architectures he is going in increasing in named registers there are ISA, so far we have the stack and the accumulator and next we have Register-Memory, where you name the source coming from memory and an operand coming from a register file, and also you can name the destination i wonder what a register file is lemme investigate so a register file, is multiple registers together used as a single unit. still hazy on that i dont get if that means multiple adders or is that a mix of adders subtractions and what not,  its the register register arch that has three named operands which is weird because the other one had two and an optional.. well whatever


ok something i really wanna note here is that you dont need just these four archetectures you can also have memory memory, something like the VAX architecture which was popular in the 70's so you could have all your operands
remember your operands are your variables

heh.. the Java virtual machine was stack based, thats interesting 
ok so remember the reverse polish thing.. its like a way of notating an equation, anyway its important for machines because you can put the operands in a stack there you go SHADAZI

he says the stack is part of the processor state, I havent the slightest

ok its something interesting he talks basically with the stack based architecture we have an issue of redundancy becuase youll need values that you can load if your limited by how many registers you have that means youll have to go out to main memory more, same problem different daze.. this is a ISA issue not a microarchitecture issue


one thousand percent right i think

ok so to summize really he just goes through the broad types of big A architecture in increasing register, the stack model while being the simpler model, has a problem when youre doing more and more complicated instructions, because it means that their maybe more potential reads to memory.. I honestly dont know how bad that really would be in use, if what youre reading from is the l1 cache, but there you are ummm.. 

decisions to i go the learning route or 


ok he's just gonna talk about other aspects of the ISA he then goes into details the instructions you have and we start off with classes of instructions 

the first class is Mov/Load operations
then arithmetic logic unit instructions
control flow instructios, branches logic whatnot
floating point instructions, add subtractions, weird i would of thought it would of been in the ALU

then there is SIMD operations

then he just shows a weird operation its REP MovsB an x86 instruction its a string operation copies part of a string into another i believe, then he just starts rambling about other weird complicated instructions like fast fourier transforms in one instruction

ok another thing ISA needs to consider is how to get memory, and what are the different addressing mode you can use, Im not sure what addressing mode means how you get operands from memory



// just wanna add a note hizeere
KUROSAWA - I always tell my people, "no matter how grueling things may be at first, you'll eventually start to enjoy it if you just keep at it. Once you reach that state, you'll be putting in a lot of effort without evening knowing it." And it's true. I might say "ok, that's good enough," but their response will be "just a second. . .one more thing" They're that immersed in their work. Conversely, if you let things slide thinking "well, this won't be in view of the camera," then there's no end to how lazy you can get. You either give it your all, or don't even bother.


 better to be off model and dynamic then on model and stiff, stiffness will kill your animation
 - Aaron Blaise

 the fewest strokes to express a fact - John Singer Sargent
 painting is a science
 which it was necessary to acquire in order to make of it an art -John Singer Sargent

  He never attempted to repaint one eye or to raise or
 lower it, for he held that the construction of a head prepared the place for the eye, and if it was wrongly placed, the understructure was wrong, and he ruthlessly scraped and repainted the head from the beginning

 TODO:: sonic note outlines are too thick on sonic i should thin them out


 ok what needs to be done is filling it moving around the fill ness and animating the fill ness, than bits and pieces like fill the inbetweens, undo, taking and splitting the bezier with less points connecting em

 problem is if i dont hustle instead of a few weeks project this could turn into a monstrocity, well so long as it's a working monstrocity 

 // I think the last hurdle, that is the last hurdle where im not really sure how difficult it may be is the filling thing, but even then its just because Im being a bit dumb and dont want it to do tasks of the cpu for no reason i dont know 




 so where are we right now I just finished a blueprint for the box fill, it just needs to play it do the xl xh global which are introduced  when you draw it and itll fake fill it, create a random spot in the middle as the xy probably 300 150 would work  and, oh I need to create the boxrefs and use them, hopefully i can get this done before the end of the night
 
 which means essentially im gonna draw the damn thing and then im gonna let loose with the code right after the release it puts this into motion 

  after that i tackle the triangle fill for each of the boxes its pretty simple really it should be actually the same as the line drawing algorithm but the bottom of it goes to the n/width of the refbox, hopefully i can get that done before the night is over, maybe im going slow cuz im not doing my usual binge coding method... i dunno anyway its gonna be interesting when i have to do planning and thats gonna suck hard for all the tedious bullshit


  so i figure i dont know whats wrong but something is up with the splitting so i need to go through and see where it goes wrong i will inspect it and then do something else 

  I wanna see if it one of these has the a list
  where would a list be 

  i think i must add it somewhere

  im looking to see where i added the thing there sould be a list of boxes or something like box ref

  glbDim? i dont know what that is is 

  found it boxRef
  // oh i may have left it 

  alright i found the fuck thats actually shape boxes 

  so where i am is i dont know where i put the boxes lemmelook through split bezier to find where i put them 

  fuck splitting up the bezier its a dumb unnessecary idea all i need is to split it where it is and do it at the point, the reason is i need to 

  ok im gonna re write the split just so its easier for me 

  heres what im gonna write im gonna tell it its percentage and a specific bezier and it returns a box, i lose terribly in performance but i gain utility i can use this anywhere and i never have to keep a box i just create the box when i need it... agai problem i need the boxes, creating the boxes every frame is silly, 

  umm im looking at the i2 and im confused what should be happeing is it should be taking the i okay so its taking the i

  okay im looking at what went down here and i cant get a good handle on the situattion ok there i am what should happen is that it should go through and then  take the ith bezier split it it and record it for the first one then for the second or subsquent split for each of th ii

  so i put it into bRef Old and now bRefOld i put this into the new one at the end Bref

  ok this right here just looks like it stuck in an infinie loop but does it even paint the goddamn thing at all? i dunno


  having trouble keeping my thoughts straight so what im thinking is im having a bit of trouble finding out how to stop the leak im at this point figured out where the leak was coming from but i dont know how to stop it and i hate hate hate hate hate gpu's i think what ill do is maybe switch it to direct3d and then use something else later or just use the original way to instead of using a vertex buffer, its overly complicated obtuse nonesense that bars me from something relatively straight forward... i hate it.. dunno if i mentioned that.


  so i guess ill just go on with the software renderer
  
  nope I fiured it out how awesome is that no more leaking, ok so now I just wanna put a thing that just waits 30 or so ibetween fills

  hey future me how is everything, you end raising that money, must of been tough with that money situation, kinda seems like you never get a moment to code or do anything even though youve set so much time aside, sure does suck to be you, well at least that stuff is behind you right? hope you didnt have any accidents or anything, and itd be super cool if you fixed the car i hope you did, teehee, anyway 
	
	as it goes the best i can explain it, it was working now its not, um what the problem is, I honestly have no idea, I was working on the collision boundary thing, which it seems to ignore completely I thought changing and limiting it may be good, instead it just broke it

	Jeez man I worked forever on this and it seems like I finally got something that works um i really wanna write down what went down but provided to say it was a comedy of errors around Appstate->shapeBoxes, shpBoxes, and looping in the static count thing, speaking of which I also added another static and i think one more one in the after i draw the first bezier one

	few problems, first it doesnt work sometimes, other is that it doesnt get inbetween to fill in boxes

	2 big problems seem to be taking place the first is that the box splitting doesnt seem to encompase the actual thing which is weird, dont know what to make of that i may rewrite the box fillin function just to be extra certain, the next is that when im filling with the boxes, the collision isnt working? which again seems odd because it works i think..



	TODO:::::: so i fucked with intersections after i found out how memcpy actually works and I have to see if that actually still works I have no idea so yeah fun times for all

	so here is what im thinking it seems like what I can do is a scan line approach but i can make it do a sort of scanline box kinda thing

	so then it makes scanline boxes and then on top of that I can make it fill a box in, I think this scanline box method may be better than the box fill, but the box fill has some other potential uses so ill kepp it around, 

	level of difficulty: not fully known i have to try it out, getting the basic thing working though i think i can pretty reasonably guess I should have that in one or two tries, its just a modified scan line

	the unknown comes into place when bezier curve bounding boxes intersect but even that shouldnt take more than two tries, 

	the last bit of dificulty is intersection points, but i think i may have tackle that on the line fill part of it, so im not gonna worry about it

	so its like c level difficulty, with possible b- grade.

	but to really bulletproof this it may be a grade difficulty so where gonna ignore a lot of problems for a while until we document it fully, or just so goddamn annoyed the thing

	then the next step is to tackle the line fill part which i think i have a sort of outline there where i already took a pass at it, I also need to add into the possibility that two of the the curve boxes intersect, if that is the case it should try and triangulate the the thing, maybe Ill do a clipped ear method, its pretty rare so i dont think it should matter that much and Ill even put it as a place holder

	actually ill just write some crappy version of it, like check where it would have lined up with and then just move the thing up to its intersection, based on the lines formed by it, I can just guess, and retriangulate the damn thing so they match, but ya knows not too important

	it types a little slow doesnt it? dasflkjdsha das;flkdsja ;aldkfj;

	thats b grade possible difficulty it might also be easy since i think i wrote it somewhere, so who knows 

	that's it.

	the next stuff is clean up beautification, thats like kerning thick and thins/pen pressure, and making a timeline and what not, adding importing and exporting images , then I gotta get it ready for presentation, undo, with degrading memory, and perfect memory where I go into flash and start locking down what I want the damn thing to look like, and feel like then after that I need to change the the filling and lines to be raster at points, its really honestly a test bed for a much more complicated system, but one I dont know how much of it is actually needed, and will deal with it as needed

	but yeah I think it wouldnt be bad to start a schedule nothing seems dire or requiring a lot of research from this point, except i have to change the cursor a bit, and use some fonts, that seems kinda scary, dealing with windows

	oof my crazy line layering system, 


	I dont know what microcoded archetecture but it seems to do with the problems with what happens when the processor is too large?

	I would think that is micro

	Im a little confused but he said if you have the problem where the processor is too large you can 

	Im confused primarly how well he says you can time multiplex the resource, instead of building a bunch of resources and connecting them together you 

	Im not sure when i got to the point wher e i could take notes just by typing them out like this but i definitely am there


	Im not to sure when i got to the point hwere I gcould just type out notes like this but i defintly am there

	so yeah its a good thing to be able to do definitely and will become useful?  when i want to start asigning tasks

 */