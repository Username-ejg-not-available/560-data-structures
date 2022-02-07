/**
* @author Ethan Grantz
* @file HashTable.h
* @date 2/8/2021
* @brief declares the functions that the HashTable class needs to work
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "LinkedList.h"
struct Data;

class HashTable {
private:
    /** Data
     *  glorified tuple
     */
    struct Data {
        std::string Key;
        int Id;
        /**
         * @param key name of person
         * @param id person's id
         */
        Data(std::string key,int id) : Key(key),Id(id){}
        /**
         * Compiler required default constructor
         */
        Data() : Key(""),Id(0) {}
    };

    unsigned int _bucketSize;
    LinkedList<LinkedList<Data>*>* _arr;

    /**
     * @param key converts key into hash value
     * @return index where an item with provided key would be inserted/found
     */
    int hashFunction(std::string key) const;
public:
    /**
     * @param bs number of buckets
     */
    HashTable(unsigned int bs);

    /**
     * @post deletes all _bucketSize + 1 LinkedLists
     */
    ~HashTable();

    /**
     * @return _bucketSize
     */
    unsigned int getBucketSize() const;

    /**
     * @param key name of person
     * @param id person's id
     * @post creates new Data with provided parameters and puts it in the hash table
     * @throw std::runtime_error if person of same name already in table
     */
    void insert(std::string key, int id);//AddStudent

    /**
     * @param key name of person
     * @param id person's id
     * @post remove person of same name and id
     * @throw std::runtime_error if person already in table
     */
    void remove(std::string key, int id);//RemoveStudent

    /**
     * @param key name of person
     * @param id person's id
     * @post searches table for person
     * @return true if person in table, false otherwise
     */
    bool contains(std::string key, int id) const;

    /**
     * @param key name of person
     * @return Data object with provided key
     * @throw std::runtime_error if person not in table
     */
    Data get(std::string key) const;

    /**
     * @param key name of person
     * @return bucket index person is in
     * @throw std::runtime_error if person not in table
     */
    unsigned int getIndex(std::string key) const;

    /**
     * @param index bucket index
     * @post creates a string used for printing the contents of a bucket
     * @return the string used for printing the contents of the bucket
     */
    std::string getPrintString(unsigned int index) const;
};
#endif