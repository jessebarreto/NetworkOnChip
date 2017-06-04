

# Compile Executable
add_executable(	OldNoCExample #Executable Binary
                main.cpp #Source List
                cod.cpp
                cod.h
            	decod.cpp
                decod.h
                full_router.h
                globals.h
            	kernel_ni.cpp
                kernel_ni.h
                master.h
                memdef.h
                mem_if.h
                memoria.cpp
                memoria.h
                mips.cpp
                mips.h
                noc_common.h
                router.cpp
                router.h
                shell_master_ni.h
                shell_memoria.cpp
                shell_mips.cpp
                shell_mips.h
                shell_mips_if.h
                shell_slave_ni.h
                slave.h
                )
target_link_libraries(OldNoCExample ${SYSTEMC_LIBRARIES})
