# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wtv/university/CG/CG1920/engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wtv/university/CG/CG1920/demos

# Include any dependencies generated for this target.
include CMakeFiles/engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/engine.dir/flags.make

CMakeFiles/engine.dir/main.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/main.cpp.o: /home/wtv/university/CG/CG1920/engine/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/engine.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/main.cpp.o -c /home/wtv/university/CG/CG1920/engine/main.cpp

CMakeFiles/engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/main.cpp > CMakeFiles/engine.dir/main.cpp.i

CMakeFiles/engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/main.cpp -o CMakeFiles/engine.dir/main.cpp.s

CMakeFiles/engine.dir/structs/transformation.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/structs/transformation.cpp.o: /home/wtv/university/CG/CG1920/engine/structs/transformation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/engine.dir/structs/transformation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/structs/transformation.cpp.o -c /home/wtv/university/CG/CG1920/engine/structs/transformation.cpp

CMakeFiles/engine.dir/structs/transformation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/structs/transformation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/structs/transformation.cpp > CMakeFiles/engine.dir/structs/transformation.cpp.i

CMakeFiles/engine.dir/structs/transformation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/structs/transformation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/structs/transformation.cpp -o CMakeFiles/engine.dir/structs/transformation.cpp.s

CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o: /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o -c /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxml.cpp

CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxml.cpp > CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.i

CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxml.cpp -o CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.s

CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o: /home/wtv/university/CG/CG1920/engine/tinyxml/tinystr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o -c /home/wtv/university/CG/CG1920/engine/tinyxml/tinystr.cpp

CMakeFiles/engine.dir/tinyxml/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/tinyxml/tinystr.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/tinyxml/tinystr.cpp > CMakeFiles/engine.dir/tinyxml/tinystr.cpp.i

CMakeFiles/engine.dir/tinyxml/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/tinyxml/tinystr.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/tinyxml/tinystr.cpp -o CMakeFiles/engine.dir/tinyxml/tinystr.cpp.s

CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o: /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlerror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o -c /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlerror.cpp

CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlerror.cpp > CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.i

CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlerror.cpp -o CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.s

CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o: /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o -c /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlparser.cpp

CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlparser.cpp > CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.i

CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/tinyxml/tinyxmlparser.cpp -o CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.s

CMakeFiles/engine.dir/structs/group.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/structs/group.cpp.o: /home/wtv/university/CG/CG1920/engine/structs/group.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/engine.dir/structs/group.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/structs/group.cpp.o -c /home/wtv/university/CG/CG1920/engine/structs/group.cpp

CMakeFiles/engine.dir/structs/group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/structs/group.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/structs/group.cpp > CMakeFiles/engine.dir/structs/group.cpp.i

CMakeFiles/engine.dir/structs/group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/structs/group.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/structs/group.cpp -o CMakeFiles/engine.dir/structs/group.cpp.s

CMakeFiles/engine.dir/structs/model.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/structs/model.cpp.o: /home/wtv/university/CG/CG1920/engine/structs/model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/engine.dir/structs/model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/structs/model.cpp.o -c /home/wtv/university/CG/CG1920/engine/structs/model.cpp

CMakeFiles/engine.dir/structs/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/structs/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/structs/model.cpp > CMakeFiles/engine.dir/structs/model.cpp.i

CMakeFiles/engine.dir/structs/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/structs/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/structs/model.cpp -o CMakeFiles/engine.dir/structs/model.cpp.s

CMakeFiles/engine.dir/structs/catmull.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/structs/catmull.cpp.o: /home/wtv/university/CG/CG1920/engine/structs/catmull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/engine.dir/structs/catmull.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/structs/catmull.cpp.o -c /home/wtv/university/CG/CG1920/engine/structs/catmull.cpp

CMakeFiles/engine.dir/structs/catmull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/structs/catmull.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/structs/catmull.cpp > CMakeFiles/engine.dir/structs/catmull.cpp.i

CMakeFiles/engine.dir/structs/catmull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/structs/catmull.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/structs/catmull.cpp -o CMakeFiles/engine.dir/structs/catmull.cpp.s

