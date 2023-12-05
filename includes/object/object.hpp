#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <SDL.h>
#include <memory.h>

#include <experimental/random>
#include <iostream>
#include <memory>

#include "../../includes/core/core.hpp"

namespace object {

struct object_rectangle_attributes {
  SDL_Rect rectangle{};
  int speed_x;
  int speed_y;
};

class object_moviment_interfaces {
 public:
  virtual ~object_moviment_interfaces() = default;
  virtual void auto_move(object_rectangle_attributes& frame,
                        std::shared_ptr<core::core_screen> screen) = 0;
  virtual void bellow_move(object_rectangle_attributes& frame,
                          std::shared_ptr<core::core_screen> screen) = 0;

 private:
  virtual void random_position_x(object_rectangle_attributes& frame,
                                std::shared_ptr<core::core_screen> screen) = 0;
};

class object_moviment : public object_moviment_interfaces {
 public:
  void auto_move(object_rectangle_attributes& frame,
                std::shared_ptr<core::core_screen> screen) override;
  void bellow_move(object_rectangle_attributes& frame,
                   std::shared_ptr<core::core_screen> screen) override;

 private:
  void random_position_x(object_rectangle_attributes& frame,
                         std::shared_ptr<core::core_screen>  screen) override;
};

}  // namespace object

#endif  // OBJECT_H
