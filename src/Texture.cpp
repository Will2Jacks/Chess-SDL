#include "../include/Texture.hpp"

Texture::Texture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

bool Texture::loadFromFile( std::string path )
{
    //Deletes what was there before
    free();

    //The texture that will be returned
    SDL_Texture* newTexture = NULL;

    //Loads image into a surface
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Transparency:
        // This line sets color key transparency for the loadedSurface, meaning that a specific color in the image will be treated as fully transparent.

        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Texture from surface
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Frees the surface memory
        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

void Texture::free()
{
    //Frees texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

// This function is responsible for rendering a texture onto the screen at a specified position, with optional transformations like cropping, rotation, and flipping.

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //How much of the texture will be rendered
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Crop the texture (to get parts of the texture)
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render on the screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int Texture::getWidth()
{
    return mWidth;
}

int Texture::getHeight()
{
    return mHeight;
}
