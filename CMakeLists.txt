cmake_minimum_required(VERSION 3.16.0)

include(settings.cmake)
add_subdirectory(roottask)

if(SIMULATION)
    include(simulation)
    GenerateSimulateScript()    
endif()