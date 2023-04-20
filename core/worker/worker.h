
#include <iostream>
#include <unordered_map>
#include <vector>

#include "common/msg_queue.h"

using namespace std;
class Worker {
 public:
  Worker();
  void run();

 private:
  // void handle_msg(Msg_with_QPnum *msg);

  vector<unordered_map<uint64_t, uint64_t>> table;
  Msg_Queue *msg_recv;
  Msg_Queue *send;
};

void run_worker(Worker *worker);