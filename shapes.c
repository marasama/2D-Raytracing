#include "draw.h"

void AID_FillRect(SDL_Surface *surface, AID_Rect *rect, uint32_t color)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    for (int16_t x = rect->x; x < rect->x + rect->w; x++)
    {
        for (int16_t y = rect->y; y < rect->y + rect->h; y++)
        {
            AID_PutPixel(surface, x, y, color);
        }
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}

void AID_PutPixel(SDL_Surface *surface, int x, int y, uint32_t color)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    if (x >= 0 && x < surface->w && y >= 0 && y < surface->h)
    {
        uint32_t *pixel = (uint32_t *)((uint8_t *)surface->pixels + y * surface->pitch + x * 4);
        *pixel = color;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}

void AID_DrawLine(SDL_Surface *surface, AID_Line *line, uint32_t color)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    int x1 = line->start_x;
    int y1 = line->start_y;
    int x2 = line->end_x;
    int y2 = line->end_y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sign_x = (x1 < x2) ? 1 : -1;
    int sign_y = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    int half_thickness = (int)(line->thickness / 2.0);

    while (1)
    {
        for (int i = -half_thickness; i <= half_thickness; i++)
        {
            for (int j = -half_thickness; j <= half_thickness; j++)
                AID_PutPixel(surface, x1 + i, y1 + j, color);
        }

        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sign_x;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sign_y;
        }
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}


void AID_FillCircle(SDL_Surface *surface, AID_Circle *circle, uint32_t color, double border)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    double radiusSquared = circle->radius * circle->radius;
    double innerCircleSquared = (circle->radius - border) * (circle->radius - border);
    double outerCircleSquared = (circle->radius + border) * (circle->radius + border);
    for (uint16_t x = circle->x - circle->radius - border; x <= circle->x + border + circle->radius; x++)
    {
        for (uint16_t y = circle->y - circle->radius - border; y <= circle->y + border + circle->radius; y++)
        {
            int distance = (x - circle->x) * (x - circle->x) + (y - circle->y) * (y - circle->y);
            if ((border > 0 && (double)distance <= outerCircleSquared && (double)distance >= innerCircleSquared) || \
            (border <= 0 && (double)distance <= radiusSquared))
            {
                uint32_t *pixel = (uint32_t *)((uint8_t *)surface->pixels + y * surface->pitch + x * 4);
                *pixel = color;
            }
        }
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}

void AID_InitRays(SDL_Surface *surface, AID_Ray rays[RAY_COUNT], AID_Circle *circle)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    for (int i = 0; i < RAY_COUNT; i++)
    {
        double angle = (2 * M_PI / RAY_COUNT) * i;

        AID_Ray ray = {circle->x, circle->y, (double)cos(angle), (double)sin(angle)};
        rays[i] = ray;
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}

void AID_DrawRays(SDL_Surface *surface, AID_Ray rays[RAY_COUNT], AID_Objects *objects)
{
    if (SDL_MUSTLOCK(surface))
        SDL_LockSurface(surface);

    for (int i = 0; i < RAY_COUNT; i++)
    {
        uint32_t color = 0x8967B3;
        double x_path = rays[i].x;
        double y_path = rays[i].y;
        int screen_end = 0;
        int collided = 0;
        while (!screen_end)
        {
            AID_PutPixel(surface, x_path, y_path, color);
            x_path += rays[i].normal_x;
            y_path += rays[i].normal_y;
            if (AID_CheckCollisions(objects, x_path, y_path))
            {
                collided = 1;
                color = 0xFFFFFFFF;
            }
            else if (collided)
            {
                color = 0x01010101;
            }
            if (x_path < 0 || x_path >= WIDTH || y_path < 0 || y_path >= HEIGHT)
                screen_end = 1;
        }
    }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}