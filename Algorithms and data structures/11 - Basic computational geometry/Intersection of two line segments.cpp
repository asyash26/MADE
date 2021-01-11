#include <iostream>

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

bool areSegmentsIntersected(Point a, Point b, Point c, Point d) {
    Vector ac(a, c);
    Vector ab(a, b);
    Vector ad(a, d);
    double aBCrossAC = ab.crossProduct(ac);
    double aBCrossAD = ab.crossProduct(ad);

    Vector cd(c, d);
    Vector ca(c, a);
    Vector cb(c, b);
    double cdCrossCA = cd.crossProduct(ca);
    double cDCrossCB = cd.crossProduct(cb);
    if (aBCrossAC * aBCrossAD <= 0) {
        if (cdCrossCA * cDCrossCB <= 0) {
            if (aBCrossAC == 0 && aBCrossAD == 0 && cdCrossCA == 0 && cDCrossCB == 0) {
                if (isPointOnSegment(c, a, b) || isPointOnSegment(d, a, b))
                    return true;
                if (isPointOnSegment(a, c, d) || isPointOnSegment(b, c, d))
                    return true;
            } else
                return true;
        }
    }
    return false;
}

int main() {
    double segmentStartX, segmentStartY, segmentEndX, segmentEndY;
    cin >> segmentStartX >> segmentStartY >> segmentEndX >> segmentEndY;
    Point a(segmentStartX, segmentStartY);
    Point b(segmentEndX, segmentEndY);
    cin >> segmentStartX >> segmentStartY >> segmentEndX >> segmentEndY;
    Point c(segmentStartX, segmentStartY);
    Point d(segmentEndX, segmentEndY);

    if (areSegmentsIntersected(a, b, c, d))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
