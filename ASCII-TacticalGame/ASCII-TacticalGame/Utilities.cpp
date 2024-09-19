#include "Utilities.h"

#include <cmath>

int Utilities::ManhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

float Utilities::Round(float v)
{
    return floor(v + 0.5f);
}
