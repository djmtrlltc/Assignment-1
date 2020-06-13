//****************************************************
// Starter code for assignment #1.  It is provided to 
// help get you started, but you are not obligated to
// use this starter code.
//****************************************************

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include "smVector.hpp"
//include header file for glfw library so that we can use OpenGL
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//#ifdef _WIN32
//static DWORD lastTime;
//#else
//static struct timeval lastTime;
//#endif

#define PI 3.14159265 // Should be used from mathlib

using namespace std;

bool using_phong = true;
bool using_WARD = false;
bool using_toon = false;
bool using_translucent = false;
bool using_sketch = false;

//****************************************************
// Global Variables
// Generally speaking, global variables should be 
// avoided, but for this small assignment we'll make
// and exception.
//****************************************************

GLfloat Translation[3] = {0.0f, 0.0f, 0.0f};
bool Auto_strech = false;
int  Width_global = 400;
int  Height_global = 400;

int  SizeX_saved_global;
int  SizeY_saved_global;

int  PosX_saved_global;
int  PosY_saved_global;

const GLFWvidmode * VideoMode_global = NULL;

inline float sqr(float x) { return x*x; }



//****************************************************
// Simple init function
//****************************************************

void initializeRendering()
{
    glfwInit();
}


//****************************************************
// A routine to set a pixel by drawing a GL point.  This is not a
// general purpose routine as it assumes a lot of stuff specific to
// this example.
//****************************************************



void setPixel(float x, float y, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glVertex2f(x+0.5, y+0.5);  
    // The 0.5 is to target pixel centers
    // Note that some OpenGL implementations have created gaps in the past.
}

//****************************************************
// Keyboard inputs
//****************************************************

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key) {
                    
        // Hint on making up/down left/right work: the variable Translation [0] and [1].
                
        case GLFW_KEY_ESCAPE: 
        case GLFW_KEY_Q:      
            glfwSetWindowShouldClose(window, GLFW_TRUE); 
            break;
        case GLFW_KEY_LEFT :
            break;
        case GLFW_KEY_RIGHT:
            break;
        case GLFW_KEY_UP   :
            break;
        case GLFW_KEY_DOWN :
            break;
        case GLFW_KEY_F:
            if (action) {
                Auto_strech = !Auto_strech;                 
                if (Auto_strech){
                    glfwGetWindowPos(window, &PosX_saved_global, &PosY_saved_global);
                    glfwGetWindowSize(window, &SizeX_saved_global, &SizeY_saved_global);
                    glfwSetWindowSize(window, VideoMode_global->width, VideoMode_global->height);
                    glfwSetWindowPos(window, 0, 0);
                }else{
                    glfwSetWindowSize(window, SizeX_saved_global, SizeY_saved_global);
                    glfwSetWindowPos(window, PosX_saved_global, PosY_saved_global);
                }
            }
            break;
        case GLFW_KEY_SPACE: 
            break;  
        default: 
            break;
    }
    
}



//****************************************************
// Draw a filled circle.
//****************************************************

