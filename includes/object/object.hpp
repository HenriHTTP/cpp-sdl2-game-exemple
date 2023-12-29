#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <memory.h>

// #include <experimental/random>
#include <iostream>
#include <memory>

#include "../../includes/core/core.hpp"
#include "../../includes/event/event.hpp"

namespace object
{

struct object_rectangle_attributes
{
  private:
    SDL_Rect rectangle{};
    SDL_Texture *Texture{};
    int speed_x;
    int speed_y;

  public:
    object_rectangle_attributes() = default;

    void set_speed_x(const int &speed_x);
    void set_negative_speed_x();
    void set_negative_speed_y();
    void set_speed_y(const int &speed_y);
    bool set_texture(const std::string &file_path, core::core_renderer &render);
    void set_positon_x(const int &positon_x);
    void set_positon_y(const int &positon_y);
    void set_position_center(std::shared_ptr<core::core_screen> screen);
    void set_width(const int &widht);
    void set_height(const int &height);

    const SDL_Rect &get_rectangle() const;
    SDL_Texture *get_texture() const;
    int get_speed_x() const;
    int get_speed_y() const;
    int get_position_x() const;
    int get_position_y() const;
    int get_width() const;
    int get_height() const;

    void auto_move_x();
    void auto_move_x_negative();
    void auto_move_y();
    void auto_move_y_negative();
    void auto_move_jump();
    void auto_fall();
    void auto_move();
    void auto_gravity();
    bool colision_x(std::shared_ptr<object_rectangle_attributes> &other);
    bool colision_y(std::shared_ptr<object_rectangle_attributes> &other);
};

class object_moviment
{
  public:
    object_moviment() = default;

    void auto_move(std::shared_ptr<object_rectangle_attributes> &frame, std::shared_ptr<core::core_screen> &screen);
    void bellow_move(std::shared_ptr<object_rectangle_attributes> &frame, std::shared_ptr<core::core_screen> &screen);

    bool object_clicked(event::listener_event &event, std::shared_ptr<object_rectangle_attributes> &frame);
};
}; // namespace object

#endif // OBJECT_H
