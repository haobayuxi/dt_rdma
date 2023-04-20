
#include <unistd.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "common/msg.h"
#include "common/msg_queue.h"

using namespace std;
class Worker {
 public:
  Worker(Msg_Queue *msg_recv, DtxType dtx_type);
  void run();

 private:
  void handle_msg(Msg *msg, Msg_Queue *queue);
  DtxType dtx_type;
  vector<unordered_map<uint64_t, uint64_t>> table;
  Msg_Queue *msg_recv;
};

void run_worker(Worker *worker);