//--------------------------------------------------------------------------------------------------
#include "Frame.hpp"
#include <iostream>
#include <cmath>
//--------------------------------------------------------------------------------------------------
Frame::Frame()
{
    this->window = new RenderWindow(VideoMode(width, height), "Mandelbrot");
    this->window->setFramerateLimit(60);
    this->mandelBrotWidth = std::pow(2, 2 - zoom);
    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
}
//--------------------------------------------------------------------------------------------------
Frame::~Frame()
{
    delete this->window;
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
                 std::cout << centerX << " " << centerY << std::endl;
                break;
            case Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta <= -1)
                {
                    this->zoom -= 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
                }
                else if (event.mouseWheelScroll.delta >= 1)
                {
                    this->zoom += 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
                }
                std::cout << zoom << std::endl;
                break;
            case Event::KeyPressed:
                switch (this->event.key.code)
                {
                case Keyboard::Add:
                    this->zoom += 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
                    break;
                case Keyboard::Subtract:
                    this->zoom -= 0.025;
                    this->mandelBrotWidth = std::pow(2, 2 - zoom);
                    this->mandelBrotHeight = (height / width) * this->mandelBrotWidth;
                    break;
                default:
                    break;
                }
                break;
            default:
                //std::cout << this->event.type << std::endl;
                break;
            }
        }

        
        Shader shader;
        
        auto shape = sf::RectangleShape{ sf::Vector2f{ this->window->getSize() } };

        shader.loadFromFile("../mandelbrot.frag", Shader::Fragment);

        shader.setUniform("res", Vector2f{width, height});
        shader.setUniform("zoom", this->zoom);
        shader.setUniform("centerX", this->centerX);
        shader.setUniform("centerY", this->centerY);

        this->window->clear();
        this->window->draw(shape, &shader);
        this->window->display();
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
    std::cout << newY << " - " << oldY << std::endl;

    return newY - oldY;
}
//--------------------------------------------------------------------------------------------------