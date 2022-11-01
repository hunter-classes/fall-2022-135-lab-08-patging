/*
Patrick Ging
Professor Zamanksy
Lab 8

main.cpp
*/
#include <iostream>

#include "image_functions.h"

int main() {

    //testing tasks a through f

    const std::string IMAGE_PATH = "./image1.pgm";

    invert(IMAGE_PATH); // task A 

    invert_half(IMAGE_PATH); // task b

    box(IMAGE_PATH); // task C

    frame(IMAGE_PATH); // task D

    pixelate(IMAGE_PATH); // task F

    scale(IMAGE_PATH); // task E


    return 0;
}
