#ifndef CORE_H
#define CORE_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory.h>

#include <iostream>
#include <memory>

namespace core
{

struct core_renderer
{
    SDL_Renderer *renderer{};
    SDL_Window *window{};
};

struct core_rgb
{
  private:
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    Uint8 alpha{};

  public:
    core_rgb() = default;
    core_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : red(r), green(g), blue(b), alpha(a)
    {
    }

    void set_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    Uint8 get_red() const;
    Uint8 get_green() const;
    Uint8 get_blue() const;
    Uint8 get_alpha() const;
};

struct core_running
{
  private:
    bool running{true};

  public:
    core_running() = default;
    core_running(bool running_state) : running(running_state)
    {
    }

    void set_running(bool new_state);
    bool get_running() const;
};

struct core_screen
{
  private:
    int width{};
    int height{};

  public:
    core_screen() = default;
    core_screen(const int &w, const int &h) : width(w), height(h)
    {
    }

    void set_resolution(const int &w, const int &h);
    void set_width(const int &w);
    void set_height(const int &h);

    int get_width() const;
    int get_height() const;
};

class core_sdl2
{
  public:
    core_sdl2() = default;

    bool init_sdl2();
    bool init_sdl2_ttf();
    void quit_sdl2(core_renderer &renderer);
    bool create_sdl2_window(core_renderer &renderer, std::shared_ptr<core_screen> screen);
    void background_color_sdl2(core_renderer &renderer, std::shared_ptr<core_rgb> rgb);
};

} // namespace core

#endif // CORE_H