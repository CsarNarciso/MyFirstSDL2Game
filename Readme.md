Steps to set up SDL2 in windows without Visual Studio

Download Mingw64 for windows version W64 builds posix seh ucrt rt
Add mingw bin folder to path and now you can use gcc command as c++ compiler in cmd
Download SDL2 mingw64 version
Download SDL2 mingw64 image
Copy include, lib and bin folders from sdl2 image dir to normal sdl2 folder (it contains also these three folders, so add the contents from the image to the normal version)
Create your project folder, inside, copy sdl2 lib folder to it in the root
Create include dir in your project root dir and inside create sdl folder, inside, copy everything inside sdl2/include/SDL2
now, in your root, paste all .dll files from sdl2 bin folder
in the root create src folder and place there your main.cpp files, or in general your .cpp files
and finally create in the root a Makefile with this content: 

all:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

and that's it, now you can just compile your program with mingw32-make -f Makefile to create a .exe
then just run main.exe to open your program
