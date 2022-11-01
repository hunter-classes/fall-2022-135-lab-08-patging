/*
Patrick Ging
Professor Zamanksy
Lab 8

image_functions.cpp 

contains functions that operate tasks on pgm files
*/
#include <iostream>
#include <cmath>

#include "imageio.h"

void invert(std::string filename) {
    /*
    Inverts the pixels of the image and writes to it
    */
    int image_data[MAX_H][MAX_W];

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    for(int i=0;i<h;i++) {
        // interating through each row
        for (int j = 0; j<w; j++) {
            // iterating through each col
            image_data[i][j] = std::abs (image_data[i][j] - 255); 
            /*
                Transforming the pixels to 'inverse'
                eg 0 to 255, 255 to 0, 2 to 253, 253 to 2....
            */
        }
    }

    writeImage("taskA.pgm", image_data, h,w); // wriitng to the image
}

void invert_half(std::string filename) {
    /*
    Inverts the right half of the image (horizontally) and writes to it
    */
    int image_data[MAX_H][MAX_W];

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    //std::cout << h << "x" << w << std::endl;

    for(int i=0;i<h;i++) {
        // interating through each row
        for (int j = 0; j<w; j++) {
            // iterating through each col

            if(j >= (int) (w/ 2)) {
                image_data[i][j] = std::abs (image_data[i][j] - 255); 
            }
            /*
                Transforming the pixels to 'inverse'
                eg 0 to 255, 255 to 0, 2 to 253, 253 to 2....
            */
        }
    }

    writeImage("taskB.pgm", image_data, h,w); // wriitng to the image
}

void box(std::string filename) {
    /*
    Draws a white box that's half the img's height and length on the image. 
    the box is centered on the image
    */
    int image_data[MAX_H][MAX_W];

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    bool isCenter = false;

    for(int i=0;i<h;i++) {
        // interating through each row
        for (int j = 0; j<w; j++) {
            // iterating through each col

            isCenter = (0.25 * w < j) && (j < 0.75 * w) && (0.25 * h < i) && (i < 0.75 * h);
            /*
            If we're in a centered box taking up 50% of the larger box, then the j (horizonal) and the i (vertical) variables 
            should be within the .25 and .75 times of the max width and height respectively
            */

            if(isCenter) {
                image_data[i][j] = 255; // writing white onto the pixel 
            }
            /*
                Transforming the pixels to 'inverse'
                eg 0 to 255, 255 to 0, 2 to 253, 253 to 2....
            */
        }
    }

    writeImage("taskC.pgm", image_data, h,w); // wriitng to the image
}

void frame(std::string filename) {
    /*
    Draws a frame that's half the img's height and length on the image. 
    the box is centered on the image
    */
    int image_data[MAX_H][MAX_W];

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    bool isFrame = false;

    for(int i=0;i<h;i++) {
        // interating through each row
        for (int j = 0; j<w; j++) {
            // iterating through each col

            isFrame = (((0.25 * w < j) && (j < 0.75 * w)) && i == (int)(.25 * h)) || // top part 
                    (((0.25 * w < j) && (j < 0.75 * w)) && i == (int)(.75 * h)) ||
                    (((0.25 * h < i) && (i < 0.75 * h)) && j == (int)(.25 * w)) ||
                    (((0.25 * h < i) && (i < 0.75 * h)) && j == (int)(.75 * w)) ;
            //|| (0.25 * h < i) || (i < 0.75 * h);
            
            /*
            If we're in a centered box taking up 50% of the larger box, then the j (horizonal) and the i (vertical) variables 
            should be within the .25 and .75 times of the max width and height respectively
            */

            if(isFrame) {
                image_data[i][j] = 255; // writing white onto the pixel 
            }
            /*
                Transforming the pixels to 'inverse'
                eg 0 to 255, 255 to 0, 2 to 253, 253 to 2....
            */
        }
    }

    writeImage("taskD.pgm", image_data, h,w); // wriitng to the image
}


void scale(std::string filename) {
    // scales the image by 200% and writes to the file

    int image_data[MAX_H][MAX_W];
    int new_image_data[MAX_H][MAX_W];
    // space may be an issue in the future

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    for(int i=0;i<h;i++) {
        // interating through each row
        for (int j = 0; j<w; j++) {
            // iterating through each col
            
            new_image_data[2*i][2*j] = image_data[i][j];
            new_image_data[2*i][2*j + 1] = image_data[i][j];
            // for each val we also add the extra item next to it
            // doubling the length of the pixel arr

            new_image_data[2*i+1][2*j] = image_data[i][j];
            new_image_data[2*i+1][2*j + 1] = image_data[i][j];
            // same as above, except we're doubling the length
        }
    }

    writeImage("taskE.pgm", new_image_data, h*2,w*2); // wriitng to the image    

    return;
}

void pixelate(std::string filename) {
    /*
        'pixelates' a pgm image via writing every 2x2 pixel cluster image
        to be the average pixel value of that said cluster; then writes to the file
    */

    int image_data[MAX_H][MAX_W];
    int new_image_data[MAX_H][MAX_W];
    // space may be an issue in the future

    int h, w; // height and width respectively

    readImage(filename, image_data,h,w); // marhsalling to img_data, h,w

    // file processing

    int average; // average of each 2x2 pixel cluster

    for(int i=0;i<h - (h%2);i+=2) { // h%2 is to ensure evenness
        // interating through each row
        for (int j = 0; j<w - (w%2); j+=2) {
            // iterating through each col

            //average of the four pixels
            average = (image_data[i][j] + image_data[i+1][j] + image_data[i][j+1] + image_data[i+1][j+1]) / 4;

            new_image_data[i][j] = average;
            new_image_data[i+1][j] = average;
            new_image_data[i][j+1] = average;
            new_image_data[i+1][j+1] = average;

            // updating the cluster ^^
        }
    }

    writeImage("taskF.pgm", new_image_data, h,w); // wriitng to the image    

    return;
}