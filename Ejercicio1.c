/* Algoritmo DDA para el trazado de líneas */

#include <stdio.h>
#include <graphics.h>
#include <math.h>
int DDALine(int x0, int y0, int x1, int y1, int puntos[]);
void generaArchivo(int puntos[], int count);

int main(int argc, char **argv)
{
	int x1, y1, x2, y2;

	int gd = DETECT, gm = VGAMAX;

	int puntos[1000], count;
	int sides;
	printf("Lados del polígono: ");
	scanf("%i", &sides);
	initgraph(&gd, &gm, NULL);


	double radius = 100;
	double angle = (double)360.0/(double)sides;
	double xc = (getmaxx()/2);
	double yc = (getmaxy()/2);
	int xi,yi,xf,yf;
	double val = M_PI / 180;
	angle *= val;
	int a = 0;
	double currAngle = 0;
	for(a=1; a<=sides; a++)
	{
		xi = xc + (radius * cos(angle*a));
		yi = yc + (radius * sin(angle*a));

		xf = xc + (radius * cos(angle*(a+1)));
		yf = yc + (radius * sin(angle*(a+1)));

		count = DDALine(xi, yi, xf, yf, puntos);
		generaArchivo(puntos, count);
	}

	getch();

	closegraph();

	return 0;
}

/* Algoritmo DDA */
int DDALine(int x0, int y0, int x1, int y1, int puntos[])
{

	if((x1 - x0 < 0) || (y1 - y0 < 0)  )
	{
		int temp = x0;
		x0 = x1;
		x1 = temp;

		int temp1 = y0;
		y0 = y1;
		y1 = temp1;
	}

	int maxY, i;

	float dx, dy, m, x, y;

	i=0;

	dx=x1-x0;
	dy=y1-y0;

	maxY=getmaxy();

	if (dx == 0) /* Es una línea vertical */
	{
		for(y = y0; y <= y1; ++y)
		{
			putpixel(x0, maxY-y, WHITE);
			puntos[i] = x0;
			puntos[i+1] = y;
			i += 2;
		}
	}
	else if (dy == 0) /* Es una línea horizontal */
	{
		for(x = x0; x <= x1; ++x)
		{
			putpixel(x, y0, WHITE);
			puntos[i] = x0;
			puntos[i+1] = y;
			i += 2;
		}
	}
	else if (dy <= dx) /* Es una línea con pendiente < 1 */
	{
		m = dy/dx;
		y = y0;

		for(x = x0; x <= x1; ++x)
		{
			putpixel(x, (int)(maxY-y), WHITE);
			puntos[i] = x;
			puntos[i+1] = (int)y;
			i += 2;
			y = y + m;
		}
	}
	else /* Es una línea con pendiente > 1 */
	{
		m = dx/dy;
		x = x0;
		for(y = y0; y <= y1; ++y)
		{
			putpixel((int)x, maxY-y, WHITE);
			puntos[i] = (int)x;
			puntos[i+1] = y;
			i += 2;
			x = x + m;
		}
	}

	return i;
 }


/* Guardar los puntos dibujados en un archivo */
void generaArchivo(int puntos[], int count)
{
	FILE *fp;

	int i,np;

	fp=fopen("puntos.txt","w");

	fprintf(fp,"%s","Los puntos dibujados son:\n");

	np=0;

	for(i = 0; i < count; i += 2)
	{
		fprintf(fp,"(%d, %d) ", puntos[i], puntos[i+1]);

		np++;

		if(np==5) { fprintf(fp,"\n"); np=0; }
	}

	fclose(fp);
}
