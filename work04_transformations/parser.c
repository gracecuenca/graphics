#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

/*======== void parse_file () ==========
Inputs:   char * filename
          struct matrix * transform,
          struct matrix * pm,
          screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
   line: add a line to the edge matrix -
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 ident: set the transform matrix to the identity matrix -
	 scale: create a scale matrix,
	    then multiply the transform matrix by the scale matrix -
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix,
	    then multiply the transform matrix by the translation matrix -
	    takes 3 arguments (tx, ty, tz)
	 rotate: create an rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 2 arguments (axis, theta) axis should be x y or z
	 apply: apply the current transformation matrix to the
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format

IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename,
                  struct matrix * transform,
                  struct matrix * edges,
                  screen s) {

  FILE *f;
  char line[256];
  char* args[8];
  char * temp;
  int i;

  color c;

  c.red = 20;
  c.blue = 255;
  c.green = 240;

  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 )
    f = stdin;
  else
    f = fopen(filename, "r");

  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);

    //line:
    if( !strcmp(line, "line") ){
      //need to get the next line which contains the coordinates for the point
      fgets(line, 255, f);
      //temp now has all the points
      temp = line;
      //fetching the arguments
      i = 0;
      while( (args[i] = strsep(&temp, " ")) ){
        i++;
      }

      //adding da points
      add_edge(edges, atoi(args[0]), atoi(args[1]), atoi(args[2]), atoi(args[3]), atoi(args[4]), atoi(args[5]));
      //args = 0;
    }

    //ident:
    else if( !strcmp(line, "ident") ){
      ident(transform);
    }

    //scale:
    else if( !strcmp(line, "scale") ){
      //needs to get the next line which contains the scale factors for the points
      fgets(line, 255, f);
      //temp now contains the scaling factors
      temp = line;
      //fetching the arguments
      i = 0;
      while( (args[i] = strsep(&temp, " ")) ){
        i++;
      }
      //creating the scale matrix
      matrix_mult(make_scale( atoi(args[0]), atoi(args[1]), atoi(args[2])), transform);
      //args = 0;
    }

    //translate:
    else if( !strcmp(line, "move") ){
      //need to get the next line which contains the translation factors
      fgets(line, 255, f);
      //temp now contains these addings/subtractions
      temp = line;
      //fetching the arguments
      i = 0;
      while( (args[i] = strsep(&temp, " ")) ){
        i++;
      }
      //creating the translation matrix
      matrix_mult(make_translate( atoi(args[0]), atoi(args[1]), atoi(args[2])), transform);
      //args = 0;
    }

    //rotation:
    else if( !strcmp(line, "rotate") ){
      //need to get the next line which contains axis and theta
      fgets(line, 255, f);
      //temp now contains axis and theta
      temp = line;
      //fetching the arguments
      i = 0;
      while( (args[i] = strsep(&temp, " ")) ){
        i++;
      }
      //creating the rotation matrix
      if( !strcmp(args[0], "x")){
        matrix_mult(make_rotX( atoi(args[1])), transform);
      }
      else if( !strcmp(args[0], "y")){
        matrix_mult(make_rotY( atoi(args[1])), transform);
      }
      else if( !strcmp(args[0], "z")){
        matrix_mult(make_rotZ( atoi(args[1])), transform);
      }
      else{
        printf("invalid argument\n");
      }
    }

    //apply:
    else if( !strcmp(line, "apply") ){
      matrix_mult(transform, edges);
    }

    //display:
    else if( !strcmp(line, "display") ){
      clear_screen(s);
      draw_lines(edges, s, c);
      display(s);
    }

    //save:
    else if( !strcmp(line, "save") ){
      //need to get next line which contains the filename
      fgets(line, 255, f);
      draw_lines( edges, s, c );
      save_extension(s, line);
    }

    //quit:
    else if( !strcmp(line, "quit") ){
      exit(0);
    }

    //invalid argument:
    else{
      printf("invalid argument\n");
    }

  }
}
