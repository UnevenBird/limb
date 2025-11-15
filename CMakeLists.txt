cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
project(Ardus VERSION 0.1 LANGUAGES CXX)

option(LUAJIT_FORCE_UTF8_FOPEN ON)
add_subdirectory(external/LuaJIT)

set(LIMB_COMMON
	src/common/luax.cpp
)

add_executable(${PROJECT_NAME}
	${LIMB_COMMON}
	src/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/external/LuaJIT/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE libluajit)
