#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:  struct matrix * points
         int x
         int y
         int z
Returns:
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
	if(points->cols == points->lastcol){
		grow_matrix(points, points->lastcol * 2);
	}
	points->m[0][points->lastcol] = x;
	points->m[1][points->lastcol] = y;
	points->m[2][points->lastcol] = z;
	points->m[3][points->lastcol] = 1.0;
	points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns:
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points,
	       double x0, double y0, double z0,
	       double x1, double y1, double z1) {
					 add_point(points,x0,y0,z0);
					 add_point(points,x1,y1,z1);

}

/*======== void draw_lines() ==========
Inputs:  struct matrix * points
         screen s
         color c
Returns:
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
	int max_col = points->lastcol;
	int counter;
	int x0, y0, x1, y1;
	for(counter = 0; counter < max_col-1; counter+=2){
		x0 = points->m[0][counter];
		y0 = points->m[1][counter];
		x1 = points->m[0][counter+1];
		y1 = points->m[1][counter+1];
		draw_line(x0,y0,x1,y1,s,c);
	}
}


//draw_line
void draw_line(int x0, int y0, int x1, int y1, screen s, color c){
  //if the slope is underfined ie. vertical line
  if(x0 == x1){
    if(y1 > y0){
      vertical(x0,y0,x1,y1,s,c);
    }
    else{
      vertical(x1,y1,x0,y0,s,c);
    }
  }
  //normal stuff
  else{
    double m = slope(x0,y0,x1,y1);
    if(x0 < x1){
      //octI
      if(m >= 0 && m <= 1){
        oct_one(x0,y0,x1,y1,s,c);
      }
      //octII
      else if(m > 1){
        oct_two(x0,y0,x1,y1,s,c);
      }
      //octVIII
      else if(m < 0 && m >= -1){
        oct_eight(x0,y0,x1,y1,s,c);
      }
      //octVII
      else {
        oct_seven(x0,y0,x1,y1,s,c);
      }
    }
    else{
      //octV
      if(m >= 0 && m <= 1){
        oct_one(x1,y1,x0,y0,s,c);
      }
      //octVI
      else if(m > 1){
        oct_two(x1,y1,x0,y0,s,c);
      }
      //octIV
      else if(m < 0 && m >= -1){
        oct_eight(x1,y1,x0,y0,s,c);
      }
      //octIII
      else {
        oct_seven(x1,y1,x0,y0,s,c);
      }
    }
  }
}

//SLOPE
double slope(int x0, int y0, int x1, int y1){
  return (1.0*(y1-y0))/(1.0*(x1-x0));
}

//OCTANT I
void oct_one(int x0, int y0, int x1, int y1, screen s, color c){
  int x = x0;
  int y = y0;
  int A = y1 - y;
  int B = -(x1 - x);
  int d = 2*A + B;

  while(x <= x1){
    plot(s,c,x,y);
    if(d > 0){
      y++;
      d+=2*B;
    }
    x++;
    d+=2*A;
  }
}

//OCTANT II
void oct_two(int x0, int y0, int x1, int y1, screen s, color c){
  int x = x0;
  int y = y0;
  int A = y1 - y;
  int B = -(x1 - x);
  int d = A + 2*B;

  while(y <= y1){
    plot(s,c,x,y);
    if(d < 0){
      x++;
      d+=2*A;
    }
    y++;
    d+=2*B;
  }
}

//OCTANT VII
void oct_seven(int x0, int y0, int x1, int y1, screen s, color c){
  int x = x0;
  int y = y0;
  int A = y1 - y;
  int B = -(x1 - x);
  int d = A - 2*B;

  while(y >= y1){
    plot(s,c,x,y);
    if(d > 0){
      x++;
      d+=2*A;
    }
    y--;
    d-=2*B;
  }
}

//OCTANT VIII
void oct_eight(int x0, int y0, int x1, int y1, screen s, color c){
  int x = x0;
  int y = y0;
  int A = y1 - y;
  int B = -(x1 - x);
  int d = 2*A - B;

  while(x <= x1){
    plot(s,c,x,y);
    if(d < 0){
      y--;
      d-=2*B;
    }
    x++;
    d+=2*A;
  }
}

//VERTICAL LINE! SEPARATED INTO SEPARATE FXN
void vertical(int x0, int y0, int x1, int y1, screen s, color c){
  int x = x0;
  int y = y0;

  while(y <= y1){
    plot(s,c,x,y);
    y++;
  }

}
