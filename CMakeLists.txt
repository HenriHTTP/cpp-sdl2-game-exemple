cmake_minimum_required(VERSION 3.0)
project(SDL2_OpenGL_Demo)

# Encontre o pacote SDL2
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

# Adicione o diretório das bibliotecas SDL2_ttf
include_directories(includes/)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Configurar o executável
add_executable(SDL2_OpenGL_Demo ${SOURCE_FILES})

# Definir as bibliotecas e incluir diretórios
target_link_libraries(SDL2_OpenGL_Demo PRIVATE SDL2::SDL2)
target_link_libraries(SDL2_OpenGL_Demo PRIVATE SDL2::SDL2main)
target_link_libraries(SDL2_OpenGL_Demo PRIVATE GL)
target_link_libraries(SDL2_OpenGL_Demo PRIVATE GLEW::GLEW)

# Definir as flags de compilação
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Configurar a instalação (opcional)
install(TARGETS SDL2_OpenGL_Demo DESTINATION bin)

# Verificar o compilador do sistema
if(ANDROID)
    message("ANDROID")
elseif (UNIX)
    message("LINUX")
elseif (WIN32)
    message("WINDOWS")
endif()
