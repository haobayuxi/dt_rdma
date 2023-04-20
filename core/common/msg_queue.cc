#include "msg_queue.h"

using namespace std;

Msg_Queue::Msg_Queue(int size) {
  queue.resize(size);
  queue_size = size;
  tail = 0;
  head = 0;
}

bool Msg_Queue::is_empty() {
  int tail_temp = tail;
  if (tail_temp == head) {
    return true;
  }
  return false;
}

// return 0 for success
void* Msg_Queue::get() {
  if (head != tail) {
    // get msg
    void* temp = queue[head];
    head = (head + 1) % queue_size;
    return temp;
  }
  // empty return false
  return NULL;
}

// return 0 for success
bool Msg_Queue::put(void* write) {
  int tail_temp;
  do {
    tail_temp = tail;
    // printf("tail_next = %d, head = %d\n", (tail_temp + 1) % queue_size,
    // head);
    if (((tail_temp + 1) % queue_size) == head) {
      // full
      return false;
    }
  } while (!tail.compare_exchange_strong(tail_temp, tail_temp + 1,
                                         memory_order_relaxed));

  queue[tail_temp] = write;
  printf("put queue success\n");
  return true;
}