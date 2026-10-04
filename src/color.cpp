#include <sdlow.hpp>

sdl::Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

sdl::Color::Color(const sdl::Color &color)
{
  this->r = color.r;
  this->g = color.g;
  this->b = color.b;
  this->a = color.a;
}

sdl::Color::~Color()
{
}

sdl::Color &sdl::Color::operator=(const sdl::Color &color)
{
  if (this != &color)
  {
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
    this->a = color.a;
  }
  return *this;
}

sdl::Color operator+(const sdl::Color &color, const sdl::Color &color2)
{
  sdl::Color c(color.getR8bit() + color2.getR8bit(),
               color.getG8bit() + color2.getG8bit(),
               color.getB8bit() + color2.getB8bit(), color.getA8bit() + color2.getA8bit());
  return c;
}

// Subtract two colors
sdl::Color operator-(const sdl::Color &color, const sdl::Color &color2)
{
  sdl::Color c;
  c = sdl::Color(color.getR8bit() - color2.getR8bit(),
                 color.getG8bit() - color2.getG8bit(),
                 color.getB8bit() - color2.getB8bit(),
                 color.getA8bit() - color2.getA8bit());
  return c;
}

sdl::Color operator+(const sdl::Color &color, const sdl::Color &color2)
{
  sdl::Color c(color.getR8bit() + color2.getR8bit(),
               color.getG8bit() + color2.getG8bit(),
               color.getB8bit() + color2.getB8bit(), color.getA8bit() + color2.getA8bit());
  return c;
}

// Subtract two colors
sdl::Color operator-(const sdl::Color &color, const sdl::Color &color2)
{
  sdl::Color c;
  c = sdl::Color(color.getR8bit() - color2.getR8bit(),
                 color.getG8bit() - color2.getG8bit(),
                 color.getB8bit() - color2.getB8bit(),
                 color.getA8bit() - color2.getA8bit());
  return c;
}

// Multiplies a color with an integer
sdl::Color operator*(const sdl::Color &color, int a)
{
  sdl::Color c;
  c = sdl::Color(color.getR8bit() * a,
                 color.getG8bit() * a,
                 color.getB8bit() * a,
                 color.getA8bit() * a);
  return c;
}

// Divides a color through an integer
sdl::Color operator/(const sdl::Color &color, int a)
{
  if (a == 0)
    return color;
  sdl::Color c(color.getR8bit() / a,
               color.getG8bit() / a,
               color.getB8bit() / a,
               color.getA8bit() / a);
  return c;
}

sdl::Color overlay(const sdl::Color &color, const sdl::Color &color2)
{
  sdl::Color c(color.getR8bit() * color.getA8bit() / 255 +
                   color2.getR8bit() * color2.getA8bit() * (255 - color.getA8bit()) / (255 * 255),
               color.getG8bit() * color.getA8bit() / 255 +
                   color2.getG8bit() * color2.getA8bit() * (255 - color.getA8bit()) / (255 * 255),
               color.getB8bit() * color.getA8bit() / 255 +
                   color2.getB8bit() * color2.getA8bit() * (255 - color.getA8bit()) / (255 * 255),
               color.getA8bit() + (color2.getA8bit() * (255 - color.getA8bit()) / 255));
  return c;
}

bool operator==(const sdl::Color &color, const sdl::Color &color2)
{
  return (color.getR8bit() == color2.getR8bit() && color.getG8bit() == color2.getG8bit() && color.getB8bit() == color2.getB8bit() &&
          color.getA8bit() == color2.getA8bit());
}

// Are both colors not equal?
bool operator!=(const sdl::Color &color, const sdl::Color &color2)
{
  return (!(color.getR8bit() == color2.getR8bit() && color.getG8bit() == color2.getG8bit() && color.getB8bit() == color2.getB8bit() &&
            color.getA8bit() == color2.getA8bit()));
}
