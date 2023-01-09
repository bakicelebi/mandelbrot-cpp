#include <Frame.hpp>
#include<iostream>
#include<string>

int main(int argc, char** argv)
{
    std::string usage = "usage: width height fps";
    if(argc != 4)
    {
        std::cout << usage << std::endl;
        return 0;
    }


    uint width, height, fps;
    try
    {
        width = std::stoul(std::string(argv[1]));
        height = std::stoul(std::string(argv[2]));
        fps = std::stoul(std::string(argv[3]));
    }
    catch(const std::exception& e)
    {
        std::cout << usage << std::endl;
        return 0;
    }
    
    Frame mainFrame = Frame(width, height, fps);
    mainFrame.startLoop();
    return 0;
}