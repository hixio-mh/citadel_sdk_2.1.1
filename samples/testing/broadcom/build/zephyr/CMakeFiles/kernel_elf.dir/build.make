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
include zephyr/CMakeFiles/kernel_elf.dir/depend.make

# Include the progress variables for this target.
include zephyr/CMakeFiles/kernel_elf.dir/progress.make

# Include the compile flags for this target's objects.
include zephyr/CMakeFiles/kernel_elf.dir/flags.make

zephyr/isr_tables.c: zephyr/zephyr_prebuilt.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating isr_tables.c"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-objcopy -I elf32-littlearm -O binary --only-section=.intList /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/zephyr_prebuilt.elf isrList.bin
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /usr/bin/python3 /home/paulkim/work/sdk/citadel/arch/common/gen_isr_tables.py --output-source isr_tables.c --kernel /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/zephyr_prebuilt.elf --intlist isrList.bin   --sw-isr-table

zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj: zephyr/CMakeFiles/kernel_elf.dir/flags.make
zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj: ../../../../misc/empty_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj   -c /home/paulkim/work/sdk/citadel/misc/empty_file.c

zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kernel_elf.dir/misc/empty_file.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/misc/empty_file.c > CMakeFiles/kernel_elf.dir/misc/empty_file.c.i

zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kernel_elf.dir/misc/empty_file.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/misc/empty_file.c -o CMakeFiles/kernel_elf.dir/misc/empty_file.c.s

zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.obj: zephyr/CMakeFiles/kernel_elf.dir/flags.make
zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.obj: zephyr/isr_tables.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.obj"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && ccache /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/kernel_elf.dir/isr_tables.c.obj   -c /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/isr_tables.c

zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/kernel_elf.dir/isr_tables.c.i"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/isr_tables.c > CMakeFiles/kernel_elf.dir/isr_tables.c.i

zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/kernel_elf.dir/isr_tables.c.s"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/isr_tables.c -o CMakeFiles/kernel_elf.dir/isr_tables.c.s

# Object files for target kernel_elf
kernel_elf_OBJECTS = \
"CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj" \
"CMakeFiles/kernel_elf.dir/isr_tables.c.obj"

# External object files for target kernel_elf
kernel_elf_EXTERNAL_OBJECTS =

zephyr/zephyr.elf: zephyr/CMakeFiles/kernel_elf.dir/misc/empty_file.c.obj
zephyr/zephyr.elf: zephyr/CMakeFiles/kernel_elf.dir/isr_tables.c.obj
zephyr/zephyr.elf: zephyr/CMakeFiles/kernel_elf.dir/build.make
zephyr/zephyr.elf: zephyr/linker_pass_final.cmd
zephyr/zephyr.elf: app/libapp.a
zephyr/zephyr.elf: zephyr/libzephyr.a
zephyr/zephyr.elf: zephyr/arch/arch/arm/core/cortex_a/libarch__arm__core__cortex_a.a
zephyr/zephyr.elf: zephyr/lib/libc/minimal/liblib__libc__minimal.a
zephyr/zephyr.elf: zephyr/boards/arm/citadel_svk_58201/libboards__arm__citadel_svk_58201.a
zephyr/zephyr.elf: zephyr/subsys/testsuite/ztest/libsubsys__testsuite__ztest.a
zephyr/zephyr.elf: zephyr/subsys/zbar-0.10/libsubsys__zbar-0.10.a
zephyr/zephyr.elf: zephyr/drivers/serial/libdrivers__serial.a
zephyr/zephyr.elf: zephyr/drivers/broadcom/pka/libdrivers__broadcom__pka.a
zephyr/zephyr.elf: zephyr/drivers/broadcom/qspi_flash/libdrivers__broadcom__qspi_flash.a
zephyr/zephyr.elf: zephyr/drivers/broadcom/smau/libdrivers__broadcom__smau.a
zephyr/zephyr.elf: zephyr/kernel/libkernel.a
zephyr/zephyr.elf: zephyr/CMakeFiles/offsets.dir/arch/arm/core/offsets/offsets.c.obj
zephyr/zephyr.elf: src/drivers/smau/libsamples__testing__broadcom__src__drivers__smau.a
zephyr/zephyr.elf: zephyr/linker_pass_final.cmd
zephyr/zephyr.elf: zephyr/CMakeFiles/kernel_elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable zephyr.elf"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kernel_elf.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating files from zephyr.elf for board: citadel_svk_58201"
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /usr/bin/python3 /home/paulkim/work/sdk/citadel/scripts/check_link_map.py zephyr.map
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-objcopy -S -Obinary --gap-fill 0xff -R .comment -R COMMON -R .eh_frame zephyr.elf zephyr.bin
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-objdump -S zephyr.elf > zephyr.lst
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && /home/paulkim/work/toolchains/gcc-arm-none-eabi-6-2017-q1-update/bin/arm-none-eabi-readelf -e zephyr.elf > zephyr.stat
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && rm -rf /home/paulkim/work/sdk/citadel/drivers/broadcom/pm/crmu/build/ && touch /home/paulkim/work/sdk/citadel/drivers/broadcom/pm/crmu/../mproc_pm.c

# Rule to build all files generated by this target.
zephyr/CMakeFiles/kernel_elf.dir/build: zephyr/zephyr.elf

.PHONY : zephyr/CMakeFiles/kernel_elf.dir/build

zephyr/CMakeFiles/kernel_elf.dir/clean:
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr && $(CMAKE_COMMAND) -P CMakeFiles/kernel_elf.dir/cmake_clean.cmake
.PHONY : zephyr/CMakeFiles/kernel_elf.dir/clean

zephyr/CMakeFiles/kernel_elf.dir/depend: zephyr/isr_tables.c
	cd /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paulkim/work/sdk/citadel/samples/testing/broadcom /home/paulkim/work/sdk/citadel /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr /home/paulkim/work/sdk/citadel/samples/testing/broadcom/build/zephyr/CMakeFiles/kernel_elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/CMakeFiles/kernel_elf.dir/depend

