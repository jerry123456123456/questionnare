# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build

# Include any dependencies generated for this target.
include CMakeFiles/greeter_server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/greeter_server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/greeter_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/greeter_server.dir/flags.make

CMakeFiles/greeter_server.dir/greeter_server.cc.o: CMakeFiles/greeter_server.dir/flags.make
CMakeFiles/greeter_server.dir/greeter_server.cc.o: ../greeter_server.cc
CMakeFiles/greeter_server.dir/greeter_server.cc.o: CMakeFiles/greeter_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/greeter_server.dir/greeter_server.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/greeter_server.dir/greeter_server.cc.o -MF CMakeFiles/greeter_server.dir/greeter_server.cc.o.d -o CMakeFiles/greeter_server.dir/greeter_server.cc.o -c /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter_server.cc

CMakeFiles/greeter_server.dir/greeter_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greeter_server.dir/greeter_server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter_server.cc > CMakeFiles/greeter_server.dir/greeter_server.cc.i

CMakeFiles/greeter_server.dir/greeter_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greeter_server.dir/greeter_server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter_server.cc -o CMakeFiles/greeter_server.dir/greeter_server.cc.s

CMakeFiles/greeter_server.dir/greeter.pb.cc.o: CMakeFiles/greeter_server.dir/flags.make
CMakeFiles/greeter_server.dir/greeter.pb.cc.o: ../greeter.pb.cc
CMakeFiles/greeter_server.dir/greeter.pb.cc.o: CMakeFiles/greeter_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/greeter_server.dir/greeter.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/greeter_server.dir/greeter.pb.cc.o -MF CMakeFiles/greeter_server.dir/greeter.pb.cc.o.d -o CMakeFiles/greeter_server.dir/greeter.pb.cc.o -c /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.pb.cc

CMakeFiles/greeter_server.dir/greeter.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greeter_server.dir/greeter.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.pb.cc > CMakeFiles/greeter_server.dir/greeter.pb.cc.i

CMakeFiles/greeter_server.dir/greeter.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greeter_server.dir/greeter.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.pb.cc -o CMakeFiles/greeter_server.dir/greeter.pb.cc.s

CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o: CMakeFiles/greeter_server.dir/flags.make
CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o: ../greeter.grpc.pb.cc
CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o: CMakeFiles/greeter_server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o -MF CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o.d -o CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o -c /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.grpc.pb.cc

CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.grpc.pb.cc > CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.i

CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/greeter.grpc.pb.cc -o CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.s

# Object files for target greeter_server
greeter_server_OBJECTS = \
"CMakeFiles/greeter_server.dir/greeter_server.cc.o" \
"CMakeFiles/greeter_server.dir/greeter.pb.cc.o" \
"CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o"

# External object files for target greeter_server
greeter_server_EXTERNAL_OBJECTS =

greeter_server: CMakeFiles/greeter_server.dir/greeter_server.cc.o
greeter_server: CMakeFiles/greeter_server.dir/greeter.pb.cc.o
greeter_server: CMakeFiles/greeter_server.dir/greeter.grpc.pb.cc.o
greeter_server: CMakeFiles/greeter_server.dir/build.make
greeter_server: /usr/local/lib/libgrpc++.a
greeter_server: /usr/local/lib/libprotobuf.so
greeter_server: /usr/local/lib/libgrpc.a
greeter_server: /usr/local/lib/libz.a
greeter_server: /usr/local/lib/libcares.a
greeter_server: /usr/local/lib/libaddress_sorting.a
greeter_server: /usr/local/lib/libre2.a
greeter_server: /usr/local/lib/libabsl_raw_hash_set.a
greeter_server: /usr/local/lib/libabsl_hashtablez_sampler.a
greeter_server: /usr/local/lib/libabsl_hash.a
greeter_server: /usr/local/lib/libabsl_city.a
greeter_server: /usr/local/lib/libabsl_low_level_hash.a
greeter_server: /usr/local/lib/libabsl_statusor.a
greeter_server: /usr/local/lib/libabsl_bad_variant_access.a
greeter_server: /usr/local/lib/libgpr.a
greeter_server: /usr/local/lib/libupb.a
greeter_server: /usr/local/lib/libabsl_status.a
greeter_server: /usr/local/lib/libabsl_random_distributions.a
greeter_server: /usr/local/lib/libabsl_random_seed_sequences.a
greeter_server: /usr/local/lib/libabsl_random_internal_pool_urbg.a
greeter_server: /usr/local/lib/libabsl_random_internal_randen.a
greeter_server: /usr/local/lib/libabsl_random_internal_randen_hwaes.a
greeter_server: /usr/local/lib/libabsl_random_internal_randen_hwaes_impl.a
greeter_server: /usr/local/lib/libabsl_random_internal_randen_slow.a
greeter_server: /usr/local/lib/libabsl_random_internal_platform.a
greeter_server: /usr/local/lib/libabsl_random_internal_seed_material.a
greeter_server: /usr/local/lib/libabsl_random_seed_gen_exception.a
greeter_server: /usr/local/lib/libabsl_cord.a
greeter_server: /usr/local/lib/libabsl_bad_optional_access.a
greeter_server: /usr/local/lib/libabsl_cordz_info.a
greeter_server: /usr/local/lib/libabsl_cord_internal.a
greeter_server: /usr/local/lib/libabsl_cordz_functions.a
greeter_server: /usr/local/lib/libabsl_exponential_biased.a
greeter_server: /usr/local/lib/libabsl_cordz_handle.a
greeter_server: /usr/local/lib/libabsl_str_format_internal.a
greeter_server: /usr/local/lib/libabsl_synchronization.a
greeter_server: /usr/local/lib/libabsl_stacktrace.a
greeter_server: /usr/local/lib/libabsl_symbolize.a
greeter_server: /usr/local/lib/libabsl_debugging_internal.a
greeter_server: /usr/local/lib/libabsl_demangle_internal.a
greeter_server: /usr/local/lib/libabsl_graphcycles_internal.a
greeter_server: /usr/local/lib/libabsl_malloc_internal.a
greeter_server: /usr/local/lib/libabsl_time.a
greeter_server: /usr/local/lib/libabsl_strings.a
greeter_server: /usr/local/lib/libabsl_throw_delegate.a
greeter_server: /usr/local/lib/libabsl_int128.a
greeter_server: /usr/local/lib/libabsl_strings_internal.a
greeter_server: /usr/local/lib/libabsl_base.a
greeter_server: /usr/local/lib/libabsl_spinlock_wait.a
greeter_server: /usr/local/lib/libabsl_raw_logging_internal.a
greeter_server: /usr/local/lib/libabsl_log_severity.a
greeter_server: /usr/local/lib/libabsl_civil_time.a
greeter_server: /usr/local/lib/libabsl_time_zone.a
greeter_server: /usr/local/lib/libssl.a
greeter_server: /usr/local/lib/libcrypto.a
greeter_server: CMakeFiles/greeter_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable greeter_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/greeter_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/greeter_server.dir/build: greeter_server
.PHONY : CMakeFiles/greeter_server.dir/build

CMakeFiles/greeter_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/greeter_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/greeter_server.dir/clean

CMakeFiles/greeter_server.dir/depend:
	cd /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build /home/jerry/Desktop/questionnare/questionnare-src/test/grpc_test/build/CMakeFiles/greeter_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/greeter_server.dir/depend

