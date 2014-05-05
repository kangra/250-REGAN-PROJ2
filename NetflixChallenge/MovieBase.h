/* 
 * File:   MovieBase.h
 * Author: Benjamin
 *
 * Created on May 4, 2014, 1:49 PM
 */

#ifndef MOVIEBASE_H
#define	MOVIEBASE_H

#include <string>
#include <vector>
#include <map>

using namespace std;
class MovieBase{
    friend class Movie;
    public:
        class Movie{
            friend class MovieBase;
        public:
            /* Default Constructor
             *
             * Arguments: NONE
             * Returns: NONE
             */
            Movie();
            
            /* Constructor
             * 
             * Arguments: unsigned int movieID (sets movie ID - will most likely be same as vector index
             * Returns: NONE
             */
            Movie(unsigned int movieID, unsigned int yr, string nm);
            
            /* isGenre
             * 
             * This will check through the HashMap of genres and check if the key (genre) has a true/false bool associated with it.
             * 
             * Arguments: string genre - string name representation of the genre
             * Returns: boolean - if this movie fits within this genre
             */
            bool isGenre(string genre);
            
            /* addReview
             * 
             * this will push a score into the vector of all scores.
             * 
             * Arguments: unsigned int score - The review score (0-5)
             * Returns: NONE
             */
            void addReview(unsigned int score);
            
            /* getScores
             * 
             * Returns the vector of all scores.
             */
            vector<int> getScores();
            
            /* setAverage
             * 
             * Sets the average rating. Called from the superclass.
             */
            void setAverage(float avg);
            
            /* getID
             * 
             * Returns the ID number of this movie.
             */
             unsigned int getID();
             
            /*  Returns the average value.
             * 
             */
            float getAverage();
           
            
             /* getGenres
             * 
             * Returns all genres mapped to "true" in the genre map.
             */
            vector<string> getGenres();

        private: 
            unsigned int ID;
            unsigned int year;
            string name;
            float average;
            vector<int> scores;
            map<string,bool> genres;
        };
        vector<Movie> allMovies;
        /*
         * Default Constructor
         */
        MovieBase();
        
        /*  parseString
         * 
         * This will take in a string from the u.item file, and parse it correctly as an individual movie.
         * 
         * Arguments: string s - the string (line) of u.item to be parsed.
         * Returns: NONE
         */
        void parseString(string s);
        
        /* operator[] // get
         * 
         * This will return a pointer to the movie object in the array of allmovies.
         * 
         * Arguments: movieID - this is the unique identification number as outlines by u.data
         * Returns: Pointer to movie object that is associated with this id
         */
        Movie* operator[](unsigned int movieID);
        Movie* get(unsigned int movieID);
        
        /*  calculateAverages
         * 
         * This will cycle through all the movies in the vector allMovies, and calculate the average score for that movie.
         * Called after all movies have been inserted. 
         * 
         * Arguments: NONE
         * Returns: NONE
         */
        void calculateAverages();
        
};

#endif	/* MOVIEBASE_H */

