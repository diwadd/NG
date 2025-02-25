set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Data)
include_directories(${PARENT_DIR}/Utilities)
include_directories(${PARENT_DIR}/UserEquipment)
include_directories(${PARENT_DIR}/Messages)
include_directories(${PARENT_DIR}/BaseStation)

add_library(Pools PoolFactory.cpp)
add_dependencies(Pools FlatBufferMessages)

target_link_libraries(Pools PRIVATE UserEquipment)
