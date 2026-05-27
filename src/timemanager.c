#include "timemanager.h"

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "movesearch.h"

volatile _Atomic int stop_search = 0;

void timer(uint32_t time_ms);

void* search_with_stop_search(void* args) {
  // TODO: Call some function in movesearch.c to return best move via uci.c
  return NULL;
}

void* start_timer(void* args) {
  uint32_t time_ms = (uint32_t)(uintptr_t)args;
  timer(time_ms);
  stop_search = 1;
  return NULL;
}

void timer(uint32_t time_ms) {
  struct timespec tp = {
      .tv_sec = time_ms / 1000,
      .tv_nsec = (time_ms % 1000) * 1000000L,
  };

  nanosleep(&tp, NULL);
}

void timemanager_go(Board* board, char* args) {
  (void)board;

  stop_search = 0;
  char* token = strtok(args, " \n");
  pthread_t search_thread, timer_thread;

  if (token && strcmp(token, "movetime") == 0) {
    token = strtok(NULL, " \n");
    if (!token) return;

    uint32_t time_ms = (uint32_t)strtoul(token, NULL, 10);

    pthread_create(&search_thread, NULL, search_with_stop_search, NULL);
    pthread_create(&timer_thread, NULL, start_timer, (void*)(uintptr_t)time_ms);
  }
}