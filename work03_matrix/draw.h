#ifndef DRAW_H
#define DRAW_H

#include "matrix.h"
#include "ml6.h"

//draw_line fxn headers
void oct_one(int x0, int y0, int x1, int y1, screen s, color c);
void oct_two(int x0, int y0, int x1, int y1, screen s, color c);
void oct_seven(int x0, int y0, int x1, int y1, screen s, color c);
void oct_eight(int x0, int y0, int x1, int y1, screen s, color c);
void vertical(int x0, int y0, int x1, int y1, screen s, color c);
double slope(int x0, int y0, int x1, int y1);

void add_point( struct matrix * points, double x, double y, double z);
void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1);
void draw_lines( struct matrix * points, screen s, color c);
void draw_line(int x0, int y0, int x1, int y1, screen s, color c);

#endif
