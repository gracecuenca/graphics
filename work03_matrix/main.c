#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  printf("===== matrix * edges created =====\n");
  printf("===== matrix * mult created =====\n");
  printf("===== matrix * other created =====\n");
  struct matrix *edges;
  struct matrix *mult;
  struct matrix *other;
  edges = new_matrix(4, 4);
  mult = new_matrix(4,1);
  other = new_matrix(4,4);

  printf("===== adding points to matrix * other =====\n");
  add_point(other, 0.0,0.0,0.0);
  add_point(other, 50.0,0.0,0.0);
  add_point(other, 50.0,50.0,0.0);
  add_point(other, 0.0,50.0,0.0);

  printf("===== printing matrix * other =====");
  print_matrix(other);

  printf("===== turning matrix * other to identity matrix =====\n");
  ident(other);

  printf("===== printing matrix * other =====");
  print_matrix(other);

  printf("===== adding point to matrix * mult =====\n");
  add_point(mult, 1.0, 3.0, 0.0);

  printf("===== printing matrix * mult =====");
  print_matrix(mult);

  printf("===== adding edges to matrix * edges =====\n");
  add_edge(edges, 50.0,50.0,0.0,100.0,50.0,0.0);
  add_edge(edges, 100.0,50.0,0.0,100.0,100.0,0.0);
  //add_edge(edges,100.0,100.0,0.0,50.0,100.0,0.0);
  //add_edge(edges,50.0, 100.0, 0.0,50.0, 50.0, 0.0);

  printf("===== printing matrix * edges =====");
  print_matrix(edges);

  printf("===== testing matrix multiplication: edges * mult =====\n");
  matrix_mult(edges, mult);

  printf("===== printing matrix * mult =====");
  print_matrix(mult);

  printf("===== testing matrix multiplication: mult * other (now ident)=====\n");
  matrix_mult(other, mult);

  printf("===== printing matrix * mult =====\n");
  printf("===== should be the same as above! =====");
  print_matrix(mult);

  printf("===== generating image!=====\n");
  //BELIEVER -- IMAGINE DRAGONS

  screen s;
  clear_screen(s);

  //white
  color c;
  c.red = 255;
  c.green = 255;
  c.blue = 255;

  //grid
  struct matrix * grid = new_matrix(4,12);

  //horizontal lines
  add_edge(grid,0.0,450.0,0.0,500.0,450.0,0.0);
  add_edge(grid,0.0,400.0,0.0,500.0,400.0,0.0);
  add_edge(grid,0.0,350.0,0.0,500.0,350.0,0.0);
  add_edge(grid,0.0,300.0,0.0,500.0,300.0,0.0);
  add_edge(grid,0.0,250.0,0.0,500.0,250.0,0.0);

  //vertical lines
  add_edge(grid,50.0,500.0,0.0,50.0,230.0,0.0);
  add_edge(grid,100.0,500.0,0.0,100.0,230.0,0.0);
  add_edge(grid,150.0,500.0,0.0,150.0,230.0,0.0);
  add_edge(grid,200.0,500.0,0.0,200.0,230.0,0.0);
  add_edge(grid,250.0,500.0,0.0,250.0,230.0,0.0);
  add_edge(grid,300.0,500.0,0.0,300.0,230.0,0.0);
  add_edge(grid,350.0,500.0,0.0,350.0,230.0,0.0);
  add_edge(grid,400.0,500.0,0.0,400.0,230.0,0.0);
  add_edge(grid,450.0,500.0,0.0,450.0,230.0,0.0);

  draw_lines(grid, s, c);

  //pillars

  //orange pillar
  struct matrix * o_pillar = new_matrix(4,4);
  c.red = 231;
  c.green = 154;
  c.blue = 40;

  double x = 175.0;
  while(x < 220.0){
    add_edge(o_pillar, x,500.0,0.0,x,230.0,0.0);
    x+=1.0;
  }

  draw_lines(o_pillar,s,c);

  //green pillar
  struct matrix * g_pillar = new_matrix(4,4);
  c.red = 39;
  c.green = 228;
  c.blue = 183;

  x = 227.0;
  while(x < 272.0){
    add_edge(g_pillar, x,500.0,0.0,x,230.0,0.0);
    x+=1.0;
  }

  draw_lines(g_pillar,s,c);

  //blue pillar
  struct matrix * b_pillar = new_matrix(4,4);
  c.red = 96;
  c.green = 226;
  c.blue = 217;

  x = 280.0;
  while(x < 325.0){
    add_edge(b_pillar, x,500.0,0.0,x,230.0,0.0);
    x+=1.0;
  }

  draw_lines(b_pillar,s,c);

  //mountains
  struct matrix* mountains = new_matrix(4,4);
  struct matrix* shadow = new_matrix(4,4);
  struct matrix* light = new_matrix(4,4);

  //dark
  c.red = 140;
  c.green = 86;
  c.blue = 86;

  add_edge(mountains,50.0,100.0,0.0,150.0,200.0,0.0);
  add_edge(mountains,150.0,200.0,0.0,125.0,100.0,0.0);
  add_edge(mountains,150.0,200.0,0.0,250.0,100.0,0.0);

  //shadowed
  double shade = 125.0;
  while(shade < 250.0){
    add_edge(shadow,150.0,200.0,0.0,shade,100.0,0.0);
    shade+=1.0;
  }

  add_edge(mountains,200.0,200.0,0.0,300.0,300.0,0.0);
  add_edge(mountains,300.0,300.0,0.0,275.0,200.0,0.0);
  add_edge(mountains,300.0,300.0,0.0,400.0,200.0,0.0);

  //shadowed
  shade = 275.0;
  while(shade < 400.0){
    add_edge(shadow,300.0,300.0,0.0,shade,200.0,0.0);
    shade+=1.0;
  }

  add_edge(mountains,300.0,150.0,0.0,400.0,250.0,0.0);
  add_edge(mountains,400.0,250.0,0.0,375.0,150.0,0.0);
  add_edge(mountains,400.0,250.0,0.0,500.0,150.0,0.0);

  //shadowed
  shade = 375.0;
  while(shade < 500.0){
    add_edge(shadow,400.0,250.0,0.0,shade,150.0,0.0);
    shade+=1.0;
  }

  draw_lines(mountains,s,c);
  draw_lines(shadow,s,c);

  //light
  c.red = 191;
  c.green = 202;
  c.blue = 226;

  //light
  double lighten = 50.0;
  while(lighten < 125.0){
    add_edge(light,150.0,200.0,0.0,lighten,100.0,0.0);
    lighten+=1.0;
  }

  //light
  lighten = 200.0;
  while(lighten < 275.0){
    add_edge(light,300.0,300.0,0.0,lighten,200.0,0.0);
    lighten+=1.0;
  }

  //light
  lighten = 300.0;
  while(lighten < 375.0){
    add_edge(light,400.0,250.0,0.0,lighten,150.0,0.0);
    lighten+=1.0;
  }

  draw_lines(light,s,c);

  save_extension(s, "image.jpg");

  display(s);

  free_matrix(edges);
  free_matrix(mult);
  free_matrix(other);
  free_matrix(grid);
  free_matrix(o_pillar);
  free_matrix(b_pillar);
  free_matrix(g_pillar);
  free_matrix(mountains);
  free_matrix(shadow);
  free_matrix(light);
}
