#include "msg_queue.h"

using namespace std;

Msg_Queue::Msg_Queue(int size) {
  queue.resize(size);
  queue_size = size;
  tail = 0;
  head = 0;
}

// return 0 for success
bool Msg_Queue::get(Msg* read) {
  if (head != tail) {
    // get msg
    printf("read = %ld\n", read);
    memcpy(read, queue[head], 8);
    printf("read = %ld\n", read);
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
    printf("a = %d, head = %d\n", (tail_temp + 1) % queue_size, head);
    if (((tail_temp + 1) % queue_size) == head) {
      // full
      return false;
    }
  } while (!tail.compare_exchange_strong(tail_temp, tail_temp + 1,
                                         memory_order_relaxed));

  queue[tail_temp] = write;
  printf("put seuccess %ld\n", write);
  return true;
}