#include "timemanager.h"

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "movesearch.h"

volatile _Atomic int stop_search = 0;
static pthread_mutex_t search_mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t search_done = PTHREAD_COND_INITIALIZER;
static bool search_running = false;

void timer(uint32_t time_ms);

typedef struct {
  Board* board;
  Move* bestmove;
  FILE* out;
} SearchArgs;

void* search_thread(void* args) {
  SearchArgs* sargs = (SearchArgs*)args;

  iddfs(sargs->board, sargs->bestmove);

  char lan[6];
  lan_from_move(*sargs->bestmove, lan);

  fprintf(sargs->out, "bestmove %s\n", lan);

  fflush(sargs->out);
  free(sargs);

  pthread_mutex_lock(&search_mtx);
  search_running = false;
  pthread_cond_broadcast(&search_done);
  pthread_mutex_unlock(&search_mtx);

  return NULL;
}

void* timer_thread(void* args) {
  uint32_t time_ms = (uint32_t)(uintptr_t)args;
  timer(time_ms);
  timemanager_stop();
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
  stop_search = 1;
  char* token = strtok(args, " \n");

  pthread_t tid;

  if (token && strcmp(token, "movetime") == 0) {
    token = strtok(NULL, " \n");
    if (!token) return;

    SearchArgs* sargs = malloc(sizeof(SearchArgs));
    sargs->board = board;
    sargs->bestmove = bestmove;
    sargs->out = out;

    uint32_t time_ms = (uint32_t)strtoul(token, NULL, 10);

    pthread_mutex_lock(&search_mtx);
    while (search_running) pthread_cond_wait(&search_done, &search_mtx);
    stop_search = 0;
    search_running = true;
    pthread_mutex_unlock(&search_mtx);
    int err = pthread_create(&tid, NULL, search_thread, sargs);
    if (!err){
      pthread_detach(tid);
    }else{
      free(sargs);
      pthread_mutex_lock(&search_mtx);
      search_running = false;
      pthread_cond_broadcast(&search_done);
      pthread_mutex_unlock(&search_mtx);
      return;
    }
    err = pthread_create(&tid, NULL, timer_thread, (void*)(uintptr_t)time_ms);
    if (!err){
      pthread_detach(tid);
    }else{
      timemanager_stop();
      return;
    }

  } else if (token && strcmp(token, "infinite") == 0) {
    SearchArgs* sargs = malloc(sizeof(SearchArgs));
    sargs->board = board;
    sargs->bestmove = bestmove;
    sargs->out = out;

    pthread_mutex_lock(&search_mtx);
    while (search_running) pthread_cond_wait(&search_done, &search_mtx);
    stop_search = 0;
    search_running = true;
    pthread_mutex_unlock(&search_mtx);
    int err = pthread_create(&tid, NULL, search_thread, sargs);
    if (!err){
      pthread_detach(tid);
    }else{
      free(sargs);
      pthread_mutex_lock(&search_mtx);
      search_running = false;
      pthread_cond_broadcast(&search_done);
      pthread_mutex_unlock(&search_mtx);
    }
  }
}

void timemanager_stop(void) {
  stop_search = 1;

  pthread_mutex_lock(&search_mtx);
  while (search_running) {
    pthread_cond_wait(&search_done, &search_mtx);
  }
  pthread_mutex_unlock(&search_mtx);
}

// For unit testing
void timemanager_wait(void) {
  pthread_mutex_lock(&search_mtx);
  while (search_running) {
    pthread_cond_wait(&search_done, &search_mtx);
  }
  pthread_mutex_unlock(&search_mtx);
}