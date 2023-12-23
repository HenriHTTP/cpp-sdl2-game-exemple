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
  auto rgb = std::make_shared<core::core_rgb>(0, 0, 0, 255);

  app->background_color_sdl2(render, rgb);

  // event instance
  auto event_processor = std::make_shared<event::event_sdl2>();

  event::listener_event events;

  // object instance
  auto object = std::make_shared<object::object_moviment>();

  // player instance
  auto object_colision =
      std::make_shared<object::object_rectangle_attributes>();
  object_colision->set_width(30);
  object_colision->set_height(30);
  object_colision->set_position_center(screen);
  object_colision->set_speed_x(5);
  object_colision->set_speed_y(5);

  auto player = std::make_shared<object::object_rectangle_attributes>();
  player->set_width(250);
  player->set_height(30);
  player->set_position_center(screen);
  auto end_y = screen->get_height() - player->get_height();
  player->set_positon_y(end_y);
  player->set_speed_x(5);
  player->set_speed_y(5);

  auto opponent = std::make_shared<object::object_rectangle_attributes>();
  opponent->set_width(250);
  opponent->set_height(30);
  opponent->set_position_center(screen);
  opponent->set_positon_y(0);
  opponent->set_speed_x(5);
  opponent->set_speed_y(5);

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

    SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(render.renderer, &player->get_rectangle());

    SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(render.renderer, &opponent->get_rectangle());

    SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(render.renderer, &object_colision->get_rectangle());

    SDL_RenderDrawLine(render.renderer, 0, screen->get_height() / 2,
                       screen->get_height(), screen->get_height() / 2);

    object->auto_move(object_colision, screen);
    if (object_colision->colision_x(player) ||
        object_colision->colision_x(opponent)) {
      object_colision->set_negative_speed_x();
    }
    if (object_colision->colision_y(player) ||
        object_colision->colision_y(opponent)) {
      object_colision->set_negative_speed_y();
    }

    while (SDL_PollEvent(&events.event) != 0) {
      if (event_processor->simple_events(events)) {
        loop->set_running(false);
      }
      if (events.event.type == SDL_KEYDOWN) {
        if (events.event.key.keysym.sym == SDLK_d) {
          player->set_speed_x(20);
          player->auto_move_x();
        }
        if (events.event.key.keysym.sym == SDLK_a) {
          player->set_speed_x(20);
          player->auto_move_x_negative();
        }

        if (events.event.key.keysym.sym == SDLK_RIGHT) {
          opponent->set_speed_x(20);
          opponent->auto_move_x();
        }
        if (events.event.key.keysym.sym == SDLK_LEFT) {
          opponent->set_speed_x(20);
          opponent->auto_move_x_negative();
        }
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
