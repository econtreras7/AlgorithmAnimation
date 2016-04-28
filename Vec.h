//
//  Vec.h
//  glutapp
//
//  Created by Ezequiel Contreras on 3/11/16.
//  Copyright © 2016 Angelo Kyrilov. All rights reserved.
//

#ifndef Vec_h
#define Vec_h

#include <iostream>
#include <vector>

using namespace std;

class Vec{
public:
    float x,y;
    //static Vec null;
    
    Vec(){
        x=0;
        y=0;
    }
    Vec(float xC, float yC){
        x=xC;
        y=yC;
    }
    void add(Vec v){
        x+=v.x;
        y+=v.y;
    }
    void print(){
        cout<<"("<<x<<", "<<y<<")"<<endl;
    }
    
};
//Vec Vec:: null(0,0);

#endif /* Vec_h */
