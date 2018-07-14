# Chess-SDL

A simple Test driven Chess implementation my group and I made for an university project.
We used the Catch test framework, SDL2 and C++.
The original project is here: https://github.com/rodrigo-xavier/Xadrez

**Some Goals for this fork**

* Fixing some minor aspects of the interface like the buggy mouse hover in the color selection;
* Improving the implementation itself. The GUI code is a mess right now, but it's working!
* board and piece skin selection feature;
* Giving an actual minmax style tree inteligence;
* Translate the comments to English (They are in portuguese right now)
* Cross-platform;

**The files are organized this way:**

*	docs -> some gcov and doxygen stuff that was used.
*	include-> header files
*	obj-> object files
*	src-> main, makefile and source codes
*   tests-> where the tests were written

-----------

**Requirements:**
	
* Any linux distro you can install SDL libraries
* C++
* g++
* make
* SDL2
* SDL2-IMAGE
 
Check the correct package name of the SDL libraries. On Debian based distros that's libsdl2-dev and libsdl2-image-dev. On arch based distros the packages are: sdl2 and sdl2_image.

**Compile and run**
	
* go to the src directory.
* make
* make project (or just run ./Project)
* you can compile and run the tests in tests/Test_main typing "make test". The executable is generated at the top directory.

**makefile commands:**
	
	make		 -	Compile the project
    make test    -  compile the test
	make project -  run the project
	make gcov	 -	create gcov reports in docs
	make clean	 -	clean object and executable files
	make all	 -	compile, create test and run
    
-----------
** Board and pieces assets were taken from https://www.behance.net/gallery/10018309/Chess-Artwork-Pieces-and-Board-Art-Assets **
