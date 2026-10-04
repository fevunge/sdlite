#include <sdloo.hpp>

sdl::App::App(): initialized(false)
{

    window = new sdl::Window(800, 600);
    pencil = new sdl::Pencil(sdl::RGB_Black);
}

sdl::Pencil *sdl::App::getPencil()
{
    return pencil;
}

sdl::App::~App()
{
    delete pencil;
}