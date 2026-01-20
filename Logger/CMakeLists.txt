set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Data)
include_directories(${PARENT_DIR}/Messages)

add_library(Logger Logger.cpp)
add_dependencies(Logger FlatBufferMessages)