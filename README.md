# Line_Counter

## Project Description
Time complexity on my project is O(n^2) with space complexity O(1).

Purpose of this project is to mimic the functionality shown in 'cloc' terminal commmand which tabulates the files, blanks, comments and code lines in a specific file/directory. Thus I will be closely comparing functionality of my project with 'cloc' as a basis. I have also discovered issues present within the 'cloc' implementation according to my version ubuntu 22.04 using github.com/AlDanial/cloc which I will discuss later in issues section. This project is able to track CPP and ruby files.

The project seeks to do the same similar to cloc in this regard. The `project structure` is as follows:
```
Line_Counter/
 |
 |---src/
 |    |
 |    |---directory_processor.cpp   (Parse the Directory)
 |    |---directory_processor.h
 |    |---file_processor.cpp        (Parse the files)
 |    |---file_processor.h
 |    |---main.cpp                  (Print Report + Call Functions)
 |    |---utils.cpp                 (To place all utility functions)
 |    |---utils.h
 |
 |---include/
 |    |
 |    |---line_counts.h             (Store my structs)
 |
 |---report/
 |    |
 |    |---report.txt                (Where report of the path/file is stored)
 |
 |---.gitignore
 |
 |---manager.sh                     (Store commands for compilation/builds)
```

**This project is done by sticking to a more functional programming style rather than Object Oriented Programming (OOP) more as test to myself. There is still a struct typical of C++, but it is mostly functions.**

## Specifications

### Windows Subsystem for Linux(WSL) or Vbox Ubuntu 22.04 distro (Recommended)
`This project is done in wsl`, ideally, any system with the relevant C libraries and can use bash script can run this file. 

### If none of the above, then install docker
This project can be run in docker as well. If you are on windows system please refer to the docker website for [installation](https://docs.docker.com/desktop/install/windows-install/).

## WSL how to run without docker

1) Ensure you are able to run bash files in your system and have given the relevant access to it:
```
chmod +X ./manager.sh
```
2) Now run it:
```
./manager.sh run <path/from/current/directory/to/target/directory/or/file>
```

This will auto clean, build and run the project everytime it is run for smooth usage. `manager.sh` also can be run in its isolated parts as well:

1) To build the project
```
./manager.sh build
```
2) To clean the project of binary/obj files
```
./manager.sh clean
```
3) If wish to run the .exe file directly, I have stored it in the bin/ folder
```
./bin/line_counter.exe <path/from/current/directory/to/target/directory/or/file>
```
## Run with docker

1) Copy paste folder in zip into folder of choice. Enter the folder.
```
# Copy paste the repository if in zip to the folder of choice.
cd Line_Counter/

# git clone it but it is not public or given access via collaboraters tag in settings
```

2) Build the image
```
docker build -t line_counter_image .
```

3) Run the image after it finishes building (depends on OS the command might be different)

`WSL/Virtualbox Ubuntu 22.04 distro `
```
docker run --rm -v "$(pwd)":/app -w /app line_counter_image /app/manager.sh run <path/to/destination>
```

`Windows:`
```
docker run --rm -v "%cd%:/app" -w /app line_counter_image /app/manager.sh run <path/to/destination>
```

**Note that the path is the path from the user's current terminal directory to the target directory/file.**

## Output

The output from Line_Counter that is expected is similar to that of cloc's output.

e.g. Cloc Output:
```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             11            311             22           1547
C/C++ Header                    11             71              0            396
-------------------------------------------------------------------------------
SUM:                            22            382             22           1943
-------------------------------------------------------------------------------
```

e.g. Line_Counter Output

1) Running the project to the Hacks Directory

![Sample Image](images/picture1.png)

2) View report.txt in folder ./report to see results
```
./test-libs/Osiris/Hacks/
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
    11    1880    1547        22     311
-------------------------------------------------------------------------------
```

3) (optional) Can also be run against the .cpp/.cc/.c file as well
```
./test-libs/Osiris/Hacks/Aimbot.cpp
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
     1     210     166         0      44
-------------------------------------------------------------------------------
```

There is no cpp header count for this project. I only calculated: (.cpp, .cc, .c, .rb, .rake) and 
the only file I let throught was the Rakefile.

## Results

For Osiris CPP file
```
./test-libs/Osiris/
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
    30   38430   30450      3971    4009
-------------------------------------------------------------------------------
```

For lib3 ruby file
```
./test-libs/lib 3//
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
  1501  297430  216886     46570   33974
-------------------------------------------------------------------------------
```

## Design Choices

- Chose C++ for this project because of speed purposesm, especially since lib3 has >1000 ruby files
- I used regex search due to speed as well. For line based searches, especially since I want to handle multiple cases with a single expression, I resorted to this. Later when multiline block comments with `specific edge cases` popped up, I had to resort to the traditional if-else and .find() methods.
- Chose to place the .h files in src instead of include as I think that main functionality should all be placed in src even h files, stuff like the line_counts.h in /include folder is a struct thus I think it should be put there.
- Even if the codeline ended up like this: `} // Example comment insert here`, I still resolved it as a code line.
- 

## Issues discovered in cloc when doing comparisons with my own implementation

### File parsing issue with cloc

Over the course of this project, I have noticed some discrepancies with my implementation compared to cloc, namely the file parsing might be wrong for cloc's.

