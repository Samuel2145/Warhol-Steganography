//
// Created by Sam on 12/5/2020.
//

#include "../Source/Composite.h"

vector<Image> imgs;
vector<int> order;
vector<Image> imgOrder;

bool check(int toCheck){
    for(int i = 0; i < order.size(); i++){
        if(toCheck == order[i])
            return true;
    }
    return false;
}

int main(int argc, char* argv[]){

    srand(time(nullptr));

    Image src("Images/a");
    Image src2("Images/a");
    Image src3("Images/a");

    src.redWarhol();
    imgs.push_back(src);

    src2.greenWarhol();
    imgs.push_back(src2);

    ///Dont use
    src3.blueWarhol();

    Image mix = src3;
    mix.Screen(src);
    imgs.push_back(mix);

    Image mix2 = src;
    mix2.Screen(src2);
    imgs.push_back(mix2);

    ///Randomizes order of images
    while(order.size() != 4){
        int rNum = rand() % 4 + 1;

        if(!check(rNum))
            order.push_back(rNum);

    }

    for(int i = 0; i < order.size(); i++){
        imgOrder.push_back(imgs[order[i]-1]);
    }

    imgs.clear();
    order.clear();

    ///Initialize composite image with the given image order
    Composite endWar(2,2,imgOrder);
    endWar.displayInfo();

    ///Take user input

    cout << "Please type in your message to encode:" << endl;
    string toEncode;
    getline(cin, toEncode);

    ///Encode message into pictures
    endWar.encodeMessage(toEncode);

    ///Create composite and initialize it with images
    endWar.createComposite();

    ///Write out files
    endWar.writeFile("Outputs/Warhol.tga");
    endWar.writeKey("Keys/key.txt");

    return 0;
}