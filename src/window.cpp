#include <sdloo.hpp>

sdl::Window::Window()
{
    _object = nullptr;
}

sdl::Window::Window(std::uint32_t width, std::uint32_t height) : width(width), height(height)
{
}

sdl::Window::Window(int width, int height) : width((width < 0) ? 0 : static_cast<std::uint32_t>(width)), height((height < 0) ? 0 : static_cast<std::uint32_t>(height))
{
}

sdl::Window::~Window()
{
}