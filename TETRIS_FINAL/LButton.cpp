#include "LButton.h"

//constructor
LButton::LButton() 
{
    mPosition.x = 0; mPosition.y = 0;
    BUTTON_WIDTH = 0; BUTTON_HEIGHT = 0;
    cur_status = MOUSE_OUT;
    pre_status = MOUSE_OUT;
}

void LButton::set_up(const std::string &Button_Image_Path, const int &x, const int &y, SDL_Renderer* renderer)
{
    Button_Image.loadFromFile(Button_Image_Path, renderer);

    mPosition.x = x;
    mPosition.y = y;

    BUTTON_WIDTH = Button_Image.getWidth();
    BUTTON_HEIGHT = Button_Image.getHeight();
}

bool LButton::be_clicked() {
    if(cur_status != MOUSE_DOWN && pre_status == MOUSE_DOWN) 
    {
        return true;
    }

    return false;
}

void LButton::update_button_status() 
{
    pre_status = cur_status;
}

void LButton::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
            //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
            //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
            //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            cur_status = MOUSE_OUT;
        }
            //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    cur_status = MOUSE_OVER_MOTION;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    cur_status = MOUSE_DOWN;
                    break;

                case SDL_MOUSEBUTTONUP:
                    cur_status = MOUSE_UP;
                    break;
            }
        }
    }
}

void LButton::render(SDL_Renderer* renderer)
{
    Button_Image.render(mPosition.x, mPosition.y, renderer);
}

void LButton::set_button_without_texture(int x, int y, int width, int height)
{
    mPosition.x = x;
    mPosition.y = y;

    BUTTON_WIDTH = width;
    BUTTON_HEIGHT = height;
}

int LButton::get_button_width()
{
    return Button_Image.getWidth();
}

int LButton::get_button_height()
{
    return Button_Image.getWidth();
}

void LButton::free()
{
    Button_Image.free();
    mPosition.x = 0;
    mPosition.y = 0;
    BUTTON_WIDTH = 0;
    BUTTON_HEIGHT = 0;
}