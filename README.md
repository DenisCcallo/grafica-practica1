# Computación Grafica-practica1
Dibujo de linea, polígono, rotación,  traslación y escalamiento en 2D


**Tabla de Contenido**
- Linea
- Poligono
- Transformaciones
- - Rotación
- - Traslación
- - Escalamiento


**Linea**

Para dibujar la linea se toma el punto de referencia con el clic izquierdo del mouse, despues hacer otra vez el clic izquierdo del mouse para que el algoritmo proceda a dobujar la linea.
```c++
void linea (int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd - y0, pasos, k;
    float xp, yp, x = x0, y = y0;
    if (fabs (dx) > fabs (dy))
        pasos = fabs (dx);
    else
        pasos = fabs (dy);
    xp = float (dx) / float (pasos);
    yp = float (dy) / float (pasos);
    plotPoint(round (x), round (y));
    for (k = 0; k < pasos; k++)
    {
        x += xp;
        y += yp;
        plotPoint(round (x), round (y));
    }
}
```
![Dibujando linea](https://github.com/DenisCcallo/grafica-practica1/blob/master/imagenes/linea.PNG "Dibujando linea")

**Poligono**

Para dibujar el poligono se toma como referencia para los vertices haciendo clic izquierdo del mouse, cuando se quiere tomar el ultimo vertice del poligono se da clic derecho del mouse. A continuacion con el algoritmo de la linea se va trazando la linea de vertice a vertice, cuando llega al final une el ultimo vertice con el primero para cerrar el poligono

```c++
void poligono()
{
    int tam=coor1.size();

    for(int i=1; i<tam; i++)
    {
        linea(coor1[i-1],coor2[i-1],coor1[i],coor2[i]);
    }
    linea(coor1[tam-1],coor2[tam-1],coor1[0],coor2[0]);
}
```
![Poligono](https://github.com/DenisCcallo/grafica-practica1/blob/master/imagenes/poligono.PNG "Poligono")

**Rotación**

En la rotacion  se toma como referencia un punto del cual se rotara la imagen graficada, despues se le asigna un angulo para que rote esa cantidad segun la formula.

```c++
void rotacion(int px, int py, int cx, int cy)
{
    float theta = 60.0;
    int xf, yf;
    if (theta >= (2.0 * 3.14159))
        theta = theta - (2.0 * 3.14159);
    //calcular rotacion..
    xf = cx + (int)((float)(px - cx) * cos(theta))  - ((float)(py - cy) * sin(theta));
    yf = cy + (int)((float)(px - cx) * sin(theta))  + ((float)(py - cy) * cos(theta));
    plotPoint(xf, yf); // rotacion
    glFlush();
}
```
![Rotacion](https://github.com/DenisCcallo/grafica-practica1/blob/master/imagenes/rotacion.PNG "Rotacion")


**Traslación**

Para trasladar el grafico se desplaza una cantidad (x,y) sumando el punto original y la cantidad a trasladar

```c++
void traslacion(int px, int py, int tx, int ty)
{
    int fx = px, fy = py;
    //glClear(GL_COLOR_BUFFER_BIT);
    px = px + tx;
    py = py + ty;
    if (px > maxWD || px < 0 || py > maxHT || py < 0) //si el punto se pasa de la ventana
    {
        px = fx;
        py = fy;
    }
    plotPoint(px, py);
    glFlush();
}
```
![Traslacion](https://github.com/DenisCcallo/grafica-practica1/blob/master/imagenes/traslacion.PNG "Traslacion")

**Escalamiento**
Para todos los puntos dados en la figura original se hace una multiplicacion del punto original y la cantidad a escalar de la figura

```c++
void escalamiento(int px, int py, int esx, int esy)
{
    int fx, fy;
    //escala
    fx = px * esx;
    fy = py * esy;
    plotPoint(fx, fy);
    glFlush();
}
```
![Escalamiento](https://github.com/DenisCcallo/grafica-practica1/blob/master/imagenes/escalamiento.PNG "Escalamiento")

Nota: En el escalamiento cuando se hace mas grande queda entrecortado la figura, falta hacer para que escale los vertices y despues que recien dibuje las lineas, asi estaria bien escalado.
