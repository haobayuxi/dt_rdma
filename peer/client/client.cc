#include "client.h"

#include <assert.h>
#include <stdio.h>

#include <chrono>
#include <ctime>

using namespace std::chrono;

int client_node_id = 0;
int tcp_port = 10001;
int server_port = 10001;

char *gen_test_string(int len, int times) {
  char *str;
  str = (char *)malloc(len + 1);

  sprintf(str, "send msg %d times", times);
  str[len] = '1';

  return str;
}

int main(int argc, char *argv[]) {
  rdma_fd *handler = (rdma_fd *)malloc(sizeof(rdma_fd));

  // init_client(handler, "192.168.3.72", 10001);
  int sock = client_exchange("192.168.3.72", 10001);
  handler->fd = sock;
  context_info *ib_info = (context_info *)malloc(sizeof(context_info));
  open_device_and_alloc_pd(ib_info);
  get_context_info(handler, ib_info);
  build_rdma_connection(handler);
  srand((unsigned)time(NULL));
  uint32_t buf_size = 20;
  for (int i = 0; i < 10; i++) {
    char *buf = gen_test_string(buf_size, i);
    printf("buf = %d\n", i);
    client_send(handler, (char *)&i, 4);
    free(buf);
    client_recv(handler);
    // printf("get response = %s\n", response);
    // free(response);
  }

  return 0;
}
