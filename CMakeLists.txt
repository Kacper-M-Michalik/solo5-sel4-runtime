cmake_minimum_required(VERSION 3.16.0)

include(settings.cmake)

set(project_dir "${CMAKE_CURRENT_LIST_DIR}")
include(${project_dir}/tools/seL4/cmake-tool/helpers/application_settings.cmake)
include(${project_dir}/kernel/configs/seL4Config.cmake)

ApplyCommonReleaseVerificationSettings(${RELEASE} OFF)

if(SIMULATION)
    include(simulation)
    ApplyCommonSimulationSettings(${KernelSel4Arch})
    GenerateSimulateScript()    
endif()

add_subdirectory(roottask)