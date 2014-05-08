/*
 * File: UserBase.cpp
 * Author: Benjamin
 * 
 * 05.04.2014 - 7:46 PM/EDT
 * 
 */

#include "UserBase.h"
#include "MovieBase.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

/* doubleEndedMovieMap
 * 
 * This class, and associated functions, were added after-the-fact when a
 * map with iterator and insertion functionality wasn't behaving. This is very
 * similar to our FlexArray class, only it was made specifically for this task
 * so it is not a template. 
 */
class doubleEndedMovieMap{
public:
    class movieNode{
        const MovieBase::Movie* thisMovie;
        const float weightedScore;
        movieNode* prevNode;
        movieNode* nextNode;
    public:
        movieNode(MovieBase::Movie* m, float s) : thisMovie(m),weightedScore(s){prevNode = NULL; nextNode = NULL;}
        movieNode* getPrev(){return prevNode;}
        movieNode* getNext(){return nextNode;}
        void setNext(movieNode* next){nextNode = next;}
        void setPrev(movieNode* prev){prevNode = prev;}
        const float getScore(){return weightedScore;}
        const MovieBase::Movie* getMovie(){return thisMovie;}
        inline bool operator> (movieNode* rhs){return weightedScore > rhs->weightedScore;}
        inline bool operator< (movieNode* rhs){return weightedScore < rhs->weightedScore;}
        inline bool operator==(movieNode* rhs){return weightedScore == rhs->weightedScore;}
        inline bool operator!=(movieNode* rhs){return weightedScore != rhs->weightedScore;}
        inline bool operator<=(movieNode* rhs){return weightedScore <= rhs->weightedScore;}
        inline bool operator>=(movieNode* rhs){return weightedScore >= rhs->weightedScore;}
    };
    movieNode* first;
    movieNode* last;
    const int movieLimit;
    int movieCount;
    doubleEndedMovieMap() : movieLimit(10){
        first = NULL;
        last = NULL;
        movieCount = 0;
    }
    doubleEndedMovieMap(int ml) : movieLimit(ml){
        first = NULL;
        last = NULL;
        movieCount = 0;
    }
    void setFirst(movieNode* f){
        first = f;
    }
    void setLast(movieNode* l){
        last = l;
    }
    /*insert
     * 
     * This is the bread and butter of this class. All movies, when being
     * iterated through, call this method. It first checks if the first node
     * is null (i.e., empty movieMap), and if so inserts the first node. Moving
     * down the line, if a movie is inserted and the movieMap is not at capacity
     * yet, it will find the appropriate place for it and insert it. After the
     * capacity has been reached, it will first check the weighted score of the
     * item at the first node. If the weighted score of the item to be inserted
     * is less than this, it simply breaks out of the function by returning false.
     * If it is higher, it will find the appropriate place to insert it, and
     * then "remove" the first node (now lowest average) by orphaning it.
     */
    bool insert(MovieBase::Movie* mov, float weightedScore){
        if(first==NULL){
            this->setFirst(new movieNode(mov, weightedScore));
            this->setLast(first);
        }
        else if(movieCount<movieLimit){
            if(first->getScore()>=weightedScore){
                movieNode* thisMov = new movieNode(mov, weightedScore);
                thisMov->setNext(first);
                first->setPrev(thisMov);
                this->setFirst(thisMov);
                movieCount++;
            }
            else{
                movieNode* checker = first;
                if(checker->getNext()!=NULL){
                    while(checker->getNext()->getScore()<weightedScore){
                        checker = checker->getNext();
                        if(checker->getNext()==NULL)break;
                    }
                }
                if(checker->getNext()==NULL){
                    checker->setNext(new movieNode(mov,weightedScore));
                    checker->getNext()->setPrev(checker);
                    movieCount++;
                }
                else{
                    movieNode* thisMov = new movieNode(mov,weightedScore);
                    thisMov->setPrev(checker);
                    thisMov->setNext(checker->getNext());
                    checker->setNext(thisMov);
                    thisMov->getNext()->setPrev(thisMov);
                    movieCount++;
                }
            }
        }
        else{
            if(weightedScore<=first->getScore()){
                return false;
            }
            else{
                movieNode* checker = first;
                while(checker->getNext()->getScore()<weightedScore){
                    checker = checker->getNext();
                    if(checker->getNext()==NULL)break;
                }
                if(checker->getNext()==NULL){
                    checker->setNext(new movieNode(mov,weightedScore));
                    checker->getNext()->setPrev(checker);
                }
                else{
                    movieNode* thisMov = new movieNode(mov,weightedScore);
                    thisMov->setPrev(checker);
                    thisMov->setNext(checker->getNext());
                    checker->setNext(thisMov);
                    thisMov->getNext()->setPrev(thisMov);
                }
                first->getNext()->setPrev(NULL);
                first = first->getNext();
            }
        }
        return false;
    }
};

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
void UserBase::addReview(MovieBase* mb, unsigned int movieID, unsigned int score, unsigned int id){
    this->get(id)->push_review(movieID,score);
    mb->get(movieID)->addReview(score);
}
void UserBase::addUser(unsigned int ID){
    allUsers.push_back(User(ID));
}

