#include "../../includes/object/object.hpp"

namespace object {
void object_moviment::auto_move(object_rectangle_attributes& frame,
                                std::shared_ptr<core::core_screen> screen) {
  frame.rectangle.x += frame.speed_x;
  frame.rectangle.y += frame.speed_y;

  if (frame.rectangle.x < 0 ||
      frame.rectangle.x + frame.rectangle.w > screen->get_width()) {
    frame.speed_x = -frame.speed_x;
  }

  if (frame.rectangle.y < 0 ||
      frame.rectangle.y + frame.rectangle.h > screen->get_height()) {
    frame.speed_y = -frame.speed_y;
  }
}

void object_moviment::random_position_x(object_rectangle_attributes& frame,
                                        std::shared_ptr<core::core_screen> screen) {
  int n_position =
      std::experimental::randint(10, (screen->get_width() - frame.rectangle.x));
  frame.rectangle.x = n_position;
  std::cerr << "Message: x  position : " << n_position << '\n';
}

void object_moviment::bellow_move(object_rectangle_attributes& frame,
                                 std::shared_ptr<core::core_screen>  screen) {
  static int object_leaks{};
  std::cerr << "Message: Positon x :" << frame.rectangle.x << '\n';
  frame.rectangle.y += frame.speed_y;

  if (frame.rectangle.y > screen->get_height() ||
      frame.rectangle.y == screen->get_height() - frame.rectangle.h) {
    ++object_leaks;
    std::cerr << "Failed: messsage object overflow" << '\n';
    std::cerr << "Failed: message object leak windown " << object_leaks << '\n';
    frame.rectangle.y = 0;
    this->random_position_x(frame, screen);
  }
}

}  // namespace object