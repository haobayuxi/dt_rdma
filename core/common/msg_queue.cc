#include "msg_queue.h"

using namespace std;

Msg_Queue::Msg_Queue(int queue_size) {
  //   queue.resize(queue_size);
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
  //   do {
  tail_temp = tail;
  if (((tail_temp + 1) % queue_size) == head) {
    // full
    return false;
  }
  printf("tail = %d\n", tail_temp);
  //   } while (tail.compare_exchange_strong(tail_temp, tail_temp + 1,
  // memory_order_relaxed));
  printf("tail = %d\n", tail.load());
  //   write = queue[tail_temp];
  return true;
}