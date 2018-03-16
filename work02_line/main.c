#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

int main() {

  screen s;
  color c;

  c.red = MAX_COLOR;
  c.green = MAX_COLOR;
  c.blue = MAX_COLOR;

  clear_screen(s);
  /***
  //rectangle
  draw_line(50,400,450,400,s,c);
  draw_line(450,400,450,200,s,c);
  draw_line(450,200,50,200,s,c);
  draw_line(50,200,50,400,s,c);

  //square
  draw_line(260,390,440,390,s,c);
  draw_line(440,390,440,210,s,c);
  draw_line(440,210,260,210,s,c);
  draw_line(260,210,260,390,s,c);

  //T
  draw_line(80,280,100,280,s,c);
  draw_line(90,280,90,260,s,c);
  //h
  draw_line(105,280,105,260,s,c);
  draw_line(105,273,115,273,s,c);
  draw_line(115,273,115,260,s,c);
  //e
  draw_line(120,266,130,266,s,c);
  draw_line(130,266,130,273,s,c);
  draw_line(130,273,120,273,s,c);
  draw_line(120,273,120,260,s,c);
  draw_line(120,260,130,260,s,c);

  //O
  draw_line(80,250,100,250,s,c);
  draw_line(100,250,100,230,s,c);
  draw_line(100,230,80,230,s,c);
  draw_line(80,230,80,250,s,c);
  //f
  draw_line(115,250,105,250,s,c);
  draw_line(105,250,105,230,s,c);
  draw_line(105,240,115,240,s,c);
  //f
  draw_line(130,250,120,250,s,c);
  draw_line(120,250,120,230,s,c);
  draw_line(120,240,130,240,s,c);
  //i
  draw_line(135,240,135,230,s,c);
  draw_line(135,246,135,243,s,c);
  //c
  draw_line(150,245,140,245,s,c);
  draw_line(140,245,140,230,s,c);
  draw_line(140,230,150,230,s,c);
  //e
  draw_line(155,245,165,245,s,c);
  draw_line(165,245,165,238,s,c);
  draw_line(165,238,155,238,s,c);
  draw_line(155,245,155,230,s,c);
  draw_line(155,230,165,230,s,c);

  //standing dude
  //head
  draw_line(300,370,320,370,s,c);
  draw_line(320,370,320,350,s,c);
  draw_line(320,350,300,350,s,c);
  draw_line(300,350,300,370,s,c);

  //body
  draw_line(285,345,335,345,s,c);

  draw_line(285,345,285,295,s,c);
  draw_line(285,295,295,295,s,c);
  draw_line(295,295,295,325,s,c);
  draw_line(295,325,298,325,s,c);
  draw_line(298,325,298,260,s,c);
  draw_line(298,260,308,260,s,c);
  draw_line(308,260,308,300,s,c);

  draw_line(335,345,335,295,s,c);
  draw_line(335,295,325,295,s,c);
  draw_line(325,295,325,325,s,c);
  draw_line(325,325,322,325,s,c);
  draw_line(322,325,322,260,s,c);
  draw_line(322,260,314,260,s,c);
  draw_line(314,260,314,300,s,c);

  draw_line(308,300,314,300,s,c);

  //suitcase

  //table
  draw_line(340,280,380,280,s,c);
  draw_line(355,280,355,240,s,c);

  //sitting dude

  //chair

  ***/

  //COBWEBS

  int change = 50;
  int count = 0;

  while(count < 10){
    draw_line(0,0,change,500,s,c);
    change+=50;
    count++;
  }

  count = 0;
  change = 50;

  while(count < 10){
    draw_line(0,500,change,0,s,c);
    change+=50;
    count++;
  }

  count = 0;
  change = 50;

  while(count < 10){
    draw_line(500,500,change,0,s,c);
    change+=50;
    count++;
  }

  count = 0;
  change = 50;

  while(count < 10){
    draw_line(500,0,change,500,s,c);
    change+=50;
    count++;
  }

  draw_line(0,250,500,250,s,c);
  draw_line(250,500,250,0,s,c);

  draw_line(0,500,500,0,s,c);
  draw_line(0,0,500,500,s,c);


  display(s);
  save_extension(s, "lines.png");
}
