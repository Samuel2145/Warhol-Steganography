//
// Created by samue on 12/5/2020.
//

#ifndef WARHOL_COMPOSITE_H
#define WARHOL_COMPOSITE_H

#include "Image.h"
#include <cstdlib>
#include <ctime>

class Composite {
    int x;
    int y;
    vector<Image> images;
    vector<int> positions;
    vector<int> key;

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
    vector<Pixel> pixels;
public:
    Composite(int w, int h);
    Composite(int w, int h, vector<Image> x);
    void createComposite();
    void writePixels(Image a, int start);
    void writeFile(const string&);
    void displayInfo();
    bool check(int toCheck, vector<int>);
    void createKey(string&);
    void encodeMessage(string&);
    void writeKey(const string&);
    void loadFile(const string&);
    void extractImages();
    void writeImagePixels(int, int, int);
    void decodeMessage(vector<int>);
};


#endif //WARHOL_COMPOSITE_H
