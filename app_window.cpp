
# include <iostream>
# include "app_window.h"
#include "Rect.h"
using namespace std;
AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   addMenuEntry ( "Option 0", evOption0 );
   addMenuEntry ( "Option 1", evOption1 );
     //stash.push_back(new Rect(-0.6,0.6,0.8,0.6,1.0,0.0,0.0));
     //stash.push_back(new Rect(-0.6,-0.2,0.8,0.6,1.0,1.0,0.0));
     stash.push_back(new Rect(-0.9,-0.1,0.1,0.8,0.0,0.0,1.0));
     stash.push_back(new Rect(-0.7,-0.1,0.1,0.7,0.0,0.0,1.0));
     stash.push_back(new Rect(-0.5,-0.1,0.1,0.8,0.0,0.0,1.0));
     stash.push_back(new Rect(-0.3,-0.1,0.1,0.3,0.0,0.0,1.0));
     stash.push_back(new Rect(-0.1,-0.1,0.1,0.5,0.0,0.0,1.0));
     stash.push_back(new Rect(0.1,-0.1,0.1,0.4,0.0,0.0,1.0));
     stash.push_back(new Rect(0.3,-0.1,0.1,0.66,0.0,0.0,1.0));
     stash.push_back(new Rect(0.5,-0.1,0.1,0.3,0.0,0.0,1.0));
     yOffset=0;
     xOffset=0;
     mousedown = false;
     drag=false;
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
 {
   bool rd=true;

   if ( e.type==Keyboard ) 
    switch ( e.key )
    { case ' ': // space bar
	   std::cout << "Space pressed.\n";
	   bubbleSort();
       redraw();
	   break;

	  case 27: // Esc was pressed
	   exit(1);
	}

   if ( e.type==MouseDown || e.type==Motion)
    { _markx=(float)e.mx;
      _marky=(float)e.my;
      windowToScene(_markx,_marky);
    }
     Vec mousePos= Vec(_markx,_marky);
     
     if(!mousedown){
         Vec mousePos= Vec(_markx,_marky);
         for(vector<Rect*> ::iterator i=stash.begin();i!=stash.end();i++){
            (*i)->deselect();
         }
         for(vector<Rect*> ::iterator i=stash.begin();i!=stash.end();i++){
             if((*i)->contains(mousePos)){
                 (*i)->select();
                 drag=true;
                 xOffset=_markx-(*i)->getX();
                 yOffset=_marky-(*i)->getY();
                 Rect * temp = *i;
                 stash.erase(i);
                 stash.insert(stash.begin(),temp);
                 
                 break;
             }
             
         }
         
     }
     mousedown=true;
     if(drag){
         Rect *top=stash[0];
         top->setX(_markx-xOffset);
         top->setY(_marky-yOffset);
     }
     if(e.type==MouseUp){
         mousedown=false;
         drag=false;
     }

   if ( e.type==Menu )
    { std::cout<<"Menu Event: "<<e.menuev<<std::endl;
      rd=false; // no need to redraw
    }

   const float incx=0.02f;
   const float incy=0.02f;
   if ( e.type==SpecialKey )
    switch ( e.key )
    { case GLUT_KEY_LEFT:  _markx-=incx; break;
      case GLUT_KEY_RIGHT: _markx+=incx; break;
      case GLUT_KEY_UP:    _marky+=incy; break;
      case GLUT_KEY_DOWN:  _marky-=incy; break;
      default: rd=false; // no redraw
	}

   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

void AppWindow::bubbleSort(){
    swap(*stash[2],*stash[5]);
    /*bool check;
    do{
        check=false;
        for(vector<Rect*>::iterator i=stash.begin();i!=stash.end();i++){
            
        
        }
        
        
        
        
    }while(check);*/

}


void AppWindow::swap(Rect& left, Rect& right){
	float i,j,r;

	j = right.getX();
	r = right.getX();	
	for(i = left.getX(); i < r; i = i + 0.03){
		left.setX(i);
		right.setX(j);
		draw();
		j = j - 0.03;
	}
}

void AppWindow::insertionSort(){
    
    
    
}
void AppWindow::selectionSort(){
    
    
}
// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   // Set drawing color to yellow
   //glColor3d ( 1.0, 0.9, 0.3 );
     for(vector<Rect*>::iterator i=stash.begin();i!=stash.end();i++){
         Vec tl,tr,br,bl;
         tl=Vec((*i)->getX(),(*i)->getY());
         tr=Vec((*i)->getX()+(*i)->getW(),(*i)->getY());
         br=Vec((*i)->getX()+(*i)->getW(),(*i)->getY()-(*i)->getH());
         bl=Vec((*i)->getX(),(*i)->getY()-(*i)->getH());
         
         float r,g,b;
         r=(*i)->getR();
         g=(*i)->getG();
         b=(*i)->getB();
         
         if((*i)->selected()){
             glLineWidth(5);
             glColor3f(1.0, 1.0, 1.0);
             glBegin(GL_LINES);
             glVertex2d(tl.x, tl.y);
             glVertex2d(tr.x, tr.y);
             
             glVertex2d(tr.x, tr.y);
             glVertex2d(br.x, br.y);
             
             glVertex2d(br.x, br.y);
             glVertex2d(bl.x, bl.y);
             
             glVertex2d(bl.x, bl.y);
             glVertex2d(tl.x, tl.y);
             
             glVertex2d(tl.x, tl.y);
             glVertex2d(br.x, br.y);
             
             glEnd();
         }
         
         glBegin(GL_POLYGON);
         glColor3f(r,g,b);
         glVertex2d(tl.x,tl.y);
         glVertex2d(tr.x,tr.y);
         glVertex2d(br.x,br.y);
         glVertex2d(bl.x,bl.y);
         glEnd();
         
         
     }
     

   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

