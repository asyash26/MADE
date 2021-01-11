#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Point {
public:
    double x;
    double y;

    Point(double x, double y) : x(x), y(y) {}
};

class Vector {
public:
    double x;
    double y;

    Vector(double x, double y) : x(x), y(y) {}

    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }

    double dotProduct(Vector vector) {
        return x * vector.x + y * vector.y;
    }

    double crossProduct(Vector vector) {
        return x * vector.y - y * vector.x;
    }
};

bool isPointOnSegment(Point targetPoint, Point segmentStart, Point segmentEnd) {
    Vector a(targetPoint, segmentStart);
    Vector b(targetPoint, segmentEnd);
    return a.crossProduct(b) == 0 && a.dotProduct(b) <= 0;
}

int main() {
    double pointX, pointY, segmentStartX, segmentStartY, segmentEndX, segmentEndY;
    cin >> pointX >> pointY >> segmentStartX >> segmentStartY >> segmentEndX >> segmentEndY;
    Point targetPoint(pointX, pointY);
    Point segmentStart(segmentStartX, segmentStartY);
    Point segmentEnd(segmentEndX, segmentEndY);
    if (isPointOnSegment(targetPoint, segmentStart, segmentEnd))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