void drawCircle(float centerX, float centerY, float radius) {

    // Start drawing a list of points
    glBegin(GL_POINTS);
    
    // We could eliminate wasted work by only looping over the pixels
    // inside the sphere's radius.  But the example is more clear this
    // way.  In general drawing an object by loopig over the whole
    // screen is wasteful.

    int minI = max(0,(int)floor(centerX-radius));
    int maxI = min(Width_global-1,(int)ceil(centerX+radius));

    int minJ = max(0,(int)floor(centerY-radius));
    int maxJ = min(Height_global-1,(int)ceil(centerY+radius));


    for (int i = 0; i < Width_global; i++) {
        for (int j = 0; j < Height_global; j++) {
                
            // Location of the center of pixel relative to center of sphere
            float x = (i+0.5-centerX);
            float y = (j+0.5-centerY);

            float dist = sqrt(sqr(x) + sqr(y));

            if (dist <= radius) {

                // This is the front-facing Z coordinate
                float z = sqrt(radius * radius - dist * dist); 
                
                SmVector3 v = { 0,0,1 };
                SmVector3 s = { x,y,z };
                SmVector3 c = { centerX,centerY,0 };
                SmVector3 n = s - c;
                normalize(n); 
                SmVector3 p1 = { 123,34,555 };         //position of the light, can be changed.
                SmVector3 p2 = { 132,56,239 };         //position of the light, can be changed.
                SmVector3 p3 = { 400,39,-20 };         //position of the light, can be changed.
                SmVector3 p4 = { 12,455,66 };          //position of the light, can be changed.
                SmVector3 p5 = { 23,533,0 };           //position of the light, can be changed.
                SmVector3 l1 = p1 - s;
                SmVector3 l2 = p2 - s;
                SmVector3 l3 = p3 - s;
                SmVector3 l4 = p4 - s;
                SmVector3 l5 = p5 - s;
                normalize(l1);
                normalize(l2);
                normalize(l3);
                normalize(l4);
                normalize(l5);
                float ka = 0.01;
                float kd = 0.5;
                float ks = 0.5;
                SmVector3 r1 = 2 * n * dot(l1, n) - l1;
                SmVector3 r2 = 2 * n * dot(l2, n) - l2;
                SmVector3 r3 = 2 * n * dot(l3, n) - l3;
                SmVector3 r4 = 2 * n * dot(l4, n) - l4;
                SmVector3 r5 = 2 * n * dot(l5, n) - l5;
                normalize(r1);
                normalize(r2);
                normalize(r3);
                normalize(r4);
                normalize(r5);
                SmVector3 zero = { 0,0,0 };
                SmVector3 sum1 = ka * l1 + kd * l1 * max(dot(l1, n), zero) + ks * l1 * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero) * max(dot(r1, v), zero);   
                SmVector3 sum2 = ka * l2 + kd * l2 * max(dot(l2, n), zero) + ks * l2 * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero) * max(dot(r2, v), zero);   
                SmVector3 sum3 = ka * l3 + kd * l3 * max(dot(l3, n), zero) + ks * l3 * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero) * max(dot(r3, v), zero);   
                SmVector3 sum4 = ka * l4 + kd * l4 * max(dot(l4, n), zero) + ks * l4 * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero) * max(dot(r4, v), zero);   
                SmVector3 sum5 = ka * l5 + kd * l5 * max(dot(l5, n), zero) + ks * l5 * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero) * max(dot(r5, v), zero);   
                SmVector3 sum = sum1 + sum2 + sum3 + sum4 + sum5;
                


                
                setPixel(i, j, sum[1] ,sum[2],sum[3]);

                // This is amusing, but it assumes negative color values are treated reasonably.
                // setPixel(i,j, x/radius, y/radius, z/radius );
                
            }
        }
    }

    glEnd();
}



//****************************************************
// function that does the actual drawing of stuff
//***************************************************

void display( GLFWwindow* window )
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );      //clear background screen to black
    
    glClear(GL_COLOR_BUFFER_BIT);                // clear the color buffer (sets everything to black)
    
    glMatrixMode(GL_MODELVIEW);                  // indicate we are specifying camera transformations
    glLoadIdentity();                            // make sure transformation is "zero'd"
    
    //----------------------- code to draw objects --------------------------
    glPushMatrix();
    glTranslatef (Translation[0], Translation[1], Translation[2]);
    drawCircle(
        Width_global / 2.0 , 
        Height_global / 2.0 , 
        min(Width_global, Height_global) * 0.8 / 2.0);  // What do you think this is doing?
    glPopMatrix();
    
    glfwSwapBuffers(window);
    
}

//****************************************************
// function that is called when window is resized
//***************************************************

void size_callback(GLFWwindow* window, int width, int height)
{
    // The width and height arguments are not used
    // because they are not the size of the window 
    // in pixels.

    // Get the pixel coordinate of the window
    // it returns the size, in pixels, of the 
    // framebuffer of the specified window
    glfwGetFramebufferSize(window, &Width_global, &Height_global);
    
    glViewport(0, 0, Width_global, Height_global);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Width_global, 0, Height_global, 1, -1);
    
    display(window);
}



//****************************************************
// the usual stuff, nothing exciting here
//****************************************************


int main(int argc, char *argv[]) {
    //This initializes glfw

    initializeRendering();
    
    GLFWwindow* window = glfwCreateWindow( Width_global, Height_global, "Computer Graphics", NULL, NULL );
    if ( !window )
    {
        cerr << "Error on window creating" << endl;
        glfwTerminate();
        return -1;
    }
    
    VideoMode_global = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if ( !VideoMode_global )
    {
        cerr << "Error on getting monitor" << endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent( window );

    size_callback(window, 0, 0);
    
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);
                
    while( !glfwWindowShouldClose( window ) ) // main loop to draw object again and again
    {   
        display( window );
                
        glfwPollEvents();        
    }

    return 0;
}








