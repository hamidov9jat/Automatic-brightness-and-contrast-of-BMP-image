# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/dsa_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dsa_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dsa_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dsa_project.dir/flags.make

CMakeFiles/dsa_project.dir/main.c.obj: CMakeFiles/dsa_project.dir/flags.make
CMakeFiles/dsa_project.dir/main.c.obj: ../main.c
CMakeFiles/dsa_project.dir/main.c.obj: CMakeFiles/dsa_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dsa_project.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dsa_project.dir/main.c.obj -MF CMakeFiles\dsa_project.dir\main.c.obj.d -o CMakeFiles\dsa_project.dir\main.c.obj -c "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\main.c"

CMakeFiles/dsa_project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dsa_project.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\main.c" > CMakeFiles\dsa_project.dir\main.c.i

CMakeFiles/dsa_project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dsa_project.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\main.c" -o CMakeFiles\dsa_project.dir\main.c.s

CMakeFiles/dsa_project.dir/bmp.c.obj: CMakeFiles/dsa_project.dir/flags.make
CMakeFiles/dsa_project.dir/bmp.c.obj: ../bmp.c
CMakeFiles/dsa_project.dir/bmp.c.obj: CMakeFiles/dsa_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/dsa_project.dir/bmp.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/dsa_project.dir/bmp.c.obj -MF CMakeFiles\dsa_project.dir\bmp.c.obj.d -o CMakeFiles\dsa_project.dir\bmp.c.obj -c "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\bmp.c"

CMakeFiles/dsa_project.dir/bmp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dsa_project.dir/bmp.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\bmp.c" > CMakeFiles\dsa_project.dir\bmp.c.i

CMakeFiles/dsa_project.dir/bmp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dsa_project.dir/bmp.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\bmp.c" -o CMakeFiles\dsa_project.dir\bmp.c.s

# Object files for target dsa_project
dsa_project_OBJECTS = \
"CMakeFiles/dsa_project.dir/main.c.obj" \
"CMakeFiles/dsa_project.dir/bmp.c.obj"

# External object files for target dsa_project
dsa_project_EXTERNAL_OBJECTS =

dsa_project.exe: CMakeFiles/dsa_project.dir/main.c.obj
dsa_project.exe: CMakeFiles/dsa_project.dir/bmp.c.obj
dsa_project.exe: CMakeFiles/dsa_project.dir/build.make
dsa_project.exe: CMakeFiles/dsa_project.dir/linklibs.rsp
dsa_project.exe: CMakeFiles/dsa_project.dir/objects1.rsp
dsa_project.exe: CMakeFiles/dsa_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable dsa_project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\dsa_project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dsa_project.dir/build: dsa_project.exe
.PHONY : CMakeFiles/dsa_project.dir/build

CMakeFiles/dsa_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\dsa_project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/dsa_project.dir/clean

CMakeFiles/dsa_project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image" "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image" "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug" "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug" "C:\Users\User\Documents\Other\dsa L2\Automatic-brightness-and-contrast-of-BMP-image\cmake-build-debug\CMakeFiles\dsa_project.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/dsa_project.dir/depend
