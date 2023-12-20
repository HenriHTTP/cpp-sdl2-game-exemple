#include "../includes/game.hpp"

int main() {
  // renderer instance
  core::core_renderer render;

  // screen instance
  auto screen = std::make_shared<core::core_screen>(600, 800);

  // sdl instance
  auto app = std::make_shared<core::core_sdl2>();

  app->init_sdl2();
  app->create_sdl2_window(render, screen);

  // rgb instance
  auto rgb = std::make_shared<core::core_rgb>(255, 0, 127, 255);

  app->background_color_sdl2(render, rgb);

  // event instance
  auto event_processor = std::make_shared<event::event_sdl2>();

  event::listener_event events;

  // object instance
  auto object = std::make_shared<object::object_moviment>();

  // player instance
  auto player_shape = std::make_shared<object::object_rectangle_attributes>();
  player_shape->set_width(30);
  player_shape->set_height(30);
  player_shape->set_position_center(screen);
  player_shape->set_speed_x(5);
  player_shape->set_speed_y(5);
  player_shape->set_texture("../assets/textures/cube.png", render);

  auto plataform = std::make_shared<object::object_rectangle_attributes>();
  plataform->set_width(300);
  plataform->set_height(30);
  plataform->set_position_center(screen);
  auto end_y = screen->get_height() - plataform->get_height();
  plataform->set_positon_y(end_y);
  plataform->set_speed_x(5);
  plataform->set_speed_y(5);
  plataform->set_texture("../assets/textures/cube.png", render);

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

    SDL_RenderCopy(render.renderer, player_shape->get_texture(), NULL,
                   &player_shape->get_rectangle());
    SDL_RenderCopy(render.renderer, plataform->get_texture(), NULL,
                   &plataform->get_rectangle());
 

    object->auto_move(player_shape, screen);
    player_shape->colision_x(plataform);
    player_shape->colision_y(plataform);

    while (SDL_PollEvent(&events.event) != 0) {
      if (event_processor->simple_events(events)) {
        loop->set_running(false);
      }
      if (events.event.type == SDL_KEYDOWN) {
        if (events.event.key.keysym.sym == SDLK_d) {
          plataform->auto_move_x();
        }
        if (events.event.key.keysym.sym == SDLK_a) {
          plataform->auto_move_x_negative();
        }
      }

    SDL_RenderPresent(render.renderer);

    // set fps delay
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }


    SDL_GL_SwapWindow(render.window);
    continue;
  }

  // drop app
  app->quit_sdl2(render);

  return 0;
}
