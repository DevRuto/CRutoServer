//
// Created by Ruto on 8/5/2016.
//

#include "nr_thread.h"

int nr_invokethread(nr_thread_callback callback, void* args) {
    if (!callback)
    {
        puts("\nERROR, CALLBACK NULL\n");
        return 0;
    }
#ifdef _WIN32
    DWORD threadid;
    return (int)CreateThread(NULL, 0, callback, args, 0, &threadid);
#else
    pthread_t thread;
    return pthread_create(&thread, NULL, callback, args);
#endif
}