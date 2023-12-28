#ifndef ASSET_H
#define ASSET_H

#include <GL/glew.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory.h>
#include <stab.h>

#include <iostream>
#include <memory>
#include <string>

namespace asset {
class font {
 private:
  const char* file_path{};
  int font_size{};
  TTF_Font* ttf_font{};
  SDL_Texture* texture{};
  SDL_Surface* text_surface{};

 public:
  font() = default;
  font(const char* path, const int& size) : file_path(path), font_size(size) {}

  void set_font_size(int font_size);
  void set_file_path(const char* file_path);
  bool set_ttf_font();
  void set_texture(SDL_Renderer* renderer);
  void set_text_surface(const char* text, SDL_Color& text_color);

  int get_font_size() const;
  const char* get_file_path() const;
  TTF_Font* get_ttf_font();
  SDL_Surface* get_text_surface();
  SDL_Texture* get_texture();
};
}  // namespace asset

#endif  // ASSET_H
