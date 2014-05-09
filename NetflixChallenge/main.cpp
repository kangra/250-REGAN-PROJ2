/* 
 * File:   mainBAPKA.cpp
 * Author: Benjamin and Kunal
 *
 * Created on May 3, 2014, 11:21 PM
 */

#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "MovieBase.h"
#include "UserBase.h"
using namespace std;

int parseInt (const string &str) {
  stringstream ss(str);
  int num;
  if((ss >> num).fail())
  { 
      //ERROR 
  }
  return num;
}

void reviewParse(string s, UserBase* ub, MovieBase* mb){
    int state = 0;
    /* 
     * States:
     * 0 - Reading UserID
     * 1 - Reading MovieID
     * 2 - Reading Score
     */
    bool breakout = false;
    string userID = "";
    string movieID = "";
    string score = "";
    for(int i=0;i<s.length()&!breakout;i++){
        switch(state){
            case 0:
                if(s.at(i)=='\t'){
                    state = 1;
                }else{
                    userID+=s.at(i);
                }break;
            case 1:
                if(s.at(i)=='\t'){
                    state = 2;
                }else{
                    movieID+=s.at(i);
                }break;
            case 2:
                score = s.at(i);
                if(movieID!="267"){
                    ub->addReview(mb,parseInt(movieID),parseInt(score),parseInt(userID));
                }
                breakout = true;
                break;
            default: break;
        }
    }
}
int main(int argc, char** argv) {
    MovieBase* mb = new MovieBase();
    UserBase* ub = new UserBase();
    
    /* Read in Movies */
    ifstream iFile("u.item");
    if(iFile.is_open()){
        string line = "";
        while(getline(iFile,line)){
            mb->parseString(line);
        }
    }
    
    /* Read in Users */
    ifstream uFile("u.user");
    if(uFile.is_open()){
        string line = "";
        int userNumber = 1;
        while(getline(uFile,line)){
            ub->addUser(userNumber);
            userNumber++;
        }
    }
    uFile.close();
    
    /* Read in Reviews */
    ifstream rFile("u.data");
    if(rFile.is_open()){
        string line = "";
        while(getline(rFile,line)){
            reviewParse(line,ub,mb);
        }
    }
    rFile.close();
    mb->calculateAverages();
    
    ub->calculatePreferenceFactors(mb);
    
    ub->getAllTop(10,mb);
}

