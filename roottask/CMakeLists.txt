cmake_minimum_required(VERSION 3.16.0)

project(roottask C)

#set(configure_string "")

find_package(seL4 REQUIRED)
find_package(elfloader-tool REQUIRED)

find_package(musllibc REQUIRED)
find_package(util_libs REQUIRED)
find_package(seL4_libs REQUIRED)
find_package(sel4_projects_libs REQUIRED)

sel4_import_kernel()
elfloader_import_project()

musllibc_setup_build_environment_with_sel4runtime()
sel4_import_libsel4()
util_libs_import_libraries()
sel4_libs_import_libraries()

#add_config_library(roottask "${configure_string}")

file(
    GLOB
        static
        src/*.c
)
add_executable(roottask)
target_include_directories(roottask PRIVATE "include")
target_link_libraries(
    roottask
    sel4_autoconf
    muslc
    sel4
    sel4runtime
    sel4allocman
    sel4vka
    sel4utils
    sel4platsupport
    sel4muslcsys
    sel4serialserver
)

include(rootserver)
DeclareRootserver(roottask)