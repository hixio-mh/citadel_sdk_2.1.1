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

# Include any dependencies generated for this target.
include zephyr/CMakeFiles/zephyr_prebuilt.dir/depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/zephyr_prebuilt.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/CMakeFiles/zephyr_prebuilt.dir/flags.make

zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/zephyr_prebuilt.dir/flags.make
zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj: ../../../../misc/empty_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj   -c /home/paulkim/work/sdk/citadel/misc/empty_file.c

zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/misc/empty_file.c > CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.i

zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/misc/empty_file.c -o CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.s

# Object files for target zephyr_prebuilt
zephyr_prebuilt_OBJECTS = \
"CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj"

# External object files for target zephyr_prebuilt
zephyr_prebuilt_EXTERNAL_OBJECTS =

zephyr/zephyr_prebuilt.elf: zephyr/CMakeFiles/zephyr_prebuilt.dir/misc/empty_file.c.obj
zephyr/zephyr_prebuilt.elf: zephyr/CMakeFiles/zephyr_prebuilt.dir/build.make
zephyr/zephyr_prebuilt.elf: zephyr/linker.cmd
zephyr/zephyr_prebuilt.elf: app/libapp.a
zephyr/zephyr_prebuilt.elf: zephyr/libzephyr.a
zephyr/zephyr_prebuilt.elf: zephyr/arch/arch/arm/core/cortex_a/libarch__arm__core__cortex_a.a
zephyr/zephyr_prebuilt.elf: zephyr/lib/libc/minimal/liblib__libc__minimal.a
zephyr/zephyr_prebuilt.elf: zephyr/boards/arm/citadel_svk_58201/libboards__arm__citadel_svk_58201.a
zephyr/zephyr_prebuilt.elf: zephyr/subsys/testsuite/ztest/libsubsys__testsuite__ztest.a
zephyr/zephyr_prebuilt.elf: zephyr/subsys/zbar-0.10/libsubsys__zbar-0.10.a
zephyr/zephyr_prebuilt.elf: zephyr/drivers/serial/libdrivers__serial.a
zephyr/zephyr_prebuilt.elf: zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a
zephyr/zephyr_prebuilt.elf: zephyr/drivers/broadcom/qspi_flash/libdrivers__broadcom__qspi_flash.a
zephyr/zephyr_prebuilt.elf: zephyr/drivers/broadcom/smau/libdrivers__broadcom__smau.a
zephyr/zephyr_prebuilt.elf: zephyr/kernel/libkernel.a
zephyr/zephyr_prebuilt.elf: zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj
zephyr/zephyr_prebuilt.elf: src/drivers/smau/libsamples__testing__broadcom__src__drivers__smau.a
zephyr/zephyr_prebuilt.elf: zephyr/linker.cmd
zephyr/zephyr_prebuilt.elf: zephyr/CMakeFiles/zephyr_prebuilt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable zephyr_prebuilt.elf"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/zephyr_prebuilt.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
zephyr/CMakeFiles/zephyr_prebuilt.dir/build: zephyr/zephyr_prebuilt.elf

.PHONY : zephyr/CMakeFiles/zephyr_prebuilt.dir/build

zephyr/CMakeFiles/zephyr_prebuilt.dir/clean:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/zephyr_prebuilt.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/zephyr_prebuilt.dir/clean

zephyr/CMakeFiles/zephyr_prebuilt.dir/depend:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulkim/work/sdk/citadel/samples/testing/broadcom /home/paulkim/work/sdk/citadel /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/CMakeFiles/zephyr_prebuilt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/zephyr_prebuilt.dir/depend

