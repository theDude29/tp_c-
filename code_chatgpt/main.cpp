#ifdef _WIN32
#include <SDL.h>
#define not !
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <memory>

int const WIDTH = 800;
int const HEIGHT = 600;
float const PI = 3.1415927f; // TODO: better PI

struct global_t {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::random_device rd;
    std::default_random_engine eng{ rd() };
    std::uniform_real_distribution<float> rand{-1.0f, 1.0f};
} g;

// Exception for SDL errors
class SDLException : public std::runtime_error {
public:
    SDLException(const std::string& message) : std::runtime_error(message + ": " + SDL_GetError()) {}
};

// Abstract base class for all boids
class Boid {
public:
    virtual ~Boid() = default;
    virtual void update(const std::vector<std::unique_ptr<Boid>>& boids) = 0;
    virtual void render(SDL_Renderer* renderer) const = 0;
};

// Concrete class for bird-like boids
class Bird : public Boid {
private:
    float x, y;
    float vx, vy;
    float maxSpeed = 2.0f;
    float perceptionRadius = 50.0f;

public:
    Bird(float x, float y) : x(x), y(y), vx(g.rand(g.eng)), vy(g.rand(g.eng)) {
        float length = std::sqrt(vx * vx + vy * vy);
        vx /= length;
        vy /= length;
    }

    void update(const std::vector<std::unique_ptr<Boid>>& boids) override {
        float alignX = 0, alignY = 0;
        float cohesionX = 0, cohesionY = 0;
        float separationX = 0, separationY = 0;
        int count = 0;

        for (const auto& other : boids) {
            if (other.get() == this) continue;
            const Bird* bird = dynamic_cast<const Bird*>(other.get());
            if (!bird) continue;

            float dx = bird->x - x;
            float dy = bird->y - y;
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < perceptionRadius) {
                // Alignment
                alignX += bird->vx;
                alignY += bird->vy;

                // Cohesion
                cohesionX += bird->x;
                cohesionY += bird->y;

                // Separation
                if (distance > 0) {
                    separationX -= dx / distance;
                    separationY -= dy / distance;
                }
                count++;
            }
        }

        if (count > 0) {
            // Average alignment
            alignX /= count;
            alignY /= count;
            float alignLength = std::sqrt(alignX * alignX + alignY * alignY);
            if (alignLength > 0) {
                alignX /= alignLength;
                alignY /= alignLength;
            }

            // Average cohesion
            cohesionX /= count;
            cohesionY /= count;
            cohesionX -= x;
            cohesionY -= y;

            // Combine forces
            vx += alignX * 0.1f + cohesionX * 0.01f + separationX * 0.1f;
            vy += alignY * 0.1f + cohesionY * 0.01f + separationY * 0.1f;

            // Limit speed
            float speed = std::sqrt(vx * vx + vy * vy);
            if (speed > maxSpeed) {
                vx = (vx / speed) * maxSpeed;
                vy = (vy / speed) * maxSpeed;
            }
        }

        // Update position
        x += vx;
        y += vy;

        // Wrap around screen edges
        if (x < 0) x += WIDTH;
        if (y < 0) y += HEIGHT;
        if (x >= WIDTH) x -= WIDTH;
        if (y >= HEIGHT) y -= HEIGHT;
    }

    void render(SDL_Renderer* renderer) const override {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
    }
};

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLException("Failed to initialize SDL");
    }
    g.window = SDL_CreateWindow("Boids Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!g.window) {
        throw SDLException("Failed to create window");
    }
    g.renderer = SDL_CreateRenderer(g.window, -1, SDL_RENDERER_ACCELERATED);
    if (!g.renderer) {
        throw SDLException("Failed to create renderer");
    }
}

void cleanupSDL() {
    if (g.renderer) SDL_DestroyRenderer(g.renderer);
    if (g.window) SDL_DestroyWindow(g.window);
    SDL_Quit();
}

int main() {
    try {
        initSDL();

        std::vector<std::unique_ptr<Boid>> boids;
        for (int i = 0; i < 100; ++i) {
            boids.push_back(std::make_unique<Bird>(g.rand(g.eng) * WIDTH, g.rand(g.eng) * HEIGHT));
        }

        bool running = true;
        SDL_Event event;

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
            }

            // Update boids
            for (auto& boid : boids) {
                boid->update(boids);
            }

            // Render boids
            SDL_SetRenderDrawColor(g.renderer, 0, 0, 0, 255);
            SDL_RenderClear(g.renderer);
            for (const auto& boid : boids) {
                boid->render(g.renderer);
            }
            SDL_RenderPresent(g.renderer);

            SDL_Delay(16); // ~60 FPS
        }

        cleanupSDL();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        cleanupSDL();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

