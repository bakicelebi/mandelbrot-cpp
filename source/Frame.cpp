//--------------------------------------------------------------------------------------------------
#include "Frame.hpp"
#include <iostream>
#include <cmath>
//--------------------------------------------------------------------------------------------------
Frame::Frame(uint width, uint height, uint fps)
{
    this->window = new RenderWindow(VideoMode(width, height), "Mandelbrot");
    this->width = width;
    this->height = height;
    this->window->setFramerateLimit(fps);
    
    this->mandelBrotWidth = std::pow(2, 2 - zoom);
    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
    
    this->mandelbrotShader = new Shader();
    this->juliaShader = new Shader();

    this->mandelbrotShader->loadFromFile("../mandelbrot.frag", Shader::Fragment);
    this->juliaShader->loadFromFile("../julia.frag", Shader::Fragment);
}
//--------------------------------------------------------------------------------------------------
Frame::~Frame()
{
    std::cout << "Closed" << std::endl;
    delete this->juliaShader;
    delete this->mandelbrotShader;
    delete this->window;
    this->juliaShader = nullptr;
    this->mandelbrotShader= nullptr;
    this->window = nullptr;
    

}
//--------------------------------------------------------------------------------------------------
void Frame::startLoop()
{
    Vector2f deltaMousePosition;
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(this->event))
        {
            switch (this->event.type)
            {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                if(this->event.mouseButton.button == 0)
                {
                    isDrag = true;
                    oldMousePosition = getMousePosition();
                }
                break;
            case Event::MouseButtonReleased:
                if(this->event.mouseButton.button == 0)
                {
                    isDrag = false;
                }
                break;
            case Event::MouseMoved:
                if(!isDrag) break;
                newMousePosition = getMousePosition();
                centerX -= getMouseDeltaX();
                centerY += getMouseDeltaY();
                oldMousePosition = newMousePosition;
                break;
            case Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta <= -1)
                {
                    this->zoom -= 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (this->height/ this->width) * this->mandelBrotWidth;
                }
                else if (event.mouseWheelScroll.delta >= 1)
                {
                    this->zoom += 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (this->height / this->width) * this->mandelBrotWidth;
                }
                break;
            case Event::KeyPressed:
                switch (this->event.key.code)
                {
                case Keyboard::Add:
                    this->zoom += 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (this->height / this->width) * this->mandelBrotWidth;
                    break;
                case Keyboard::Subtract:
                    this->zoom -= 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (this->height / this->width) * this->mandelBrotWidth;
                    break;
                case Keyboard::M:
                    this->isMandelBrot = true;
                    break;
                case Keyboard::J:
                    this->isMandelBrot = false;
                    break;
                case Keyboard::C:
                    if(this->isColor == 1.0)
                    {
                        this->isColor = 0.0;
                    }
                    else
                    {
                        this->isColor = 1.0;
                    }
                    break;
                case Keyboard::S:
                    Frame::saveWindowContentToFile(window, createFileNameWithTimeStamp());
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        Shader *shader = isMandelBrot ? this->mandelbrotShader : this->juliaShader;

        this->initializeShaderUniforms(shader);

        this->update(shader);
    }
}
//--------------------------------------------------------------------------------------------------
Vector2f Frame::getMousePosition()
{
    return Vector2f(Mouse::getPosition(*window).x, Mouse::getPosition(*window).y);
}
//--------------------------------------------------------------------------------------------------
float Frame::map(float xy, float a, float b, float c, float d)
{
    return (xy - a) * ((d - c) / (b - a)) + c;
}
//--------------------------------------------------------------------------------------------------
float Frame::getMouseDeltaX()
{
    float centerX = (this->mandelBrotWidth / 2) + this->centerX;
    float centerXN = -(this->mandelBrotWidth / 2) + this->centerX;
    float oldX = map(oldMousePosition.x, 0, this->window->getSize().x, centerXN, centerX);
    float newX = map(newMousePosition.x, 0, this->window->getSize().x, centerXN, centerX);
    
    return newX - oldX;
}
//--------------------------------------------------------------------------------------------------
float Frame::getMouseDeltaY()
{
    float centerY = (this->mandelBrotHeight / 2) + this->centerY;
    float centerYN = -(this->mandelBrotHeight / 2) + this->centerY;
    float oldY = map(oldMousePosition.y, 0, this->window->getSize().y, centerYN, centerY);
    float newY = map(newMousePosition.y, 0, this->window->getSize().y, centerYN, centerY);

    return newY - oldY;
}
//--------------------------------------------------------------------------------------------------
void Frame::update(Shader *shader)
{
    auto size = RectangleShape{ Vector2f{(float)this->width, (float)this->height} };
    this->window->clear();
    this->window->draw(size, shader);
    this->window->display();
}

void Frame::initializeShaderUniforms(Shader *shader)
{
    shader->setUniform("res", Vector2f{(float)this->width, (float)this->height});
    shader->setUniform("zoom", this->zoom);
    shader->setUniform("centerX", this->centerX);
    shader->setUniform("centerY", this->centerY);
    shader->setUniform("isColor", this->isColor);
}
//--------------------------------------------------------------------------------------------------
void Frame::saveWindowContentToFile(RenderWindow *window, std::string fileName)
{
    Texture texture;
    texture.create(window->getSize().x, window->getSize().y);
    texture.update(*window);

    if(texture.copyToImage().saveToFile(fileName))
    {
        std::cout << "Current window contents saved to file " << fileName << std::endl;
    }
    else
    {
        std::cout << "Failed to save window content to file: " + fileName << std::endl;
    }
}
//--------------------------------------------------------------------------------------------------
std::string Frame::createFileNameWithTimeStamp()
{
    std::string filePrefix;

    if(this->isMandelBrot)
    {
        filePrefix = "mandelbrot";
    }
    else
    {
        filePrefix = "julia";
    }

    std::time_t ct = std::time(0);
    char* cc = ctime(&ct);

    return filePrefix + " - " + cc + ".png";
}