CMakeFiles/engine.dir/mouse/mouse.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/mouse/mouse.cpp.o: /home/wtv/university/CG/CG1920/engine/mouse/mouse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/engine.dir/mouse/mouse.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/mouse/mouse.cpp.o -c /home/wtv/university/CG/CG1920/engine/mouse/mouse.cpp

CMakeFiles/engine.dir/mouse/mouse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/mouse/mouse.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/mouse/mouse.cpp > CMakeFiles/engine.dir/mouse/mouse.cpp.i

CMakeFiles/engine.dir/mouse/mouse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/mouse/mouse.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/mouse/mouse.cpp -o CMakeFiles/engine.dir/mouse/mouse.cpp.s

CMakeFiles/engine.dir/structs/light.cpp.o: CMakeFiles/engine.dir/flags.make
CMakeFiles/engine.dir/structs/light.cpp.o: /home/wtv/university/CG/CG1920/engine/structs/light.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/engine.dir/structs/light.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/engine.dir/structs/light.cpp.o -c /home/wtv/university/CG/CG1920/engine/structs/light.cpp

CMakeFiles/engine.dir/structs/light.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/engine.dir/structs/light.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wtv/university/CG/CG1920/engine/structs/light.cpp > CMakeFiles/engine.dir/structs/light.cpp.i

CMakeFiles/engine.dir/structs/light.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/engine.dir/structs/light.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wtv/university/CG/CG1920/engine/structs/light.cpp -o CMakeFiles/engine.dir/structs/light.cpp.s

# Object files for target engine
engine_OBJECTS = \
"CMakeFiles/engine.dir/main.cpp.o" \
"CMakeFiles/engine.dir/structs/transformation.cpp.o" \
"CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o" \
"CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o" \
"CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o" \
"CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o" \
"CMakeFiles/engine.dir/structs/group.cpp.o" \
"CMakeFiles/engine.dir/structs/model.cpp.o" \
"CMakeFiles/engine.dir/structs/catmull.cpp.o" \
"CMakeFiles/engine.dir/mouse/mouse.cpp.o" \
"CMakeFiles/engine.dir/structs/light.cpp.o"

# External object files for target engine
engine_EXTERNAL_OBJECTS =

engine: CMakeFiles/engine.dir/main.cpp.o
engine: CMakeFiles/engine.dir/structs/transformation.cpp.o
engine: CMakeFiles/engine.dir/tinyxml/tinyxml.cpp.o
engine: CMakeFiles/engine.dir/tinyxml/tinystr.cpp.o
engine: CMakeFiles/engine.dir/tinyxml/tinyxmlerror.cpp.o
engine: CMakeFiles/engine.dir/tinyxml/tinyxmlparser.cpp.o
engine: CMakeFiles/engine.dir/structs/group.cpp.o
engine: CMakeFiles/engine.dir/structs/model.cpp.o
engine: CMakeFiles/engine.dir/structs/catmull.cpp.o
engine: CMakeFiles/engine.dir/mouse/mouse.cpp.o
engine: CMakeFiles/engine.dir/structs/light.cpp.o
engine: CMakeFiles/engine.dir/build.make
engine: /usr/lib/x86_64-linux-gnu/libGL.so
engine: /usr/lib/x86_64-linux-gnu/libGLU.so
engine: /usr/lib/x86_64-linux-gnu/libglut.so
engine: /usr/lib/x86_64-linux-gnu/libGLEW.so
engine: /usr/lib/x86_64-linux-gnu/libIL.so
engine: CMakeFiles/engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wtv/university/CG/CG1920/demos/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/engine.dir/build: engine

.PHONY : CMakeFiles/engine.dir/build

CMakeFiles/engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/engine.dir/clean

CMakeFiles/engine.dir/depend:
	cd /home/wtv/university/CG/CG1920/demos && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wtv/university/CG/CG1920/engine /home/wtv/university/CG/CG1920/engine /home/wtv/university/CG/CG1920/demos /home/wtv/university/CG/CG1920/demos /home/wtv/university/CG/CG1920/demos/CMakeFiles/engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/engine.dir/depend
