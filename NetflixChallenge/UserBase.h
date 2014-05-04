/* 
 * File:   UserBase.h
 * Author: Benjamin
 *
 * Created on May 4, 2014, 1:49 PM
 */

#ifndef USERBASE_H
#define	USERBASE_H

#include <string>

using namespace std;

class UserBase{
    friend class movieBase;
    friend class Movie;
    
private: 
        vector<User> allUsers;
public:
    class User{
    private:
        unsigned int userID;
        //[MovieID,score]
        HashMap<unsigned int, unsigned int> movieReviews;
        HashMap<string,float> preferenceFactors;
    public:
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
    };
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
     * 
     */
    void addReview(unsigned int movieID, unsigned int score, unsigned int id);
    
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
    void calculatePreferenceFactors();
    
    /*
     * parseString
     * 
     * This method will take in a line from u.user, and turn the information
     * into a new User in the allUsers vector.
     * 
     * Arguments: string S - the line from u.user.
     */
    void parseString(string s);
};

#endif	/* USERBASE_H */