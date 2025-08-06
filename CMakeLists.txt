cmake_minimum_required(VERSION 3.16.0)

include(settings.cmake)

project(runtime C)

find_package(seL4 REQUIRED)
find_package(elfloader-tool REQUIRED)

sel4_import_kernel()

if(KernelArchARM)
    # Elfloader settings that correspond to how Data61 sets its boards up.
    ApplyData61ElfLoaderSettings(${KernelPlatform} ${KernelSel4Arch})
endif()
if(KernelArchRiscV)
    message(FATAL_ERROR "RISCV not supported.")
endif()

elfloader_import_project()

add_subdirectory(roottask)

if(SIMULATION)
    include(simulation)

    # Might want to change later
    if(KernelSel4ArchX86_64)
        SetSimulationScriptProperty(MEM_SIZE "3G")
    endif()
    if(KernelPlatformQEMUArmVirt)
        SetSimulationScriptProperty(MEM_SIZE "2G")
    endif()

    ApplyCommonSimulationSettings(${KernelSel4Arch})
    GenerateSimulateScript()
endif()