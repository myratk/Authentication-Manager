#include "stdafx.h"
#include "Point2D.h"

Point2D::Point2D(int x, int y)
{
    mx = x;
    my = y;
}

int Point2D::getX()
{
    return mx;
}

int Point2D::getY()
{
    return my;
}

void Point2D::setX(int x) {
    mx = x;
}

void Point2D::setY(int y) {
    my = y;
}
