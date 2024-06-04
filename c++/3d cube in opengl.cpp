/* A simple program to show how to set up an X window for OpenGL rendering.
 * X86 compilation: gcc -o -L/usr/X11/lib   main main.c -lGL -lX11
 * X64 compilation: gcc -o -L/usr/X11/lib64 main main.c -lGL -lX11
 */
#include <stdio.h>
#include <stdlib.h>

#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>

#include <X11/X.h>    /* X11 constant (e.g. TrueColor) */
#include <X11/keysym.h>
#include <math.h>


static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
static int dblBuf[]  = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};

Display   *dpy;
Window     win;
GLfloat    xAngle = 42.0, yAngle = 82.0, zAngle = 112.0;
GLboolean  doubleBuffer = GL_TRUE;


void drawQuad(

              double cr1, double cg1, double cb1,
              double cr2, double cg2, double cb2,
              double cr3, double cg3, double cb3,
              double cr4, double cg4, double cb4,

              double x1, double y1, double z1,
              double x2, double y2, double z2,
              double x3, double y3, double z3,
              double x4, double y4, double z4)
{
    glColor3d(cr1, cg1, cb1);
    glVertex3d(x1,y1,z1);
    glColor3d(cr2, cg2, cb2);
    glVertex3d(x2,y2,z2);
    glColor3d(cr3, cg3, cb3);
    glVertex3d(x3,y3,z3);

    glColor3d(cr1, cg1, cb1);
    glVertex3d(x1,y1,z1);
    glColor3d(cr4, cg4, cb4);
    glVertex3d(x4,y4,z4);
    glColor3d(cr3, cg3, cb3);
    glVertex3d(x3,y3,z3);
};


void drawCubeEx(double r, double g, double b,
              double x1, double y1, double z1,
              double x2, double y2, double z2
              )
{
    double coord[24];
    double color[24];

    for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
    for (int k = 0; k < 2; k++)
    {
        coord[ (4*k+2*j+i)*3+0] = (i==1)?x2:x1;
        coord[ (4*k+2*j+i)*3+1] = (j==1)?y2:y1;
        coord[ (4*k+2*j+i)*3+2] = (k==1)?z2:z1;

        double coef = (i+j+k)/6.0;

        color[ (4*k+2*j+i)*3+0] = (1.0-coef)*r+coef;
        color[ (4*k+2*j+i)*3+1] = (1.0-coef)*g+coef;
        color[ (4*k+2*j+i)*3+2] = (1.0-coef)*b+coef;
    }

    #define DRAW_PL(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X4, Y4, Z4) { \
    drawQuad(color[(4*Z1+2*Y1+X1)*3+0], color[(4*Z1+2*Y1+X1)*3+1], color[(4*Z1+2*Y1+X1)*3+2],  \
             color[(4*Z2+2*Y2+X2)*3+0], color[(4*Z2+2*Y2+X2)*3+1], color[(4*Z2+2*Y2+X2)*3+2],\
             color[(4*Z3+2*Y3+X3)*3+0], color[(4*Z3+2*Y3+X3)*3+1], color[(4*Z3+2*Y3+X3)*3+2],\
             color[(4*Z4+2*Y4+X4)*3+0], color[(4*Z4+2*Y4+X4)*3+1], color[(4*Z4+2*Y4+X4)*3+2],\
             coord[(4*Z1+2*Y1+X1)*3+0], coord[(4*Z1+2*Y1+X1)*3+1], coord[(4*Z1+2*Y1+X1)*3+2],  \
             coord[(4*Z2+2*Y2+X2)*3+0], coord[(4*Z2+2*Y2+X2)*3+1], coord[(4*Z2+2*Y2+X2)*3+2],\
             coord[(4*Z3+2*Y3+X3)*3+0], coord[(4*Z3+2*Y3+X3)*3+1], coord[(4*Z3+2*Y3+X3)*3+2],\
             coord[(4*Z4+2*Y4+X4)*3+0], coord[(4*Z4+2*Y4+X4)*3+1], coord[(4*Z4+2*Y4+X4)*3+2]\
             ); \
    }

    #define DRAW_PLANE(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3, X4, Y4, Z4) \
    DRAW_PL((X1),(Y1),(Z1),(X2), (Y2), (Z2), (X3),(Y3),(Z3),(X4),(Y4), (Z4))

    for (int i = 0; i < 2 ;i ++)
    {
        DRAW_PLANE(i, 0, 0, i, 0, 1, i, 1,1,i,1,0);
        DRAW_PLANE(0,i,0, 0, i, 1, 1, i, 1,1 , i,0);
        DRAW_PLANE(0,0,i, 0, 1,i, 1, 1,i, 1, 0, i);
    };

}

