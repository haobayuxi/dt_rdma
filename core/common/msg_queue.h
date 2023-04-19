
#include <vector>

#include "msg.h"

class Queue {
 public:
  Queue int init();
  bool get(Msg* read);
  bool put(Msg* write);

 private:
  std::vector<Msg*> queue;
  int32_t queue_size;
  int32_t tail;
  int32_t head;
}