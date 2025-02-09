set(PARENT_DIR "${CMAKE_CURRENT_LIST_DIR}/..")

include_directories(${PARENT_DIR}/Data)

add_library(UserEquipment UserEquipment.cpp)