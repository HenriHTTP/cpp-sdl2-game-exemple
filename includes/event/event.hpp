#ifndef EVENT_H
#define EVENT_H

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

namespace event {

struct listener_event {
  SDL_Event event;
};

class event_sdl2 {
 public:
  event_sdl2() = default;

  bool simple_events(listener_event& events);
};

}  // namespace event

#endif