#include "../../includes/utils/asset.hpp"

namespace asset {
void font::set_font_size(int font_size) { this->font_size = font_size; }
void font::set_file_path(const char* file_path) { this->file_path = file_path; }

void font::set_text_surface(const char* text, SDL_Color& text_color) {
  this->text_surface = TTF_RenderText_Blended(this->ttf_font, text, text_color);
}

void font::set_texture(SDL_Renderer* renderer) {
  this->texture = SDL_CreateTextureFromSurface(renderer, this->text_surface);
  SDL_FreeSurface(this->text_surface);
}

int font::get_font_size() const { return this->font_size; }
const char* font::get_file_path() const { return this->file_path; }

bool font::set_ttf_font() {
  this->ttf_font = TTF_OpenFont(this->file_path, this->font_size);
  return true;
}

TTF_Font* font::get_ttf_font() { return this->ttf_font; }
SDL_Surface* font::get_text_surface() { return this->text_surface; }
SDL_Texture* font::get_texture() { return this->texture; }

}  // namespace asset