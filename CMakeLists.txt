cmake_minimum_required (VERSION 3.5)
project(BoxingTimer)
if (UNIX)
  add_definitions(-Wno-sign-compare -Wno-enum-compare)
endif(UNIX)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wconversion -pedantic -Wno-unknown-pragmas")
endif()

add_definitions(-DBOOST_ALL_DYN_LINK)
SET(BOOST_ROOT "C:/Boost")                             # FindBoost.cmake handles this on its own in the linux case
SET(BOOST_LIBRARYDIR ${BOOST_ROOT}"/lib")
SET(BOOST_INCLUDEDIR ${BOOST_ROOT})
find_package(Boost 1.66.0 COMPONENTS system REQUIRED)
list(APPEND INCLUDE_EXT_DIRS ${Boost_INCLUDE_DIRS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CPP_REST_FOUND False)
find_package(cpprestsdk REQUIRED) # populates CPP_REST_INCLUDE_DIR and CPP_REST_LIBRARY
if(MSVC)                        # Microsoft uses magic to handle this
    SET(LINK FLAGS "")
else()
    SET(LINK_FLAGS "-lboost_system -lssl -lcrypto")
endif()

SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}" )

include_directories(${PROJECT_ROOT}/include)
include_directories(SYSTEM ${CPP_REST_INCLUDE_DIR})
project(BoxingTimer)
set (CMAKE_CXX_STANDARD 11)
include_directories("${CMAKE_SOURCE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/src")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)


add_executable(BoxingTimer src/main.cpp src/Timer.cpp src/Timer.h)

#set(BoxingTimer_LIBRARIES "-lboost_system -lcrypto -lssl -lcpprest")
#target_link_libraries(BoxingTimer ${Casablanca_LIBRARIES})
target_link_libraries(BoxingTimer PRIVATE cpprestsdk::cpprest)
target_link_libraries(BoxingTimer "${CPP_REST_LIBRARY};${CMAKE_DL_LIBS}")