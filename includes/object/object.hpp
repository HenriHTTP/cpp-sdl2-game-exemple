#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <SDL.h>
#include <memory.h>

#include <experimental/random>
#include <iostream>
#include <memory>

#include "../../includes/core/core.hpp"
#include "../../includes/event/event.hpp"

namespace object {

struct object_rectangle_attributes {
 private:
  SDL_Rect rectangle{};
  int speed_x;
  int speed_y;

 public:
  object_rectangle_attributes() = default;

  void set_speed_x(int speed_x);
  void set_speed_y(int speed_y);
  void set_positon_x(int positon_x);
  void set_positon_y(int positon_y);
  void set_position_center(std::shared_ptr<core::core_screen> screen);
  void set_width(int widht);
  void set_height(int height);

  const SDL_Rect& get_rectangle() const;
  int get_speed_x() const;
  int get_speed_y() const;
  int get_position_x() const;
  int get_position_y() const;
  int get_width() const;
  int get_height() const;

  void auto_move_x();
  void auto_move_y();
  void auto_move();
};

class object_moviment_interfaces {
 public:
  virtual ~object_moviment_interfaces() = default;
  virtual void auto_move(std::shared_ptr<object_rectangle_attributes> frame,
                         std::shared_ptr<core::core_screen> screen) = 0;
  virtual void bellow_move(std::shared_ptr<object_rectangle_attributes> frame,
                           std::shared_ptr<core::core_screen> screen) = 0;
  virtual void random_position_x(
      std::shared_ptr<object_rectangle_attributes> frame,
      std::shared_ptr<core::core_screen> screen) = 0;
  virtual bool object_clicked(
      event::listener_event& event,
      std::shared_ptr<object_rectangle_attributes> frame) = 0;
};

class object_moviment : public object_moviment_interfaces {
 public:
  void auto_move(std::shared_ptr<object_rectangle_attributes> frame,
                 std::shared_ptr<core::core_screen> screen) override;
  void bellow_move(std::shared_ptr<object_rectangle_attributes> frame,
                   std::shared_ptr<core::core_screen> screen) override;
  void random_position_x(std::shared_ptr<object_rectangle_attributes> frame,
                         std::shared_ptr<core::core_screen> screen) override;

  bool object_clicked(
      event::listener_event& event,
      std::shared_ptr<object_rectangle_attributes> frame) override;
};
};  // namespace object

#endif  // OBJECT_H
