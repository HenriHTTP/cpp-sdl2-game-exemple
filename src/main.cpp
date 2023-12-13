#include "../includes/game.hpp"

int main() {
  // renderer instance
  core::core_renderer render;

  // screen instance
  auto screen = std::make_shared<core::core_screen>(1280, 720);

  // sdl instance
  auto app = std::make_shared<core::core_sdl2>();

  if (!app->init_sdl2()) {
    return -1;
  } else {
    std::cerr << "Menssage: sucess to init SDL2" << '\n';
  }

  app->create_sdl2_window(render, screen);
  std::cerr << screen->get_width() << std::endl;

  // rgb instance
  auto rgb = std::make_shared<core::core_rgb>(255, 0, 127, 255);

  app->background_color_sdl2(render, rgb);

  // event instance
  auto event_processor = std::make_shared<event::event_sdl2>();

  event::listener_event events;

  // object instance
  auto object = std::make_shared<object::object_moviment>();

  // frames instance vector
  auto vect_frames =
      std::vector<std::shared_ptr<object::object_rectangle_attributes>>(5);

  for (auto& frame : vect_frames) {
    frame = std::make_shared<object::object_rectangle_attributes>();
    frame->set_width(200);
    frame->set_height(200);
    frame->set_position_center(screen);
    frame->set_speed_x(5);
    frame->set_speed_y(5);
    frame->set_texture("../assets/textures/cube.png", render);
  }
  // fps limit
  const int targetFPS = 60;
  const int frameDelay = 1000 / targetFPS;

  // main loop
  auto loop = std::make_shared<core::core_running>();

  while (loop->get_running()) {
    Uint32 frameStart = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

    if (!loop->get_running()) {
      std::cerr << "Failed: loop is not running" << '\n';
      app->quit_sdl2(render);
      return -1;
    }

    while (SDL_PollEvent(&events.event) != 0) {
      if (event_processor->simple_events(events)) {
        loop->set_running(false);
      }

      if (events.event.button.button == SDL_BUTTON_LEFT) {
        // const auto is a name for reference a individual item inside vector
        for (const auto& frame : vect_frames) {
          if (object->object_clicked(events, frame)) {
            std::cerr << "acertou o objeto" << '\n';
            frame->set_positon_y(0);
            object->random_position_x(frame, screen);
          }
        }
      }
    }

    for (const auto& frame : vect_frames) {
      object->bellow_move(frame, screen);
      SDL_Rect retangle_shape = frame->get_rectangle();
      SDL_RenderCopy(render.renderer, frame->get_texture(), NULL,
                     &retangle_shape);
    }

    SDL_RenderPresent(render.renderer);

    // set fps delay
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }

    SDL_GL_SwapWindow(render.window);
    // std::cerr << "loop is running" << '\n';
    continue;
  }

  // drop app
  app->quit_sdl2(render);

  return 0;
}
