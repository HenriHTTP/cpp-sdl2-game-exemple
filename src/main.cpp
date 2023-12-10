#include "../includes/game.hpp"

SDL_Texture* loadTexture(const std::string& filePath,
                         core::core_renderer& render);

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

  app->background_color_sdl2(render, rgb);

  /*
this is a test for implementing textures in the future as this has no class or
structure implemented
*/

  // texturs instance
  SDL_Texture* texture = loadTexture("../assets/textures/cube.png", render);

  if (!texture) {
    std::cerr << "Failed: Texture is not found" << '\n';
    return -1;
  }

  // event instance
  std::shared_ptr<event::event_sdl2> event_processor =
      std::make_shared<event::event_sdl2>();

  event::listener_event events;

  // object instance
  std::shared_ptr<object::object_moviment> object =
      std::make_shared<object::object_moviment>();

  // frame instance

  // std::shared_ptr<object::object_rectangle_attributes> frame =
  //     std::make_shared<object::object_rectangle_attributes>();

  // frame->set_width(75);
  // frame->set_height(75);
  // frame->set_position_center(screen);
  // frame->set_speed_x(5);
  // frame->set_speed_y(5);

  // frame instance with vector smart_ptr
  std::vector<std::shared_ptr<object::object_rectangle_attributes>> vect_frames(
      5);

  for (size_t i{0}; i < vect_frames.size(); ++i) {
    vect_frames[i] = std::make_shared<object::object_rectangle_attributes>();
    vect_frames[i]->set_width(75);
    vect_frames[i]->set_height(75);
    vect_frames[i]->set_position_center(screen);
    vect_frames[i]->set_speed_x(5);
    vect_frames[i]->set_speed_y(5);
    vect_frames[i]->set_texture(texture);
  }
  // fps limit
  const int targetFPS = 60;
  const int frameDelay = 1000 / targetFPS;

  // main loop
  std::shared_ptr<core::core_running> loop =
      std::make_shared<core::core_running>();

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
      SDL_Rect destRect = frame->get_rectangle();
      // SDL_SetRenderDrawColor(render.renderer, 0, 0, 255, 255);
      // SDL_RenderFillRect(render.renderer, &frame->get_rectangle());
      SDL_RenderCopy(render.renderer, frame->get_texture(), NULL, &destRect);
    }

    SDL_RenderPresent(render.renderer);

    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }

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
    // std::cerr << "loop is running" << '\n';
    continue;
  }

  // drop app
  app->quit_sdl2(render);

  return 0;
}

SDL_Texture* loadTexture(const std::string& filePath,
                         core::core_renderer& render) {
  // Carrega a imagem usando SDL_image
  SDL_Surface* surface = IMG_Load(filePath.c_str());
  if (!surface) {
    std::cerr << "Failed to load image: " << IMG_GetError() << '\n';
    return nullptr;
  }

  // Cria uma textura a partir da superfície
  SDL_Texture* texture = SDL_CreateTextureFromSurface(render.renderer, surface);
  if (!texture) {
    std::cerr << "Failed to create texture: " << SDL_GetError() << '\n';
  }

  // Libera a superfície, pois a textura já foi criada
  SDL_FreeSurface(surface);

  return texture;
}