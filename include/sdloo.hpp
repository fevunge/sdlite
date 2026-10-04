
#ifndef SDLOO_HPP
#define SDLOO_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdint>

namespace sdl
{
    class Window
    {
    private:
        SDL_Window *_object;
        std::uint32_t width;
        std::uint32_t height;

    public:
        Window();
        Window(std::uint32_t width, std::uint32_t height);
        Window(int width, int height);
        ~Window();
        Window(const Window &) = delete;
        Window &operator=(const Window &) = delete;
        std::uint32_t getWidth() const { return width; }
        std::uint32_t getHeight() const { return height; }
    };

    class Color
    {
    private:
        Uint8 r, g, b, a;

    public:
        Color();
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        ~Color();
        Color(const Color &);
        Color &operator=(const Color &);

        Uint8 getR8bit() const { return r; }
        Uint8 getG8bit() const { return g; }
        Uint8 getB8bit() const { return b; }
        Uint8 getA8bit() const { return a; }
        int getR() const { return r; }
        int getG() const { return g; }
        int getB() const { return b; }
        int getA() const { return a; }
    };

    Color operator+(const Color &color, const Color &color2);
    Color operator-(const Color &color, const Color &color2);
    Color operator*(const Color &color, int a);
    Color operator*(int a, const Color &color);
    Color operator/(const Color &color, int a);
    Color overlay(const Color &color, const Color &color2);
    bool operator==(const Color &color, const Color &color2);
    bool operator!=(const Color &color, const Color &color2);

    const Color RGB_Black(0, 0, 0, 255);
    const Color RGB_Red(255, 0, 0, 255);
    const Color RGB_Green(0, 255, 0, 255);
    const Color RGB_Blue(0, 0, 255, 255);
    const Color RGB_Cyan(0, 255, 255, 255);
    const Color RGB_Magenta(255, 0, 255, 255);
    const Color RGB_Yellow(255, 255, 0, 255);
    const Color RGB_White(255, 255, 255, 255);
    const Color RGB_Gray(128, 128, 128, 255);
    const Color RGB_Grey(192, 192, 192, 255);
    const Color RGB_Maroon(128, 0, 0, 255);
    const Color RGB_Darkgreen(0, 128, 0, 255);
    const Color RGB_Navy(0, 0, 128, 255);
    const Color RGB_Teal(0, 128, 128, 255);
    const Color RGB_Purple(128, 0, 128, 255);
    const Color RGB_Olive(128, 128, 0, 255);

    class Pencil
    {
    private:
        Color color;

    public:
        Pencil();
        Pencil(const Color &color);
        ~Pencil();
        bool drawVLine(int x, int start, int end, sdl::Window &window);
        Pencil(const Pencil &) = delete;
        Pencil &operator=(const Pencil &) = delete;
    };

    class App
    {
    private:
        bool initialized;
        Window *window;
        Pencil *pencil;

    public:
        App();
        ~App();
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        Window &getWindow();
        Pencil *getPencil();
    };
}

#endif