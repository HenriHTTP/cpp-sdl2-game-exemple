#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <memory.h>

#include <iostream>
#include <memory>

#include "../../includes/core/core.hpp"
#include "../../includes/event/event.hpp"

namespace object
{

class object_rectangle_attributes

/**
 * @class object_rectangle_attributes
 * @brief this class representing a primitive rectangle object.
 *
 * @details Manages the attributes of a primitive rectangle object, including
 * position, velocity, dimension, and texture.
 */

{
  private:
    /**
     * @brief Class attributes
     *
     * @details The class attributes using primitive types int and SDL structure rectangle,texture.
     */

    SDL_Rect rectangle{};
    SDL_Texture *Texture{};
    int speed_x;
    int speed_y;

  public:
    /**
     * @brief Default construtor class object_moviment
     *
     * @details the all params contructor is NULL
     */

    object_rectangle_attributes() = default;
    object_rectangle_attributes(const int &speed_x, const int &speed_y, const int &width, const int &height)
        : speed_x(speed_x), speed_y(speed_y)
    {
        set_width(width);
        set_height(height);
    };

    /**
     * @brief configuiration methods (set)
     *
     * @details this section contains set methods prototypes
     */

    void set_speed_x(const int &speed_x);
    void set_negative_speed_x();
    void set_negative_speed_y();
    void set_speed_y(const int &speed_y);
    bool set_texture(const std::string &file_path, core::core_renderer &render);
    void set_positon_x(const int &positon_x);
    void set_positon_y(const int &positon_y);
    void set_position_center(std::shared_ptr<core::core_screen> &screen);
    void set_width(const int &widht);
    void set_height(const int &height);

    /**
     * @brief configuiration methods (get)
     *
     * @details this section contains get methods prototypes
     */

    const SDL_Rect &get_rectangle() const;
    SDL_Texture *get_texture() const;
    int get_speed_x() const;
    int get_speed_y() const;
    int get_position_x() const;
    int get_position_y() const;
    int get_width() const;
    int get_height() const;

    /**
     * @brief configuiration abstract moviments methods
     *
     * @details this section contains moviments methods prototypes
     */

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
    void colision_width_screen(std::shared_ptr<core::core_screen> &screen);
    void move_towards_with_randomness(const std::shared_ptr<object_rectangle_attributes> &target, int speed,
                                      int randomness);
};

class object_moviment

/**
 * @class object_moviment
 * @brief Class representing a primitive movement.
 *
 * @details Manages the attributes of an object's movements, including
 * collision, velocity, gravity, and event click on the object.
 * @note this class dont have anyone atribute
 */

{
  public:
    /**
     * @brief Default construtor class object_moviment
     *
     * @details the all params contructor is NULL
     */

    object_moviment() = default;

    /**
     * @brief configuiration abstract moviments methods
     *
     * @details this section contains moviments methods prototypes
     */

    void auto_move(std::shared_ptr<object_rectangle_attributes> &frame, std::shared_ptr<core::core_screen> &screen);
    void bellow_move(std::shared_ptr<object_rectangle_attributes> &frame, std::shared_ptr<core::core_screen> &screen);
    bool object_clicked(event::listener_event &event, std::shared_ptr<object_rectangle_attributes> &frame);
};

}; // namespace object

#endif // OBJECT_H
