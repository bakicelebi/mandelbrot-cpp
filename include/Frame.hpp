//--------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
//--------------------------------------------------------------------------------------------------
using namespace sf;
//--------------------------------------------------------------------------------------------------
class Frame
{
    //Members
    private:
        RenderWindow *window;
        uint fps;
        uint width;
        uint height;
        Event event;
        float zoom = 0.0f;
        float centerX = 0.0f;
        float centerY = 0.0f;
        Vector2f oldMousePosition;
        Vector2f newMousePosition;
        bool isDrag = false;
        float mandelBrotWidth;
        float mandelBrotHeight;
        bool isMandelBrot = true;
        float isColor = 0.0;
        Image currentFractal;

    public:
        //Constructor | Destructor
        Frame(uint width, uint height, uint fps);
        ~Frame();

    //Methods
    public:
        void startLoop();

    private:
        Vector2f getMousePosition();
        float map(float xy, float a, float b, float c, float d);
        float getMouseDeltaX();
        float getMouseDeltaY();

};