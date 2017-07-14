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
set(SYSTEMC_HOME /opt/systemc-2.3.1a)
#set(SYSTEMC_HOME /usr/local/systemc-2.3.1/)
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

# Add files
# Source List
file(GLOB sourceList src/flit.cpp
                     src/router.cpp
                     src/routerchannel.cpp
                     src/networkinterface.cpp
                     src/networkinterfacefrontendbase.cpp
                     src/nocassembler.cpp
                     src/nocrouting.cpp
                     src/pemaster.cpp
                     src/pemaster.h
                     src/peslave.cpp
                     src/peslave.h
                     src/pemastershell.cpp
                     src/pemastershell.h
                     src/peslaveshell.cpp
                     src/peslaveshell.h
                     src/penull.cpp
                     src/penull.h
                     src/penullshell.cpp
                     src/penullshell.h
                     )

# Test files list
file(GLOB testList test/channeltester.cpp
                   test/petestsenderfrontend.cpp
                   test/petestsender.cpp
                   test/petestreceiver.cpp
                   test/petestreceiverfrontend.cpp
                   test/master.cpp
                   test/slave.cpp
                   test/slaveshell.cpp
                   test/mastershell.cpp
                   )

# Include files list
file(GLOB includeList include/noccommon.h
                      include/nocdebug.h
                      include/irouterchannel.h
                      include/inetworkinterfacefrontend.h
                      )

# This Semester NoC
# Compile Executable
add_executable( NoC #Executable Binary
                src/main.cpp
                #Source List
                ${sourceList}
                 # PE List
                 # Test List
                ${testList}
                #Include List
                ${includeList}
                )
target_link_libraries(NoC ${SYSTEMC_LIBRARIES})

##Disable compilation of the channel tester
## Compile Executable
#add_executable( NoCRouterChannelTester #Executable Binary
#                test/routerchanneltester.cpp
#                #Source List
#                ${sourceList}
#                 # Test List
#                ${testList}
#                #Include List
#                ${includeList}
#                )
#target_link_libraries(NoCRouterChannelTester ${SYSTEMC_LIBRARIES})

## Disable compilation of the networkInterface tester.
## Compile Executable
#add_executable( NoCNetworkInterfaceTester #Executable Binary
#                test/networkinterfacetester.cpp #Source List
#                #Source List
#                ${sourceList}
#                 # Test List
#                ${testList}
#                #Include List
#                ${includeList}
#               )
#target_link_libraries(NoCNetworkInterfaceTester ${SYSTEMC_LIBRARIES})

## Disable the compilation of the basic shell communication tester.
## Compile Executable
#add_executable( BasicShellCommunicationTest #Executable Binary
#                test/basicshellscommunication.cpp
#                include/specialkernel.cpp
#                #Source List
#                ${sourceList}
#                 # Test List
#                ${testList}
#                #Include List
#                ${includeList}
#               )
#target_link_libraries(BasicShellCommunicationTest ${SYSTEMC_LIBRARIES})

## Disable the compilation of the router tester.
## Compile Executable
#add_executable( RouterTest #Executable Binary
#                test/routertester.cpp #Source List
#                #Source List
#                ${sourceList}
#                 # Test List
#                ${testList}
#                #Include List
#                ${includeList}
#               )
#target_link_libraries(RouterTest ${SYSTEMC_LIBRARIES})
