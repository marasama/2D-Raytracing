#include "draw.h"

void AID_AddObject(AID_Objects **objects, int new_type, void *new_object)
{
    AID_Objects *newNode = (AID_Objects *)malloc(sizeof(AID_Objects));

    AID_Objects *tmp = *objects;
    newNode->type = new_type;
    newNode->object = new_object;
    newNode->next = tmp;
    *objects = newNode;
}

void AID_FreeObjects(AID_Objects **objects)
{
    AID_Objects *tmp;

    while (*objects != NULL)
    {
        tmp = *objects;
        *objects = (*objects)->next;
        free(tmp);
    }
}

static int handle_circle(AID_Circle *object, double x, double y)
{
    double radiusSquared = object->radius * object->radius;
    if ((x - object->x) * (x - object->x) + (y - object->y) * (y - object->y) <= radiusSquared)
        return (1);
    return (0);
}

static int handle_rect(AID_Rect *object, double x, double y)
{
    if (x >= object->x && x <= object->x + object->w && y >= object->y && y <= object->y + object->h)
        return (1);
    return (0);
}

static int handle_line(AID_Line *line, double x, double y)
{
    int x1 = line->start_x;
    int y1 = line->start_y;
    int x2 = line->end_x;
    int y2 = line->end_y;

    double half_thickness = line->thickness / 2.0;

    double numerator = fabs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
    double denominator = sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
    double distance = numerator / denominator;

    if (distance <= half_thickness)
    {
        if ((x >= fmin(x1, x2) && x <= fmax(x1, x2)) && 
            (y >= fmin(y1, y2) && y <= fmax(y1, y2)))
        {
            return (1);
        }
    }
    return (0);
}

int AID_CheckCollisions(AID_Objects *objects, double x, double y)
{
    AID_Objects *tmp = objects;
    while (tmp != NULL)
    {
        if (tmp->type == CIRCLE && handle_circle((AID_Circle *)tmp->object, x, y))
            break;
        if (tmp->type == LINE && handle_line((AID_Line *)tmp->object, x, y))
            break;
        if (tmp->type == RECT && handle_rect((AID_Rect *)tmp->object, x, y))
            break;
        tmp = tmp->next;
    }
    if (tmp != NULL)
        return (1);
    return (0);
}

void AID_FillObjects(SDL_Surface *surface, AID_Objects *objects)
{
    AID_Objects *tmp = objects;
    while (tmp != NULL)
    {
        if (tmp->type == CIRCLE)
            AID_FillCircle(surface, (AID_Circle *)tmp->object, 0xFFFFFFFF, -1);
        if (tmp->type == LINE)
            AID_DrawLine(surface, (AID_Line *)tmp->object, 0xFFFFFFFF);
        if (tmp->type == RECT)
            AID_FillRect(surface, (AID_Rect *)tmp->object, 0xFFFFFFFF);
        tmp = tmp->next;
    }
}