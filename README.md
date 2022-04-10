# Gargantua
A 2d game engine under development.


# Project structure and directories
Concepts: files for the definition of various concepts. 
Core: Core component abstractions of the engine. 
DataStructures: Personal implementation of datastructures. 
Event: Basic building blocks for handling events. 
Generators: Number generators. 
Input: Low level input state. 
Log: Basic logging system. 
Math: Vector and Matrices definitions (2d, 3d, 4d). Various math utility functions. 
Parallel: Components for parallel code. Only prototypes and various ideas. (Not for use yet) 
Renderer: Low level components for handling renderer objects. 
Streams: Input and output streams. 
Systems: Important directory that contains the systems that allows the engine to function. 
Time: Handling time. 


# Language 
The project is based on C++20.
I wanted to use modules but they are impossible to use even in visual studio :(. Too much bugs and cryptic errors when i started the project.
Since the beginning i was planning to use only opengl and glfw so most of the class are not abstract (for the API definition); the only platform supported is 
Windows with opengl and glfw. 


# Personal considerations
This is my first real project in C++ and my first engine.


# Resource that i found useful
TheCerno game engine series.  
Godot engine source code.  
Spring RTS source code.  
Ogre engine source code.  
https://github.com/cocos-creator/engine-native  


## Books
Large scale C++ volume 1 by John Lakos.
Game engine architecture by Jason Gregory.  

## Conferences and articles
Input:  
https://sites.psu.edu/ist446/2015/04/16/so-you-want-to-make-a-game-engine-part-6-input-need-input/

https://ourmachinery.com/post/   
https://www.gamedeveloper.com/programming/writing-a-game-engine-from-scratch---part-1-messaging  


Memory management: https://gist.github.com/simonrenger/d1da2a10d11f8a971fc6f1b574ab3e99  

Talk about task oriented multi threading: 
https://www.gdcvault.com/play/1022186/Parallelizing-the-Naughty-Dog-Engine  
https://www.gdcvault.com/play/1012189/Don-t-Dread  
https://vkguide.dev/docs/extra-chapter/multithreading/ (useful additional resources)  
GCAP 2016: Parallel Game Engine Design - Brooke Hodgman: https://www.youtube.com/watch?v=JpmK0zu4Mts   
CppCon 2016: Jason Jurecka “Game engine using STD C++ 11": https://youtu.be/8AjRD6mU96s   



https://gafferongames.com/categories/game-physics/  

Mathieu Ropert “This Videogame Programmer Used the STL and You Will Never Guess What Happened Next”: https://youtu.be/6hC9IxqdDDw   

Custom Containers and iterators:
https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp   


Graphics:
How 3D video games do graphics: https://www.youtube.com/watch?v=bGe-d09Nc_M  
https://github.com/ssloy/tinyrenderer   
