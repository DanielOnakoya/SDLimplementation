#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* win = SDL_CreateWindow("2D Rendering", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Load background image
    SDL_Surface* bgSurf = SDL_LoadBMP("bg.bmp");
    if (bgSurf == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* bgTex = SDL_CreateTextureFromSurface(ren, bgSurf);
    SDL_FreeSurface(bgSurf);
    if (bgTex == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // Load openGL image
    SDL_Surface* oglSurf = SDL_LoadBMP("openGL.bmp");
    if (oglSurf == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* oglTex = SDL_CreateTextureFromSurface(ren, oglSurf);
    SDL_FreeSurface(oglSurf);
    if (oglTex == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return 1;
    }

    // Load Blender image
    SDL_Surface* blenderSurf = SDL_LoadBMP("Blender.bmp");
    if (blenderSurf == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(oglTex);
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* blenderTex = SDL_CreateTextureFromSurface(ren, blenderSurf);
    SDL_FreeSurface(blenderSurf);
    if (blenderTex == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(oglTex);
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return 1;
    }

    // Load frame image
    SDL_Surface* frameSurf = SDL_LoadBMP("frame.bmp");
    if (frameSurf == NULL) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(blenderTex);
        SDL_DestroyTexture(oglTex);
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* frameTex = SDL_CreateTextureFromSurface(ren, frameSurf);
    SDL_FreeSurface(frameSurf);
    if (frameTex == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyTexture(blenderTex);
        SDL_DestroyTexture(oglTex);
        SDL_DestroyTexture(bgTex);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        return 1;
    }

    // Calculate positions and scale for foreground images
    int windowW = 800, windowH = 600;
    int oglW, oglH, blenderW, blenderH;
    SDL_QueryTexture(oglTex, NULL, NULL, &oglW, &oglH);
    SDL_QueryTexture(blenderTex, NULL, NULL, &blenderW, &blenderH);

    // Scaling to fit the images to 720p scaled down to 25% of the size
    float scale = 0.25; // Scale down to 25% of the original size
    oglW = (int)(oglW * scale);
    oglH = (int)(oglH * scale);
    blenderW = (int)(blenderW * scale);
    blenderH = (int)(blenderH * scale);

    // Calculate frame dimensions
    int frameW = oglW + 20; // Add 20 pixels to width for frame
    int frameH = oglH + 20; // Add 20 pixels to height for frame

    // Calculate positions for side by side display
    SDL_Rect oglRect = { 50, (windowH - oglH) / 2, oglW, oglH }; // Adjusted position
    SDL_Rect blenderRect = { 450, (windowH - blenderH) / 2, blenderW, blenderH }; // Adjusted position

    // Calculate frame positions
    SDL_Rect oglFrameRect = { oglRect.x - 10, oglRect.y - 10, frameW, frameH }; // Adjust frame size and position
    SDL_Rect blenderFrameRect = { blenderRect.x - 10, blenderRect.y - 10, frameW, frameH }; // Adjust frame size and position

    // Main loop flag
    int quit = 0;
    SDL_Event e;

    // Main loop
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear renderer
        SDL_RenderClear(ren);

        // Render background
        SDL_RenderCopy(ren, bgTex, NULL, NULL);

        // Render frames
        SDL_RenderCopy(ren, frameTex, NULL, &oglFrameRect);
        SDL_RenderCopy(ren, frameTex, NULL, &blenderFrameRect);

        // Render openGL image
        SDL_RenderCopy(ren, oglTex, NULL, &oglRect);

        // Render Blender image
        SDL_RenderCopy(ren, blenderTex, NULL, &blenderRect);

        // Present renderer
        SDL_RenderPresent(ren);
    }

    // Cleanup
    SDL_DestroyTexture(frameTex);
    SDL_DestroyTexture(blenderTex);
    SDL_DestroyTexture(oglTex);
    SDL_DestroyTexture(bgTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
