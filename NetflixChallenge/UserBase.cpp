/*
 * File: UserBase.cpp
 * Author: Benjamin
 * 
 * 05.04.2014 - 7:46 PM/EDT
 * 
 */

#include "UserBase.h"
#include "MovieBase.h"
    
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