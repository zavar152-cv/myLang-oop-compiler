#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define INITIAL_SIZE 8
#define LOAD_FACTOR 0.75

unsigned int hash(const char *key, int table_size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + *key++;
    }
    return hash % table_size;
}

HashNode *createHashNode(const char *key, void *value) {
    HashNode *node = malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    node->next = NULL;
    return node;
}

HashTable *createHashTable(int size) {
    HashTable *table = malloc(sizeof(HashTable));
    table->buckets = calloc(size, sizeof(HashNode *));
    table->size = size;
    table->count = 0;
    return table;
}

void resizeHashTable(HashTable *table) {
    int new_size = table->size * 2;
    HashNode **new_buckets = calloc(new_size, sizeof(HashNode *));
    
    for (int i = 0; i < table->size; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *next = node->next;
            unsigned int index = hash(node->key, new_size);

            node->next = new_buckets[index];
            new_buckets[index] = node;

            node = next;
        }
    }

    free(table->buckets);
    table->buckets = new_buckets;
    table->size = new_size;
}

void insertInHashTable(HashTable *table, const char *key, void *value) {
    if ((float)table->count / table->size > LOAD_FACTOR) {
        resizeHashTable(table);
    }

    unsigned int index = hash(key, table->size);
    HashNode *node = table->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }

    node = createHashNode(key, value);
    node->next = table->buckets[index];
    table->buckets[index] = node;
    table->count++;
}

void *searchHashTable(HashTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    HashNode *node = table->buckets[index];
    
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void deleteKeyFromHashTable(HashTable *table, const char *key) {
    unsigned int index = hash(key, table->size);
    HashNode *node = table->buckets[index];
    HashNode *prev = NULL;

    while (node) {
        if (strcmp(node->key, key) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->buckets[index] = node->next;
            }
            free(node->key);
            free(node);
            table->count--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void freeHashTable(HashTable *table, void (*freeValue)(void *)) {
    if (table == NULL)
        return;
    for (int i = 0; i < table->size; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            HashNode *temp = node;
            node = node->next;
            free(temp->key);
            if(freeValue) {
                freeValue(temp->value);
            }
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}

void printHashTable(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        HashNode *node = table->buckets[i];
        while (node) {
            printf("Key: %s, Value: %p", node->key, node->value);
            printf("\n");
            node = node->next;
        }
    }
}
