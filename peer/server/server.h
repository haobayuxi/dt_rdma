
#include <thread>

#include "common/msg_queue.h"
#include "connection/rdma.h"

// class Server {
//  public:
//   Server(int id, SystemConfig config) : server_id(id), config(config) {}

//   ~Server() {}

//   void GenThreads();

//   void InitData();

//   void InitRdma();

//  private:
//   const int server_id;
//   const SystemConfig config;
// };