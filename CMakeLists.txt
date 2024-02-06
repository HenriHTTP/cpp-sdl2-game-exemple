cmake_minimum_required(VERSION 3.0)
project(Game)

# include find packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# include libs required
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# include directories
include_directories(
        ${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# configure executable
add_executable(Game ${SOURCE_FILES})

# define target libraries link
target_link_libraries(Game PRIVATE ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} GL ${GLEW_LIBRARIES} ${SDL2_TTF_LIBRARIES})

# configs compilation
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# verification system platform
if(ANDROID)
    message("ANDROID")
elseif (UNIX)
    message("LINUX")
elseif (WIN32)
    message("WINDOWS")
endif()