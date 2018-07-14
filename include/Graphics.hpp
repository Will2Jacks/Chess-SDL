#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "common.hpp"


#include <string> 

/**@brief Método que retorna um booleano indicando se o movimento é possível
*/

class Graphics{
    public: 
        //metodos

        bool init();
        bool loadMedia();
        void close(); 

        const int SCREEN_WIDTH = 680;
        const int SCREEN_HEIGHT = 680;
}; 

