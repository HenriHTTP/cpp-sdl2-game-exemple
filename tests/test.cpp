#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "ERROR: Failed initialize SDL2" << std::endl;
    SDL_Quit();
    return -1;
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  SDL_Window* window =
      SDL_CreateWindow("OpenGL Display", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
  if (!window) {
    std::cerr << "ERROR: Failed to create a SDL2 display" << std::endl;
    SDL_Quit();
    return -1;
  }

  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_SetSwapInterval(1);  // set vsync true 1 or 0 false
  
  //initialize GLEW and check fileds
  if (glewInit() != GLEW_OK) {
    std::cerr << "ERROR: Failed initialize a GLEW" << std::endl;
    SDL_Quit();
    return -1;
  }

  // Configuration color to white
  glClearColor(0.3f,0.3f, 0.3f, 1.0f);

  // main loop
  bool init_loop = false;
  while (!init_loop) {
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        std::cerr << "Quit and close SDL" << std::endl;
        init_loop = true;
      }
      if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          std::cerr << "Quit and close SDL" << std::endl;
          init_loop = true;  
        }
      }
    }
  }

  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
