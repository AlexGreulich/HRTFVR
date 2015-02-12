cmake_minimum_required(VERSION 2.8)

project("Sample OpenGL Application")

set(GLEW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glew)
set(GLFW_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glfw)
set(GLM_ROOT_DIR ${CMAKE_SOURCE_DIR}/include/glm)

find_package(OpenGL REQUIRED)

## ADD SOURCE FILES
file(GLOB_RECURSE SOURCE_FILE_HEADERS src/*.h)
file(GLOB_RECURSE SOURCE_FILE_IMPLEMENTATIONS src/*.cpp src/*.cc)

set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# define executable
add_executable(
	myapp 
	${SOURCE_FILE_HEADERS}
	${SOURCE_FILE_IMPLEMENTATIONS}
)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/resources)

## add after-build files to build directory
## the resources directory
add_custom_command(
	TARGET
	myapp
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:myapp>/resources
)

## add glew32.dll to build directory
## if we're running on windows 
if(WIN32)
add_custom_command(
	TARGET
	myapp
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/build-deps $<TARGET_FILE_DIR:myapp>
)
endif(WIN32)

if(MSVC)

	message("USING MSVC CONFIGURATION")

	## add GLEW lib
	add_library(glew_static STATIC IMPORTED)
	set_target_properties(
		glew_static
		PROPERTIES
	    IMPORTED_LOCATION
	    ${GLEW_ROOT_DIR}/lib/Win32/glew32.lib)

	## add GLFW lib
	add_library(glfw_static STATIC IMPORTED)
	set_target_properties(
		glfw_static
		PROPERTIES
	    IMPORTED_LOCATION
	    ${GLFW_ROOT_DIR}/glfw-3.1.bin.WIN32/lib-vc2013/glfw3.lib)


	set_target_properties(
		myapp
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
	)

	set_target_properties(
		myapp
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build
	)

endif(MSVC)

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

target_link_libraries(
	myapp
	${OPENGL_LIBRARIES}
	${GLFW_LIBRARIES}
	glew_static
	glfw_static
)