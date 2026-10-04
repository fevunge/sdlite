# sdlite

An Object-Oriented Abstraction for easier, more lightweight programming with SDL2.

## What is included

- `include/sdlite.hpp`: a single header with lightweight RAII wrappers for SDL2
  - `sdlite::Context`
  - `sdlite::Window`
  - `sdlite::Renderer`
  - `sdlite::App`
- `examples/minimal.cpp`: minimal usage example

## Minimal example

```cpp
#include "sdlite.hpp"

int main() {
    sdlite::App app("sdlite", 640, 480);

    app.run([](sdlite::Renderer& renderer, bool&) {
        renderer.clear(30, 30, 30);
    });

    return 0;
}
```

Compile in your own project by adding `include/` to include paths and linking against SDL2.
