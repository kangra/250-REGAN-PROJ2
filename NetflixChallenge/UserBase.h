/* 
 * File:   UserBaseKA.h
 * Author: Kunal
 *
 * Created on May 4, 2014, 1:49 PM
 */

#ifndef USERBASE_H
#define	USERBASE_H
#include <string>
#include <map>
#include <fstream>
#include "MovieBase.h"

using namespace std;
class UserBase{
    friend class movieBase;
    friend class Movie;
    
public:
    class User{
        friend class Movie;
        friend class MovieBase;
        friend class UserBase;
    public:
        unsigned int userID;
        //[MovieID,score]
        
        map<int,int> movieReviews;
        map<string,float> preferenceFactors;
        /*
         * Default Constructor
         */
        User();
        
        /*
         * Constructor
         * 
         * Arguments: id - sets userID.
         */
        User(unsigned int id);
        
        /*
         * push_review
         * 
         * Arguments: int mid - Movie ID
         *            int score - score(0-5)
         * 
         * Adds a review to the movieReviews hashmap.
         */
        void push_review(unsigned int mid, unsigned int score);
        
        /*
         * Returns userID
         */
        unsigned int getID();
    };
    vector<User> allUsers;
    /*
     * Default Constructor
     */
    UserBase();
    
    /*
     * addReview
     * 
     * Adds a review. This will span UserBase and MovieBase - it will
     * locate the movie in MovieBase, add the score to its reviews,
     * then locate the genre from MovieBase and add this review to
     * the user's genreReviews.
     * 
     * Arguments: movieID - the id of the movie this review is about.
     *            score - the rating this review gives this movie (0-5)
     *            id - the UserID associated with this review.
     *            MovieBase - the associate MovieBase to insert this review into.
     */
    void addReview(MovieBase* mb, unsigned int movieID, unsigned int score, unsigned int id);
    
    /*
     * CalculatePreferenceFactors
     * 
     * Rather than spend computing time recalculating the preference factors
     * while adding reviews, it's easiest to call a method that calculates all
     * the preference factors for every genre for every user at once.
     * 
     * This method should be called after calling calculateAverages() from the
     * MovieBase class.
     * 
     * This will cycle through all reviews of every user, putting them into 
     * a vector (genre) of HashMaps [MovieID, score], then cycle through the
     * maps for each genre, calculate the average of the scores by the general
     * user base, and the average from this user. UserAVG/GeneralAVG = prefFactor. 
     */
    void calculatePreferenceFactors(MovieBase* mb);
    
    /* 
     * getAllTop
     * 
     * Calculates the top n movies from MovieBase mb, where n is passed to the function. 
     * It will cycle through every movie in the MovieBase and form a constantly-sorting list.
     * This will save memory in the long run, as we won't need to store an array of pointers
     * to every single movie. It will take the average rating of all users, and multiply that
     * by the users preference factor. Thus, this should be called after calculatePreferenceFactors
     * has been called. 
     * 
     * Arguments:   int MoviesToShow - how many movies this function should sort and print.
     *              MovieBase* mb - the MovieBase containing the Movie objects to sort.
     */
    void getAllTop(int moviesToShow, MovieBase* mb);
    
    /*
     * As the only information we need from u.user is the user ID number,
     * which can easily be extracted simply from checking the number of lines
     * or newline characters is present, we needn't concern ourselves with parsing
     * the string. Instead, we'll have an addUser class that simply pushes a new
     * user into the UserBase vector.
     */
    void addUser(unsigned int userID);
    
    /*
     * Operator[] // get
     * 
     * Returns a pointer to the associated user object
     * 
     * Arguments: unsigned int userID - the userID to find.
     * 
     */
    User* operator[](unsigned int userID);
    User* get(unsigned int userID);
    
    /*
     *  debug method
     */
    
    void testPrint();
    
    /* topMovieList
     * 
     * this is the individual component of "getAllTop". Read the above methods
     * to ascertain how this functions.
     */
    void topMovieList(ofstream outputFile, int moviesToShow, MovieBase* mb, unsigned int userID);
};

#endif	/* USERBASE_H */
