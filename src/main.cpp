#include <memory.h>

#include <memory>

#include "../includes/core/core.hpp"
#include "../includes/event/event.hpp"
#include "../includes/object/object.hpp"

int main() {
  // renderer instance
  core::core_renderer render;

  // screen instance
  std::shared_ptr<core::core_screen> screen =
      std::make_shared<core::core_screen>(1280, 720);

  // sdl instance
  std::shared_ptr<core::core_sdl2> app = std::make_shared<core::core_sdl2>();

  if (!app->init_sdl2()) {
    return -1;
  } else {
    std::cerr << "Menssage: sucess to init SDL2" << '\n';
  }

  app->create_sdl2_window(render, screen);
  std::cerr << screen->get_width() << std::endl;

  // rgb instance
  std::shared_ptr<core::core_rgb> rgb =
      std::make_shared<core::core_rgb>(255, 255, 255, 255);
  // rgb->red = 255;
  // rgb->blue = 255;
  // rgb->green = 255;

  app->background_color_sdl2(render, rgb);

  // event instance
  std::shared_ptr<event::event_sdl2> event_processor =
      std::make_shared<event::event_sdl2>();
  event::listener_event events;

  // frame instance
  std::shared_ptr<object::object_moviment> move =
      std::make_shared<object::object_moviment>();

  std::shared_ptr<object::object_rectangle_attributes> frame =
      std::make_shared<object::object_rectangle_attributes>();

  // frame.rectangle.w = 75;
  // frame.rectangle.h = 75;
  // frame.rectangle.x = screen->get_width() / 2 - frame.rectangle.w / 2;
  // frame.rectangle.y = screen->get_height() / 2 - frame.rectangle.h / 2;
  // frame.speed_x = 5;
  // frame.speed_y = 5;

  frame->set_width(75); 
  frame->set_height(75); 
  frame->set_position_center(screen);
  frame->set_speed_x(5);
  frame->set_speed_y(5);

  // fps limit
  const int targetFPS = 60;
  const int frameDelay = 1000 / targetFPS;

  // main loop
  std::shared_ptr<core::core_running> loop =
      std::make_shared<core::core_running>();

  while (loop->get_running()) {
    Uint32 frameStart = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);
    // SDL_GL_SwapWindow(render.window);

    if (!loop->get_running()) {
      std::cerr << "Failed: loop is not running" << '\n';
      app->quit_sdl2(render);
      return -1;
    }

    // while (SDL_PollEvent(&event) != 0) {
    //   if (event.type == SDL_QUIT) {
    //     std::cerr << "Menssage: loop is end" << std::endl;
    //     app->quit_sdl2(render);
    //     return -1;
    //   }
    //   if (event.type == SDL_KEYDOWN) {
    //     if (event.key.keysym.sym == SDLK_ESCAPE) {
    //       std::cerr << "Menssage: SDL quit and close " << std::endl;
    //       app->quit_sdl2(render);
    //       return -1; ;
    //     }
    //   }
    // }

    while (SDL_PollEvent(&events.event) != 0) {
      if (event_processor->simple_events(events)) {
        loop->set_running(false);
      }
      if (events.event.button.button == SDL_BUTTON_LEFT) {
        if (move->object_clicked(events, frame)) {
          std::cerr << "acertou o objeto" << '\n';
          move->random_position_x(frame, screen);
        }
      }
    }

    // // Move the rectangle automatically
    // frame.rectangle.x += frame.speed_x;
    // frame.rectangle.y += frame.speed_y;

    // // Invert direction when hitting the screen edges
    // if (frame.rectangle.x < 0 ||frame.rectangle.x + frame.rectangle.w >
    // screen.width) {
    //   frame.speed_x = -frame.speed_x;
    // }

    // if (frame.rectangle.y < 0 || frame.rectangle.y + frame.rectangle.h >
    // screen.height) {
    //   frame.speed_y = -frame.speed_y;
    // }
    // move->auto_move(frame, screen);
    move->bellow_move(frame, screen);
    SDL_SetRenderDrawColor(render.renderer, 75, 0, 75, 255);
    SDL_RenderFillRect(render.renderer, &frame->get_rectangle());
    SDL_RenderPresent(render.renderer);

    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
    // frame::auto_move(frame ,1280,720);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0, screen.width, screen.height, 0, -1, 1);
    // glMatrixMode(GL_MODELVIEW);

    // Draw a line
    // glBegin(GL_LINES);

    // glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    // glVertex2f(50, 50);
    // glVertex2f(350, 350);

    // glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
    // glVertex2f(100, 50);
    // glVertex2f(50, 250);

    // glEnd();

    // Draw the rectangle

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // glOrtho(0, screen.width, screen.height, 0, -1, 1);
    // glMatrixMode(GL_MODELVIEW);

    // // Draw the rectangle
    // glBegin(GL_QUADS);
    // glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    // glVertex2f(frame.rectangle.x, frame.rectangle.y);
    // glVertex2f(frame.rectangle.x + frame.rectangle.w, frame.rectangle.y);
    // glVertex2f(frame.rectangle.x + frame.rectangle.w,
    //            frame.rectangle.y + frame.rectangle.h);
    // glVertex2f(frame.rectangle.x, frame.rectangle.y + frame.rectangle.h);
    // glEnd();

    SDL_GL_SwapWindow(render.window);
    //  SDL_Delay(16);
    // std::cerr << "loop is running" << '\n';
    continue;
  }

  // drop app
  app->quit_sdl2(render);

  return 0;
}
