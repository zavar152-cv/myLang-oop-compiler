#include <stdint.h>
typedef struct HashNode {
    char *key;
    void *value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode **buckets;
    uint32_t size;
    uint32_t count;
} HashTable;

HashTable *createHashTable(int size);

void insertInHashTable(HashTable *table, const char *key, void *value);

void *searchHashTable(HashTable *table, const char *key);

void deleteKeyFromHashTable(HashTable *table, const char *key);

void freeHashTable(HashTable *table, void (*free_value)(void *));

void printHashTable(HashTable *table);