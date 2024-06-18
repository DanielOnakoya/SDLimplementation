#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BALL_SIZE = 20;

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Bouncing Ball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set initial position and velocity of the ball
    int ballX = SCREEN_WIDTH / 2;
    int ballY = SCREEN_HEIGHT / 2;
    int ballVelX = 5;
    int ballVelY = 5;

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Update ball position
        ballX += ballVelX;
        ballY += ballVelY;

        // Check if the ball hit the boundaries
        if (ballX < 0 || ballX + BALL_SIZE > SCREEN_WIDTH) {
            ballVelX = -ballVelX;
        }
        if (ballY < 0 || ballY + BALL_SIZE > SCREEN_HEIGHT) {
            ballVelY = -ballVelY;
        }

        // Render ball
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect ballRect = { ballX, ballY, BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);

        // Update screen
        SDL_RenderPresent(renderer);

        // Cap frame rate
        SDL_Delay(16);
    }

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
