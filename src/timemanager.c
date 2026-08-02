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
} DebugArgs;

void* debug_thread(void* args) {
  DebugArgs* dargs = (DebugArgs*)args;

  while (!stop_search) {
    print_grid(*dargs->board);
    timer(1000);
  }

  free(dargs);
  return NULL;
}

typedef struct {
  Board* board;
  Move* bestmove;
  FILE* out;
} SearchArgs;

void* search_thread(void* args) {
  SearchArgs* sargs = (SearchArgs*)args;

  iddfs(sargs->board, sargs->bestmove);
  fprintf(sargs->out, "bestmove");
  fprintf(sargs->out, "{%i, %i, %i, %i}\n", sargs->bestmove->from_rank,
          sargs->bestmove->from_file, sargs->bestmove->to_rank,
          sargs->bestmove->to_file);
  fflush(sargs->out);
  free(sargs);
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

void timemanager_go(Board* board, char* args, Move* bestmove, FILE* out) {
  stop_search = 0;
  char* token = strtok(args, " \n");
  pthread_t search_tid, timer_tid, debug_tid;

  if (token && strcmp(token, "movetime") == 0) {
    token = strtok(NULL, " \n");
    if (!token) return;

    SearchArgs* sargs = malloc(sizeof(SearchArgs));
    sargs->board = board;
    sargs->bestmove = bestmove;
    sargs->out = out;

    uint32_t time_ms = (uint32_t)strtoul(token, NULL, 10);

    pthread_create(&search_tid, NULL, search_thread, sargs);
    pthread_create(&timer_tid, NULL, timer_thread, (void*)(uintptr_t)time_ms);

  } else if (token && strcmp(token, "infinite") == 0) {
    SearchArgs* sargs = malloc(sizeof(SearchArgs));
    sargs->board = board;
    sargs->bestmove = bestmove;
    sargs->out = out;

    DebugArgs* dargs = malloc(sizeof(DebugArgs));
    dargs->board = board;

    pthread_create(&search_tid, NULL, search_thread, sargs);
    pthread_create(&debug_tid, NULL, debug_thread, dargs);
  }
}