These are the filepaths for the test-libs Osiris folder as test cases:
```
File path: ./test-libs/Osiris/Hooks.cpp
File path: ./test-libs/Osiris/Interfaces.cpp
File path: ./test-libs/Osiris/Memory.cpp
File path: ./test-libs/Osiris/nSkinz/item_definitions.cpp
File path: ./test-libs/Osiris/nSkinz/Utilities/Platform.cpp
File path: ./test-libs/Osiris/nSkinz/config_.cpp
File path: ./test-libs/Osiris/imgui/stripped.cpp
File path: ./test-libs/Osiris/imgui/imgui_widgets.cpp
File path: ./test-libs/Osiris/imgui/imgui.cpp
File path: ./test-libs/Osiris/imgui/imgui_draw.cpp
File path: ./test-libs/Osiris/imgui/imgui_impl_dx9.cpp
File path: ./test-libs/Osiris/imgui/imgui_impl_win32.cpp
File path: ./test-libs/Osiris/imgui/imgui_demo.cpp
File path: ./test-libs/Osiris/Hacks/Reportbot.cpp
File path: ./test-libs/Osiris/Hacks/SkinChanger.cpp
File path: ./test-libs/Osiris/Hacks/AntiAim.cpp
File path: ./test-libs/Osiris/Hacks/Aimbot.cpp
File path: ./test-libs/Osiris/Hacks/Glow.cpp
File path: ./test-libs/Osiris/Hacks/Visuals.cpp
File path: ./test-libs/Osiris/Hacks/Chams.cpp
File path: ./test-libs/Osiris/Hacks/Triggerbot.cpp
File path: ./test-libs/Osiris/Hacks/Backtrack.cpp
File path: ./test-libs/Osiris/Hacks/Esp.cpp
File path: ./test-libs/Osiris/Hacks/Misc.cpp
File path: ./test-libs/Osiris/Netvars.cpp
File path: ./test-libs/Osiris/Config.cpp
File path: ./test-libs/Osiris/SDK/GlobalVars.cpp
File path: ./test-libs/Osiris/Osiris.cpp
File path: ./test-libs/Osiris/jsoncpp.cpp
File path: ./test-libs/Osiris/GUI.cpp
```

According to my implementation it is thus 30 files as seen above and below, tallied up correctly with me physically checking said folder
from the files around 28 times as well:
```
./test-libs/Osiris/
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
    30   38430   30450      3971    4009
-------------------------------------------------------------------------------
```

And yet cloc itself didn't detect one of them:
```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             29           4009           3978          30443
C/C++ Header                    73           2110           3511          11370
XML                              2              0              0            619
-------------------------------------------------------------------------------
SUM:                           104           6119           7489          42432
-------------------------------------------------------------------------------
```

### Cloc does not catch mutliline comments in string literals

As can be seen above, when checking the folder there is a difference of code and comments between my implementation and cloc's, 30450 vs 30443 and 3971 vs 3978.

Cloc implementation:
```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             29           4009           3978          30443
```
My implementation:
```
./test-libs/Osiris/
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
    30   38430   30450      3971    4009
-------------------------------------------------------------------------------
```

I have tested it out and there are issues in the cloc implementation, that being if a multiline comment is caught in a string literal,
it is not counted as a string, but a comment.

Take the example below (sample from imgui_demo.cpp line 966, if line number changed feel free to search):
```

static char text[1024 * 16] =
    "/*\n"
    " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
    " the hexadecimal encoding of one offending instruction,\n"
    " more formally, the invalid operand with locked CMPXCHG8B\n"
    " instruction bug, is a design flaw in the majority of\n"
    " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
    " processors (all in the P5 microarchitecture).\n"
    "*/\n\n"
```

From here it can be seen that these are 9 lines of code, as it is all within a string. However this was the result of cloc after I isolated the code block
from the imgui_demo file:
```
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                              1              1              7              2
-------------------------------------------------------------------------------
```
The next set of data is my implementation:
```
-------------------------------------------------------------------------------
 Files   Lines    Code  Comments  Blanks
-------------------------------------------------------------------------------
     1      10       9         0       1
-------------------------------------------------------------------------------
```
Moreover from the above implementation, it can even be seen that one of the comments implemented in cloc bled into the code section. This is because cloc
considers either the `"/*\n"` or the `"*/\n\n"` lines as code. When one of them is removed the other is immediately considered a code block and the rest
converted to comments.

To my understanding there are different implementations of cloc within github.com/AlDanial/cloc works depending on the language involved in its development. I have also not tested this across other OS's as well, perhaps the implementation varies on the OS as well. However as of ubuntu 22.04 github.com/AlDanial/cloc version seems to have an error with comments in string literals for C++.

## Conclusions and Improvements

There are some issues on my end too, in terms of speed compared to cloc, it is much slower when there are more than 100 files. 7-12 seconds slower when it came to parsing the CPP folder and approx. 29-33 seconds slower for the ruby implementation as it has >1500 files excudling non ruby related files. Perhaps spawning threads when calculating the directory could be a method of improvement, concurrency would however be another issue as they would all be writing to the same memory address where I stored my initial count in struct counts. `Race Condition` will most certainly occur if I am not careful. 