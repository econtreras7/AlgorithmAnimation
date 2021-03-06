
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H
#include <vector>
# include "glut_window.h"
#include "Rect.h"
// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    enum MenuEv { evOption0, evOption1 };
    float _markx, _marky;
    int _w, _h;
     std::vector<Rect*> stash;
     float xOffset,yOffset;
     bool drag;
     bool mousedown;
     
   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void windowToScene ( float& x, float &y );
    

   private : // functions derived from the base class
    virtual void handle ( const Event& e );
    virtual void draw ();
    virtual void resize ( int w, int h );
     virtual void swap(Rect* l,Rect* r);
     virtual void bubbleSort();
     virtual void insertionSort();
     virtual void selectionSort();
     virtual void quickSort(int arr[], int left, int right);
     virtual void displayText( float x, float y, int r, int g, int b, const char *string );
     //virtual int partition(vector<Rect*> s,int l,int h);
     //virtual void quickSort(vector<Rect*> s,int l,int h);
     
 };

#endif // APP_WINDOW_H
