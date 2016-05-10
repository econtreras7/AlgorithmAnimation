
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
    stash.push_back(new Rect(-0.9f,-0.1f,0.1f,-0.9f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(-0.7f,-0.1f,0.1f,-0.7f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(-0.5f,-0.1f,0.1f,-0.8f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(-0.3f,-0.1f,0.1f,-0.3f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(-0.1f,-0.1f,0.1f,-0.5f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(0.1f,-0.1f,0.1f,-0.4f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(0.3f,-0.1f,0.1f,-0.6f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(0.5f,-0.1f,0.1f,-0.3f,0.0f,0.0f,1.0f));
    stash.push_back(new Rect(0.7f, -0.1f, 0.1f, -0.6f, 0.0f, 0.0f, 1.0f));
    stash.push_back(new Rect(0.9f, -0.1f, 0.1f, -0.3f, 0.0f, 0.0f, 1.0f));
    
    yOffset=0;
    xOffset=0;
    mousedown = false;
    drag=false;
    cout<<"Welcome, PLease Select from the following menu:"<<endl;
    cout<<"Key B: Bubble Sort"<<endl;
    cout<<"Key I: Insertion Sort"<<endl;
    cout<<"Key S: Selection Sort"<<endl;
    cout<<"Key R: Reset the rectangles."<<endl;
    cout<<"++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
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
    char *h="hey";
    
    if ( e.type==Keyboard )
        switch ( e.key )
    { case 'b': // space bar
            std::cout << "Bubble Sort.\n";
            bubbleSort();
            //redraw();
            break;
        case 'i': // space bar
            std::cout << "Insertion Sort.\n";
            insertionSort();
            //redraw();
            break;
        case 's': // space bar
            std::cout << "Selection Sort.\n";
            selectionSort();
            break;
        case 'w': // space bar
            std::cout << "S pressed.\n";
            //char *h="hey";
            displayText(0.0, -0.4, 1, 1, 1,h );
            break;
        case 'r':
            std::cout << "Reset.\n";
            stash.clear();
            stash.push_back(new Rect(-0.9f,-0.1f,0.1f,-0.9f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(-0.7f,-0.1f,0.1f,-0.7f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(-0.5f,-0.1f,0.1f,-0.8f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(-0.3f,-0.1f,0.1f,-0.3f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(-0.1f,-0.1f,0.1f,-0.5f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(0.1f,-0.1f,0.1f,-0.4f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(0.3f,-0.1f,0.1f,-0.6f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(0.5f,-0.1f,0.1f,-0.3f,0.0f,0.0f,1.0f));
            stash.push_back(new Rect(0.7f, -0.1f, 0.1f, -0.6f, 0.0f, 0.0f, 1.0f));
            stash.push_back(new Rect(0.9f, -0.1f, 0.1f, -0.3f, 0.0f, 0.0f, 1.0f));
            redraw();
            break;
        case 'q':
            std::cout << "q pressed.\n";
            int n = stash.size();
            int* arr = new int[n];
            
            for (int i = 0; i < n; i++) {
                //cout << -stash[i]->getH()<<endl;
                arr[i] = -stash[i]->getH()*10;
                cout << arr[i] << endl;
            }
            
            quickSort(arr,0, n-1);
            break;
      
           // case 27: // Esc was pressed
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
void AppWindow:: displayText( float x, float y, int r, int g, int b, const char *string ) {
    int j = strlen( string );
    
    glColor3f( r, g, b );
    glRasterPos2f( x, y );
    for( int i = 0; i < j; i++ ) {
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, string[i] );
    }
}

void AppWindow::swap(Rect* left, Rect* right){
    float r = right->getX();
    float l = left->getX();
    float diff=r-l;
    float count=0.0f;
    float offset = 0.01f;
    //float rgb=1;
    do{
        count=count+offset;
        r=r-offset;
        l=l+offset;
        left->setX(l);
        right->setX(r);
        left->setB(0);
        right->setB(0);
        left->setG(1);
        right->setG(1);
        draw();
        left->setB(1.0);
        right->setB(1.0);
        
        //cout<<"right: "<< right->getX()<<" letf: "<<left->getX()<<endl;
    }while(count<diff-(offset/2));
    
    //actuall swapping happens here
    Rect temp;
    temp= *left;
    *left=*right;
    *right=temp;
}

void AppWindow::bubbleSort(){
    cout<<"Bubble Sort"<<endl;
	   int n=stash.size();
    //Rect tmp;
    int j, i;
    for ( i = 0; i < n - 1; i++) {
        for(j=0;j<n-i-1;j++){
            if (-stash[j]->getH() > -stash[j + 1]->getH() ) {
                cout<<"goes through"<<endl;
                swap(stash[j], stash[j+1]);
                stash[j]->setB(1);
                stash[j+1]->setB(1);
                draw();
            }
        }
    }
}
void AppWindow::insertionSort(){
    int i,j;
    float key = 0.0f;
    int n=stash.size();
    for(j=1;j<n;j++){
        key = -stash[j]->getH();
        i=j-1;
        
        while(i>=0 && -stash[i]->getH()>key){
            swap(stash[i], stash[i+1]);
            stash[i]->setG(1);
            stash[i+1]->setG(1);
            i--;
        }
        
        
    }
    
}
void AppWindow::selectionSort(){
    
    int i, j, min_idx;
    float n=stash.size();
    
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (-stash[j]->getH() < -stash[min_idx]->getH())
                min_idx = j;
        
        // Swap the found minimum element with the first element
        if (i != min_idx) {
            swap(stash[i], stash[min_idx]);
        }
    }
    for(int i=0;i<stash.size();i++){
        stash[i]->setG(1);
        draw();
    }
}

void AppWindow::quickSort(int arr[], int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];
    
    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            swap(stash[i], stash[j]);
            i++;
            j--;
        }
    };
    
    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}
/*
 int AppWindow:: partition(vector<Rect*> s,int l,int h){
 
 int pivot = -stash[h]->getH();    // pivot
 int i = (l - 1);  // Index of smaller element
 
 for (int j = l; j <= h- 1; j++)
 {
 // If current element is smaller than or
 // equal to pivot
 if (-stash[j]->getH() <= pivot)
 {
 i++;    // increment index of smaller element
 if(i>j){
 swap(stash[j], stash[i]);
 }
 else{
 swap(stash[i], stash[j]);
 }
 }
 }
 if((i+1)>h){
 swap(stash[h], stash[i+1]);
 }
 else{
 swap(stash[i + 1], stash[h]);
 }
 return (i + 1);
 
 }
 void AppWindow:: quickSort(vector<Rect*> s,int l,int h){
 //int l=0;
 //int h=stash.size()-1;
 if (l < h)
 {
 
 int pi = partition(stash, l, h);
 
 // Separately sort elements before
 // partition and after partition
 quickSort(stash , l, pi - 1);
 quickSort(stash, pi + 1, h);
 }
 
 }
 */
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

