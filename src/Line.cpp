//
// Created by HP on 2020/3/4.
//

#include <cmath>
#include <iostream>
#include "Line.h"

Line::Line(float x0, float y0, float x1, float y1) {
    // 转化成 ax+by+c=0 形式
    a = y1 - y0;
    b = x0 - x1;
    c = x1 * y0 - x0 * y1;
}

bool Line::parallel(Line l) {
    return a * l.b == l.a * b;
}

void Line::intersect(set<Dot> *intersections, Line l) {
    try {
        intersections->insert(intersect(l));
    } catch (exception e) {}
}

Dot Line::intersect(Line l) {
    if(parallel(l)) throw exception();
    return Dot(b * l.c - l.b * c, l.a * c - a * l.c)/ (a * l.b - l.a * b);
}

Line::Line(float aa, float ab, float ac) {
    a = aa;
    b = ab;
    c = ac;
}

float Circle::distance(Line l) {
    return fabs(l.a * x + l.b * y + l.c) / Dot(l.a, l.b).abs();
}

void Circle::intersect(set<Dot> *intersections, Line l) {
    float d = distance(l);
    if (d > r) return;
    Line ll(l.b, -l.a, l.a * y - l.b * x);
    Dot dot = ll.intersect(l);
    if (d == r) {
        intersections->insert(dot);
        return;
    }
    float t = sqrt(r * r - d * d);
    Dot direction(l.b, -l.a);
    direction.unify();
    intersections->insert(dot + direction * t);
    intersections->insert(dot - direction * t);
}

void Circle::intersect(set<Dot> *intersections, Circle c) {
    float a1, b1, R1, a2, b2, R2;
    a1 = x;
    b1 = y;
    R1 = r;

    a2 = c.x;
    b2 = c.y;
    R2 = c.r;

    float R1R1 = R1 * R1;
    float a1a1 = a1 * a1;
    float b1b1 = b1 * b1;

    float a2a2 = a2 * a2;
    float b2b2 = b2 * b2;
    float R2R2 = R2 * R2;

    float subs1 = a1a1 - 2 * a1 * a2 + a2a2 + b1b1 - 2 * b1 * b2 + b2b2;
    if(subs1<=0) return;

    float subs2 = -R1R1 * a1 + R1R1 * a2 + R2R2 * a1 - R2R2 * a2 + a1a1 * a1 - a1a1 * a2 - a1 * a2a2 + a1 * b1b1 -
                  2 * a1 * b1 * b2 + a1 * b2b2 + a2a2 * a2 + a2 * b1b1 - 2 * a2 * b1 * b2 + a2 * b2b2;
    float subs3 = -R1R1 * b1 + R1R1 * b2 + R2R2 * b1 - R2R2 * b2 + a1a1 * b1 + a1a1 * b2 - 2 * a1 * a2 * b1 -
                  2 * a1 * a2 * b2 + a2a2 * b1 + a2a2 * b2 + b1b1 * b1 - b1b1 * b2 - b1 * b2b2 + b2b2 * b2;
    float sigma = sqrt((R1R1 + 2 * R1 * R2 + R2R2 - a1a1 + 2 * a1 * a2 - a2a2 - b1b1 + 2 * b1 * b2 - b2b2) *
                       (-R1R1 + 2 * R1 * R2 - R2R2 + subs1));

    Dot dot1(subs2, subs3), dot2(b1 - b2, a2 - a1);
    intersections->insert((dot1 + dot2 * sigma) / (2 * subs1));
    intersections->insert((dot1 - dot2 * sigma) / (2 * subs1));
}

