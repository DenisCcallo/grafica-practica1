#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
using namespace std;

#define maxWD 800
#define maxHT 600

vector<int> coor1, coor2;

GLsizei winWidth =800, winHeight =600; // Tamano inicial de la ventana
int x1=-1,y1=-1,x2=-1,y2=-1;
bool bandx=false, bandy=false;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
    //gluOrtho2D(100.0,200.0,150.0,150.0);
}
void displayFcn(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //Borrar ventana devisualizacion.
    glColor3f(1.0,0.0,0.0); //color de punto.
    glPointSize(2.0); //tamaño de punto
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    /*Reinicializar parametro de proyección y visor*/
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0.0 , GLdouble(newWidth),0.0 , GLdouble( newHeight));
    /*reinicializa parametro de tamano ventana*/
    winWidth = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex2i(x,y);
    glEnd();
}


void inc_line(int x1, int y1, int x2, int y2)
{
    int dx, dy, incE, incNE, d, x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    d = 2 * dy - dx; /* Valor inicial de d */
    incE = 2 * dy; /* Incremento de E */
    incNE = 2 * (dy - dx); /* Incremento de NE */
    x = x1;
    y = y1;
    plotPoint(x, y);
    while (x < x2){
        if (d <= 0){
            /* Escolhe E */
            d = d + incE;
            x = x + 1;
        }else{
            /* Escolhe NE */
            d = d + incNE;
            x = x + 1;
            y = y + 1;
        }/* end if */
        plotPoint(x, y);
    }/* end while */
}/* end inc_line */

void line(int xx1, int yy1, int xx2, int yy2)
{
    int x, y;
    float a;
    int valor;
    a=(yy2-yy1)/(xx2-xx1);
    for (x=xx1;x<=xx2;x++)
    {
        /* arredonda y */
        y = (yy1 + a * (x - xx1));
        plotPoint(x, y);
    }
}

inline int round (const float a) { return int (a + 0.5); }
void linea(int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - y0, steps, k;
    float xIncrement, yIncrement, x = x0, y = y0;
    if (fabs (dx) > fabs (dy))
        steps = fabs (dx);
    else
        steps = fabs (dy);
    xIncrement = float (dx) / float (steps);
    yIncrement = float (dy) / float (steps);
    plotPoint(round (x), round (y));
    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        plotPoint(round (x), round (y));
    }
}
void poligono()
{
    int tam=coor1.size();
    for(int i=1; i<tam; i++)
    {
        linea(coor1[i-1],coor2[i-1],coor1[i],coor2[i]);
    }
    linea(coor1[tam-1],coor2[tam-1],coor1[0],coor2[0]);
}

void mousePtPlot(GLint button , GLint action , GLint xMouse, GLint yMouse)
{
    if(button==GLUT_LEFT_BUTTON && action==GLUT_DOWN) //GLUT_RIGHT_BUTTON
    {

        printf("obtiene coordenada: ");
        x1=xMouse;
        y1=winHeight-yMouse;
        plotPoint(x1,y1);
        printf("%d %d\n",x1,y1);
        coor1.push_back(x1);
        coor2.push_back(y1);


    }
    if(button==GLUT_RIGHT_BUTTON && action==GLUT_DOWN)
    {
        printf("ultima coordenada: ");
        x1=xMouse;
        y1=winHeight-yMouse;
        plotPoint(x1,y1);
        coor1.push_back(x1);
        coor2.push_back(y1);
        printf("%d %d\n",x1,y1);
        poligono();


    }
    glFlush();

}
int main(int argc, char**argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,100);

    glutInitWindowSize(winWidth, winHeight );//ancho alto de ventana
    glutCreateWindow("Poligono con puntos por mouse" );
    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(mousePtPlot);
    glutMainLoop();
}
