//
// Created by samue on 12/5/2020.
//

#ifndef WARHOL_IMAGE_H
#define WARHOL_IMAGE_H

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Pixel.h"

using namespace std;
class Image {
    string fileName;
    int imageSize;
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
public:
    vector<Pixel> pixels;
    Image();
    Image(string);
    Image(int, int, vector<Pixel>);
    void loadFile();
    void writeFile(const string&);
    void redWarhol();
    void greenWarhol();
    void blueWarhol();
    void Screen(Image &g);
    short getWidth();
    short getHeight();
    int getImageSize();
    bool encryptChar(int pos);
    void stand();
};


#endif //WARHOL_IMAGE_H
