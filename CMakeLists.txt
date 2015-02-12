cmake_minimum_required(VERSION 2.8)

project("Sample OpenGL Application")

set(GLEW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glew)
set(GLFW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glfw)
set(GLM_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glm)

##
## GLEW LIB
add_library(glew_static STATIC IMPORTED)

set_target_properties(
	glew_static
	PROPERTIES
    IMPORTED_LOCATION
    ${GLEW_ROOT_DIR}/lib/Win32/glew32.lib)

##

##
## GLFW LIB
add_library(glfw_static STATIC IMPORTED)

set_target_properties(
	glfw_static
	PROPERTIES
    IMPORTED_LOCATION
    ${GLFW_ROOT_DIR}/windows/lib-vc2013/glfw3.lib)

##

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE_FILE_HEADERS src/*.h)
file(GLOB_RECURSE SOURCE_FILE_IMPLEMENTATIONS src/*.cpp src/*.cc)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${GLM_ROOT_DIR}
	${GLEW_ROOT_DIR}/include
	${GLFW_INCLUDE_DIRS}
	${GLFW_ROOT_DIR}/include
	/usr/include/
)

link_directories(
	${GLEW_ROOT_DIR}/include
	${GLFW_ROOT_DIR}/include
	${GLFW_ROOT_DIR}/windows/include
	${GLM_ROOT_DIR}
	/usr/include/
)

add_executable(
	myapp 
	${SOURCE_FILE_HEADERS}
	${SOURCE_FILE_IMPLEMENTATIONS}
)



target_link_libraries(
	myapp
	${OPENGL_LIBRARIES}
	${GLFW_LIBRARIES}
	glew_static
	glfw_static
)