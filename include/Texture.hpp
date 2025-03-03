//#ifndef GAME_STATE_HPP
//#define GAME_STATE_HPP
//#include "Graphics.hpp"
#include "common.hpp"
//#endif

#ifndef SDL_INCLUDES
#define SDL_INCLUDES
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#endif

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>
class Texture {
    public:
        // Initializes variables
        Texture();

        // Deallocates memory
        ~Texture();

        // Loads images from a file
        bool loadFromFile( std::string path);

        // Deallocates texture
        void free();

        // Renders texture at a specific point
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

        // Image dimensions
        int getWidth();
        int getHeight();

    private:
        // The texture
        SDL_Texture* mTexture;

        // Image dimensions
        int mWidth;
        int mHeight;
};

#endif
