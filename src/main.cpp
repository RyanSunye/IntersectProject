#include <iostream>
#include <set>
#include <vector>
#include "Line.h"

using namespace std;

set<Dot> intersections;
vector<Line> lines;
vector<Circle> circles;


int main() {
    int n;
    cin>>n;
    char ch;
    for(int i=0;i<n;i++) {
        cin>> ch;
        switch(ch) {
            case 'L': {
                float a,b,c,d;
                cin>>a>>b>>c>>d;
                Line l(a,b,c,d);
                for(auto it: lines) it.intersect(&intersections, l);
                for(auto it: circles) it.intersect(&intersections, l);
                lines.emplace_back(l);
                break;
            }
            case 'C': {
                float a,b,c;
                cin>>a>>b>>c;
                Circle circle(a,b,c);
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

    cout<<intersections.size();

    return 0;
}
/*
3
L 0 0 1 1
L 1 0 2 4
L 0 1 4 2

4
C 1 0 2
C 2 2 1
C 3 -2 6
L -1 4 4 -1
 */