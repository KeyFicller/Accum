add_definitions(-DTRACY_ENABLE)

file(GLOB MODULE_DIRS LIST_DIRECTORIES true ${MODULE_DIR}/*)
foreach(MODULE_DIR ${MODULE_DIRS})
    if (IS_DIRECTORY ${MODULE_DIR})
        message(STATUS "Adding module: ${MODULE_DIR}")
        add_subdirectory(${MODULE_DIR})
    endif()
endforeach()