void UserBase::calculatePreferenceFactors(MovieBase* mb){
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
            vector<string> thisGenres = mb->get(reviewBegin->first)->getGenres();
            for(int k=0;k<thisGenres.size();k++){
                userGenreScores[thisGenres[k]]+=reviewBegin->second;
                userGenreReviewCount[thisGenres[k]]++;
                allGenreScores[thisGenres[k]]+=mb->get(reviewBegin->first)->getAverage();
                allGenreReviewCount[thisGenres[k]]++;
            }
            reviewBegin++;
        }
        
        map<string,float>::iterator finalIterator = allGenreScores.begin();
        while(finalIterator!=allGenreScores.end()){
            if(userGenreReviewCount[finalIterator->first]!=0&&allGenreReviewCount[finalIterator->first]!=0){
                float preferenceFactor = (float)((float)((float)(userGenreScores[finalIterator->first])/(float)(userGenreReviewCount[finalIterator->first]))/(float)((float)(finalIterator->second)/(float)(allGenreReviewCount[finalIterator->first])));
                allUsers.at(i).preferenceFactors[finalIterator->first] = preferenceFactor;
            }
            finalIterator++;
        }
    }
}

void UserBase::getAllTop(int moviesToShow, MovieBase* mb){
    ofstream outputFile;
    outputFile.open ("output.txt");
    for(int i=0;i<allUsers.size();i++){
        topMovieList(outputFile,moviesToShow,mb,allUsers[i].getID());
        outputFile << endl << endl << endl;
    }
    outputFile.close();
    cout << "File 'output.txt' has been written." << endl;
}
void UserBase::testPrint(){
    for(int i=0;i<allUsers.size();i++){
        cout << "UserID: " << allUsers[i].getID() << endl;
        map<string,float>::iterator it1 = allUsers[i].preferenceFactors.begin();
        while(it1!=allUsers[i].preferenceFactors.end()){
            cout << it1->first << ": " << it1->second << endl;
            it1++;
        }
        cout << endl;
    }
}
void UserBase::topMovieList(ofstream outputFile, int moviesToShow, MovieBase* mb, unsigned int userID){
    std::vector<MovieBase::Movie>::iterator mit = mb->allMovies.begin();
    doubleEndedMovieMap* topList = new doubleEndedMovieMap(moviesToShow);
    while(mit!=mb->allMovies.end()){
        MovieBase::Movie* thisMovie = &(*mit);
        if(thisMovie->getReviewCount()>=10){
            vector<string> theseGenres = thisMovie->getGenres();
            float weightedScore = 0;
            for(int i=0;i<theseGenres.size();i++){
                weightedScore+=this->get(userID)->preferenceFactors.at(theseGenres[i])*(thisMovie->getAverage());
            }
            weightedScore = weightedScore/theseGenres.size();
            topList->insert(thisMovie,weightedScore);
        }
        mit++;
    }
    outputFile << "User " << userID << "'s Top " << moviesToShow << " movies:" << endl;
    doubleEndedMovieMap::movieNode* checker = topList->first;
    while(checker!=NULL){
        outputFile << checker->getMovie()->getName() << " (" << checker->getMovie()->getYear() << ") - Weighted Score: " << checker->getScore() << endl;
        checker = checker->getNext();
    }
}