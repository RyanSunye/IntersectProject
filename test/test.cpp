//
// Created by HP on 2020/3/4.
//

#include<iostream>
#include <random>
#include <ctime>
#include <set>
#include "../src/Line.h"

using namespace std;

default_random_engine e;
#define random(a, b) (e()%((b)-(a)+1)+(a))

Line random_line() {
    return Line(random(-1000,1000),random(-1000,1000),random(-1000,1000));
}

Circle random_circle() {
    return Circle(random(-1000, 1000), random(-1000, 1000), random(-1000, 1000));
}

set<Dot> intersections;
vector<Line> lines;
vector<Circle> circles;

int main()
{
    e.seed(time(nullptr));
    int n;
    char ch;
    cin>>n;
    clock_t s = clock();

    for(int i=0;i<n;i++) {
        ch = random(0,1);
        switch(ch) {
            case 0: {
                Line l = random_line();
                for(auto it: lines) it.intersect(&intersections, l);
                for(auto it: circles) it.intersect(&intersections, l);
                lines.emplace_back(l);
                break;
            }
            case 1: {
                Circle circle = random_circle();
                for(auto it: lines) circle.intersect(&intersections, it);
                for(auto it: circles) circle.intersect(&intersections, it);
                circles.emplace_back(circle);
                break;
            }
            default: {
                cout<< "no such type!";
                throw exception();
            }
        }
    }

    cout<<clock()- s<<endl;
    cout<<intersections.size();

    return 0;
}
