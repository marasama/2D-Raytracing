#include "draw.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("2D-Raytracing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    AID_Objects *objects = NULL;

    AID_Circle light = {100, 100, 20};
    
    AID_Circle circle = {WIDTH / 2, HEIGHT / 2, 50};

    AID_Circle smallCircle = {700, 700, 20};

    AID_Rect rect = {300, 300, 100, 100};

    AID_Line line = {600, 100, 900, 700, 2.0};

    AID_AddObject(&objects, LINE, &line);
    AID_AddObject(&objects, CIRCLE, &smallCircle);
    AID_AddObject(&objects, RECT, &rect);
    AID_AddObject(&objects, CIRCLE, &circle);

    AID_Ray rays[RAY_COUNT];

    AID_Rect background = {0, 0, WIDTH, HEIGHT};

    SDL_Event event;

    AID_InitRays(surface, rays, &light);

    unsigned char running = 1;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0)
            {
                light.x = event.motion.x;
                light.y = event.motion.y;
                AID_InitRays(surface, rays, &light);
            }
        }
        AID_FillRect(surface, &background, 0x11111111);
        AID_FillObjects(surface, objects);
        AID_DrawRays(surface, rays, objects);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
    printf("Exiting...\n");
    AID_FreeObjects(&objects);
    SDL_DestroyWindow(window);
    SDL_Quit();
}