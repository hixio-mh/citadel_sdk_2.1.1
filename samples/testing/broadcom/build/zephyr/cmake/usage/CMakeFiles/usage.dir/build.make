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
CMAKE_COMMAND = /opt/cmake/bin/cmake

# The command to remove a file.
RM = /opt/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paulkim/work/sdk/citadel/samples/testing/broadcom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build

# Utility rule file for usage.

# Include the progress variables for this target.
include zephyr/cmake/usage/CMakeFiles/usage.dir/progress.make

zephyr/cmake/usage/CMakeFiles/usage:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/cmake/usage && /opt/cmake/bin/cmake -DBOARD_ROOT_SPACE_SEPARATED=/home/paulkim/work/sdk/citadel -DSHIELD_LIST_SPACE_SEPARATED=frdm_kw41z\ x_nucleo_iks01a1\ x_nucleo_iks01a2 -P /home/paulkim/work/sdk/citadel/cmake/usage/usage.cmake

usage: zephyr/cmake/usage/CMakeFiles/usage
usage: zephyr/cmake/usage/CMakeFiles/usage.dir/build.make

.PHONY : usage

# Rule to build all files generated by this target.
zephyr/cmake/usage/CMakeFiles/usage.dir/build: usage

.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/build

zephyr/cmake/usage/CMakeFiles/usage.dir/clean:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/cmake/usage && $(CMAKE_COMMAND) -P CMakeFiles/usage.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/clean

zephyr/cmake/usage/CMakeFiles/usage.dir/depend:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulkim/work/sdk/citadel/samples/testing/broadcom /home/paulkim/work/sdk/citadel/cmake/usage /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/cmake/usage /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/cmake/usage/CMakeFiles/usage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/depend
