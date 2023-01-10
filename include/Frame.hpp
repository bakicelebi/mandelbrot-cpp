//--------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
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
        Shader *mandelbrotShader;
        Shader *juliaShader;

    public:
        //Constructor | Destructor
        Frame(uint width, uint height, uint fps);
        ~Frame();

    //Methods
    public:
        void startLoop();
        static void saveWindowContentToFile(RenderWindow *window, std::string fileName);
    private:
        Vector2f getMousePosition();
        float map(float xy, float a, float b, float c, float d);
        float getMouseDeltaX();
        float getMouseDeltaY();
        void initializeShaderUniforms(Shader *shader);
        void update(Shader *shader);
        std::string createFileNameWithTimeStamp();

};