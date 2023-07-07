#pragma once

struct ScreenSize
{
    float width;
    float height;

    float inline topEdge() const { return ((height / 2) - 1); }
    float inline bottomEdge() const { return ((height / 2) - height); }
    float inline rightEdge() const { return ((width / 2) - 1); }
    float inline leftEdge() const { return ((width / 2) - width); }

};