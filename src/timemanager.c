#include "timemanager.h"

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "display.h"
#include "movesearch.h"

volatile _Atomic int stop_search = 0;

void timer(uint32_t time_ms);

typedef struct {
  Board* board;
} SearchArgs;

void* search_thread(void* args) {
  SearchArgs* sargs = (SearchArgs*)args;
  int depth = 7;

  get_best_move(sargs->board, depth);
  return NULL;
}

void* timer_thread(void* args) {
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
  *board = get_start_pos();

  stop_search = 0;
  char* token = strtok(args, " \n");
  pthread_t search_tid, timer_tid;

  SearchArgs* sargs = malloc(sizeof(SearchArgs));
  sargs->board = board;

  if (token && strcmp(token, "movetime") == 0) {
    token = strtok(NULL, " \n");
    if (!token) return;

    uint32_t time_ms = (uint32_t)strtoul(token, NULL, 10);

    pthread_create(&search_tid, NULL, search_thread, sargs);
    pthread_create(&timer_tid, NULL, timer_thread, (void*)(uintptr_t)time_ms);

  } else if (strcmp(token, "infinite") == 0) {
    pthread_create(&search_tid, NULL, search_thread, sargs);
  }
}