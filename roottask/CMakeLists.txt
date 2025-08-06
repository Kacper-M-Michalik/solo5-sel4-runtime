cmake_minimum_required(VERSION 3.16.0)

project(roottask C)

set(configure_string "")

find_package(musllibc REQUIRED)
find_package(util_libs REQUIRED)
find_package(seL4_libs REQUIRED)
find_package(sel4_projects_libs REQUIRED)

musllibc_setup_build_environment_with_sel4runtime()
sel4_import_libsel4()
util_libs_import_libraries()
sel4_libs_import_libraries()

#sel4_projects_libs_import_libraries()

add_config_library(roottask "${configure_string}")

file(
    GLOB
        static
        src/*.c
        #src/arch/${KernelArch}/*.c
        #src/plat/${KernelPlatform}/*.c
        #src/arch/${KernelArch}/*.S
        #src/plat/${KernelPlatform}/*.S
)

add_executable(roottask EXCLUDE_FROM_ALL ${static})
target_include_directories(roottask PRIVATE "include")
target_link_libraries(
    roottask
    PUBLIC
        sel4
        sel4_autoconf
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
#target_compile_options(roottask PRIVATE -Werror -g)

include(rootserver)
DeclareRootserver(roottask)