## 01/31/18 - 02/01/18 | Aim: Peering into the depths of color
### Color Depth
The amount of data used to represent a single pixel

| size  | color option |
| ------------- | ------------- |
| 1 bit | 1 color: on or off |
| 2 bit | 1 color with intensity (think of greyscale) |
| 3 bit | Red, Green, Blue with on or off |
| 4 bit | RGB with intensity |
| 6 bit | RGB each color has its own intensity |
| 3 byte | RGB each color with 256 possible intensities |

### Other Color Spaces
__RGBA__: red, green, blue + alpha (transparency)

__HSB__: hue, saturation, bightness
- hue: angle measurement
- saturation: radius of base of cone
- brightness: height of cone

![HSB IMAGE](https://2020spiritualvision.files.wordpress.com/2017/02/hsl-cone-graphic.jpg)

### Image File Formats
__Vector vs. Raster__

Vector formats represent images as a series of drawing instructions
- infinitely scalable
- good for stuff like fonts and shapes, not so good for actual pictures
- SVG: Scalable Vector Graphics

Raster formats represent images as a grid of pixels

__Uncompressed vs. Compressed (Raster)__

Uncompressed formats contain data for each pixel
- examples: BMP, TIFF, RAW
- __NOTE: THESE FILES CAN BE VERY LARGE__

Compressed formats use a compression algorithm to minimize file size (don't change resolution!)
- Lossless vs. Lossy
  - Lossless compression algorithms contain enough information to exactly recreate the original image
    - PNG (Portable network Graphics), GIF (Graphics interchange Format)
  - Lossy compression Algirthms do not retain all the details of the original image (generally avergae out groups of pixels and make that an entire chunk a single pixel)
    - JPEG (Joint Photographic Experts Group)

__PPM (Portable PixMap)__
- Uncompressed raster format
- Pixel data is represented by RGB triplets in either ASCII (easier) or binary
- All whitespace is equivalent
- __NOTE: THESE FILES CAN GET VERY LARGE SO DO NOT PUSH THE .PPM FILES TO GITHUB REPO__

example file (in .ppm file): 

```ppm
P3 //tells you what kind of file it is. P3 tells you it's in ASCII
4 3 //resolution, width followed by height in pixels
255 //mximum color value
//all of this is in the header^^
then, raster pixel data follows
```
## 02/05/18 - 02/07/18 | Aim: --
### Bresenham's Line Algorithm

- Find the best pixels to approximate the tangent line.
- Assume: (x0,y0) -> (x1,y1)
  - x0, y0, x1, y1 are all integers
  - x0 < x1 (we're always going to draw the line from left to right)
  - Octant Cartesian Coordinate System
  - Start at Octant I (slope is between 0 and 1)
  
![OCTANT](https://i.stack.imgur.com/Gk616.jpg)

![GRAPH](https://upload.wikimedia.org/wikipedia/commons/thumb/a/ab/Bresenham.svg/300px-Bresenham.svg.png)

if (x+1, y+1/2) is above draw the lower pixel

if (x+1, y+1/2) is below, drawn the upper pixel

__Testing (x+1,y+1/2)__

y = mx + b

0 = mx - y + b

0 = (Δy/Δx)x - y + b

0 = (Δy)Δx - (Δx)y + (Δx)b

A = Δy, B = -Δx, C = (Δx)b

0 = Ax + By + C

f(x,y) = Ax + By + C

f(x,y) = 0 (on the line)

f(x,y') < 0 (when y' > y, above line)

f(x,y'') > 0 (when y'' < y, below line)

__First Draft Line Algorithm (x0,y0) -> (x1,y1)__
```
//pseudocode
x = x0, y = y0
d = f(x+1,y+1/2)
while x <= x1
  plot (x,y)
  if d > 0
    y++
  x++
  d = f(x+1,y+1/2) //can be optimized
```

If x increases by 1, d = d + A

If y increases by 1, d = d + B

__Second Draft Line Algorithm (x0,y0) -> (x1,y1)__
```
//pseudocode
x = x0, y = y0
d = f(x+1,y+1/2) //still a problem
while x <= x1
  plot (x,y)
  if d > 0
    y++
    d+=B
  x++
  d+=A
```
d0 = f(x0+1,y0+1/2)

= A(x0+1) + B(y0+1/2) + C

= Ax0 + By0 + C + A + 1/2B

We know Ax0 + By0 + C = 0 (it is f(x0,y0))

d0 = A +1/2B

2d0 = 2A + B

__Third Draft Line Algorithm (x0,y0) -> (x1,y1)__
```
//pseudocode
x = x0, y = y0
d = 2A + B
while x <= x1
  plot (x,y)
  if d > 0
    y++
    d+=2B //two b everything doubles
  x++
  d+=2A
```

### Octant II

Slope is > 1 and < infinity

New choices: (x, y+1) and (x+1, y+1)

New midpoint: (x+1/2,y+1)

d0 = f(x+1/2,y+1) =1/2A + B = A + 2B
```
//pseudocode
x = x0, y = y0
d = A + 2B
while y <= y1
  plot (x,y)
  if d < 0 //this means that ourmidpoint is to the left of the line
    x++
    d+=2A
  y++
  d+=2B
```
Same goes for Octants VIII and VII

## 02/12/18 | Aim: --
### Represeting Image Data

__Edge List (Edge Matrix)__ 
- Images are stored as a list of points where each two points define a line
- [ P0, P1, P1, P2, P2, P0 ] in whcih each P represents a set of (x,y,z) coordinates (will need z coordinate later for rotations)

## 02/13/18 | Aim: --
### Matrix Math for Graphs

__Matrix Multiplication__
- Let M and N be two matrices; we are performing M・N
- Number of rows in the N must equal number of columns in M
- R1xC1・R2xC2 = R1xC2 (new dimensions)
- Not a commutative operation
  - M・N not necessarily equal to N・M
- __Multiplicative Identity__
  - I・M = M
  
![IDENTITY MATRIX](http://www.statisticslectures.com/images/identity2.gif)

### Transformations

__Affine transformation__: preserves the number of vertices and the order (orientation) of the vertices.; preserves the structures of the edge matrices. Includes translations, dilations, and rotations.

Let: E be the edge matrix, T be the transformation matrix

Two choices: E・T or T・E

We will go with T・E in order to preserve the size of E

__Translation__: move

(x,y,z) T(a,b,c)-> (x+a,y+b,z+c)

__Dilation__: 

__Rotation__: 


