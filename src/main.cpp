#include <memory.h>

#include <memory>

#include "../includes/core/core.hpp"
#include "../includes/event/event.hpp"
#include "../includes/object/object.hpp"

int main() {
  // int window_width = 1280;
  // int window_height = 720;
  // SDL_Window* window{};
  // SDL_Renderer* renderer{};
  // if (!core::init_SDL()) {
  //   return 1;
  // }

  // if (!core::create_window(window, window_width, window_height)) {
  //   return 1;
  // }
  // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // if (renderer == nullptr) {
  //   std::cerr << "ERROR: Renderer creation failed: " << std::endl;
  //   core::close(window);
  //   return 1;
  // }

  // core::set_backgroud_color(renderer, 255, 255, 255);

  // int frame_width = 200;
  // int frame_height = 150;
  // int frame_x = (window_width - frame_width) / 2;
  // int frame_y = (window_height - frame_height) / 2;
  // core::render_frame(renderer, frame_x, frame_y, frame_width, frame_height,
  // 75,
  //                    25, 150);

  // SDL_RenderPresent(renderer);
  // SDL_Delay(5000);
  // core::close(window);

  // struct {
  //   int width{1280};
  //   int height{720};
  // } screen;

  // struct {
  //   bool running{true};
  // } loop;

  core::core_renderer render;
  core::core_running loop;
  core::core_screen screen;

  // core::core_sdl2* app = new core::core_sdl2;
  std::shared_ptr<core::core_sdl2> app = std::make_shared<core::core_sdl2>();

  if (!app->init_sdl2()) {
    return -1;
  } else {
    std::cerr << "Menssage: sucess to init SDL2" << '\n';
  }
  // screen attributes
  screen.width = 1280;
  screen.height = 720;

  app->create_sdl2_window(render, screen);
  std::cerr << screen.width << std::endl;

  core::core_rgb rgb;
  rgb.red = 255;
  rgb.blue = 255;
  rgb.green = 255;

  app->background_color_sdl2(render, rgb);

  // event::event_sdl2* event_processor = new event::event_sdl2;

  std::shared_ptr<event::event_sdl2> event_processor =
      std::make_shared<event::event_sdl2>();
  event::listener_event events;

  // frame instance

  // frame::frame_moviment* move = new frame::frame_moviment;
  std::shared_ptr<object::object_moviment> move =
      std::make_shared<object::object_moviment>();

  object::object_rectangle_attributes frame;
  frame.rectangle.w = 75;
  frame.rectangle.h = 75;
  frame.rectangle.x = screen.width / 2 - frame.rectangle.w / 2;
  frame.rectangle.y = screen.height / 2 - frame.rectangle.h / 2;
  frame.speed_x = 5;
  frame.speed_y = 5;

  // fps limit
   const int targetFPS = 60;
   const int frameDelay = 1000 / targetFPS;

  // draw rectangle

  // SDL_Rect rectangle{};

  // struct {
  //   GLfloat x{};
  //   GLfloat y{};
  //   int width{};
  //   int height{};
  //   int speed_x{};
  //   int speed_y{};
  // } draw_rectangle;

  // auto initial_position_x{screen.width / 2 - draw_rectangle.width / 2};
  // auto inital_position_y{screen.height / 2 - draw_rectangle.height / 2};

  // draw_rectangle.width = 50;
  // draw_rectangle.height = 50;

  // rectangle.x = initial_position_x;
  // rectangle.y = inital_position_y;
  // rectangle.w = draw_rectangle.width;
  // rectangle.h = draw_rectangle.height;

  // int moveSpeedX = 5;
  // int moveSpeedY = 5;

  // main loop
  while (loop.running) {
    Uint32 frameStart = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);
   //SDL_GL_SwapWindow(render.window);

    if (loop.running == false) {
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
        loop.running = false;
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
    SDL_SetRenderDrawColor(render.renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(render.renderer, &frame.rectangle);
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

  app->quit_sdl2(render);
  // delete app;
  //
  return 0;
}
