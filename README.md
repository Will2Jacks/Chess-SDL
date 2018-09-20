# Chess-SDL

A simple Test Driven Chess implementation my group and I made for an university project.
We used the Catch test framework, SDL2 and C++.
The original project is here: https://github.com/rodrigo-xavier/Xadrez

**Some Goals for this fork**

* Fixing some minor interface things like the buggy mouse hover at the color selection and make it possible to pause at that screen;
* Improving the implementation itself. The GUI code is a mess right now, but it's working!
* Matching the actual check and check mate rules. (You still can't avoid a check mate by protecting the king with another piece for instance)
* Giving an actual minmax style tree inteligence;
* board and piece skin selection feature;
* More options for edit mode
* Translate the comments to English (They are in portuguese right now)
* Cross-platform, windows on this fork but maybe I'll create a new repo for an android implementation;

**The files are organized this way:**

*	docs -> some gcov and doxygen stuff that was used.
*	include-> header files
*	obj-> object files
*	src-> main, makefile and source codes
*   tests-> where the tests were written

-----------

**Requirements:**
	
* Any linux distribution you can install SDL libraries
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
* you can compile and run the tests located at tests/Test_main by typing "make test". The executable is generated at the top directory.

**makefile commands:**
	
	make		 -	Compile the project
    make test    -  compile the test
	make project -  run the project
	make gcov	 -	create gcov reports in docs
	make clean	 -	clean object and executable files
	make all	 -	compile, create test and run
	
**Ingame commands:**

* h -> show help (what are the possible positions for the selected piece)
* b -> best movement (there's no possible moves tree yet so it's not quite accurate)

On Edit mode:

* left and right -> select the piece
* up and down -> select the color
* click -> place the piece.
* d -> done, start a pvp mode after editing the piece positions
    
-----------
Board and pieces assets taken from https://www.behance.net/gallery/10018309/Chess-Artwork-Pieces-and-Board-Art-Assets 
