#include "../../includes/core/core.hpp"

namespace core {

// bool init_SDL() {
//   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//     std::cerr << "ERRO: Falha na inicialização do SDL: " << std::endl;
//     return false;
//   }
//   return true;
// }

// bool create_window(SDL_Window*& window, const int& width, const int& height)
// {
//   window =
//       SDL_CreateWindow("Minha Janela", SDL_WINDOWPOS_CENTERED,
//                        SDL_WINDOWPOS_CENTERED, width, height,
//                        SDL_WINDOW_SHOWN);
//   if (window == nullptr) {
//     std::cerr << "ERRO: Falha ao criar a janela SDL: " << std::endl;
//     return false;
//   }
//   return true;
// }

// void set_backgroud_color(SDL_Renderer* renderer, Uint8 red, Uint8 green,
//                          Uint8 blue) {
//   SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
//   SDL_RenderClear(renderer);
// }

// void render_frame(SDL_Renderer* renderer, int x, int y, int width, int
// height,
//                   int red, int green, int blue) {
//   SDL_Rect frame_react{x, y, width, height};
//   SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
//   SDL_RenderFillRect(renderer, &frame_react);
// }

// void close(SDL_Window* window) {
//   SDL_DestroyWindow(window);
//   SDL_Quit();
// }

bool core_sdl2::init_sdl2() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failed: error to init sdl2" << '\n';
    return false;
  }
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  return true;
}

bool core_sdl2::create_sdl2_window(core_renderer& renderer,
                                   core_screen& screen) {
  renderer.window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED, screen.width,
                                     screen.height, SDL_WINDOW_SHOWN);

  if (renderer.window == nullptr) {
    std::cerr << "Failed: error on create SDL2 window" << '\n';
    return false;
  }
  renderer.renderer =
      SDL_CreateRenderer(renderer.window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer.renderer == nullptr) {
    std::cerr << "Failed: error on create SDL2 window" << '\n';
    SDL_DestroyWindow(renderer.window);
    return false;
  }

  SDL_GL_CreateContext(renderer.window);

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cerr << "Failed: error on init glew window" << '\n';
    return false;
  }
  SDL_GL_MakeCurrent(renderer.window, SDL_GL_GetCurrentContext());

  return true;
}

void core_sdl2::background_color_sdl2(core_renderer& renderer, core_rgb& rgb) {
  SDL_SetRenderDrawColor(renderer.renderer, rgb.red, rgb.green, rgb.blue, 255);
  SDL_RenderClear(renderer.renderer);
  SDL_RenderPresent(renderer.renderer);
}

void core_sdl2::quit_sdl2(core_renderer& renderer) {
  SDL_DestroyWindow(renderer.window);
  SDL_Quit();
}

}  // namespace core
