cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Ardus VERSION 0.1 LANGUAGES CXX)

option(LUAJIT_FORCE_UTF8_FOPEN ON)
add_subdirectory(external/LuaJIT)

add_library(RGFW SHARED src/common/impl.cpp)
target_compile_definitions(RGFW PRIVATE RGFW_EXPORT)
target_include_directories(RGFW PUBLIC
	"${CMAKE_SOURCE_DIR}/external/RGFW"
)
find_package(OpenGL REQUIRED)
target_link_libraries(RGFW PUBLIC OpenGL::GL)

add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC 
	"${CMAKE_SOURCE_DIR}/external/glad/include"
)

set(LIMB_COMMON
	src/common/luax.cpp
)

set(LIMB_WINDOW
	src/window/window.cpp
	src/window/wrap.cpp
)

set(LIMB_TIMER
	src/timer/timer.cpp
	src/timer/wrap.cpp
)

set(LIMB
	src/limb/limb.cpp
	src/limb/wrap.cpp
)

add_executable(${PROJECT_NAME}
	${LIMB_COMMON}
	${LIMB_WINDOW}
	${LIMB_TIMER}
	${LIMB}
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/external/LuaJIT/src"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	libluajit
	glad
	RGFW
)
