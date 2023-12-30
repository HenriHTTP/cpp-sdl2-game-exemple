#include "../includes/game.hpp"

int main()
{
    // renderer instance
    core::core_renderer render;

    // screen instance
    auto screen = std::make_shared<core::core_screen>(400, 800);

    // sdl instance
    auto app = std::make_shared<core::core_sdl2>();

    app->init_sdl2();
    app->init_sdl2_ttf();
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
    auto object_colision = std::make_shared<object::object_rectangle_attributes>();
    object_colision->set_width(20);
    object_colision->set_height(20);
    object_colision->set_position_center(screen);
    object_colision->set_speed_x(7);
    object_colision->set_speed_y(7);

    auto player = std::make_shared<object::object_rectangle_attributes>();
    player->set_width(100);
    player->set_height(20);
    player->set_position_center(screen);
    auto end_y = screen->get_height() - player->get_height();
    player->set_positon_y(end_y);
    player->set_speed_x(5);
    player->set_speed_y(5);

    auto opponent = std::make_shared<object::object_rectangle_attributes>();
    opponent->set_width(100);
    opponent->set_height(20);
    opponent->set_position_center(screen);
    opponent->set_positon_y(0);
    opponent->set_speed_x(5);
    opponent->set_speed_y(5);

    // font instance
    auto font_asset = std::make_shared<asset::font>("../assets/fonts/font.ttf", 30);
    font_asset->set_ttf_font();
    SDL_Color font_color{255, 255, 255, 255};
    font_asset->set_text_surface("score", font_color);
    font_asset->set_texture(render.renderer);

    // main loop
    auto loop = std::make_shared<core::core_running>();

    while (loop->get_running())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (!loop->get_running())
        {
            app->quit_sdl2(render);
            return -1;
        }

        /* draw rectangle with sdl*/
        SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(render.renderer, &player->get_rectangle());

        SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(render.renderer, &opponent->get_rectangle());

        SDL_SetRenderDrawColor(render.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(render.renderer, &object_colision->get_rectangle());

        SDL_RenderDrawLine(render.renderer, 0, screen->get_height() / 2, screen->get_height(),
                           screen->get_height() / 2);

        /* position rectangle on the screen */
        SDL_Rect scoreRect = {0, 400, 0, 0};
        SDL_QueryTexture(font_asset->get_texture(), nullptr, nullptr, &scoreRect.w, &scoreRect.h);
        SDL_RenderCopy(render.renderer, font_asset->get_texture(), nullptr, &scoreRect);

        object->auto_move(object_colision, screen);

        if (object_colision->colision_x(player) || object_colision->colision_x(opponent))
        {
            object_colision->set_negative_speed_x();
        }

        if (object_colision->colision_y(player) || object_colision->colision_y(opponent))
        {
            object_colision->set_negative_speed_y();
        }

        player->colision_width_screen(screen);
        opponent->move_towards_with_randomness(object_colision, 5, 100);

        while (SDL_PollEvent(&events.event) != 0)
        {
            if (event_processor->simple_events(events))
            {
                loop->set_running(false);
            }
            if (events.event.type == SDL_KEYDOWN)
            {
                if (events.event.key.keysym.sym == SDLK_d)
                {
                    player->set_speed_x(20);
                    player->auto_move_x();
                }
                if (events.event.key.keysym.sym == SDLK_a)
                {
                    player->set_speed_x(20);
                    player->auto_move_x_negative();
                }

                if (events.event.key.keysym.sym == SDLK_RIGHT)
                {
                    opponent->set_speed_x(20);
                    opponent->auto_move_x();
                }
                if (events.event.key.keysym.sym == SDLK_LEFT)
                {
                    opponent->set_speed_x(20);
                    opponent->auto_move_x_negative();
                }
            }
        }

        SDL_RenderPresent(render.renderer);
        SDL_GL_SwapWindow(render.window);
        SDL_Delay(12);
        continue;
    }

    // drop app
    app->quit_sdl2(render);

    return 0;
}
