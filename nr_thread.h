//
// Created by Ruto on 8/5/2016.
//

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <stdio.h>

typedef void (*nr_thread_callback)(void*);

int nr_invokethread(nr_thread_callback callback, void* args);