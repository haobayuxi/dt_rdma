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
  std::unordered_map<int, Msg_Queue *> workers;
  rdma_fd *cto_qp;
};

class QP_Server_Manager {
 public:
  QP_Server_Manager(int port,
                    std::unordered_map<int, Msg_Queue *> worker_queue);
  ibv_cq *recv_cq;
  std::unordered_map<int, rdma_fd *> data_qp;
  std::unordered_map<int, Msg_Queue *> workers;
  std::unordered_map<int, Msg_Queue *> qp_recvs;

 private:
  int listen_to;
  int worker_num;
};

void poll_server_recv(QP_Server_Manager *manager);
void poll_server_send(QP_Server_Manager *manager);

void poll_client_recv(QP_Client_Manager *manager);

bool client_send(rdma_fd *handler, char *local_buf, uint32_t size);

char *client_recv(rdma_fd *handler);

void push_recv_wr(rdma_fd *handler);
