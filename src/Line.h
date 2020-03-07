//
// Created by HP on 2020/3/4.
//

#ifndef INTERSECTPROJECT_LINE_H
#define INTERSECTPROJECT_LINE_H

#include <queue>
#include <set>
#include <cmath>

#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS)

using namespace std;

class Dot : public pair<float, float> {

public:
    Dot(float a, float b) {
        first = a;
        second = b;
    }

    inline Dot operator+(Dot dot) { return {first + dot.first, second + dot.second}; }

    inline Dot operator-(Dot dot) { return {first - dot.first, second - dot.second}; }

    inline Dot operator*(float t) { return {first * t, second * t}; }

    inline Dot operator/(float t) { return {first / t, second / t}; }

    inline float norm() { return first*first + second*second; }

    inline float abs() { return sqrt(norm()); }

    inline void unify() { *this=*this/abs(); }

//    bool operator < (const Dot &p) const {
//        return first != p.first ? first < p.first : second < p.second;
//    }
//
//    bool operator == (const Dot &p) const {
//        return fabs(first - p.first) < EPS && fabs(second - p.second) < EPS;
//    }
};

class Line {
public:
    float a, b, c;

    Line(float x0, float y0, float x1, float y1);

    Line(float aa, float ab, float ac);

    bool parallel(Line l);

    void intersect(set<Dot> *intersections, Line l);

    Dot intersect(Line l);
};

class Circle {
public:
    float x, y, r;

    Circle(float ax, float ay, float ar) : x(ax), y(ay), r(ar) {

    }

    float distance(Line l);

    void intersect(set<Dot> *intersections, Line l);

    void intersect(set<Dot> *intersections, Circle c);
};


#endif //INTERSECTPROJECT_LINE_H
