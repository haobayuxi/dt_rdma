#include <malloc.h>

#include <boost/interprocess/ipc/message_queue.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/msg.h"
#include "common/msg_queue.h"
#include "rdma_transport.h"

struct remote_node {
  int node_id;
  std::string ip;
  int port;
};

class QP_Client_Manager {
 public:
  QP_Client_Manager(std::vector<remote_node> nodes);
  //  void build_rdma_connections(std::vector<remote_node> nodes);
  void build_cto_connections(remote_node cto_node);
  ibv_cq *recv_cq;
  std::unordered_map<int, rdma_fd *> data_qp;
  rdma_fd *cto_qp;
};

class QP_Server_Manager {
 public:
  QP_Server_Manager(int port, Msg_Queue *s_queue, Msg_Queue *r_queue);
  // void recv();
  ibv_cq *recv_cq;
  std::unordered_map<int, rdma_fd *> data_qp;
  std::unordered_map<int, Msg_Queue *> workers;

 private:
  int listen_to;
  Msg_Queue *send_queue;
  Msg_Queue *recv_queue;
};

void poll_server_recv(QP_Server_Manager *manager);
void poll_server_send(QP_Server_Manager *manager);

void poll_client_recv(QP_Client_Manager *manager);

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
