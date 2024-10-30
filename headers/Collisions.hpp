#ifndef Collisions_hpp
#define Collisions_hpp

#define M_PI 3.14159265358979323846f
float angle;
float px, py;
int numPoints = 8;

bool pointInRectangle(float px, float py, float rx, float ry, float rwidth, float rheight) {

    if (px > rx - rwidth / 2.0f && px < rx + rwidth / 2.0f && py > ry - rheight / 2.0f && py < ry + rheight / 2.0f)
        return true;
    
    return false;
}

bool pointInEllipse(float px, float py, float cx, float cy, float rx, float ry) {
    // Sprawdza, czy punkt (px, py) znajduje się wewnątrz elipsy o środku (cx, cy) i półosiach rx, ry
    return (std::pow(px - cx, 2) / std::pow(rx, 2)) + (std::pow(py - cy, 2) / std::pow(ry, 2)) <= 1;
}

bool intersectionTwoEllipses(float x1, float y1, float rx1, float ry1, float x2, float y2, float rx2, float ry2) {

    // Sprawdzenie punktów na pierwszej elipsie względem drugiej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x1 + rx1 * std::cos(angle);
        py = y1 + ry1 * std::sin(angle);

        if (pointInEllipse(px, py, x2, y2, rx2, ry2)) {
            return true;
        }
    }

    // Sprawdzenie punktów na drugiej elipsie względem pierwszej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x2 + rx2 * std::cos(angle);
        py = y2 + ry2 * std::sin(angle);

        if (pointInEllipse(px, py, x1, y1, rx1, ry1)) {
            return true;
        }
    }

    // Brak przecięcia
    return false;
}

bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

    if ( abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1-y2) < (height1 + height2) / 2.0f )
        return true;

    return false;

}

bool intersectionRectangleWithElipse(float r_x, float r_y, float r_width, float r_height, float e_x, float e_y, float e_radiusx, float e_radiusy) {

    // Sprawdzenie punktów na pierwszej elipsie względem drugiej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = e_x + e_radiusx * std::cos(angle);
        py = e_y + e_radiusy * std::sin(angle);

        if (px > r_x - r_width / 2.0f && px < r_x + r_width / 2.0f && py > r_y - r_height / 2.0f && py < r_y + r_height / 2.0f)
            return true;

    }

    return false;

}




#endif // !Collisions_hpp
