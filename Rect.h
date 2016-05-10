//
//  Rect.h
//  glutapp
//
//  Created by Ezequiel Contreras on 3/11/16.
//  Copyright © 2016 Angelo Kyrilov. All rights reserved.
//

#ifndef Rect_h
#define Rect_h


#include <iostream>
#include <vector>
#include "Vec.h"
//#include "rectangles.cpp"
using namespace std;

class Rect{


public:
    float Rx,Ry,w,h,Rr,Rg,Rb;
    bool sel;
    
    Rect(){
        Rx=0.0f;
        Ry=0.0f;
        w=0.0f;
        h=0.0f;
        Rr=0.0f;
        Rg=0.0f;
        Rb=0.0f;
        
    }
    Rect(float xC, float yC, float width, float height){
        Rx=xC;
        Ry=yC;
        w=width;
        h=height;
        Rr=1.0f;
        Rg=1.0f;
        Rb=1.0f;
        sel=false;
    }
    Rect(float xC, float yC, float width, float height,float r,float g,float b){
        Rx=xC;
        Ry=yC;
        w=width;
        h=height;
        Rr=r;
        Rg=g;
        Rb=b;
        sel=false;
        
    }
    float getX(){
        return Rx;
    }
    float getY(){
        return Ry;
    }
    float getW(){
        return w;
    }
    float getH(){
        return h;
    }
    float getR(){
        return Rr;
    }
    float getG(){
        return Rg;
    }
    float getB(){
        return Rb;
    }
    
    
    void deselect(){
         sel=false;
    }
    
    bool selected(){
        return sel;
    }
    
    void select(){
        sel=true;
    }
    void setR( float rgb){
        Rr=rgb;
    }
    
    void setX(float xC){
        Rx=xC;
    }
    
    void setY(float yC){
        Ry=yC;
    }
    
    bool  contains(Vec v){
        if( (v.x<=(Rx+w)) && (v.x>=Rx) && (v.y>=(Ry-h)) && (v.y<=Ry) ){
            return true;
        }	
        else{
            return false;
        }
    }
    
};


#endif /* Rect_h */
