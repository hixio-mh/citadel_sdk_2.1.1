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
include zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/depend.make

# Include the progress variables for this target.
include zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/flags.make

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/flags.make
zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj: ../../../../drivers/broadcom/pka/crypto_pka.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj   -c /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka.c

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka.c > CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.i

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka.c -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.s

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/flags.make
zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj: ../../../../drivers/broadcom/pka/crypto_pka_util.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj   -c /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_util.c

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_util.c > CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.i

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_util.c -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.s

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/flags.make
zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj: ../../../../drivers/broadcom/pka/crypto_pka_selftest.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj   -c /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_selftest.c

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_selftest.c > CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.i

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_selftest.c -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.s

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/flags.make
zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj: ../../../../drivers/broadcom/pka/crypto_pka_ushx.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj   -c /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_ushx.c

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_ushx.c > CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.i

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/crypto_pka_ushx.c -o CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.s

# Object files for target drivers__broadcom__pka
drivers__broadcom__pka_OBJECTS = \
"CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj" \
"CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj" \
"CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj" \
"CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj"

# External object files for target drivers__broadcom__pka
drivers__broadcom__pka_EXTERNAL_OBJECTS =

zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka.c.obj
zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_util.c.obj
zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_selftest.c.obj
zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/crypto_pka_ushx.c.obj
zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/build.make
zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a: zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C static library libdrivers__broadcom__pka.a"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && $(CMAKE_COMMAND) -P CMakeFiles/drivers__broadcom__pka.dir/cmake_clean_target.cmake
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/drivers__broadcom__pka.dir/link.txt --verbose=$(VERBOSE)
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && cp -f /home/paulkim/work/sdk/citadel/drivers/broadcom/pka/qlip/qlip_z_v_1_14.o /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/libqlip.a

# Rule to build all files generated by this target.
zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/build: zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a

.PHONY : zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/build

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/clean:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka && $(CMAKE_COMMAND) -P CMakeFiles/drivers__broadcom__pka.dir/cmake_clean.cmake
.PHONY : zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/clean

zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/depend:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulkim/work/sdk/citadel/samples/testing/broadcom /home/paulkim/work/sdk/citadel/drivers/broadcom/pka /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/drivers/broadcom/pka/CMakeFiles/drivers__broadcom__pka.dir/depend

