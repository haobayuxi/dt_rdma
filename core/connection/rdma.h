#include <malloc.h>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <string>
#include <unordered_map>
#include <vector>

// #include "common/queue.h"
#include "rdma_transport.h"

struct remote_node {
  int node_id;
  std::string ip;
  int port;
};

class QP_Client_Manager {
 public:
  void build_rdma_connections(std::vector<remote_node> nodes);
  void build_cto_connections(remote_node cto_node);
  void run_msg_loop();

 private:
  std::unordered_map<int, rdma_fd *> data_qp;
  rdma_fd *cto_qp;
};

class QP_Server_Manager {
 public:
  QP_Server_Manager(int port);
  // void recv();
  ibv_cq *recv_cq;
  std::unordered_map<int, rdma_fd *> data_qp;

 private:
  int listen_to;
};

void poll_server_recv(QP_Server_Manager *manager);

bool client_send(rdma_fd *handler, char *local_buf, uint32_t size);

char *client_recv(rdma_fd *handler);

bool server_send(rdma_fd *handler, char *local_buf, uint32_t size);

// void server_recv(rdma_fd *handler);

void malloc_buf(long size);

void free_buf(long size);
void push_recv_wr(rdma_fd *handler);

// init client with host name
void init_client(rdma_fd *handler, char *server, int port);
// void init_server(rdma_fd *handler, int port);
