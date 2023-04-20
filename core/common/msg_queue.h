
#pragma once
#include <string.h>

#include <atomic>
#include <cstdio>
#include <vector>

// simple mpsc channel using ring buffer
class Msg_Queue {
 public:
  Msg_Queue(int queue_size);
  void* get();
  bool put(void* write);
  bool is_empty();

 private:
  std::vector<void*> queue;
  int queue_size;
  std::atomic<int> tail;
  int head;
};