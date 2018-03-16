#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){
  int fd;
  char pixel[100];
  int count;

  int r = 0;
  int g = 0;
  int b = 0;

  fd = open("image.ppm", O_CREAT | O_WRONLY, 0666);
  write(fd, "P3\n500 500\n255\n", sizeof("P3\n500 500\n255\n"));

  for(count = 0; count < 500*500; count++){
    //sprintf replaces
    sprintf(pixel, "%d %d %d\n", r, g, b);
    if(r < 255){
      r +=1;
    }
    else if(g < 255){
      g+=1;
    }
    else if(b < 255){
      b+=1;
    }
    else{
      r = 0;
      g = 0;
      b = 0;
    }
    write(fd, pixel, sizeof(pixel));
  }

  close(fd);

  return 0;
}