double norm(double x, double y, double z)
{
    return sqrt(x*x+y*y+z*z);
}

void drawCube(double r, double g, double b,
              double x, double y, double z,
              double a
              )


{
    drawCubeEx(r,g,b,x-0.5*a, y-0.5*a, z-0.5*a,
             x+0.5*a, y+0.5*a, z+0.5*a);
}

void fatalError(char *message)
{
  fprintf(stderr, "main: %s\n", message);
  exit(1);
}


// class potential

class Potential
{
private:
    double re;
    double Dsigma;
public:
    double getRe()
    {
        return re;
    }

    double getDsigma()
    {
        return Dsigma;
    }

    void setParams(double re, double Dsigma)
    {
        this->re = re;
        this->Dsigma = Dsigma;
    }

    Potential(double re, double Dsigma)
    {
        this->re = re;
        this->Dsigma = Dsigma;
    }

    virtual double dUdx(double x)
    {
        return 1.0-exp(-x+1.0);
    }

    double dUdr(double r)
    {
        return (12 * Dsigma * pow(r,2) * pow(pow(r,3) - pow(re,3),3)) / pow(re,12); // proizvodn
    }
};


// class points
class Points;

void glDrawPoints(Points & p);

class Points
{
private:
    Potential & pot;
    double *coords;
    double *velocity;
    double *coordsNew;
    double *coordsPrev;

    double *colors;
    int N, count;
    double mass;
    double dt;

public:

    Points(int N, double mass, double dt, Potential & poten): pot(poten)
    {
        this->N = N;
        this->mass = mass;
        this->dt = dt;
        coords = new double[3*N*N*N];
        coordsNew = new double[3*N*N*N];
        coordsPrev = new double[3*N*N*N];
        colors = new double[3*N*N*N];
        velocity = new double[3*N*N*N];
        this->count = N*N*N;
        double x,y,z;
        double re = pot.getRe();
        for (int i = 0; i < N; i++)
        {
            x = i/(N-1.0);
            for (int j = 0; j < N; j++)
            {
                y = j/(N-1.0);
                for (int k = 0; k < N; k++)
                {
                    z = k/(N-1.0);
                    coords[3*(N*N*i+N*j+k)+0] = (-1.0+2.0*x)*0.5*re*(N-1.0);
                    coords[3*(N*N*i+N*j+k)+1] = (-1.0+2.0*y)*0.5*re*(N-1.0);
                    coords[3*(N*N*i+N*j+k)+2] = (-1.0+2.0*z)*0.5*re*(N-1.0);

                    colors[3*(N*N*i+N*j+k)+0] = 0.2+0.8*x;
                    colors[3*(N*N*i+N*j+k)+1] = 0.2+0.8*y;
                    colors[3*(N*N*i+N*j+k)+2] = 0.2+0.8*z;
                }
            }
        }

        for (int i = 0; i < 3*N*N*N; i++)
        {
            coordsPrev[i] = coords[i];
            velocity[i] = 0;
        };

    }

      void verlet()
    {
        double a[3];

        for (int i = 0; i < count; i++)
        {
            for (int k = 0; k < 3; k++)
                a[k] = 0;

            for (int j = 0; j < count; j++)
            {
                if (i != j)
                {
                    double rij = norm(coords[3*i]-coords[3*j], coords[3*i+1]-coords[3*j+1], coords[3*i+2]-coords[3*j+2]);
                    double dUr = pot.dUdr(rij)/rij;
                    for (int k = 0; k < 3; k++)
                    {
                        a[k] += dUr * (coords[3*j+k]-coords[3*i+k]);
                    }
                }
            }

            for (int k = 0; k < 3; k++)
            {
                coordsNew[3*i+k] = 2.0*coords[3*i+k]-coordsPrev[3*i+k]+a[k]*dt*dt;
                velocity[3*i+k] = (coordsNew[3*i+k]-coordsPrev[3*i+k])/(2.0*dt);

                coordsPrev[3*i+k] = coords[3*i+k];
                coords[3*i+k] = coordsNew[3*i+k];
            }
        };
    }

    ~Points()
    {
        delete [] coords;
        delete [] coordsNew;
        delete [] coordsPrev;
        delete [] colors;
        delete [] velocity;
    }

