#ifndef EVENT_H
#define EVENT_H

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>

namespace event {

struct listener_event {
  SDL_Event event;
};

class event_interfaces {
  // virtual bool key_down_event(SDL_Keysym key_dowm) = 0;
  // virtual bool key_press() = 0;
 public:
  virtual ~event_interfaces() = default;
  virtual bool simple_events(listener_event& events) = 0;
};
class event_sdl2 : public event_interfaces {
 public:
  // bool key_down_event(SDL_Keysym key_dowm) override;
  bool simple_events(listener_event& events) override; 
};

}  // namespace event

#endif