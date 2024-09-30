#include "collatz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Usage: %s <N> <MIN> <MAX> <cache_size> <cache_type>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);
    int cache_size = atoi(argv[4]);
    char *cache_type = argv[5];

    srand(time(NULL)); // Seed for random numbers

    if (strcmp(cache_type, "LRU") == 0) {
        LRUCache *lru_cache = create_lru_cache(cache_size);
        for (int i = 0; i < N; i++) {
            int num = rand() % (MAX - MIN + 1) + MIN;
            int steps = check_lru_cache(lru_cache, num);
            if (steps == CACHE_MISS) {
                steps = collatz_steps(num);
                add_lru_node(lru_cache, num, steps);
            }
            printf("%d,%d\n", num, steps);
        }
    } else if (strcmp(cache_type, "LFU") == 0) {
        LFUCache *lfu_cache = create_lfu_cache(cache_size);
        for (int i = 0; i < N; i++) {
            int num = rand() % (MAX - MIN + 1) + MIN;
            int steps = check_lfu_cache(lfu_cache, num);
            if (steps == CACHE_MISS) {
                steps = collatz_steps(num);
                add_lfu_node(lfu_cache, num, steps);
            }
            printf("%d,%d\n", num, steps);
        }
    }

    // Report cache hit statistics
    printf("Cache requests: %d\n", cache_requests);
    printf("Cache hits: %d\n", cache_hits);
    printf("Cache hit rate: %.2f%%\n", (float)cache_hits / cache_requests * 100);

    return 0;
}
