/*
 * File:    MovieBaseBAP.cpp
 * Author: Benjamin     
 * 
 * 05.04.2014 - 6:36PM EDT
 * 
 */
#include "MovieBase.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;
/* Helper Functions n stuff */

int sum(vector<int> values){
    int sum = 0;
    for(int i=0;i<values.size();i++){
        sum+=values.at(i);
    }
    return sum;
}

int str2int (const string &str) {
  stringstream ss(str);
  int num;
  if((ss >> num).fail())
  { 
      //ERROR 
  }
  return num;
}

/* Define Movie Methods Below */
MovieBase::Movie::Movie(unsigned int movieID, unsigned int yr, string nm) : ID(movieID), name(nm), year(yr){
    genres = map<string,bool>();
    reviewCount = 0;
}
bool MovieBase::Movie::isGenre(string genre){
    return genres[genre];
}
void MovieBase::Movie::addReview(unsigned int score){
    scores.push_back(score);
    reviewCount++;
}
unsigned int MovieBase::Movie::getReviewCount(){
    return reviewCount;
}
vector<int> MovieBase::Movie::getScores(){
    return scores;
}
void MovieBase::Movie::setAverage(float avg){
    average = avg;
}
unsigned int MovieBase::Movie::getID() const{
    return ID;
}
const float MovieBase::Movie::getAverage(){
    return average;
}
vector<string> MovieBase::Movie::getGenres(){
    vector<string> trueGenres;
    map<string,bool>::iterator genreit = genres.begin();
    while(genreit!=genres.end()){
        if(genreit->second) trueGenres.push_back(genreit->first);
        genreit++;
    }
    return trueGenres;
}
const string MovieBase::Movie::getName() const{
    return name;
}
const unsigned int MovieBase::Movie::getYear() const{
    return year;
}
MovieBase::Movie& MovieBase::Movie::operator= (const MovieBase::Movie & mo){
    return *this;
}
/* Define MovieBase methods below */
MovieBase::MovieBase(){}
void MovieBase::parseString(string s){
    string genreNames[] = {"unknown","Action","Adventure","Animation","Children's","Comedy","Crime","Documentary","Drama","Fantasy","Film-Noir","Horror","Musical","Mystery","Romance","Sci-Fi","Thriller","War","Western"};
    /*  Strings will come in one line at a time. The format is as follows:
     *  ID|Name (Year)|Date Released||imdb url|a|b|c|d|e|f|g|h|i|j|k|l|m||o|p|q|r|s
     *  Where a-s (inclusive) represents a binary 0/1 of what genre(s) this movie 
     *  belongs to.
     *  Note the double || after date released.
     */
    string movieID = "";
    string year = "";
    string name = "";
    int state = 0;
    int genreIndex = 0;
    /*
     * States
     * 0 - Reading ID
     * 1 - Reading Name
     * 2 - Reading Year
     * 3 - Reading DateStamp (skip)
     * 4 - Reading URL
     * 5 - Reading Genres
     */
    
    for(int i=0;i<s.length();i++){
        switch(state){
            case 0: 
                if(s.at(i)!='|'){
                    movieID+=s.at(i); 
                    break;
                }else{
                    state=1;
                    break;
                }
            
            case 1: 
                if(s.at(i)=='|'){
                    state = 3;
                    break;
                }else if(s.at(i)=='('){
                    if(isdigit(s.at(i+1))){
                        state = 2;
                        break;
                    }
                    else{
                        name+=s.at(i);
                        break;
                    }
                }else{
                    name+=s.at(i); 
                    break;
                }
            
            case 2:
                if(s.at(i)=='|'){
                    state = 3;
                    break;
                }else if(s.at(i)==')'){
                    i++; //Skip next |
                    state = 3;
                    if(movieID!="267"){
                        // To maintain the code in its original form, I've removed 267 - the error in our code base.
                        this->allMovies.push_back(Movie(str2int(movieID),str2int(year),name));
                    }
                    break;
                }else{
                    year+=s.at(i);
                    break;
                }
            case 3:
                if(s.at(i)=='|'){
                    i++; //Skip double |
                    state = 4;
                    break;
                }else{
                    break;
                }
            case 4:
                if(s.at(i)=='|'){
                    state = 5;
                    break;
                }else{
                    break;
                }
            case 5:
                if(s.at(i)=='|'){
                    break;
                }else if(s.at(i)!='0'&&s.at(i)!='1'){
                    state = 4;
                    break;
                }else{
                    switch(s.at(i)){
                        case '0': this->allMovies.back().genres[genreNames[genreIndex]] = false; genreIndex++; break;
                        case '1': this->allMovies.back().genres[genreNames[genreIndex]] = true; genreIndex++; break;
                        default: break;
                    }
                    break;
                }
            default: break;
        }
    }
}

MovieBase::Movie* MovieBase::operator [](unsigned int movieID){
    for(int i=0;i<allMovies.size();i++){
        if(allMovies.at(i).getID()==movieID){
            return &allMovies.at(i);
        }
        else throw "Item not found.";
    }
}

MovieBase::Movie* MovieBase::get(unsigned int movieID){
    for(int i=0;i<allMovies.size();i++){
        if(allMovies.at(i).getID()==movieID){
            return &allMovies.at(i);
        }
    }
}

void MovieBase::calculateAverages(){
    for(int i=0;i<allMovies.size();i++){
        allMovies.at(i).setAverage((float)((float)sum(allMovies.at(i).getScores())/(float)allMovies.at(i).getScores().size()));
    }
}

void MovieBase::testPrint(){
    cout << "All movies in database: " << endl << endl;
    for(int i=0;i<allMovies.size();i++){
        string genres = "";
        vector<string> these = allMovies[i].getGenres();
        for(int j=0;j<these.size();j++){
            genres+=these[j];
            if(j+1!=these.size()){
                genres+=", ";
            }
        }
        cout << allMovies[i].name << endl;
        cout << allMovies[i].year << endl;
        cout << genres << endl;
        cout << allMovies[i].getAverage() << endl;
        cout << endl;
    }
}
