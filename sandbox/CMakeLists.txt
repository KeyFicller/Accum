# set the name of the module
set(MODULE_NAME sandbox)

# set the public headers of the module
file(GLOB_RECURSE PUB_HEADERS
    
)

# set the private headers of the module
file(GLOB_RECURSE PRI_HEADERS CONFIGURE_DEPENDS
    include/**.h
    inc/**.h
)

# set the sources of the module
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    source/**.cpp
)

# set the target of the module
add_executable(${MODULE_NAME} ${SOURCES} ${PUB_HEADERS} ${PRI_HEADERS})

# set the properties of the module
set_target_properties(${MODULE_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${PUB_HEADERS}"
    DEFINE_SYMBOL "${MODULE_NAME}_MODULE"
)

# set the include directories of the module
target_include_directories(${MODULE_NAME} PUBLIC
    inc
    include

    ${ACCUM_DIR}/include
    
    ${INCLUDE_DIR}/basic
    ${INCLUDE_DIR}/math
    ${INCLUDE_DIR}/database
    ${INCLUDE_DIR}/server
    ${INCLUDE_DIR}/framework
)

# set the link dependencies of the module
target_link_libraries(${MODULE_NAME} PUBLIC
    accum
)

# set the install rules of the module
install(TARGETS ${MODULE_NAME}
    EXPORT ${MODULE_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ModularLibrary
)