    friend void glDrawPoints(Points & p);
};
// class p -> sodergit infu  o dot i coordinates
void glDrawPoints(Points & p)
{
    int count = p.N*p.N*p.N;
    double re = p.pot.getRe();
    double scale = re*(p.N-1.0);
    for (int i = 0; i < count; i++)
    {
        drawCube(p.colors[3*i], p.colors[3*i+1], p.colors[3*i+2],
        p.coordsPrev[3*i]/scale, p.coordsPrev[3*i+1]/scale, p.coordsPrev[3*i*2]/scale, 0.1/(p.N-1.0)
        );
    }
};
// draowpoints
// main verle and drow function
int main(int argc, char **argv)
{
  XVisualInfo         *vi;
  Colormap             cmap;
  XSetWindowAttributes swa;
  GLXContext           cx;
  XEvent               event;
  GLboolean            needRedraw = GL_FALSE, recalcModelView = GL_TRUE;
  int                  dummy;
  float theta = 2.2f;
  Potential pot(0.001, 1.0e-17);
  Points p(10, 2.0e-17, 0.0012, pot);
  /*** (1) open a connection to the X server ***/

  dpy = XOpenDisplay(NULL);
  if (dpy == NULL)
    fatalError("could not open display");

  /*** (2) make sure OpenGL's GLX extension supported ***/

  if(!glXQueryExtension(dpy, &dummy, &dummy))
    fatalError("X server has no OpenGL GLX extension");

  /*** (3) find an appropriate visual ***/

  /* find an OpenGL-capable RGB visual with depth buffer */
  vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
  if (vi == NULL)
  {
    vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);
    if (vi == NULL) fatalError("no RGB visual with depth buffer");
    doubleBuffer = GL_FALSE;
  }
 // if(vi->class != TrueColor)
   // fatalError("TrueColor visual required for this program");

  /*** (4) create an OpenGL rendering context  ***/

  /* create an OpenGL rendering context */
  cx = glXCreateContext(dpy, vi, /* no shared dlists */ None,
                        /* direct rendering if possible */ GL_TRUE);
  if (cx == NULL)
    fatalError("could not create rendering context");

  /*** (5) create an X window with the selected visual ***/

  /* create an X colormap since probably not using default visual */
  cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.event_mask = KeyPressMask    | ExposureMask
                 | ButtonPressMask | StructureNotifyMask;
  win = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0,
                      300, 300, 0, vi->depth, InputOutput, vi->visual,
                      CWBorderPixel | CWColormap | CWEventMask, &swa);
  XSetStandardProperties(dpy, win, "main", "main", None,
                         argv, argc, NULL);

  /*** (6) bind the rendering context to the window ***/

  glXMakeCurrent(dpy, win, cx);

  /*** (7) request the X window to be displayed on the screen ***/

  XMapWindow(dpy, win);

  /*** (8) configure the OpenGL context for rendering ***/

  glEnable(GL_DEPTH_TEST); /* enable depth buffering */
  glDepthFunc(GL_LESS);    /* pedantic, GL_LESS is the default */
  glClearDepth(1.0);       /* pedantic, 1.0 is the default */

  /* frame buffer clears should be to black */
  glClearColor(0.0, 0.0, 0.0, 0.0);

  /* set up projection transform */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
  glViewport(0, 0, 300, 300);

  printf( "Press left mouse button to rotate around X axis\n" );
  printf( "Press middle mouse button to rotate around Y axis\n" );
  printf( "Press right mouse button to rotate around Z axis\n" );
  printf( "Press ESC to quit the application\n" );

  /*** (9) dispatch X events ***/

  while (1)
  {
    if (1)
    {
      glMatrixMode(GL_MODELVIEW);

      /* reset modelview matrix to the identity matrix */
      glLoadIdentity();

      /* move the camera back three units */
      glTranslatef(0.0, 0.0, -3.0);

      /* rotate by X, Y, and Z angles */
      glRotatef(0.3*theta, 0.1, 0.0, 0.0);
      glRotatef(0.7*theta, 0.0, 0.1, 0.0);
      glRotatef(theta, 0.0, 0.0, 1.0);


      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* front face */
    glBegin(GL_TRIANGLES);
    glDrawPoints(p);
    drawCube(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glEnd();

    if (doubleBuffer)
    glXSwapBuffers(dpy, win);/* buffer swap does implicit glFlush */
  else
    glFlush();  /* explicit flush for single buffered case */

      recalcModelView = GL_FALSE;
      needRedraw = GL_TRUE;
    }
    theta += 0.5f;
    //if (needRedraw)
    //{
      //redraw();
      //needRedraw = GL_FALSE;
    //}
  }

};
//
