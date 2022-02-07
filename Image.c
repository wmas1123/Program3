/**
* Specification for an image ADT.
*
* Completion time: 1.5 hours
*
* @author William Mastronardi, Ruben Acuna
* @version 1.0
*/

#ifndef PixelProcessor_H
#define PixelProcessor_H

////////////////////////////////////////////////////////////////////////////////
// Include Files
typedef struct Image Image;
typedef struct Pixel Pixel;

struct Image {
    struct Pixel** pArr;
    int width;
    int height;
};

struct Pixel{
    char red;
    char blue;
    char green;
};



#include <stdio.h>
#include <stdlib.h>
#include "Image.h"

////////////////////////////////////////////////////////////////////////////////
//Function Declarations
int clamp_color(int val);


/* Creates a new image and returns it.
*
 * @param  pArr: Pixel array of this image.
 * @param  width: Width of this image.
 * @param  height: Height of this image.
 * @return A pointer to a new image.
*/
Image* image_create(struct Pixel** pArr, int width, int height) {
    Image * img = (Image*) malloc(sizeof(Image*));
    img->width = width;
    img->height = height;
    img->pArr = pArr;
    return img;
}



/* Destroys an image. Does not deallocate internal pixel array.
*
 * @param  img: the image to destroy.
*/
void image_destroy(Image** img) {
    free(img);
}

/* Returns a double pointer to the pixel array.
*
 * @param  img: the image.
*/
struct Pixel** image_get_pixels(Image* img) {
    return img->pArr;
}

/* Returns the width of the image.
*
 * @param  img: the image.
*/
int image_get_width(Image* img) {
    return img->width;
}

/* Returns the height of the image.
*
 * @param  img: the image.
*/
int image_get_height(Image* img) {
    return img->height;
}

/* Converts the image to grayscale.
*
 * @param  img: the image.
*/
void image_apply_bw(Image* img){
    Pixel bw;
    for(int i = 0; i < img->height; i++) {
        for(int j = 0; j < img->width; j++) {
            bw = img->pArr[i][j];
            bw.red = bw.red * 0.299 + bw.green * 0.587 +bw.blue * 0.114;
            bw.green = bw.red * 0.299 + bw.green * 0.587 +bw.blue * 0.114;
            bw.blue = bw.red * 0.299 + bw.green * 0.587 +bw.blue * 0.114;
            img->pArr[i][j] = bw;
        }
    }
}

/**
 * Shift color of the internal Pixel array. The dimension of the array is width * height.
 * The shift value of RGB is rShift, gShift，bShift. Useful for color shift.
 *
 * @param  img: the image.
 * @param  rShift: the shift value of color r shift
 * @param  gShift: the shift value of color g shift
 * @param  bShift: the shift value of color b shift
 */
void image_apply_colorshift(Image* img, int rShift, int gShift, int bShift) {
    Pixel shifted;
    for(int i = 0; i < img->height; i++) {
        for(int j = 0; j < img->width; j++) {
            shifted = img->pArr[i][j];
            shifted.red = clamp_color(shifted.red + rShift);
            shifted.green = clamp_color(shifted.green + gShift);
            shifted.blue = clamp_color(shifted.blue + bShift);
            img->pArr[i][j] = shifted;
        }
    }
}

/* Converts the image to grayscale. If the scaling factor is less than 1 the new image will be
 * smaller, if it is larger than 1, the new image will be larger.
 *
 * @param  img: the image.
 * @param  factor: the scaling factor
*/
void image_apply_resize(Image* img, float factor) {
    if(factor < 0 || factor > 100) {
        printf("Error: Invalid scaling factor");
        return;
    }

    Image * resize = (Image *) malloc(sizeof(img) * 2);
    resize->height = img->height * factor;
    resize->width = img->width * factor;
    if(resize > 1) {
        for (int i = 0; i < img->height; i++) {
            for (int j = 0; j < img->width; j++) {


            }
        }
        img = resize;
        return;
    }
    else {

    }
}

/**
 * Clamp color values to ensure they remain within 0 and 255
 * @param color_value
 * @return clamped color value
 */
 int clamp_color(int color_value) {
     if(color_value > 255)
         return 255;
     if(color_value < 0)
         return 0;
     return color_value;
 }

#endif