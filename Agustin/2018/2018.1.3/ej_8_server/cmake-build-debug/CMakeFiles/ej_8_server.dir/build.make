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
CMAKE_COMMAND = /home/agustin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/agustin/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ej_8_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ej_8_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ej_8_server.dir/flags.make

CMakeFiles/ej_8_server.dir/main.c.o: CMakeFiles/ej_8_server.dir/flags.make
CMakeFiles/ej_8_server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ej_8_server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ej_8_server.dir/main.c.o   -c /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/main.c

CMakeFiles/ej_8_server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ej_8_server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/main.c > CMakeFiles/ej_8_server.dir/main.c.i

CMakeFiles/ej_8_server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ej_8_server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/main.c -o CMakeFiles/ej_8_server.dir/main.c.s

# Object files for target ej_8_server
ej_8_server_OBJECTS = \
"CMakeFiles/ej_8_server.dir/main.c.o"

# External object files for target ej_8_server
ej_8_server_EXTERNAL_OBJECTS =

ej_8_server: CMakeFiles/ej_8_server.dir/main.c.o
ej_8_server: CMakeFiles/ej_8_server.dir/build.make
ej_8_server: CMakeFiles/ej_8_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ej_8_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ej_8_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ej_8_server.dir/build: ej_8_server

.PHONY : CMakeFiles/ej_8_server.dir/build

CMakeFiles/ej_8_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ej_8_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ej_8_server.dir/clean

CMakeFiles/ej_8_server.dir/depend:
	cd /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug /home/agustin/Documents/Taller_de_programacion_1/Practica-final-taller/Agustin/2018/2018.1.3/ej_8_server/cmake-build-debug/CMakeFiles/ej_8_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ej_8_server.dir/depend

