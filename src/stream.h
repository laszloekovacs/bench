#ifndef _STREAM_H_
#define _STREAM_H_

#include <pthread.h>
#include <stddef.h>

/* asset status flags */
typefef enum {
    ASSET_UNUSED = 0,
    ASSET_QUEUED,   // waiting with a request
    ASSET_LOADING,  // currently being read from disk
    ASSET_READY,    // asset loaded into memory
    ASSET_UPLOADED, // asset in vram
    ASSET_ERROR
} asset_state_t;

/* asset descriptor */
typedef struct
{
    // what to load
    char path[512];

    // data loaded to mem
    unsigned char *data;
    size_t size;

    // syncing.
    /* volatile keeps compiler from optimizing */
    // volatile asset_state_t status;
    volatile asset_state_t status;
} asset_t

/* ring buffer for jobs, might be better to have a linked list, less speed, more dynamic */
#define QUEUE_SIZE 16

    typedef struct
{
    asset_t *queue[QUEUE_SIZE];
    int head; // read by worker
    int tail; // written by main thread
    int count;

    // pthread primitives
    pthread_mutex_t mutex;
    pthread_cond_t cond_var; // signal for worker when job is sent
    int shutdown;            // flag for when thread should exit
} stream_queue_t;

#endif