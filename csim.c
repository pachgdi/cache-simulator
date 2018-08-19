#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include "cachelab.h"

#define BUFF_SIZE 1024

int main(int argc, char **argv, char **envp)
{
    int hits, misses, evictions;
    int opt, set_bits_count, lines_count, byte_bits_count;
    char *trace_name;

    hits = misses = evictions = 0;
    set_bits_count = lines_count = byte_bits_count = 0;

    // get options
    if (argc < 9) {
        printf("Usage: %s "
               "-s [#sets] -E [#lines] -b [#byte bits] "
               "-t [#trace_file_name]", argv[0]);
    }
    while((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch(opt) {
        case 's':
            set_bits_count = atoi(optarg);
            break;
        case 'E':
            lines_count = atoi(optarg);
            break;
        case 'b':
            byte_bits_count = atoi(optarg);
            break;
        case 't':
            trace_name = optarg;
            break;
        default:
            fprintf(stderr, "Usage: %s "
                    "-s [#sets] -E [#lines] -b [#byte bits] "
                    "-t [#trace_file_name]", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // initialize cache
    cache *instance_cache;
    init_cache(&instance_cache, set_bits_count, lines_count, byte_bits_count);
    // open file, start reading and updating counts per line
    FILE *f_stream = fopen(trace_name, "r");
    if (f_stream == NULL) {
        fprintf(stderr, "Could not open file (%s): %s", trace_name, strerror(errno));
    }

    char *buffer = malloc(BUFF_SIZE);
    int req_size; // size of request
    long address; // the memory address
    char req_type; // Kind of request (S, M, L)

    while (fgets(buffer, BUFF_SIZE, f_stream) != NULL) {
        sscanf(buffer, " %c %ld,%d", &req_type, &address, &req_size);
        update_counts(instance_cache, req_type, address,
                      &hits, &misses, &evictions);
    }
    fclose(f_stream);
    delete_cache(&instance_cache);

    printSummary(hits, misses, evictions);
    return 0;
}

void init_cache(cache **cache_pointer, int set_bits_count,
                int lines_count, int byte_bits_count)
{

}

void delete_cache(cache **cache_pointer)
{

}
void upate_counts(cache *instance_cache, long address,
                  int *hits, int *misses, int *evictions)
{

}
