cmake_minimum_required(VERSION 3.0)
project(Game) 

# Inclua o módulo FindSDL2_Image diretamente
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Encontre o pacote SDL2
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2_image REQUIRED)  

# Adicione o diretório das bibliotecas 
include_directories(includes/)
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

# Configurar o executável
add_executable(Game ${SOURCE_FILES}) 

# Definir as bibliotecas e incluir diretórios
target_link_libraries(Game PRIVATE SDL2::SDL2)
target_link_libraries(Game PRIVATE ${SDL2_IMAGE_LIBRARIES})  
target_link_libraries(Game PRIVATE SDL2::SDL2main)
target_link_libraries(Game PRIVATE GL)
target_link_libraries(Game PRIVATE GLEW::GLEW)

# Definir as flags de compilação
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Verificar o compilador do sistema
if(ANDROID)
    message("ANDROID")
elseif (UNIX)
    message("LINUX")
elseif (WIN32)
    message("WINDOWS")
endif()