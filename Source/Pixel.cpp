//
// Created by samue on 12/5/2020.
//

#include "Pixel.h"

Pixel::Pixel() {
    this->R = 0;
    this->G = 0;
    this->B = 0;
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    this->R = r;
    this->G = g;
    this->B = b;
}

unsigned char* Pixel::getR() {
    return &R;
}

unsigned char* Pixel::getG() {
    return &G;
}

unsigned char* Pixel::getB() {
    return &B;
}

///Looks alright
void Pixel::makeZeroR() {

    this->G = 0;
    this->B = 0;

    if(this->R > 130){
        this->R = 255;
        this->G = 100;
        this->B = 100;
    }else{
        this->R = 255;
        this->G = 255;
    }

}

///Looks good
void Pixel::makeZeroG() {

    this->R = 0;
    this->B = 0;

    if(this->G > 100){
        this->G = 255;
        this->R = 100;
        this->B = 100;
    }else{
        this->G = 150;
        this->R = 255;
    }

}

///fuck it why not
void Pixel::makeZeroB() {

    this->R = 0;
    this->G = 0;

    if(this->B > 80){
        this->B = 255;
    }else{
        this->B = 150;
        this->R = 200;
    }
}

void Pixel::Screen(Pixel &g) {
    float sum = (float)g.R+(float)g.G+(float)g.B;
    float temR = R;
    float temG = G;
    float temB = B;
    if(sum > 0){
        temR += (255-temR) * (sum/765.0f);
        temG += (255-temG) * (sum/765.0f);
        temB += (255-temB) * (sum/765.0f);
        temR += 0.5f;
        temG += 0.5f;
        temB += 0.5f;
    }
    R = (unsigned char)temR;
    G = (unsigned char)temG;
    B = (unsigned char)temB;
}

void Pixel::leastBit() {
    this->R -= 1;
}

void Pixel::floor() {

    while(this->R % 5 != 0){
        this->R--;
    }

}

void Pixel::reverseLSB() {
    this->R += 1;
}
