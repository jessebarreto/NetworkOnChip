#######################################################################
#
# THIS FILE MAKES THE COMPILATION OF CODE DEVELOPED IN THIS SEMESTER AUTOMATIC.
# BY jesseh.barreto@gmail.com
#
#
# TO USE JUST ADD A NEW SUB_DIRECTORY WITH A CMAKELIST.TXT INSIDE.
# WITH:
#       add_subdirectory(dir_name)
#       add_executable(bin_name source_code)
#       target_link_libraries(bin_name libraries)
#
#######################################################################

project(NoC_on_SystemC)
cmake_minimum_required(VERSION 2.8)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Find SystemC
set(SYSTEMC_HOME /home/jesseh/libs/systemc-2.3.1a)
include_directories(SYSTEM "${SYSTEMC_HOME}/include")
set(SYSTEMC_LIBRARIES ${SYSTEMC_HOME}/lib-linux64/libsystemc.a ${SYSTEMC_HOME}/lib-linux64/libsystemc-2.3.1.so)
set (CMAKE_CXX_FLAGS "-pthread")
set (CMAKE_CXX_STANDARD 11)

# Compile the NoCExample
add_subdirectory(OldNoCExample)

#Source and Include Directories
include_directories("${PROJECT_SOURCE_DIR}/src"
                    "${PROJECT_SOURCE_DIR}/test"
                    "${PROJECT_SOURCE_DIR}/include")

# This Semester NoC
# Compile Executable
add_executable(	NoC #Executable Binary
                src/main.cpp #Source List
                src/flit.cpp
                src/router.cpp
                src/routerchannel.cpp
                src/networkinterface.cpp
                src/networkinterfacefrontendbase.cpp
                test/petestsender.cpp # Test List
                test/petestsenderfrontend.cpp
                test/petestreceiver.cpp
                test/petestreceiverfrontend.cpp
                test/channeltester.cpp
                include/noccommon.h #Include List
                include/irouterchannel.h
                include/inetworkinterfacefrontend.h
                )
target_link_libraries(NoC ${SYSTEMC_LIBRARIES})
