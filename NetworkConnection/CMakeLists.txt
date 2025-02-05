set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Messages)
include_directories(${PARENT_DIR}/UserEquipment)

add_library(NetworkConnection NetworkConnection.cpp)
add_dependencies(NetworkConnection FlatBufferMessages)

