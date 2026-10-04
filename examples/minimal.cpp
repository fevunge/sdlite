#include "sdlite.hpp"

int main() {
    sdlite::App app("sdlite", 640, 480);

    app.run([](sdlite::Renderer& renderer, bool& running) {
        renderer.clear(30, 30, 30);
        (void)running;
    });

    return 0;
}
