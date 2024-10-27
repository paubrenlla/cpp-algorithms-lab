#ifndef TABLE_H
#define TABLE_H

template <class K, class V>
class Table
{
public:
 virtual ~Table() = default;

 /**
   * Insert key and valur.
   * @pre The table is not full.
   */
   virtual void insert(K key, V value) = 0;

    /**
     * Returns the value associated with the given key.
     * @pre The key must be in the hash table.
     */
    virtual V get(K key) = 0;

    /**
     * Returns if the key is in the table.
     */
    virtual bool exists(K key) = 0;

    /**
     * Removes the key and value from the table.
     * @pre The key must be in the table.
     */
    virtual void remove(K key) = 0;
};

#endif