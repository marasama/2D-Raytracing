#include "draw.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("2D-Raytracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    AID_Objects *objects = NULL;

    AID_Circle circle = {100, 100, 20};
    
    AID_AddObject(&objects, CIRCLE, &circle);

    AID_Line line = {100, 100, 200, 500, 2.0};

    AID_Ray rays[RAY_COUNT];

    AID_Rect background = {0, 0, WIDTH, HEIGHT};

    SDL_Event event;

    unsigned char running = 1;

    AID_InitRays(surface, rays, &circle);

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                AID_InitRays(surface, rays, &circle);
            }
        }
        AID_FillRect(surface, &background, 0x00000000);
        AID_FillCircle(surface, &circle, 0xFFFFFFFF, 1.0);
        SDL_UpdateWindowSurface(window);
        AID_DrawRays(surface, rays);
        SDL_Delay(10);
    }
    printf("Exiting...\n");
    AID_FreeObjects(&objects);
    SDL_DestroyWindow(window);
    SDL_Quit();
}