############################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if (COMMAND cmake_policy)
	cmake_policy (SET CMP0003 NEW)
endif (COMMAND cmake_policy)

PROJECT (projet-cpp)

############################################################

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Wextra -pedantic -fno-exceptions")

#INCLUDE(FindPkgConfig)

LINK_DIRECTORIES(
	${CMAKE_SOURCE_DIRECTORY}
)

INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/include
)

ADD_SUBDIRECTORY(src)
