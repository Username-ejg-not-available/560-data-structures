#ifndef HASHTABLE_H
#define HASHTABLE_H

enum class TableType {
    LINEAR,//not used
    QUADRATIC,
    DOUBLE
};

class HashTable {
private:
    struct Node {
        int Value;
        unsigned int EntryType;//0: empty, 1: deleted, 2: full
        /**
         * @post assigns Value and EntryType default values
         */
        Node() : Value(-1), EntryType(0) {}
    };

    unsigned int _bucketSize;
    unsigned int _load, _R;
    TableType _type;
    Node* _list;

    /**
     * @param num number being hashed
     * @param i used for collision resolution, effectively which collision we are on
     * @return hash for num based on number of collisions
     */
    unsigned int hashFunction(int num, unsigned int i) const;
public:
    /**
     * @pre bs is prime, r is prime, bs > r
     * @param bs bucket size
     * @param r R value (only matters for TableType::DOUBLE)
     * @param type table type
     * @post creates empty hash table with specified parameters
     */
    HashTable(unsigned int bs, unsigned int r, TableType type);

    /**
     * @pre bs is prime and bs > other._bucketSize
     * @param bs bucket size
     * @param other table from which to copy values and acquire R
     */
    HashTable(unsigned int bs, const HashTable& other);

    /**
     * @post deletes _list
     */
    ~HashTable();

    /**
     * @param num number to search for
     */
    bool contains(int num) const;

    /**
     * @pre num not already in table
     * @param num number to be inserted
     * @post attempts to insert num into table
     * @return true is insertion was successful, false otherwise
     */
    bool insert(int num);

    /**
     * @pre num is in table
     * @param num number to be removed
     * @post removes num from table
     */
    void remove(int num);

    /**
     * @return _bucketSize
     */
    unsigned int getBucketSize() const;

    /**
     * @return load factor
     */
    double getLoadFactor() const;

    /**
     * @post prints contents of hashtable
     */
    void print() const;
};
#endif