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

/* int AID_CheckCollisions(AID_Objects **objects, double x, double y)
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
} */