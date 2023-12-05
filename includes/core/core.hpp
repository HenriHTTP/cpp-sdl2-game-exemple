#ifndef CORE_H
#define CORE_H

#include <GL/glew.h>
#include <SDL.h>
#include <memory.h>

#include <iostream>
#include <memory>

namespace core {

struct core_renderer {
  SDL_Renderer* renderer{};
  SDL_Window* window{};
};

struct core_rgb {
 private:
  Uint8 red{};
  Uint8 green{};
  Uint8 blue{};
  Uint8 alpha{};

 public:
  core_rgb() = default;
  core_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
      : red(r), green(g), blue(b), alpha(a) {}

  void set_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  Uint8 get_red() const;
  Uint8 get_green() const;
  Uint8 get_blue() const;
  Uint8 get_alpha() const;
};

struct core_running {
 private:
  bool running{true};

 public:
  core_running() = default;
  core_running(bool running_state) : running(running_state) {}

  void set_running(bool new_state);
  bool get_running() const;
};

struct core_screen {
 private:
  int width{};
  int height{};

 public:
  core_screen() = default;
  core_screen(int w, int h) : width(w), height(h) {}

  void set_resolution(int w, int h);
  void set_width(int w);
  void set_height(int h);
  int get_width() const;
  int get_height() const;
};

class core_interfaces {
 public:
  virtual ~core_interfaces() = default;
  virtual bool init_sdl2() = 0;
  virtual bool create_sdl2_window(core_renderer& renderer,
                                  std::shared_ptr<core_screen>screen) = 0;
  virtual void background_color_sdl2(core_renderer& renderer,
                                     std::shared_ptr<core_rgb> rgb) = 0;
  virtual void quit_sdl2(core_renderer& renderer) = 0;
};

class core_sdl2 : public core_interfaces {
 public:
  bool init_sdl2() override;
  void quit_sdl2(core_renderer& renderer) override;
  bool create_sdl2_window(core_renderer& renderer,
                          std::shared_ptr<core_screen> screen) override;
  void background_color_sdl2(core_renderer& renderer,
                             std::shared_ptr<core_rgb> rgb) override;
};

}  // namespace core

#endif  // CORE_H