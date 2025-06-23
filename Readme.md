Steps to set up SDL2 in both windows and linux without IDES!

-----
for Windows

Download Mingw64 for windows version W64 builds posix seh ucrt rt
Add mingw bin folder to path and now you can use gcc command as c++ compiler in cmd
Download SDL2 mingw64 version
Download SDL2 mingw64 image
Copy include, lib and bin folders from sdl2 image dir to normal sdl2 folder (it contains also these three folders, so add the contents from the image to the normal version)
Create your project folder, inside, copy sdl2 lib folder to it in the root
Create include dir in your project root dir and inside create sdl2 folder, inside, copy everything inside sdl2/include/SDL2
now, in your root, paste all .dll files from sdl2 bin folder
in the root create src folder and place there your main.cpp files, or in general your .cpp files
and finally create in the root a Makefile with the content in this repo makefile file (it is crossplatfform support for linux and windows!) 
and that's it, now you can just compile your program with mingw32-make -f Makefile to create a .exe
then just run main.exe or "output\main.exe" to open your program

-----
for linux is actually easier...

just install: sudo apt install build-essentials (for c++, gcc, make) libsdl2-dev libsdl2-image-dev

Create your project folder, and inside create src subdir and place there your main.cpp file (or in general your .cpp files)
And finally create in the root a Makefile with the content of this repo makefile file

and since makefile is crossplatform, just compile with: make -f Makefile
and run your executable with: ./main (executable name)


Now, in your code, to include SDL2, just call it like: #include <SDL2/SDL2.h>
And this works fine for both plattforms since in linux, by default, this is the location of SDL2, and as you called the subfolder inside your project iclude dir like sdl2, then, it refers to the same!

-----
NOTE

you can change your executable program name, your cpp files directory (src) and the path for lib and include sdl2 files (for windows) in the Makefile.
If you, for example, in windows, want to move the executable path to (root dir)/output/main then set path as output/main and (IMPORTANT) move the two .dll files from your too dir to this new folder where your executable will be palced (it needs the two .dll files to run!)