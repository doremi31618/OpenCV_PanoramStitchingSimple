# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master

# Include any dependencies generated for this target.
include CMakeFiles/xmltest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/xmltest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/xmltest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xmltest.dir/flags.make

CMakeFiles/xmltest.dir/xmltest.cpp.obj: CMakeFiles/xmltest.dir/flags.make
CMakeFiles/xmltest.dir/xmltest.cpp.obj: CMakeFiles/xmltest.dir/includes_CXX.rsp
CMakeFiles/xmltest.dir/xmltest.cpp.obj: xmltest.cpp
CMakeFiles/xmltest.dir/xmltest.cpp.obj: CMakeFiles/xmltest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/xmltest.dir/xmltest.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/xmltest.dir/xmltest.cpp.obj -MF CMakeFiles\xmltest.dir\xmltest.cpp.obj.d -o CMakeFiles\xmltest.dir\xmltest.cpp.obj -c C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\xmltest.cpp

CMakeFiles/xmltest.dir/xmltest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xmltest.dir/xmltest.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\xmltest.cpp > CMakeFiles\xmltest.dir\xmltest.cpp.i

CMakeFiles/xmltest.dir/xmltest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xmltest.dir/xmltest.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\xmltest.cpp -o CMakeFiles\xmltest.dir\xmltest.cpp.s

# Object files for target xmltest
xmltest_OBJECTS = \
"CMakeFiles/xmltest.dir/xmltest.cpp.obj"

# External object files for target xmltest
xmltest_EXTERNAL_OBJECTS =

xmltest.exe: CMakeFiles/xmltest.dir/xmltest.cpp.obj
xmltest.exe: CMakeFiles/xmltest.dir/build.make
xmltest.exe: libtinyxml2.a
xmltest.exe: CMakeFiles/xmltest.dir/linklibs.rsp
xmltest.exe: CMakeFiles/xmltest.dir/objects1.rsp
xmltest.exe: CMakeFiles/xmltest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable xmltest.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\xmltest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/xmltest.dir/build: xmltest.exe
.PHONY : CMakeFiles/xmltest.dir/build

CMakeFiles/xmltest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\xmltest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/xmltest.dir/clean

CMakeFiles/xmltest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master C:\Users\panos\Desktop\PanoAWS\Projects\PanoDevIntegration\ThirdParty\tinyxml2-master\CMakeFiles\xmltest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xmltest.dir/depend

