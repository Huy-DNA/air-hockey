#pragma once

#include "sdl_utils.hpp"
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>

constexpr int SCREEN_WIDTH = 1400;
constexpr int SCREEN_HEIGHT = 700;

constexpr int FIELD_WIDTH = 1400;
constexpr int FIELD_HEIGHT = 700;
constexpr int BAT_SIZE = 100;
constexpr int PUCK_SIZE = 80;

SDL_Window *const WINDOW = createWindowOrFail(SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Renderer *const RENDERER = createRendererFromWindowOrFail(WINDOW);

const inline std::string BAT_BLUE_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/bat-blue.png";
const inline std::string BAT_RED_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/bat-red.png";
const inline std::string PUCK_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/puck.png";
const inline std::string FIELD_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/field.jpg";

SDL_Surface *const ICON_SURFACE = loadImage(BAT_BLUE_SPRITE_PATH);

SDL_Texture *const PUCK_TEXTURE = loadTexture(RENDERER, PUCK_SPRITE_PATH);
SDL_Texture *const BAT_BLUE_TEXTURE =
    loadTexture(RENDERER, BAT_BLUE_SPRITE_PATH);
SDL_Texture *const BAT_RED_TEXTURE =
    loadTexture(RENDERER, BAT_RED_SPRITE_PATH);
SDL_Texture *const FIELD_TEXTURE =
    loadTexture(RENDERER, FIELD_SPRITE_PATH);
