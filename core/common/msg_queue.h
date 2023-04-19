
#include <string.h>

#include <atomic>
#include <vector>

#include "msg.h"

// simple mpsc channel using ring buffer
class Msg_Queue {
 public:
  Msg_Queue(int32_t queue_size);
  bool get(Msg* read);
  bool put(Msg* write);

 private:
  std::vector<Msg*> queue;
  int32_t queue_size;
  std::atomic<int> tail;
  int head;
};