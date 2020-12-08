//
// Created by samue on 12/7/2020.
//

#include "../Source/Composite.h"

int main(int argc, char* argv[]){

    int x = stoi(argv[1]);
    int y = stoi(argv[2]);



    Composite toDecode(x,y);
    toDecode.loadFile("Outputs/Warhol.tga");
    toDecode.extractImages();

    string key;
    getline(cin, key);

    vector<int> k;

    for(int i = 0; i < key.length(); i++){
        k.push_back(key[i]-48);
    }

    toDecode.decodeMessage(k);
    return 0;
}