# WI
A C++ Vector Animation Program, Utilizing traditional Animation principles to help double their output, and achieve frame-rate Independence



I think one notable feature is that it doesn't use any third party libraries, its built pretty much completely from scratch minus STB image
importer. I honestly think it's just easier that way.

Nothing too out of the box thinking with anything, except the features themselves. In other words if you see it running it's more that's 
an interesting approach at the problem, rather than how did he do that.

WI came about because I was playing around in programs like flash and toon boom in this interesting way, where it
sounds obvious when you say it, but vector programs arent set up to utilize it. Traditionally when you animate animators animate the lines of a character, 
and then fill it after, where in vector animation programs generally utilize OOP so it's designed so that you create body parts first fill them, then move the 
pieces around after, but in traditional animation a line that used to be a nose, can be inbetweened to be the side of a face. it's pretty straight forward drawn
traditionally, but when you animate in a flash way you have to start dealing with layers hiding one behind another, and you're creating a huge puppeted rig for
the most probable positions.. so you end up loosing the exact solution for an almost solution, hence most flash animations. Granted there are some excellent flash
animation, but they are notably rare. 


WI takes a novel yet, oddly traditional approach. when you look at the most problematic parts of animation, animation contrary to popular belief actually doesnt take that long, It's
actually clean-up and inbetweening that are actually what take a long time a rough animation can a lot of time be made in less than an hour. which is on average considerably quicker
than a flash animator, So all WI does really is animate line to line.. for the most part, that's it. So the question becomes, why not use flash, doesnt flash do this
yes it does, but since flash isnt built for this in mind it goes really really slow, at about an unusable frame a second. also flash tools you have to use to maintain the lines orientation
have to be created in javascript, it slows down the system even more. and then if you want to fill in the shapes flash becomes comepletely unusable, and since now your operating at like sixty
frames a second, when you have intersections, it starts becoming a nightmare awfully quick, and it doesnt help you at all. But WI is built with those considerations straight out of the box, it's
optimized for the way it should be used. it leaves the artist with something extremely easy with little to no learning curve but a ton of benefits, that become apparent as soon as you start using it

-HOW DOES IT WORK? well all an animator has to do, is draw to frames and the program animates between them. the program can figure out where a bunch of the lines will go but its a good
idea to tell it manually by constantly flipping, between the keys, which is something that animators already do. Now at this point I would have been perfectly happy with an application that just would simply
automatically tween between frames, great.. but we get some unintentional benifits because of what we have done, first, despite you just doing two keys, most of the time your third key isnt that much a departure
from two of your keys, and since you've set up a tween already, you can just copy any one of the miriad of frames you've generated to make a third image, erase and replace the parts that are necessary, to make a fourth
and a fifth key, so that you can do upwards of 10 keys in the time it would have taken you to make 4, whats more everything is editable so these frames could all be rough, so as long as the rough animates, when you
erase it and clean it up, it can look incredible. so Now traditional animators can animate things at like an absurd 60 frames or 120 frames per second, while still maintaining that handmade look and feel.
now at this point when I realized this I was beside myself, it was amazing, but I thought still I have to color all these frames, that could take forever. And subsequently made yet another realization. I've told 
the system which lines are which, so if I color one frame and my system is aware which lines it fills, it knows which other lines it corresponds with meaning, I can effectively fill just a few key frames and have it
fully colored And thats when I thought it had to be done.
