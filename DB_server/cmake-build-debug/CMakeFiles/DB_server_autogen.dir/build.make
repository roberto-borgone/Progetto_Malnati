# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server\cmake-build-debug

# Utility rule file for DB_server_autogen.

# Include the progress variables for this target.
include CMakeFiles/DB_server_autogen.dir/progress.make

CMakeFiles/DB_server_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target DB_server"
	"C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E cmake_autogen C:/Users/rober/CLionProjects/Progetto_Malnati/DB_server/cmake-build-debug/CMakeFiles/DB_server_autogen.dir/AutogenInfo.cmake Debug

DB_server_autogen: CMakeFiles/DB_server_autogen
DB_server_autogen: CMakeFiles/DB_server_autogen.dir/build.make

.PHONY : DB_server_autogen

# Rule to build all files generated by this target.
CMakeFiles/DB_server_autogen.dir/build: DB_server_autogen

.PHONY : CMakeFiles/DB_server_autogen.dir/build

CMakeFiles/DB_server_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DB_server_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DB_server_autogen.dir/clean

CMakeFiles/DB_server_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server\cmake-build-debug C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server\cmake-build-debug C:\Users\rober\CLionProjects\Progetto_Malnati\DB_server\cmake-build-debug\CMakeFiles\DB_server_autogen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DB_server_autogen.dir/depend

