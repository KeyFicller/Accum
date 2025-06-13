# set the name of the module
set(TOOL_NAME FDG)

# set the public headers of the module
file(GLOB_RECURSE PUB_HEADERS
    
)

# set the private headers of the module
file(GLOB_RECURSE PRI_HEADERS CONFIGURE_DEPENDS
    inc/**.h
)

# set the sources of the module
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    source/**.cpp
)

# set the target of the module
add_executable(${TOOL_NAME} ${SOURCES} ${PUB_HEADERS} ${PRI_HEADERS})

# set the properties of the module
set_target_properties(${TOOL_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${PUB_HEADERS}"
    DEFINE_SYMBOL "${TOOL_NAME}_MODULE"
)

# set the include directories of the module
target_include_directories(${TOOL_NAME} PUBLIC
    inc
)

# set the link dependencies of the module
target_link_libraries(${TOOL_NAME} PUBLIC

)

# set the install rules of the module
install(TARGETS ${TOOL_NAME}
    EXPORT ${TOOL_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ModularLibrary
)