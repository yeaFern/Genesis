cmake_minimum_required(VERSION 3.19)
project(Genesis)

file(GLOB_RECURSE CLIENT_SRC
    client/*.cpp
    client/*.h
    lib/olc/*.cpp
    lib/olc/*.h
)

file(GLOB_RECURSE SERVER_SRC
    server/*.cpp
    server/*.h
)

file(GLOB_RECURSE SHARED_SRC
    shared/*.cpp
    shared/*.h
    lib/enet/*.cpp
    lib/enet/*.h
)

foreach(_source IN ITEMS ${CLIENT_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${SERVER_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

foreach(_source IN ITEMS ${SHARED_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

set(CMAKE_CXX_STANDARD 17)

add_executable(Genesis ${CLIENT_SRC} ${SHARED_SRC})
target_link_libraries(Genesis ${CONAN_LIBS})
target_include_directories(Genesis PRIVATE shared)
target_include_directories(Genesis PRIVATE lib/enet)
target_include_directories(Genesis PRIVATE lib/olc)

add_executable(GenesisServer ${SERVER_SRC} ${SHARED_SRC})
target_include_directories(GenesisServer PRIVATE shared)
target_include_directories(GenesisServer PRIVATE lib/enet)
