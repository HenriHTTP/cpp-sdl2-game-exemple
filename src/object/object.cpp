#include "../../includes/object/object.hpp"

namespace object {

void object_rectangle_attributes::set_speed_x(const int& speed_x) {
  this->speed_x = speed_x;
}

void object_rectangle_attributes::set_negative_speed_x() {
  this->speed_x = -this->get_speed_x();
  ;
}

void object_rectangle_attributes::set_speed_y(const int& speed_y) {
  this->speed_y = speed_y;
}

void object_rectangle_attributes::set_negative_speed_y() {
  this->speed_y = -this->get_speed_y();
}

bool object_rectangle_attributes::set_texture(const std::string& file_path,
                                              core::core_renderer& render) {
  SDL_Surface* surface = IMG_Load(file_path.c_str());

  if (!surface) {
    std::cerr << "Failed to load image: " << '\n';
    return false;
  }

  this->Texture = SDL_CreateTextureFromSurface(render.renderer, surface);

  if (Texture == nullptr) {
    std::cerr << "Failed to create texture: " << '\n';
    return false;
  }
  SDL_FreeSurface(surface);
  return true;
}

void object_rectangle_attributes::set_positon_x(const int& positon_x) {
  this->rectangle.x = positon_x;
}

void object_rectangle_attributes::set_positon_y(const int& positon_y) {
  this->rectangle.y = positon_y;
}

void object_rectangle_attributes::set_position_center(
    std::shared_ptr<core::core_screen> screen) {
  this->rectangle.x = screen->get_width() / 2 - rectangle.w / 2;
  this->rectangle.y = screen->get_height() / 2 - rectangle.h / 2;
}

void object_rectangle_attributes::set_width(const int& width) {
  this->rectangle.w = width;
}

void object_rectangle_attributes::set_height(const int& height) {
  this->rectangle.h = height;
}

const SDL_Rect& object_rectangle_attributes::get_rectangle() const {
  return this->rectangle;
}

SDL_Texture* object_rectangle_attributes::get_texture() const {
  return this->Texture;
}

int object_rectangle_attributes::get_speed_x() const { return this->speed_x; }
int object_rectangle_attributes::get_speed_y() const { return this->speed_y; }

int object_rectangle_attributes::get_position_x() const {
  return this->rectangle.x;
}
int object_rectangle_attributes::get_position_y() const {
  return this->rectangle.y;
}

int object_rectangle_attributes::get_width() const { return this->rectangle.w; }
int object_rectangle_attributes::get_height() const {
  return this->rectangle.h;
}

void object_rectangle_attributes::auto_move_x() {
  this->rectangle.x += speed_x;
}

void object_rectangle_attributes::auto_move_x_negative() {
  this->rectangle.x -= speed_x;
}

void object_rectangle_attributes::auto_move_y() {
  this->rectangle.y += speed_y;
}

void object_rectangle_attributes::auto_move_jump() {
  this->rectangle.y -= speed_y;
}
void object_rectangle_attributes::auto_fall() { this->rectangle.y += speed_y; }
void object_rectangle_attributes::auto_move() {
  this->auto_move_x();
  this->auto_move_y();
}

bool object_rectangle_attributes::colision_x(
    std::shared_ptr<object_rectangle_attributes>& other) {
  bool is_colision_x =
      (this->get_position_x() + this->get_width() >= other->get_position_x()) &&
      (this->get_position_x() <=
       other->get_position_x() + other->get_width()) &&
      (this->get_position_y() <=
       other->get_position_y() + other->get_height()) &&
      (this->get_position_y() + this->get_height() >= other->get_position_y());
  if (is_colision_x) {
    std::cerr << "Menssage: colision between obj in x" << '\n';
    return true;
  }

  return false;
}

bool object_rectangle_attributes::colision_y(
    std::shared_ptr<object_rectangle_attributes>& other) {
  bool is_colision_y =
      (this->get_position_y() <=
       other->get_position_y() + other->get_height()) &&
      (this->get_position_y() + this->get_height() > other->get_position_y()) &&
      (this->get_position_x() + this->get_width() >= other->get_position_x()) &&
      (this->get_position_x() <= other->get_position_x() + other->get_width());

  if (is_colision_y) {
    std::cerr << "Menssage: colision between obj in y" << '\n';
    return true;
  }

  return false;
}

void object_rectangle_attributes::auto_gravity() {
  this->rectangle.y += speed_y;
}

void object_moviment::auto_move(
    std::shared_ptr<object_rectangle_attributes>& frame,
    std::shared_ptr<core::core_screen>& screen) {
  frame->auto_move();

  if (frame->get_position_x() < 0 ||
      frame->get_position_x() + frame->get_width() > screen->get_width()) {
    frame->set_speed_x(-frame->get_speed_x());
  }

  if (frame->get_position_y() < 0 ||
      frame->get_position_y() + frame->get_height() > screen->get_height()) {
    frame->set_speed_y(-frame->get_speed_y());
  }
}

void object_moviment::random_position_x(
    std::shared_ptr<object_rectangle_attributes>& frame,
    std::shared_ptr<core::core_screen>& screen) {
  int n_position = std::experimental::randint(
      10, (screen->get_width() - frame->get_position_x()));
  frame->set_positon_x(n_position);
  std::cerr << "Message: x  position : " << n_position << '\n';
}

void object_moviment::bellow_move(
    std::shared_ptr<object_rectangle_attributes>& frame,
    std::shared_ptr<core::core_screen>& screen) {
  static int object_leaks{};

  std::cerr << "Message: Positon x :" << frame->get_position_x() << '\n';
  frame->auto_move_y();
  void colision_frames();

  if (frame->get_position_y() > screen->get_height() ||
      frame->get_position_y() == screen->get_height() - frame->get_height()) {
    ++object_leaks;
    std::cerr << "Failed: messsage object overflow" << '\n';
    std::cerr << "Failed: message object leak windown " << object_leaks << '\n';
    frame->set_positon_y(0);
    this->random_position_x(frame, screen);
  }
}

bool object_moviment::object_clicked(
    event::listener_event& event,
    std::shared_ptr<object_rectangle_attributes>& frame) {
  auto click_on_position_x_inital =
      event.event.button.x >= frame->get_position_x();

  auto click_on_position_x_limit =
      event.event.button.x <= frame->get_position_x() + frame->get_width();

  auto click_on_position_y_inital =
      event.event.button.y >= frame->get_position_y();

  auto click_on_position_y_limit =
      event.event.button.y <= frame->get_position_y() + frame->get_height();

  if (click_on_position_x_inital && click_on_position_x_limit &&
      click_on_position_y_inital && click_on_position_y_limit) {
    return true;
  }

  return false;
}

}  // namespace object