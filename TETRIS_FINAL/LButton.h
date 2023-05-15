#ifndef LBUTTON_H
#define LBUTTON_H

#include "Texture.h"

class LButton
{
public:

    enum MOUSE_STATUS
    {
        MOUSE_OUT ,
        MOUSE_OVER_MOTION,
        MOUSE_DOWN,
        MOUSE_UP,
        MOUSE_TOTAL
    };

    //constructor
    LButton();

    //Initializes internal variables
    void set_up(const std::string &Button_Image_Path, const int &x, const int &y, SDL_Renderer* renderer);

    //check the button has been clicked or not
    bool be_clicked();

    //update the pre_status
    void update_button_status();

    //Handles mouse event
    void handleEvent( SDL_Event* e );

    //Shows button sprite
    void render(SDL_Renderer* renderer);

    void set_button_without_texture(int x, int y, int width, int height);

    void free();

    int get_button_width();
    int get_button_height();

    //Currently used global sprite
    MOUSE_STATUS cur_status;
    MOUSE_STATUS pre_status;

private:
    //Top left position
    SDL_Point mPosition;


    //Texture
    Texture Button_Image;

    //button dimension
    int BUTTON_WIDTH;
    int BUTTON_HEIGHT;
};

#endif
