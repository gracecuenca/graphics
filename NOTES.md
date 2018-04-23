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

__HSB__: hue, saturation, brightness
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
  - Lossy compression Algorithms do not retain all the details of the original image (generally average out groups of pixels and make that an entire chunk a single pixel)
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
255 //maximum color value
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
  if d < 0 //this means that our midpoint is to the left of the line
    x++
    d+=2A
  y++
  d+=2B
```
Same goes for Octants VIII and VII

## 02/12/18 | Aim: --
### Representing Image Data

__Edge List (Edge Matrix)__
- Images are stored as a list of points where each two points define a line
- [ P0, P1, P1, P2, P2, P0 ] in which each P represents a set of (x,y,z) coordinates (will need z coordinate later for rotations)

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

## 02/26/18 - 2/27/18 | Aim: --
__Dilation__: changing the size of the shape, scaling

(x,y,z) Da-> (ax,ay,az) (where a is the scaling factor)

Multiply the matrix [x,y,z,1] by the identity matrix except instead of 1's you put the scaling factor in (except the last 1 at the bottom right stays the same)

Dilations do not have to be proportional!

Dilation are done respective to the origin

In order to deal with this, we can translate the object to the origin, dilate it, and then translate it back to its original location

__Rotation__: flipping

(x,y) RΘ-> (?,?)

__POLAR COORDINATES__

x = rcosΦ

y = rsinΦ

x1 = rcos(Θ+Φ) = rcosΦcosΘ - rsinΦsinΘ = xcosΘ - xsinΘ

y1 = rsin(Θ+Φ) = rsinΦsinΘ + cosΦsinΘ = ycosΘ + xsinΘ

(x,y,z) RΘ-> (xcosΘ-ysinΘ,ycosΘ+xsinΘ,z)

![ROTATION MATRIX](https://i.stack.imgur.com/W3hip.jpg)

in order to robustify our graphics engine, we would like to make it possible to rotate about all three axes.

In our standard coordinate plane with the z axis, we rotate about the z axis.

Rotation of Θ degrees about x axis R(Θ,x) is:

y1 = ycosΘ - zsinΘ

z1 = zcosΘ + ysinΘ

Rotation of Θ degrees about the y axis R(Θ,Y) is:

z1 = zcosΘ - xsinΘ

y1 = xcosΘ + zsinΘ

### Combining Transformations

E0 (an edge matrix), T0 (a translate matrix), R0 (a rotate matrix), S0 (a scale matrix)

__TRANSLATING__

T0・E0 = E1

__ROTATING__

R0・E1 = E2

__DILATING__

S0・E2 = E3

__SHORTCUT!__

E3 = S0・R0・T0・E0

Not commutative, but is is associative...

E3 = (S0・R0・T0)・E0

Order is important: we first TRANSLATED then ROTATED then SCALED (apply them in the reverse order for desired effect)

We don't need to multiply by edge matrix until we need to __apply__ the transformation


## 03/05/18 | Aim: --
### Parametric Equations

- Define curves as systems of equations with a single independent variable (t)
  - x = f(t)
  - y = g(t)
- For consistency, we will use the range [0,1] for t.

### General Parametric Framework

For t in range 0 - 1, t++ = some step incrementer:

x = f(t)

y = g(t)

add(x,y) //to struct matrix* edges

### Circle

We need this info: radius and center (Xc,Yc)

x = f(t) = rcosø + Xc --> x = f(t) = rcos2πt + Xc

y = g(t) = rsinø + Yc --> y = g(t) = rsin2πt + Yc

### Spline

- curves that can be connected smoothly
- only going to use cubic splines

## 03/06/18 | Aim: --
Recall from yesterday to make a circle:

We need this info: radius and center (Xc,Yc)

x = f(t) = rcosø + Xc --> x = f(t) = rcos2πt + Xc

y = g(t) = rsinø + Yc --> y = g(t) = rsin2πt + Yc

But this doesn't help us for other shapes, only circles.

Let's say we want to generalize the formula for cubics

for t between 0 and 1, t++ step:

  x = Axt^3 + Bxt^2 + Cxt + Dx
  y = Ayt^3 + Byt^2 + Cyt + Dy

### Hermite Curves
- Given information:
  - P0, P1 (endpoints)
  - R0, R1: rates of change at endpoints (derivatives kinda) IMPORTANT: IT IS X WITH RESPECT TO T AND Y WITH RESPECT TO Y
- f(t) = At^3 + Bt^2 + Ct + D: gives us points on the curve
- f'(t) = 3At^2 + 2Bt + C
- When t = 0, f(t) = d: P0 & f'(t) = c: R0
- When t = 1, f(t) = a + b + c + d: P1 & f'(t) = 3a + 2b + c: R1

__Hermite Curve Matrix__ (really just inverse)
```
[0  0  0  1]     [a]      [P0]
[1  1  1  1]     [b]      [P1]
[0  0  1  0]  ・ [c]   =  [R0]
[3  2  1  0]     [d]      [R1]
```
```
[2  -2  1  1]     [P0]      [a]
[-3  3 -2 -1]     [P1]      [b]
[0   0  1  0]  ・ [P2]   =  [c]
[1   0  0  0]     [P3]      [d]
```

In matrix form:

![HERMITE](https://image.slidesharecdn.com/21bezier-120408025345-phpapp02/95/cs-354-bezier-curves-28-728.jpg?cb=1334065768)

## 03/07/18 | Aim: --
### Bezier Curves

Goal is still

for t between 0 and 1, t++ step:

  x = Axt^3 + Bxt^2 + Cxt + Dx
  y = Ayt^3 + Byt^2 + Cyt + Dy

But we use different information

- Given n+1 points, where n = degree of the curve (aka highest power)
- For a line, we would need two points, namely the beginning point P0 and the endpoint P1
  - There would be a point Pt on the line and Pt moves along the line P0P1
  - Pt = (1-t)P0 + tP1
  - this line is being create and they are inversely related. As t gets bigger, P1 starts to get more power than P0
- Quadratic
  - I have two Bezeir lines that are static, and we move along the lines connecting points on the lines
  - (1-t)^2P0 + t(1-t)P1 + t(1-t)P1 + t^2P2 = (1-t)^2P0 + 2t(1-t)P1 + t^2P2 (not in the form we want...)
- Cubic
  - Same process again, except now you're going to have an extra layer of depth
  - (1-t)^3P0 + 3t(1-t)^2P1 + 3t^2(1-t)P2 + t^3P3

## 03/08/18 | Aim: --
Continuation of Bezier Curves

In order to simplify (1-t)^3P0 + 3t(1-t)^2P1 + 3t^2(1-t)P2 + t^3P3 to the Ax^3 + Bx^2 + Cx + Dx form, we must perform binomial expansion.

It ends up being (-P0 + 3P1 - 3P2 +3P3)t^3 + (3P0 - 6P1 + 3P2)t^2 + (-3P0 + 3P1)t + P0

__Bezier Curve Matrix__
```
[-1  3 -3  1]     [P0]      [a]
[3  -6  3  0]     [P1]      [b]
[-3  3  0  0]  ・ [P2]   =  [c]
[1   0  0  0]     [P3]      [d]
```
## 03/13/18 | Aim: --
__3D Shapes__
- Z coordinate is a modifier of the x and y
- a primitive way to do this is to mess with the z values to have one mapping to a blue image and one mapping to a red image (like in the 3D glasses)
- We will work with box, sphere, torus (donut)

__Box__

Defining points
- 8 vertices

Given information: size information
- width (x)
- height (y)
- depth (z)
- P0 (top left front)

12 calls to add_edge() function

__Sphere__

Defining Points
- Points on the surface

Givens
- Center
- Radius

Generate points by rotating a circle
- Rotating about x-axis/ y-axis

![SPHERE](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7e/Sphere_wireframe_10deg_6r.svg/1200px-Sphere_wireframe_10deg_6r.svg.png)

- Z-axis just gives a circle, so you can't generate a sphere this way
- Thus, you can use x or y axis rotation

__X Rotation__

```
     x-rotation           circle            sphere
