#include "../../includes/event/event.hpp"

namespace event
{

bool event_sdl2::simple_events(listener_event &events)
{
    switch (events.event.type)
    {
    case SDL_QUIT:
        std::cerr << "Message: SDL2 Quit" << SDL_GetKeyName(events.event.key.keysym.sym) << '\n';

        return true;

    case SDL_KEYDOWN:
        if (events.event.key.keysym.sym == SDLK_ESCAPE)
        {
            std::cerr << "Message: Quit SDL press on " << SDL_GetKeyName(events.event.key.keysym.sym) << '\n';
            return true;
        }
        break;
    }
    return false;
}

} // namespace event