/* 
 * File:   main.cpp
 * Author: Benjamin
 *
 * Created on May 3, 2014, 11:21 PM
 */

#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include "MovieBase.h"
#include "UserBase.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    MovieBase* mb = new MovieBase();
    ifstream iFile("u.item");
    if(iFile.is_open()){
        string line = "";
        while(getline(iFile,line)){
            mb->parseString(line);
        }
    }
    iFile.close();
    mb->testPrint();
}

