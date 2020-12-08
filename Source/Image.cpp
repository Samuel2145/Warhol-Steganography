//
// Created by samue on 12/5/2020.
//

#include "Image.h"

Image::Image(int w, int h, vector<Pixel> p){
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 2;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    width = w;
    height = h;
    bitsPerPixel = 24;
    imageDescriptor = 32;
    imageSize = width *height;
    for(int i = 0; i < imageSize;i++){
        pixels.push_back(p[i]);
    }
}

Image::Image(string filePath){
    this->fileName = filePath + ".tga";
    loadFile();
}


void Image::loadFile() {
    short* shortData = new short[2];
    char* charData = new char[1];
    unsigned char r,g,b;
    ifstream image(fileName, ios_base::binary);

    image.read(charData,1);
    idLength = *charData;

    image.read(charData,1);
    colorMapType = *charData;

    image.read(charData,1);
    dataTypeCode = *charData;

    image.read((char *)shortData,2);
    colorMapOrigin = *shortData;

    image.read((char *)shortData,2);
    colorMapLength = *shortData;

    image.read(charData,1);
    colorMapDepth = *charData;

    image.read((char *)shortData,2);
    xOrigin = *shortData;

    image.read((char *)shortData,2);
    yOrigin = *shortData;

    image.read((char *)shortData,2);
    width = *shortData;

    image.read((char *)shortData,2);
    height = *shortData;

    image.read(charData,1);
    bitsPerPixel = *charData;

    image.read(charData,1);
    imageDescriptor = *charData;

    imageSize = width * height;

    for(int i = 0; i<imageSize;i++){
        image.read(charData,1);
        b = *charData;
        image.read(charData,1);
        g = *charData;
        image.read(charData,1);
        r = *charData;
        pixels.push_back(Pixel(r,g,b));
    }
    image.close();
    delete[] charData;
    delete[] shortData;
}

void Image::writeFile(const string &filePath) {
    ofstream outFile(filePath, ios_base::binary);
    outFile.write(&idLength,1);
    outFile.write(&colorMapType,1);
    outFile.write(&dataTypeCode,1);
    outFile.write((char *)&colorMapOrigin,2);
    outFile.write((char *)&colorMapLength,2);
    outFile.write(&colorMapDepth,1);
    outFile.write((char *)&xOrigin,2);
    outFile.write((char *)&yOrigin,2);
    outFile.write((char *)&width,2);
    outFile.write((char *)&height,2);
    outFile.write(&bitsPerPixel,1);
    outFile.write(&imageDescriptor,1);
    for(int i = 0; i<imageSize;i++){
        outFile.write((char *)pixels[i].getB(),1);
        outFile.write((char *)pixels[i].getG(),1);
        outFile.write((char *)pixels[i].getR(),1);
    }
    outFile.close();
}

void Image::redWarhol(){

    for(unsigned i = 0; i < pixels.size(); i++){
        pixels[i].makeZeroR();
    }
}

void Image::greenWarhol(){

    for(unsigned i = 0; i < pixels.size(); i++){
        pixels[i].makeZeroG();
    }
}

void Image::blueWarhol(){

    for(unsigned i = 0; i < pixels.size(); i++){
        pixels[i].makeZeroB();
    }
}

void Image::Screen(Image &g) {
    if(imageSize != g.imageSize){
        return;
    }else{
        for(unsigned i = 0; i<pixels.size();i++){
            pixels[i].Screen(g.pixels[i]);
        }

    }
}

short Image::getWidth() {
    return this->width;
}

short Image::getHeight() {
    return this->height;
}

int Image::getImageSize() {
    return this->imageSize;
}

bool Image::encryptChar(int pos) {

    if(pos > this->pixels.size()){
        cerr << "Cannot encrypt anymore in this image" << endl;
        return false;
    }

    pixels[pos].leastBit();
    cout << "Encrypted with bit " <<(int)(*pixels[pos].getR()) << endl;
    return true;
}

void Image::stand() {

    for(int i = 0; i < pixels.size(); i++)
        pixels[i].floor();

}
