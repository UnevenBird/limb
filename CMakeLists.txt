cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME "Untitled")
project(${EXECUTABLE_NAME} VERSION 0.1 LANGUAGES CXX)

option(LUAJIT_FORCE_UTF8_FOPEN ON)
add_subdirectory(external/LuaJIT)

set(PHYSFS_BUILD_STATIC ON CACHE BOOL "Build static PhysicsFS" FORCE)
set(PHYSFS_BUILD_SHARED OFF CACHE BOOL "Build shared PhysicsFS" FORCE)
set(PHYSFS_BUILD_TEST OFF CACHE BOOL "Build tests" FORCE)
set(PHYSFS_BUILD_DOCS OFF CACHE BOOL "Build docs" FORCE)
add_subdirectory(external/physfs)

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

set(LIMB_EVENT
	src/event/event.cpp
	src/event/wrap.cpp
)

set(LIMB_GPATHICS
	src/graphics/shader.cpp
	src/graphics/mesh.cpp
	src/graphics/texture.cpp
	src/graphics/graphics.cpp
	src/graphics/wrap_shader.cpp
	src/graphics/wrap_mesh.cpp
	src/graphics/wrap_texture.cpp
	src/graphics/wrap.cpp
)

set(LIMB_FILESYSTEM
	src/filesystem/filesystem.cpp
	src/filesystem/wrap.cpp
)

set(LIMB_MATH
	src/math/mathlib.cpp
	src/math/wrap.cpp
)

set(LIMB
	src/limb/limb.cpp
	src/limb/wrap.cpp
	src/main.cpp
)

add_executable(${EXECUTABLE_NAME}
	${LIMB_COMMON}
	${LIMB_WINDOW}
	${LIMB_TIMER}
	${LIMB_EVENT}
	${LIMB_GPATHICS}
	${LIMB_FILESYSTEM}
	${LIMB_MATH}
	${LIMB}
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE FMT_HEADER_ONLY)
target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/external/expected/include"
	"${CMAKE_SOURCE_DIR}/external/fmt/include"
	"${CMAKE_SOURCE_DIR}/external/stb/include"
	"${CMAKE_SOURCE_DIR}/external/physfs/src"
	"${CMAKE_SOURCE_DIR}/external/LuaJIT/src"
	"${CMAKE_SOURCE_DIR}/external/glm"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	physfs-static
	libluajit
	glad
	RGFW
)
