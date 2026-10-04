#include <sdloo.hpp>

sdl::App::App()
{
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