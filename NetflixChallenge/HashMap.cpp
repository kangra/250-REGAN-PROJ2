/* 
 * File:   HashMap.cpp
 * Author: Benjamin
 *
 * Created on May 4, 2014, 2:00 PM
 */

#include "HashMap.h"

using namespace std;

template<typename K, typename I>
HashMap<K,I>::HashMap(){}


HashMap<K,I>::keyExists(K key){
    for(int i=0;i<keys.size();i++){
        if(key==keys.at(i)){return true;}
    }
    return false;
}

HashMap<K,I>::operator [](K key){
    for(int i=0;i<keys.size();i++){
        if(key==keys.at(i)){return items.at(i);}
    }
    throw NDE;
}

HashMap<K,I>::insert(K key, I item){
    if(keyExists(key)){throw KADE;}
    keys.push_back(key);
    items.push_back(item);
}

HashMap<K,I>::get(K key){
    for(int i=0;i<keys.size();i++){
        if(key==keys.at(i)){return items.at(i);}
    }
    throw NDE;   
}

HashMap<K,I>::erase(K key){
    bool found = false;
    for(int i=0;i<keys.size();i++){
        if(key==keys.at(i)){
            found = true;
            keys.erase(i);
            items.erase(i);
        }
    }
    if(!found){throw NDE;}
}

HashMap<K,I>::size(){
    return keys.size();
}

HashMap<K,I>::set(K key, I item){
    bool found = false;
    for(int i=0;i<keys.size();i++){
        if(key==keys.at(i)){
            found = true;
            items.at(i) = item;
        }
    }
    if(!found){throw NDE;}
}