#ifndef CORE_H
#define CORE_H

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

namespace core {

struct core_renderer {
  SDL_Renderer* renderer{};
  SDL_Window* window{};
};

struct core_rgb {
  Uint8 red{};
  Uint8 green{};
  Uint8 blue{};
};

struct core_running {
  bool running{true};
};

struct core_screen {
  int width{};
  int height{};
};

class core_interfaces {
 public:
  virtual ~core_interfaces() = default;
  virtual bool init_sdl2() = 0;
  virtual bool create_sdl2_window(core_renderer& renderer,
                                  core_screen& screen) = 0;
  virtual void background_color_sdl2(core_renderer& renderer,
                                     core_rgb& rgb) = 0;
  virtual void quit_sdl2(core_renderer& renderer) = 0;
};

class core_sdl2 : public core_interfaces {
 public:
  bool init_sdl2() override;
  void quit_sdl2(core_renderer& renderer) override;
  bool create_sdl2_window(core_renderer& renderer,
                          core_screen& screen) override;
  void background_color_sdl2(core_renderer& renderer, core_rgb& rgb) override;
};

}  // namespace core

#endif  // CORE_H