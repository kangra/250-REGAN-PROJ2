/*
 * File: UserBase.cpp
 * Author: Benjamin
 * 
 * 05.04.2014 - 7:46 PM/EDT
 * 
 */

#include "UserBase.h"
#include "MovieBase.h"
#include <vector>

/* Defining User Methods Below */
UserBase::User::User(unsigned int id){
    userID = id;
}
void UserBase::User::push_review(unsigned int mid, unsigned int score){
    movieReviews[mid] = score;
}
unsigned int UserBase::User::getID(){
    return userID;
}

/* Defining UserBase Methods Below */
UserBase::UserBase(){}
UserBase::User* UserBase::operator[](unsigned int userID){
    for(int i=0;i<allUsers.size();i++){
        if(allUsers.at(i).getID()==userID){
            return &allUsers.at(i);
        }
    }
}
UserBase::User* UserBase::get(unsigned int userID){
    for(int i=0;i<allUsers.size();i++){
        if(allUsers.at(i).getID()==userID){
            return &allUsers.at(i);
        }
    }
}
void UserBase::addReview(MovieBase mb, unsigned int movieID, unsigned int score, unsigned int id){
    this->get(id)->push_review(movieID,score);
    mb[movieID]->addReview(score);
}
void UserBase::addUser(unsigned int ID){
    allUsers.push_back(User(ID));
}

void UserBase::calculatePreferenceFactors(MovieBase mb){
    string genreNames[] = {"unknown","Action","Adventure","Animation","Children's","Comedy","Crime","Documentary","Drama","Fantasy","Film-Noir","Horror","Musical","Mystery","Romance","Sci-Fi","Thriller","War","Western"};
    map<string,int> userGenreScores;
    map<string,int> userGenreReviewCount;
    map<string,float> allGenreScores;
    map<string,int> allGenreReviewCount;
    for(int i=0;i<allUsers.size();i++){
        for(int j=0;j<sizeof(genreNames)/sizeof(genreNames[0]);j++){
            // Instantiate all preference factors to 1, maps to zero
            allUsers.at(i).preferenceFactors[genreNames[j]] = 1;
            userGenreScores[genreNames[j]] = 0;
            userGenreReviewCount[genreNames[j]] = 0;
            allGenreScores[genreNames[j]] = 0;
            allGenreReviewCount[genreNames[j]] = 0;
        }
        
        map<int,int>::iterator reviewBegin = allUsers.at(i).movieReviews.begin();
        while(reviewBegin!=allUsers.at(i).movieReviews.end()){
            vector<string> thisGenres = mb.get(reviewBegin->first)->getGenres();
            for(int k=0;k<thisGenres.size();k++){
                userGenreScores[thisGenres[k]]+=reviewBegin->second;
                userGenreReviewCount[thisGenres[k]]++;
                allGenreScores[thisGenres[k]]+=mb.get(reviewBegin->first)->getAverage();
                allGenreReviewCount[thisGenres[k]]++;
            }
            reviewBegin++;
        }
        
        map<string,float>::iterator finalIterator = allGenreScores.begin();
        while(finalIterator!=allGenreScores.end()){
            if(userGenreReviewCount[finalIterator->first]!=0&&allGenreReviewCount[finalIterator->first]!=0){
                float preferenceFactor = (((userGenreScores[finalIterator->first])/(userGenreReviewCount[finalIterator->first]))/((finalIterator->second)/(allGenreReviewCount[finalIterator->first])));
                allUsers.at(i).preferenceFactors[finalIterator->first] = preferenceFactor;
                finalIterator++;
            }
        }
    }
}