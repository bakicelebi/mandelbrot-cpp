//--------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
//--------------------------------------------------------------------------------------------------
using namespace sf;
//--------------------------------------------------------------------------------------------------
class Frame
{
    //Constants for Frame
    public:
        static const uint width = 900;
        static const uint height = 900;

    //Members
    private:
        RenderWindow *window;
        Event event;
        float zoom = 0.0f;
        float centerX = 0.0f;
        float centerY = 0.0f;
        Vector2f oldMousePosition;
        Vector2f newMousePosition;
        bool isDrag = false;
        float mandelBrotWidth;
        float mandelBrotHeight;
    public:
        //Constructor | Destructor
        Frame();
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