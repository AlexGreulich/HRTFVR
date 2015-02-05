cmake_minimum_required(VERSION 2.8)

project("Sample OpenGL Application")

set(GLEW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glew)
set(GLFW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glfw)
#set(GLUT_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glut)
set(GLM_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glm)
set(JSON_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/rapidjson)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(PkgConfig REQUIRED)

#find_package(GLM REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

file(GLOB_RECURSE SOURCE_FILE_HEADERS src/*.h)
file(GLOB_RECURSE SOURCE_FILE_IMPLEMENTATIONS src/*.cpp src/*.cc)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${GLM_ROOT_DIR}
	${GLEW_ROOT_DIR}/include
	${GLUT_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
	${JSON_ROOT_DIR}/include
	/usr/include/
)

link_directories(
	${GLEW_ROOT_DIR}/include
	${GLFW_ROOT_DIR}/include
	${GLM_ROOT_DIR}
	/usr/include/
)

message("${SOURCE_FILE_IMPLEMENTATIONS}")

add_executable(
	myapp 
	${SOURCE_FILE_HEADERS}
	${SOURCE_FILE_IMPLEMENTATIONS}
)

target_link_libraries(myapp ${OPENGL_LIBRARIES} ${GLEW_ROOT_DIR}/lib/libGLEW.so.1.11.0 ${GLFW_LIBRARIES} )