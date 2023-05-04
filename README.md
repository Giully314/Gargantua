# Gargantua
A 2d game engine under development.



# Project structure and directories
## Gargantua
app: Base class application.  
core: Core components of the engine.    
datastructure: personal implementation of data structures.  
log: Basic logging system.  
math: Vector and Matrices definitions (2d, 3d, 4d). Various math utility functions.  
render: Low level components for handling render objects.    
time: Handling time.  
mpl: meta programming library.  



# TODO
https://trello.com/b/c2i4BD7O/gargantua



# Language 
The project is based on C++20.


# Personal considerations
This is my first real project in C++ and my first engine. I'm developing this engine because i find really 
interesting how simulations are created. I also want start to develop a game based on pixel simulation.  
I minimized the usage of external libraries because i find really funny to design and develop the core functionalities.
At first i also wanted to avoid the usage of glfw (and even of opengl, after i followed the beautiful project tinyrenderer)
but then i realized that the focus of the project would shift too much. 
In the end, i hope to learn as much as possible and become better at design and develop software!  


# Resource that i found useful

## Other engines 
TheCerno game engine series.  
Godot engine source code.  
Spring RTS source code.  
Ogre engine source code.  
https://github.com/cocos-creator/engine-native  


## Books
Large scale C++ volume 1 by John Lakos.
Game engine architecture by Jason Gregory.  
Game Physics by David H. Eberly.  
Real-time collision detection by Christer Ericson.  
Mathematics for 3D Game Programming and Computer Graphics.  



## Conferences and articles
Input:  
https://sites.psu.edu/ist446/2015/04/16/so-you-want-to-make-a-game-engine-part-6-input-need-input/


About engines:  
https://www.gamedeveloper.com/programming/writing-a-game-engine-from-scratch---part-1-messaging  
https://ourmachinery.com/post/   


Memory management: https://gist.github.com/simonrenger/d1da2a10d11f8a971fc6f1b574ab3e99  


Talk about task oriented multi threading: 
https://www.gdcvault.com/play/1022186/Parallelizing-the-Naughty-Dog-Engine  
https://www.gdcvault.com/play/1012189/Don-t-Dread  
https://vkguide.dev/docs/extra-chapter/multithreading/ (useful additional resources)  
GCAP 2016: Parallel Game Engine Design - Brooke Hodgman: https://www.youtube.com/watch?v=JpmK0zu4Mts   
CppCon 2016: Jason Jurecka “Game engine using STD C++ 11": https://youtu.be/8AjRD6mU96s   


Physics:  
https://gafferongames.com/categories/game-physics/  
https://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715  



STD containers, custom containers and iterators:  
https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp   
Mathieu Ropert “This Videogame Programmer Used the STL and You Will Never Guess What Happened Next”: https://youtu.be/6hC9IxqdDDw   


Graphics:
How 3D video games do graphics: https://www.youtube.com/watch?v=bGe-d09Nc_M  
https://github.com/ssloy/tinyrenderer   
https://www.scratchapixel.com/
