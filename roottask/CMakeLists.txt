cmake_minimum_required(VERSION 3.16.0)

project(runtimeroot C)

find_package(musllibc REQUIRED)
find_package(util_libs REQUIRED)
find_package(seL4_libs REQUIRED)

musllibc_setup_build_environment_with_sel4runtime()
sel4_import_libsel4()
util_libs_import_libraries()
sel4_libs_import_libraries()

file(
    GLOB
        #static
        src/*.c
        #src/arch/${KernelArch}/*.c
        #src/plat/${KernelPlatform}/*.c
        #src/arch/${KernelArch}/*.S
        #src/plat/${KernelPlatform}/*.S
)

#include(cpio)
#MakeCPIO(archive.o "$<TARGET_FILE:app>")
#get_property(rumprunapps GLOBAL PROPERTY rumprunapps_property)
#set(cpiostring "")
#foreach(app_name IN LISTS rumprunapps)
#    list(APPEND cpiostring $<TARGET_PROPERTY:${app_name},BAKED_LOCATION>)
#endforeach()
#MakeCPIO(archive.o "${cpiostring}" DEPENDS ${rumprunapps})

add_executable(runtimeroot archive.o EXCLUDE_FROM_ALL ${static})

target_include_directories(runtimeroot PRIVATE "include")
target_link_libraries(
    runtimeroot
    PUBLIC
        sel4
        sel4runtime
        muslc
        sel4muslcsys        
        utils    
        sel4debug    
        sel4allocman
        sel4vka
        sel4utils
        sel4platsupport    
        sel4serialserver
)
#target_compile_options(runtimeroot PRIVATE -Werror -g)

include(rootserver)
DeclareRootserver(runtimeroot)