[1      0         0]     [rcos(θ)]     	    rcosθ
[0   cos(Φ) -sin(Φ)] ・  [rsin(θ)]   =    rsinθcosΦ
[0   sin(Φ)  cos(Φ)]     [   0   ]        rsinθsinΦ

θ: angle of creation
Φ: angle of circle rotation
ranges:
θ: 0 to 2π
Φ: 0 to pπ

However if we do:
θ: 0 to π
Φ: 0 to 2π
We get a semicircle that we rotate (as opposed to cirle)

But both will work!
```

## 03/14/18 | Aim: --

Pseudocode for semicricle/circle
```
for θ in range 0 to π:
	x = rcosθ + cx
	y = rsinθcosΦ + cy
	z = rsinθsinΦ + cz
```

This entire thing makes a circle/semi
```
for Φ in range 0 to 2π:
	for θ: 0 to π:
		x = rcosθ + cx
		y = rsinθcosΦ + cy
		z = rsinθsinΦ + cz
```
__Torus__

Defining points
- Surface points

Given information
- Center (cx, cy, cz)
- R (radius from center of to torus to center of the face of the cross section of the torus)
- r (radius of the cross section face)

To generate points you translate a circle and rotate it

If we move along X, then we rotate about Y

If we move along Y, we rotate about X

![TORUS](https://www.sharcnet.ca/Software/Gambit/html/modeling_guide/mgimage/fig_g_volm_create_torus.gif)

Equation

First, generate circle and move it by big R

rcosθ + R

rsinθ

θ

```
y-rot               	circle + move        torus
[cosΦ 	0   sinphi]    [rcosθ + R]     cosΦ(rcosθ+R) + cx = x
[0      1 	 Φ]   ・      [rsinθ]       rsinθ        + cy = y
[-sinΦ  0     cosΦ]       [0]         -sinΦ(rcosθ+r) + cz = z

