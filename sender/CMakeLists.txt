set(HEADERS
    program.h
)

set(SOURCES
    program.cpp
)

source_group("Source Files" FILES ${SOURCES})
source_group("Header Files" FILES ${HEADERS})

set(PROJECT_CONTENT ${SOURCES} ${HEADERS})

add_executable(sender ${PROJECT_CONTENT}) 

if(WIN32)
   set_target_properties(sender PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
   set_target_properties(sender PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
   set_target_properties(sender PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE")
   set_target_properties(sender PROPERTIES COMPILE_DEFINITIONS_RELWITHDEBINFO "_CONSOLE")
   set_target_properties(sender PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
   set_target_properties(sender PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows")
endif(WIN32)

target_link_libraries(sender
   Ws2_32.lib
)