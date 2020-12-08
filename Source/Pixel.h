//
// Created by samue on 12/5/2020.
//

#ifndef WARHOL_PIXEL_H
#define WARHOL_PIXEL_H


class Pixel {
    unsigned char R, G, B;
public:
    Pixel();
    Pixel(unsigned char, unsigned char, unsigned char);
    unsigned char* getR();
    unsigned char* getG();
    unsigned char* getB();
    void makeZeroR();
    void makeZeroG();
    void makeZeroB();
    void Screen(Pixel &g);
    void leastBit();
    void floor();
    void reverseLSB();
};


#endif //WARHOL_PIXEL_H
