#ifndef COLLATZ_H
#define COLLATZ_H

#define CACHE_MISS -1

// LRU Cache Structures and Functions
typedef struct LRUNode {
    int num;
    int steps;
    struct LRUNode *prev, *next;
} LRUNode;

typedef struct {
    int capacity;
    int size;
    LRUNode *head, *tail;
    LRUNode **hash_map;
} LRUCache;

LRUCache* create_lru_cache(int capacity);
void move_to_head(LRUCache *cache, LRUNode *node);
LRUNode* remove_tail(LRUCache *cache);
void add_lru_node(LRUCache *cache, int num, int steps);
int check_lru_cache(LRUCache *cache, int num);

// LFU Cache Structures and Functions
typedef struct LFUNode {
    int num;
    int steps;
    int frequency;
    struct LFUNode *prev, *next;
} LFUNode;

typedef struct {
    int capacity;
    int size;
    LFUNode *head, *tail;
    LFUNode **hash_map;
} LFUCache;

LFUCache* create_lfu_cache(int capacity);
LFUNode* remove_lfu_node(LFUCache *cache);
void add_lfu_node(LFUCache *cache, int num, int steps);
int check_lfu_cache(LFUCache *cache, int num);

// Collatz function
int collatz_steps(int n);

extern int cache_hits;
extern int cache_requests;

#endif
