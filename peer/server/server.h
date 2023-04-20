
#include <thread>

#include "common/msg_queue.h"
#include "connection/rdma.h"
#include "server_worker/worker.h"
class Server {
 public:
  Server();

  ~Server() {}

  void GenThreads();

  void InitData();

  void InitRdma();

 private:
  int server_id;
  SystemConfig config;
};