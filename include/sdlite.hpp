#pragma once

#include <stdexcept>
#include <string>
#include <utility>

#if __has_include(<SDL.h>)
#include <SDL.h>
#elif __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#else
#error "SDL2 headers not found"
#endif

namespace sdlite {

class Error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

inline void throw_if(bool condition, const char* context) {
    if (!condition) {
        return;
    }

    throw Error(std::string(context) + ": " + SDL_GetError());
}

class Context {
public:
    explicit Context(Uint32 flags = SDL_INIT_VIDEO) {
        throw_if(SDL_Init(flags) != 0, "SDL_Init failed");
    }

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;

    ~Context() {
        SDL_Quit();
    }
};

class Window {
public:
    Window(const char* title, int width, int height, Uint32 flags = SDL_WINDOW_SHOWN)
        : handle_(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)) {
        throw_if(handle_ == nullptr, "SDL_CreateWindow failed");
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}

    Window& operator=(Window&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        destroy();
        handle_ = std::exchange(other.handle_, nullptr);
        return *this;
    }

    ~Window() {
        destroy();
    }

    [[nodiscard]] SDL_Window* get() const {
        return handle_;
    }

private:
    void destroy() {
        if (handle_ != nullptr) {
            SDL_DestroyWindow(handle_);
            handle_ = nullptr;
        }
    }

    SDL_Window* handle_ = nullptr;
};

class Renderer {
public:
    explicit Renderer(Window& window, int index = -1,
                      Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
        : handle_(SDL_CreateRenderer(window.get(), index, flags)) {
        throw_if(handle_ == nullptr, "SDL_CreateRenderer failed");
    }

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}

    Renderer& operator=(Renderer&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        destroy();
        handle_ = std::exchange(other.handle_, nullptr);
        return *this;
    }

    ~Renderer() {
        destroy();
    }

    void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
        throw_if(SDL_SetRenderDrawColor(handle_, r, g, b, a) != 0, "SDL_SetRenderDrawColor failed");
        throw_if(SDL_RenderClear(handle_) != 0, "SDL_RenderClear failed");
    }

    void present() {
        SDL_RenderPresent(handle_);
    }

    [[nodiscard]] SDL_Renderer* get() const {
        return handle_;
    }

private:
    void destroy() {
        if (handle_ != nullptr) {
            SDL_DestroyRenderer(handle_);
            handle_ = nullptr;
        }
    }

    SDL_Renderer* handle_ = nullptr;
};

class App {
public:
    App(const char* title, int width, int height,
        Uint32 window_flags = SDL_WINDOW_SHOWN,
        Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
        : context_(),
          window_(title, width, height, window_flags),
          renderer_(window_, -1, renderer_flags) {}

    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    template <typename FrameFn>
    void run(FrameFn&& frame) {
        running_ = true;

        while (running_) {
            SDL_Event event{};
            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    running_ = false;
                }
            }

            frame(renderer_, running_);
            renderer_.present();
        }
    }

    void stop() {
        running_ = false;
    }

    [[nodiscard]] Renderer& renderer() {
        return renderer_;
    }

private:
    Context context_;
    Window window_;
    Renderer renderer_;
    bool running_ = true;
};

}  // namespace sdlite