θ in range 0 to 2π
Φ in range 0 to 2π
```

## 03/20/18 - 03/23/18 | Aim: --

__Vector Math "Review"__

Use < > (angle brackets)

(x,y,z): just a point

<x,y,z>: magnitude + direction

- magnitude: size of the vector
- (insert vector A image)
- denoted as ||A||
- to get the magnitude, do sqrt(x^2 + y^2 + z^2) aka pythagorean theorem on the x and y components
- unit vector has a magnitude of 1, really just conveying the direction of the vector
- normalized vector: turning a non-unit vector into a unit vector
- if you have vector A and want to normalize it to A hat = 1/||A|| ・<Ax,Ay,Az>

__Vector Multiplication__

__Dot Product__

(insert two vector diagram)

A ・ B = ||A|| ・ ||B||

If A and B are both pointing in the same direction, this is indeed the case

There is angle θ between A and B and as theta gets bigger, the dot product gets smaller

A ・ B = ||A|| ・ ||B|| ・ cosθ (same as B ・ A)

ALSO same as AxBx + AyBy + AzBz which is the way we'll be writing it

__Cross Product__

(insert two vector diagram with a cross product)

You get back a vector (something with both direction and magnitude)

Cannot exist unless you are in at least three dimensions

- perpendicular to the two other vectors
- the magnitude is equal to the area of the parallelogram formed by the two vectors
- you can get the cross product by doing ||A||||B||sinθ
- opposite relationship with θ (as θ gets bigger, area gets bigger)
- this results in scalar
- to get vector: ||A||||B||sinθ and multiply by a unit vector
- use Right Hand Rule to see where vector ends up

Vector A x Vector B = <AyBz - AzBy, AzBx - AxBz, AxBy - AyBx>

- Finding a vector between two points
- If you have a vector PQ, in order to find the point, you do <Q-P> (aka subtract components)
- If you have the vector QP instead, direction is important so you do <P-Q>

__Two options with creating Polygons__

__Wireframe Mesh__
- Shape definiton is created by connecting __edges__ between points on the surface
- These edges are lines that lack certain properties we might find useful, reason why we turn to polygon meshes

__Polygon Mesh__
- shape defintion is created by connecting points on the surface to create polygons (usually triangles or quadrilaterals)
- these help us with shading, lighting, filling in a polygon, perception of depth, etc...

But in order to do this we have to change the way we make things

Edge matrix -> Polygon Matrix

__Polgygon Matrix__

Go through a triangle at a time

Old schema:

add_box -> add_edge -> add_point -> draw_lines -> draw_line -> plot

New schema:

add_box -> add_triangle -> add_point -> draw_triangle -> draw_line -> plot

- add points counterclockwise

For a box, add 12 triangles (2 on each face)

For a sphere, we rotate about the x axis in a positive direction (towards us). The next point will come in front of the previous point (so forward, toward us)
- go up to an include zero/one on both ends
- this will cause overlapping points and some degerate triangles

For a torus, the next point will be behind the previous point
- no overlapping points in torus so no degenerate triangles

## 03/28/18| Aim: Backface Culling

__Backface Culling__
- Only draw the forward facing surfaces
- Now the question is: How can we tell which triangles are facing you and which aren't?

Let's say we have a surface vector and have a vector perpendicular to the surface vector (aka surface normal) and is perpendicular to the polygon

But, where we are looking at the surface also affects which side is facing us.

We introduce a third vector, V, which is a view vector and is the vector from the surface to the eye/camera

The angle between the surface normal vector and the view vector is what tells us whether it is facing us or not.

__Backface Culling Procedure__
- Calculate surface normal vector
- Find θ
- If -90 < θ < 90, we can see the face so draw the polygon

In order to calculate the surface normal vector, find cross product. You have two edges on the triangle that share a point and then you can get the surface normal vector.

In order to find θ, you do the dot product of surface normal vector and view vector which is the magnitude of each vector times each other times the cos of θ

cosθ > 0 if -90 < θ < 90
- if cosθ < 0, it's negative and we don't draw it (not facing us!)
- if cosθ > 0, it's positive and we want to draw it (facing us!)

The entire thing will be positive if it's facing us. The entire thing will be negative if it isn't facing us.

View vector = <0,0,1> (good view vector to start with, it is a fixed vector)

Normal vector <x,y,z>

DOT PRODUCT IS: 0 + 0 + Z

Thus, you don't even need to calculate the dot product. You just need z. If z is positive, it's a front face. If z is negative, it's a back face.

## 04/11/18 - 04/12/18 | Aim: Relative Coordinate System (Coordinate Stack System)

- Current transformations are applied to all the shapes in an image

```
| 1 0 0 0 |   |  2  0  0  50  |
| 0 1 0 0 | · |  0  2  0  100 |
| 0 0 1 0 |   |  0  0  2  0   |
| 0 0 0 1 |   |  0  0  0  1   |
     A               B
