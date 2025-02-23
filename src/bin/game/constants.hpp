#pragma once

#include "sdl_utils.hpp"
#include "sprite.hpp"
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <string>

constexpr int SCREEN_WIDTH = 1400;
constexpr int SCREEN_HEIGHT = 800;

constexpr int FIELD_WIDTH = 1400;
constexpr int FIELD_HEIGHT = 700;
constexpr int PUCK_SIZE = 80;
constexpr int BAT_SIZE = 100;

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
const inline std::string WIND_RIGHT_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/wind-right.png";
const inline std::string WIND_LEFT_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/wind-left.png";

const inline std::string W_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/w.png";
const inline std::string A_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/a.png";
const inline std::string S_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/s.png";
const inline std::string D_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/d.png";
const inline std::string F_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/f.png";

const inline std::string UP_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/up.png";
const inline std::string LEFT_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/left.png";
const inline std::string RIGHT_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/right.png";
const inline std::string DOWN_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/down.png";
const inline std::string K_KEY_SPRITE_PATH =
    std::string(ASSETS_PATH) + "/keys/k.png";

const inline std::string SMACK_SOUND_PATH =
    std::string(ASSETS_PATH) + "/smack.wav";

inline SDL_Surface *const ICON_SURFACE = loadImage(BAT_BLUE_SPRITE_PATH);

inline SDL_Texture *const PUCK_TEXTURE =
    loadTexture(RENDERER, PUCK_SPRITE_PATH);
inline SDL_Texture *const BAT_BLUE_TEXTURE =
    loadTexture(RENDERER, BAT_BLUE_SPRITE_PATH);
inline SDL_Texture *const BAT_RED_TEXTURE =
    loadTexture(RENDERER, BAT_RED_SPRITE_PATH);
inline SDL_Texture *const FIELD_TEXTURE =
    loadTexture(RENDERER, FIELD_SPRITE_PATH);
inline SDL_Texture *const WIND_RIGHT_TEXTURE =
    loadTexture(RENDERER, WIND_RIGHT_SPRITE_PATH);
inline SDL_Texture *const WIND_LEFT_TEXTURE =
    loadTexture(RENDERER, WIND_LEFT_SPRITE_PATH);

inline SDL_Texture *const W_KEY_TEXTURE =
    loadTexture(RENDERER, W_KEY_SPRITE_PATH);
inline SDL_Texture *const A_KEY_TEXTURE =
    loadTexture(RENDERER, A_KEY_SPRITE_PATH);
inline SDL_Texture *const S_KEY_TEXTURE =
    loadTexture(RENDERER, S_KEY_SPRITE_PATH);
inline SDL_Texture *const D_KEY_TEXTURE =
    loadTexture(RENDERER, D_KEY_SPRITE_PATH);
inline SDL_Texture *const F_KEY_TEXTURE =
    loadTexture(RENDERER, F_KEY_SPRITE_PATH);

inline SDL_Texture *const UP_KEY_TEXTURE =
    loadTexture(RENDERER, UP_KEY_SPRITE_PATH);
inline SDL_Texture *const LEFT_KEY_TEXTURE =
    loadTexture(RENDERER, LEFT_KEY_SPRITE_PATH);
inline SDL_Texture *const DOWN_KEY_TEXTURE =
    loadTexture(RENDERER, DOWN_KEY_SPRITE_PATH);
inline SDL_Texture *const RIGHT_KEY_TEXTURE =
    loadTexture(RENDERER, RIGHT_KEY_SPRITE_PATH);
inline SDL_Texture *const K_KEY_TEXTURE =
    loadTexture(RENDERER, K_KEY_SPRITE_PATH);

const inline Sprite BAT_BLUE_SPRITE = Sprite(
    BAT_BLUE_TEXTURE, {BAT_SIZE / 2.0f, BAT_SIZE / 2.0f}, BAT_SIZE, BAT_SIZE);
const inline Sprite BAT_RED_SPRITE = Sprite(
    BAT_RED_TEXTURE, {BAT_SIZE / 2.0f, BAT_SIZE / 2.0f}, BAT_SIZE, BAT_SIZE);
const inline Sprite PUCK_SPRITE = Sprite(
    PUCK_TEXTURE, {PUCK_SIZE / 2.0f, PUCK_SIZE / 2.0f}, PUCK_SIZE, PUCK_SIZE);

inline TTF_Font *const FONT =
    loadFontOrFail(std::string(ASSETS_PATH) + "/font.ttf", 200);

inline static Mix_Chunk *const SMACK_SOUND = loadMixerChunkOrFail(SMACK_SOUND_PATH);
