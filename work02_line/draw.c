#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//fxn headers
void oct_one(int x0, int y0, int x1, int y1, screen s, color c);
void oct_two(int x0, int y0, int x1, int y1, screen s, color c);
void oct_seven(int x0, int y0, int x1, int y1, screen s, color c);
void oct_eight(int x0, int y0, int x1, int y1, screen s, color c);
void vertical(int x0, int y0, int x1, int y1, screen s, color c);
double slope(int x0, int y0, int x1, int y1);


//Insert your line algorithm here
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
