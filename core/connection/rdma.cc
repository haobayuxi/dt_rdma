

#include "rdma.h"

using namespace boost::interprocess;

QP_Client_Manager::QP_Client_Manager(std::vector<remote_node> nodes) {
  for (int i = 0; i < nodes.size(); i++) {
    rdma_fd *handler = (rdma_fd *)malloc(sizeof(rdma_fd));
    int sock =
        client_exchange(const_cast<char *>(nodes[i].ip.c_str()), nodes[i].port);
    handler->fd = sock;
    context_info *ib_info = (context_info *)malloc(sizeof(context_info));
    open_device_and_alloc_pd(ib_info);
    get_context_info(handler, ib_info);
    build_rdma_connection(handler);

    data_qp.insert(std::make_pair(handler->qp->qp_num, handler));
  }
}

void QP_Client_Manager::build_cto_connections(remote_node cto_node) {
  rdma_fd *handler = (rdma_fd *)malloc(sizeof(rdma_fd));

  int sock =
      client_exchange(const_cast<char *>(cto_node.ip.c_str()), cto_node.port);
  handler->fd = sock;
  context_info *ib_info = (context_info *)malloc(sizeof(context_info));
  open_device_and_alloc_pd(ib_info);
  get_context_info(handler, ib_info);
  build_rdma_connection(handler);
  cto_qp = handler;
}

QP_Server_Manager::QP_Server_Manager(
    int port, std::unordered_map<int, Msg_Queue *> worker_queue) {
  workers = worker_queue;
  listen_to = init_sockt(port);
  // for(int i = 0;i < nodes.size();i++) {
  rdma_fd *handler = (rdma_fd *)malloc(sizeof(rdma_fd));

  struct sockaddr_in csin;
  socklen_t csinsize = sizeof(csin);
  int c = accept(listen_to, (struct sockaddr *)&csin, &csinsize);
  handler->fd = c;
  context_info *ib_info = (context_info *)malloc(sizeof(context_info));
  open_device_and_alloc_pd(ib_info);
  get_context_info(handler, ib_info);
  build_rdma_connection(handler);
  // init_server(handler, port);
  recv_cq = handler->recv_cq;
  data_qp.insert(std::make_pair(handler->qp->qp_num, handler));
  auto qp_recv_queue = new Msg_Queue(100);
  qp_recvs.insert(std::make_pair(handler->qp->qp_num, qp_recv_queue));
  // }

  push_recv_wr(handler);
  // init message queue
}

void push_recv_wr(rdma_fd *handler) {
  struct ibv_recv_wr recv_wr, *recv_failure;
  recv_wr.next = NULL;
  recv_wr.sg_list = NULL;
  recv_wr.num_sge = 0;
  recv_wr.wr_id = 0;

  auto ret = ibv_post_recv(handler->qp, &recv_wr, &recv_failure);
}

void poll_server_recv(QP_Server_Manager *manager) {
  int result = 0;
  while (1) {
    struct ibv_wc wc;
    while (!ibv_poll_cq(manager->recv_cq, 1, &wc))
      ;
    printf("imm=%d, qp_num=%d \n", wc.imm_data, wc.qp_num);
    // return read_msg(handler);
    auto handler = manager->data_qp[wc.qp_num];
    memcpy(&result, handler->receive_buf + handler->have_read, 4);
    push_recv_wr(handler);
    struct SerializedRequest *request = (struct SerializedRequest *)malloc(8);
    request->msg = (char *)(handler->receive_buf + handler->have_read);
    request->queue = manager->qp_recvs[wc.qp_num];
    auto ret = manager->workers[wc.imm_data]->put((void *)request);
    printf("received = %d %d\n", result, ret);
    // result += 10;
    // rdma_write(handler, (char *)&result, 4, 10);
    handler->have_read += 4;
  }
}

void poll_server_send(QP_Server_Manager *manager) {
  struct SerializedReply *msg = (struct SerializedReply *)malloc(8);
  while (1) {
    for (auto kv : manager->qp_recvs) {
      if (kv.second->get((void *)msg)) {
        auto handler = manager->data_qp[kv.first];
        rdma_write(handler, msg->msg, msg->size, 10);
      }
    }
  }
}

void poll_client_recv(QP_Client_Manager *manager) {
  while (1) {
    struct ibv_wc wc;
    while (!ibv_poll_cq(manager->recv_cq, 1, &wc))
      ;
    printf("imm=%d, qp_num=%d \n", wc.imm_data, wc.qp_num);
    // return read_msg(handler);
    int result = 0;
    auto handler = manager->data_qp[wc.qp_num];
    memcpy(&result, handler->receive_buf + handler->have_read, 4);
    // lf_queue_push(manager->queue, handler->receive_buf+handler->have_read);
    push_recv_wr(handler);
    printf("result = %d\n", result);
    handler->have_read += 4;
  }
}

bool client_send(rdma_fd *handler, char *local_buf, uint32_t size) {
  rdma_write(handler, local_buf, 4, 0);
  return true;
}

char *client_recv(rdma_fd *handler) {
  // use rdma read to get a msg
  // return read_msg(handler);
  push_recv_wr(handler);
  struct ibv_wc wc;
  while (!ibv_poll_cq(handler->recv_cq, 1, &wc))
    ;
  printf("imm=%d, qp_num=%d \n", wc.imm_data, wc.qp_num);
  int result = 0;
  memcpy(&result, handler->receive_buf + handler->have_read, 4);
  // lf_queue_push(manager->queue, handler->receive_buf+handler->have_read);
  push_recv_wr(handler);
  printf("result = %d\n", result);
  handler->have_read += 4;
}
