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

# Utility rule file for m0_build.

# Include the progress variables for this target.
include zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/progress.make

zephyr/drivers/broadcom/pm/CMakeFiles/m0_build:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pm && rm -rf /home/paulkim/work/sdk/citadel/drivers/broadcom/pm/crmu/build && ZEPHYRINCLUDE="-I/home/paulkim/work/sdk/citadel/include -I/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/include/generated -I/home/paulkim/work/sdk/citadel/include/broadcom/drivers -I/home/paulkim/work/sdk/citadel/arch/arm/include -I/home/paulkim/work/sdk/citadel/subsys/testsuite/ztest/include -DCONFIG_ARMV6_M_ARMV8_M_BASELINE -DDEFINE_LOCAL_STRUCT_DEVICE " make -C /home/paulkim/work/sdk/citadel/drivers/broadcom/pm/crmu M0 && touch /home/paulkim/work/sdk/citadel/drivers/broadcom/pm/crmu/../mproc_pm.c

m0_build: zephyr/drivers/broadcom/pm/CMakeFiles/m0_build
m0_build: zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/build.make

.PHONY : m0_build

# Rule to build all files generated by this target.
zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/build: m0_build

.PHONY : zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/build

zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/clean:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pm && $(CMAKE_COMMAND) -P CMakeFiles/m0_build.dir/cmake_clean.cmake
.PHONY : zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/clean

zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/depend:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulkim/work/sdk/citadel/samples/testing/broadcom /home/paulkim/work/sdk/citadel/drivers/broadcom/pm /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pm /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/drivers/broadcom/pm/CMakeFiles/m0_build.dir/depend

