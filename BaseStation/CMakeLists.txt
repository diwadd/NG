set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Data)
include_directories(${PARENT_DIR}/Messages)
# include_directories(${PARENT_DIR}/UserEquipment)

add_library(BaseStation BaseStation.cpp)
add_dependencies(BaseStation FlatBufferMessages)