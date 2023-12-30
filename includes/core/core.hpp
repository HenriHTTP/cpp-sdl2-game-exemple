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

class core_renderer

/**
 * @class core_renderer
 * @brief this class representing the renderer core and window context.
 *
 * @details creating a rederer and window contex
 * @note this struct note dont have methods
 */

{
  public:
    /**
     * @brief Default construtor class  core_renderer
     *
     * @details the all params contructor is NULL
     */

    core_renderer() = default;

    /**
     * @brief Class attributes
     *
     * @details The class attributes usin SDL structure renderer, window.
     */

    SDL_Renderer *renderer{};
    SDL_Window *window{};
};

struct core_rgb

/**
 * @class core_rgb
 * @brief this class representing the values RGB.
 *
 * @details Manages the RGB attributes, including values,
 * and provides set and get methods for manipulation.
 */

{
  private:
    /**
     * @brief Class attributes
     *
     * @details The class attributes using primitive types uint8.
     */

    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    Uint8 alpha{};

  public:
    /**
     * @brief Default construtor class object_moviment
     *
     * @details the all params is NULL or uint8
     *
     * @param r uint8(red)
     * @param g uint8(red)
     * @param b uint8(blue)
     */

    core_rgb() = default;
    core_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : red(r), green(g), blue(b), alpha(a)
    {
    }

    /**
     * @brief configuiration methods (set)
     *
     * @details this section contains set methods prototypes
     */
    void set_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    /**
     * @brief configuiration methods (get)
     *
     * @details this section contains get methods prototypes
     */

    Uint8 get_red() const;
    Uint8 get_green() const;
    Uint8 get_blue() const;
    Uint8 get_alpha() const;
};

class core_running

/**
 * @class core_running
 * @brief this class representing the runtime loop game.
 *
 * @details Manages the RGB attributes, including values,
 * and provides set and get methods for manipulation.
 */

{
  private:
    /**
     * @brief Class attributes
     *
     * @details The class attributes using primitive types boolean.
     * @note This boolean represent a main loop game.
     */

    bool running{true};

  public:
    /**
     * @brief Default construtor class object_moviment
     *
     * @details the all params is NULL or boolean
     *
     * @param running_state boolean(running)
     */

    core_running() = default;
    core_running(bool running_state) : running(running_state)
    {
    }

    /**
     * @brief configuiration methods (set)
     */

    void set_running(bool new_state);

    /**
     * @brief configuiration methods (get)
     */

    bool get_running() const;
};

class core_screen

/**
 * @class core_running
 * @brief this class representing the runtime loop game.
 *
 * @details Manages the RGB attributes, including values,
 * and provides set and get methods for manipulation.
 */

{
  private:
    /**
     * @brief Class attributes
     *
     * @details The class attributes using primitive types integer.
     * @note This integer represent a resolition screen.
     */

    int width{};
    int height{};

  public:
    /**
     * @brief Default construtor class core_screen
     *
     * @details the all params is NULL or integer
     *
     * @param w integer(width)
     * @param h integer(height)
     */
    core_screen() = default;
    core_screen(const int &w, const int &h) : width(w), height(h)
    {
    }

    /**
     * @brief configuiration methods (set)
     *
     * @details this section contains set methods prototypes
     */

    void set_resolution(const int &w, const int &h);
    void set_width(const int &w);
    void set_height(const int &h);

    /**
     * @brief configuiration methods (get)
     *
     * @details this section contains get methods prototypes
     */

    int get_width() const;
    int get_height() const;
};

class core_sdl2

/**
 * @class core_sdl2
 * @brief Class representing a primitive sdl action.
 *
 * @details Manages the sdl attributes primitive
 * @note this class dont have anyone atribute
 */

{
  public:
    /**
     * @brief Default construtor class core_sdl2
     *
     * @details the all params is NULL or integer
     */

    core_sdl2() = default;

    /**
     * @brief configuiration abstract methods
     *
     * @details this section contains congihuration methods prototypes
     */

    bool init_sdl2();
    bool init_sdl2_ttf();
    /**
     * @bug vsync is not working
     * @note resolve and fix bug
     */
    bool init_vsync(bool enable);
    void quit_sdl2(core_renderer &renderer);
    bool create_sdl2_window(core_renderer &renderer, std::shared_ptr<core_screen> screen);
    void background_color_sdl2(core_renderer &renderer, std::shared_ptr<core_rgb> rgb);
};

} // namespace core

#endif // CORE_H