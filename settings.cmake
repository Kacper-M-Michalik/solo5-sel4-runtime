cmake_minimum_required(VERSION 3.16.0)

set(RELEASE OFF CACHE BOOL "Performance optimized build")
set(SIMULATION OFF CACHE BOOL "Simulation build")

#include(${CMAKE_CURRENT_LIST_DIR}/tools/seL4/cmake-tool/helpers/application_settings.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/kernel/configs/seL4Config.cmake)
#correct_platform_strings()
#ApplyCommonReleaseVerificationSettings(${RELEASE} OFF)
#if(SIMULATION)
#   include(${CMAKE_CURRENT_LIST_DIR}/tools/seL4/cmake-tool/helpers/simulation.cmake)
#   ApplyCommonSimulationSettings(${KernelSel4Arch})
#   GenerateSimulateScript()    
#endif()

cmake_minimum_required(VERSION 3.16.0)

set(project_dir "${CMAKE_CURRENT_LIST_DIR}")
file(GLOB project_modules ${project_dir}/projects/*)
list(
    APPEND
        CMAKE_MODULE_PATH
        ${project_dir}/kernel
        ${project_dir}/tools/seL4/cmake-tool/helpers/
        ${project_dir}/tools/seL4/elfloader-tool/
        ${project_modules}
)

include(application_settings)

correct_platform_strings()

#find_package(seL4 REQUIRED)
#sel4_configure_platform_settings()

set(valid_platforms ${KernelPlatform_all_strings} ${correct_platform_strings_platform_aliases})
set_property(CACHE PLATFORM PROPERTY STRINGS ${valid_platforms})
if(NOT "${PLATFORM}" IN_LIST valid_platforms)
    message(FATAL_ERROR "Invalid PLATFORM selected: \"${PLATFORM}\"
Valid platforms are: \"${valid_platforms}\"")
endif()

ApplyCommonReleaseVerificationSettings(${RELEASE} OFF)

if(SIMULATION)
    include(simulation)
    ApplyCommonSimulationSettings(${KernelSel4Arch})
    GenerateSimulateScript()    
endif()