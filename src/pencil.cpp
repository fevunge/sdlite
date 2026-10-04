#include <sdloo.hpp>
#include <SDL2/SDL_pixels.h>

sdl::Pencil::Pencil()
{
}

sdl::Pencil::Pencil(const sdl::Color &color) : color(color)
{
}

sdl::Pencil::~Pencil()
{
}

bool sdl::Pencil::drawVLine(int x, int start, int end, sdl::Window &window)
{
    if (end < start)
    {
        start += end;
        end = start - end;
        start -= end;
    }
    if (end < 0 || start >= window.getHeight() || x < 0 || x >= window.getWidth())
        return 0; // no single point of the line is on screen
    if (start < 0)
        start = 0; // clip
    if (end >= window.getHeight())
        end = window.getHeight() - 1; // clip

    Uint32 colorSDL = SDL_MapRGBA(fmt, color.r, color.g, color.b, color.a);
    Uint32 *bufp;

    bufp = (Uint32 *)srf->pixels + y1 * srf->pitch / 4 + x;
    for (int y = start; y <= end; y++)
    {
        *bufp = colorSDL;
        bufp += srf->pitch / 4;
    }
    return (true);
}
