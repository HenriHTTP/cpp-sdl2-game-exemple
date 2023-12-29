#include "../../includes/core/core.hpp"

namespace core
{

void core_rgb::set_rgb(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    this->red = r;
    this->green = g;
    this->blue = b;
    this->alpha = a;
}

Uint8 core_rgb::get_red() const
{
    return this->red;
}

Uint8 core_rgb::get_green() const
{
    return this->green;
}

Uint8 core_rgb::get_blue() const
{
    return this->blue;
}

Uint8 core_rgb::get_alpha() const
{
    return this->alpha;
}

void core_running::set_running(bool new_state)
{
    this->running = new_state;
}
bool core_running::get_running() const
{
    return this->running;
}

void core_screen::set_resolution(const int &w, const int &h)
{
    this->width = w;
    this->height = h;
}

void core_screen::set_width(const int &w)
{
    this->width = w;
}

void core_screen::set_height(const int &h)
{
    this->height = h;
}

int core_screen::get_width() const
{
    return this->width;
}

int core_screen::get_height() const
{
    return this->height;
}

bool core_sdl2::init_sdl2()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed: error to init sdl2" << '\n';
        return false;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    return true;
}

bool core_sdl2::init_sdl2_ttf()
{
    if (TTF_Init() == -1)
    {
        std::cerr << "Failed: SDL_ttf could not initialize! SDL_ttf Error " << '\n';
        return false;
    }
    return true;
}

bool core_sdl2::create_sdl2_window(core_renderer &renderer, std::shared_ptr<core_screen> screen)
{
    renderer.window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       screen->get_width(), screen->get_height(), SDL_WINDOW_SHOWN);

    if (renderer.window == nullptr)
    {
        std::cerr << "Failed: error on create SDL2 window" << '\n';
        return false;
    }
    renderer.renderer = SDL_CreateRenderer(renderer.window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer.renderer == nullptr)
    {
        std::cerr << "Failed: error on create SDL2 window" << '\n';
        SDL_DestroyWindow(renderer.window);
        return false;
    }

    SDL_GL_CreateContext(renderer.window);

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cerr << "Failed: error on init glew window" << '\n';
        return false;
    }
    SDL_GL_MakeCurrent(renderer.window, SDL_GL_GetCurrentContext());

    return true;
}

void core_sdl2::background_color_sdl2(core_renderer &renderer, std::shared_ptr<core_rgb> rgb)
{
    SDL_SetRenderDrawColor(renderer.renderer, rgb->get_red(), rgb->get_green(), rgb->get_blue(), rgb->get_alpha());
    SDL_RenderClear(renderer.renderer);
    SDL_RenderPresent(renderer.renderer);
}

void core_sdl2::quit_sdl2(core_renderer &renderer)
{
    SDL_DestroyWindow(renderer.window);
    SDL_Quit();
}

} // namespace core
