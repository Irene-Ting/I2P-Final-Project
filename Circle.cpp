#include "Circle.h"

bool
Circle::isOverlap(Circle *circle_1, Circle *circle_2)
{
    /*int length = circle_1->r + circle_2->r;
    int distance_square = (circle_1->x - circle_2->x) * (circle_1->x - circle_2->x)
                            + (circle_1->y - circle_2->y) * (circle_1->y - circle_2->y);

    if(length * length >= distance_square)
        return true;

    return false;*/
    int A_X_UR = circle_1->x+circle_1->r;
    int B_X_UL = circle_2->x-circle_2->r;
    int B_X_UR = circle_2->x+circle_2->r;
    int A_X_UL = circle_1->x-circle_1->r;
    int B_Y_UL = circle_2->y-circle_2->r;
    int A_Y_DL = circle_1->y+circle_1->r;
    int A_Y_UL = circle_1->y-circle_1->r;
    int B_Y_DL = circle_2->y+circle_2->r;
    if(A_X_UR>B_X_UL && B_X_UR>A_X_UL && B_Y_UL>A_Y_DL && A_Y_UL>B_Y_DL)
    {
        return true;
    }
    return false;
}
