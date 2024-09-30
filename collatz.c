#include "collatz.h"
#include <stdlib.h>
#include <stdio.h>

// Global variables for cache statistics
int cache_hits = 0;
int cache_requests = 0;

/***********************************
 * Collatz Sequence Implementation *
 ***********************************/
int collatz_steps(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

/**************************
 * LRU Cache Implementation *
 **************************/
LRUCache* create_lru_cache(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->hash_map = (LRUNode**)malloc(sizeof(LRUNode*) * capacity);
    for (int i = 0; i < capacity; i++) {
        cache->hash_map[i] = NULL;
    }
    return cache;
}

void move_to_head(LRUCache *cache, LRUNode *node) {
    if (cache->head == node) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (cache->tail == node) cache->tail = node->prev;

    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (!cache->tail) cache->tail = node;
}

LRUNode* remove_tail(LRUCache *cache) {
    if (!cache->tail) return NULL;

    LRUNode *node = cache->tail;
    cache->tail = node->prev;

    if (cache->tail) cache->tail->next = NULL;
    else cache->head = NULL;

    return node;
}

void add_lru_node(LRUCache *cache, int num, int steps) {
    if (cache->size == cache->capacity) {
        LRUNode *node = remove_tail(cache);
        cache->hash_map[node->num % cache->capacity] = NULL;
        free(node);
        cache->size--;
    }

    LRUNode *new_node = (LRUNode*)malloc(sizeof(LRUNode));
    new_node->num = num;
    new_node->steps = steps;
    new_node->prev = NULL;
    new_node->next = cache->head;

    if (cache->head) cache->head->prev = new_node;
    cache->head = new_node;
    if (!cache->tail) cache->tail = new_node;

    cache->hash_map[num % cache->capacity] = new_node;
    cache->size++;
}

int check_lru_cache(LRUCache *cache, int num) {
    cache_requests++;
    LRUNode *node = cache->hash_map[num % cache->capacity];
    if (node && node->num == num) {
        move_to_head(cache, node);
        cache_hits++;
        return node->steps;
    }
    return CACHE_MISS;
}

/**************************
 * LFU Cache Implementation *
 **************************/
LFUCache* create_lfu_cache(int capacity) {
    LFUCache* cache = (LFUCache*)malloc(sizeof(LFUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->hash_map = (LFUNode**)malloc(sizeof(LFUNode*) * capacity);
    for (int i = 0; i < capacity; i++) {
        cache->hash_map[i] = NULL;
    }
    return cache;
}

LFUNode* remove_lfu_node(LFUCache *cache) {
    if (!cache->tail) return NULL;

    LFUNode *node = cache->tail;
    cache->tail = node->prev;

    if (cache->tail) cache->tail->next = NULL;
    else cache->head = NULL;

    return node;
}

void add_lfu_node(LFUCache *cache, int num, int steps) {
    if (cache->size == cache->capacity) {
        LFUNode *node = remove_lfu_node(cache);
        cache->hash_map[node->num % cache->capacity] = NULL;
        free(node);
        cache->size--;
    }

    LFUNode *new_node = (LFUNode*)malloc(sizeof(LFUNode));
    new_node->num = num;
    new_node->steps = steps;
    new_node->frequency = 1;
    new_node->prev = NULL;
    new_node->next = cache->head;

    if (cache->head) cache->head->prev = new_node;
    cache->head = new_node;
    if (!cache->tail) cache->tail = new_node;

    cache->hash_map[num % cache->capacity] = new_node;
    cache->size++;
}

int check_lfu_cache(LFUCache *cache, int num) {
    cache_requests++;
    LFUNode *node = cache->hash_map[num % cache->capacity];
    if (node && node->num == num) {
        node->frequency++;
        cache_hits++;
        return node->steps;
    }
    return CACHE_MISS;
}































