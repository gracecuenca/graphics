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
