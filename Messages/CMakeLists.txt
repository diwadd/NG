find_package(PkgConfig)
find_package(FlatBuffers REQUIRED)
pkg_search_module(FlatBuffers REQUIRED flatbuffers)

if(FlatBuffers_FOUND)
    message(STATUS "FlatBuffers found: ${FlatBuffers_VERSION}")
else()
    message(FATAL_ERROR "FlatBuffers not found!")
endif()

set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Data)

include_directories(${FlatBuffers_INCLUDE_DIRS})
link_directories(${FlatBuffers_LIBRARY_DIRS})

set(FLATBUFFERS_SCHEMA "${CMAKE_CURRENT_LIST_DIR}/Definitions/Messages.fbs")
set(FLATBUFFERS_OUTPUT_DIR "${CMAKE_CURRENT_LIST_DIR}/Definitions")

add_custom_command(
    OUTPUT xkdc.cpp
    COMMAND touch xkdc.cpp
    COMMENT "XKDC touch"
    VERBATIM
    COMMAND_ERROR_IS_FATAL ANY
)

message(STATUS "Running flatc to generate code from ${FLATBUFFERS_SCHEMA} and ${FLATBUFFERS_OUTPUT_DIR}")
add_custom_command(
    OUTPUT custom_generated.h
    COMMAND flatc --cpp -o ${FLATBUFFERS_OUTPUT_DIR} ${FLATBUFFERS_SCHEMA}
    COMMENT "XKDC Generating FlatBuffers code from ${FLATBUFFERS_SCHEMA} and ${FLATBUFFERS_OUTPUT_DIR}"
    VERBATIM
    COMMAND_ERROR_IS_FATAL ANY
)
message(STATUS "Finnished running flatc to generate code from ${FLATBUFFERS_SCHEMA}")

add_custom_target(
  FlatBufferMessages
  DEPENDS custom_generated.h
)

include_directories(${FLATBUFFERS_OUTPUT_DIR})

add_library(Messages MessageOperations.cpp MessageBuilders.cpp)
add_dependencies(Messages FlatBufferMessages)