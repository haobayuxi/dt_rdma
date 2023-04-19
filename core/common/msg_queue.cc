#include "queue.h"

Msg_Queue::Queue(int32_t queue_size) {
  queue.resize(queue_size);
  queue_size = queue_size;
  tail = 0;
  head = 0;
}

// return 0 for success
bool Msg_Queue::get(Msg* read) {
  if (head != tail) {
    // get msg
    memcpy(read, queue[head], 8);
    head = (head + 1) % queue_size;
    return true;
  }
  // empty return false
  return false;
}

// return 0 for success
bool Msg_Queue::put(Msg* write) {
  int tail_temp;
  do {
    tail_temp = tail;
    if (((tail_temp + 1) % queue_size) == head) {
      // full
      return false;
    }
  } while (compare_exchange_strong(&tail, tail_temp, tail_temp + 1));

  return true;
}