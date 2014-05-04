/* 
 * File:   HashMap.h
 * Author: Benjamin
 *
 * Created on May 4, 2014, 2:00 PM
 */

#ifndef HASHMAP_H
#define	HASHMAP_H

#include <vector>

using namespace std;

/* HashMap Class
 * K = Key, I = Item
 * Holds vectors of Keys<K> and items<I> initialized with constructor
 */
template<typename K, typename I>
class HashMap{
    public:
        /*  Default Constructor
         *  
         *  Arguments: NONE
         *  Returns: NONE
         */
        HashMap();
        
        /*  keyExists
         * 
         *  Arguments: K key - Key to be checked. Assumes comparison operator
         *  is declared, throws error if not.
         * 
         *  Returns: bool - True if key is found, false if not.
         */
        bool keyExists(K key);
        
        /* insert
         * 
         * Arguments: K key - Key to be associated with item I.
         *            I item - Item to be associated with key K.
         * 
         * Returns: NONE
         */
        void insert(K key, I item);
        
        /*  operator[]
         * 
         *  Arguments: k key - Key to be checked.
         * 
         *  Returns: I - Item associated with Key. If not found, throws
         *  notDefinedException.
         */
        I operator[](K key);
        
        /*  get
         * 
         *  Arguments: K key - Key to be checked.
         * 
         *  Returns: I - Item associated with Key. If not found, throws
         *  notDefinedException.
         */
        I get(K key);
        
        /* erase
         * 
         * Arguments: K key - key to be erased.
         * 
         * Method: Finds key/item pair, uses stock
         * vector deletion method to remove. Unlikely
         * to be used in this challenge, included
         * for possibility of use.
         * 
         * Returns: void
         */
        
        /*
         * set
         * 
         * Arguments: K key - key that already exists
         *            I item - Value to change key-item pair to
         * 
         * This will find the key in the argument and change the value associated to
         * the new value I.
         */
        void set(K key, I item);
        void erase(K key);
        
        /*
         * size
         * 
         * Returns the size of the HashMap based on the size of the
         * underlying vectors.
         */
        unsigned int size();
        
        class notDefinedException : public exception{} NDE;
        class keyAlreadyDefinedException : public exception{} KADE;
    
    private:
        vector<K> keys;
        vector<I> items;
};
#endif	/* HASHMAP_H */