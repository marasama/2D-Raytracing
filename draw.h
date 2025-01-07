#ifndef DRAW_H
# define DRAW_H

# include <SDL2/SDL.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 1200
# define HEIGHT 800
# define RAY_COUNT 360

# define CIRCLE 1
# define LINE 2
# define RECT 3

typedef struct
{
    int x;
    int y;
    int radius;
} AID_Circle;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
} AID_Rect;

typedef struct
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    double thickness;
} AID_Line;

typedef struct
{
    int x;
    int y;
    double normal_x;
    double normal_y;
} AID_Ray;

typedef struct All_Objects
{
    int type;
    void *object;
    struct All_Objects *next;
} AID_Objects;


// Object Helpers
void AID_AddObject(AID_Objects **objects, int new_type, void *new_object);
void AID_FreeObjects(AID_Objects **objects);
int  AID_CheckCollisions(AID_Objects *objects, double x, double y);
void AID_FillObjects(SDL_Surface *surface, AID_Objects *objects);

// Shape Drawing
void AID_PutPixel(SDL_Surface *surface, int x, int y, uint32_t color);
void AID_FillRect(SDL_Surface *surface, AID_Rect *rect, uint32_t color);
void AID_InitRays(SDL_Surface *surface, AID_Ray rays[RAY_COUNT], AID_Circle *circle);
void AID_DrawRays(SDL_Surface *surface, AID_Ray rays[RAY_COUNT], AID_Objects *objects);
void AID_DrawLine(SDL_Surface *surface, AID_Line *line, uint32_t color);
void AID_FillCircle(SDL_Surface *surface, AID_Circle *circle, uint32_t color, double border);

#endif