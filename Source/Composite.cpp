//
// Created by samue on 12/5/2020.
//

#include "Composite.h"

Composite::Composite(int w, int h) {
    this->x = w;
    this->y = h;

    int temp = w*h;

    for(int i = 0; i < temp; i++){
        positions.push_back(0);
    }

}

Composite::Composite(int w, int h, vector<Image> x) {
    this->x = w;
    this->y = h;

    for(int i = 0; i < x.size(); i++){
        this->images.push_back(x[i]);
        positions.push_back(0);
    }

    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 2;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    width = (short)(images[0].getWidth() * this->x);
    height = (short)(images[0].getHeight() * this->y);
    bitsPerPixel = 24;
    imageDescriptor = 32;
    imageSize = width*height;
    for(int i = 0; i < imageSize;i++){
        pixels.push_back(Pixel(0,0,0));
    }

}

void Composite::createComposite() {

    int imgCounter = 0;

    for(int i = 0; i < this->y; i++){

        for(int j = 0; j < this->x; j++){
            int startPos = (i*(width/this->x)) * (i * (height/this->y) * this->x) + (j* (width/this->x));
            //cout << startPos << endl;
            writePixels(images[imgCounter], startPos);
            imgCounter++;
        }
    }

}

void Composite::writePixels(Image a, int start) {

    int count = start;
    int xLength = width/this->x;
    int offset = xLength * (this->x - 1);
    for(int i = 0; i < a.getImageSize(); i++){
        this->pixels[count] = a.pixels[i];
        count++;

        if(count % xLength == 0)
            count+= offset;

    }
}

void Composite::writeFile(const string &filePath) {

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
        outFile.write((char *)this->pixels[i].getB(),1);
        outFile.write((char *)this->pixels[i].getG(),1);
        outFile.write((char *)this->pixels[i].getR(),1);
    }
    outFile.close();
}

void Composite::displayInfo() {
    cout << "X: " << this->x << endl;
    cout << "Y: " << this->y << endl;
    cout << "Images vector size: " << images.size() << endl;
    cout<<"ID Length: "<< (int)idLength<<endl;
    cout<<"Color Map Type: "<< (int)colorMapType<<endl;
    cout<<"Data Type code: "<<(int)dataTypeCode<<endl;
    cout<<"Color Map Origin: "<< colorMapOrigin<<endl;
    cout<<"Color Map Length: "<<colorMapLength<<endl;
    cout<<"Color Map Depth: "<<(int)colorMapDepth<<endl;
    cout<<"X Origin: "<< xOrigin<<endl;
    cout<<"Y Origin: "<< yOrigin<<endl;
    cout<<"Width: "<< width<<endl;
    cout<<"Height: "<< height<<endl;
    cout<<"Bits per Pixel: "<< (int)bitsPerPixel<<endl;
    cout<<"Image Descriptor: "<< (int)imageDescriptor<<endl<<endl;
    cout << "Pixel vector size: " << pixels.size() << endl;
}

bool Composite::check(int toCheck, vector<int> x){

    for(int i = 0; i < x.size(); i++){
        if(toCheck == x[i])
            return true;
    }
    return false;
}

/*
 * Pads message so we can encode in rounds, each round is n-images long
 *
*/
void Composite::createKey(string &a) {

    while(a.length() % images.size() != 0)
        a.push_back('x');

    vector<int> temp;
    int blockSize = positions.size();

    while(key.size() != a.length()){

        while(temp.size() != blockSize){
            int rNum = rand() % blockSize + 1;

            if(!check(rNum, temp))
                temp.push_back(rNum);
        }

        for(int i = 0; i < temp.size(); i++)
            key.push_back(temp[i]);

        temp.clear();
    }
}

void Composite::encodeMessage(string &a) {

    createKey(a);

    for(int i = 0; i < images.size(); i++)
        images[i].stand();

    for(int i = 0; i < a.size(); i++){
        int img = key[i] - 1;
        int pos = (int)(unsigned char)a[i];

        positions[img] += pos;
        images[img].encryptChar(positions[img]);
    }

}

void Composite::writeKey(const string &path) {

    ofstream keyFile;
    keyFile.open(path);
    string k = "";

    for( int i = 0; i < key.size(); i++){
        k += to_string(key[i]);
    }

    keyFile << k ;
    keyFile.close();
}

void Composite::loadFile(const string &path) {

    short* shortData = new short[2];
    char* charData = new char[1];
    unsigned char r,g,b;
    ifstream image(path, ios_base::binary);

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

void Composite::extractImages() {

    int imgWidth = this->width/x;
    int imgHeight = this->height/y;

    for(int i = 0; i < this->y; i++){

        for(int j = 0; j < this->x; j++){
            int startPos = (i*(width/this->x)) * (i * (height/this->y) * this->x) + (j* (width/this->x));
            writeImagePixels(startPos, imgWidth, imgHeight);
        }
    }
}

void Composite::writeImagePixels(int start, int imgWidth, int imgHeight) {

    int imgSize = imgWidth * imgHeight;
    int offset = imgWidth * (this->x - 1);
    vector<Pixel> temp;

    for(int i = 0; i < imgSize; i++){
        temp.push_back(this->pixels[start]);
        start++;

        if(start % imgWidth == 0)
            start += offset;
    }

    images.push_back(Image(imgWidth, imgHeight, temp));
}

void Composite::decodeMessage(vector<int> k) {

    string message = "";

    for(int i = 0; i < k.size(); i++){
        int start = positions[k[i]-1];
        char toPush = ' ';

        for(int j = start; j < images[k[i]-1].pixels.size(); ++j){

            if(*images[k[i]-1].pixels[j].getR() % 5 != 0){
                toPush = (char)(j - start);
                positions[k[i] - 1] += (j-start);
                images[k[i] - 1].pixels[j].reverseLSB();
                break;
            }
        }
        message.push_back(toPush);
    }
    cout << message << endl;
}
