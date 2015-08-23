#include "lines.hxx"

double dist_to_line(FPoint p, FPoint a, FPoint b) {
    FPoint ap = p - a, ab = b - a;
    double u = (ap | ab) / (ab | ab);
    FPoint c = a + ab * u;
    return p.dist(c);
}