```

- In a relative coordinate system we can apply transformations to individual or groups of shapes
- Transformations will be applied to the "world" or current coordinate system (aka you change the coordinates or where you are and THEN you draw the object rather than the other way around)

__Drawing in a RCS__
- Generate the polygons or edges
- Apply the current coordinate system to those points
- Draw the polygons or edges to the image

Original process:
```
sphere
rotate
move
apply
display
```

New process:
```
rotate
move
sphere
```

__Coordinate Stack System__
- Will maintain a stack of coordinate systems
- Top: the most current system
- Bottom: identity matrix (global system)
- All transformations modify the top and none of the other matrices
- Push: pushes a __copy__ of the top

There is distinction between transformation ・ top and top ・ transformation

Latter is correct way to go

## 04/17/18 - 04/18/18 | Aim: Filling in Shapes

__Scanline Conversion__

The process of filling a polygon by drawing consecutive horizontal (or vertical) lines.
- Need to find the top, middle, and bottom
- Need to find the endpoints of each scanline
- Y starts at: Yb
- Y ends at: Yt
- Y+=1 every time
- X0 is on the line TB (top bottom)
- X0 starts at: Xb
- X1 starts at: Xt
- X0+=  d0 (negative slope reciprocal)

d0 = (Xt - Xb)/(Yt - Yb) (reciprocal)

X1 is on the line MT until y = Ym and then it is on MB

We will use the y value as our trigger because there will be no rounding errors with this

X1 += delta1

delta1 = (Xm - Xb)/(Ym - Yb)

or

delta1 = (Xt - Xm)/(Yt - Ym)

Check for dividing by zero in the cases

Don't forget X = Xm

## 04/19/ 18 | Aim: Z Buffer

Screen maps to Z-Buffer: color maps to Z value

__Z Buffer__
- 2D Array of floating point values that directly correspond to the screen
- Only stores current Z value of what's at that current pixel
- Before modifying the screen, we will check the Z-Buffer
- We want our reseted Z-Buffer values to be negative infinity so that everything is in front of it
- Z values should be initialized to the lowest possible value
- In every argument that we have to pass the screen, we now also need to pass the z-buffer as well
- Also, now we also have to calculate the Z value in every place basically

__Functions with Significant Changes__
- plot must check/ modify the z-buffer
- draw_line must calculate z values (currently just does x and y)
- scanline convert must calculate z values
