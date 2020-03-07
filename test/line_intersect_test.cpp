//
// Created by HP on 2020/3/4.
//
#include "../src/Line.h"
#include <iostream>
using namespace std;

set<Dot> intersections;
int main(){
    Line l(-1,4,4,-1);
    Circle c(3, -2, 6);

    c.intersect(&intersections,l);
    for(auto it: intersections){
        cout << it.first<<','<<it.second<<endl;
    }
}

/*
2
C 3 -2 6
L -1 4 4 -1
 */