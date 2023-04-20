
#include "server.h"

#include <iostream>
#include <thread>

// #include "common/common.h"
// #include "common/json.h"

using namespace std;

// auto thread_num = config.executor_num + net_handler_thread_num;

// auto thread_arr = new std::thread[thread_num];
// t_id_t t_id = 0;

// for (; t_id < net_handler_thread_num; t_id++) {
//   thread_arr[t_id] = std::thread(run_thread, &param_arr[t_id], tatp_client,
//                                  smallbank_client, tpcc_client);
//   /* Pin thread i to hardware thread i */
//   cpu_set_t cpuset;
//   CPU_ZERO(&cpuset);
//   CPU_SET(t_id, &cpuset);
//   int rc = pthread_setaffinity_np(thread_arr[t_id].native_handle(),
//                                   sizeof(cpu_set_t), &cpuset);
//   if (rc != 0) {
//     RDMA_LOG(WARNING) << "Error calling pthread_setaffinity_np: " << rc;
//   }
// }

// for (; t_id < thread_num; t_id++) {
//   thread_arr[t_id] = std::thread(run_thread, &param_arr[t_id], tatp_client,
//                                  smallbank_client, tpcc_client);
//   /* Pin thread i to hardware thread i */
//   cpu_set_t cpuset;
//   CPU_ZERO(&cpuset);
//   CPU_SET(t_id, &cpuset);
//   int rc = pthread_setaffinity_np(thread_arr[t_id].native_handle(),
//                                   sizeof(cpu_set_t), &cpuset);
//   if (rc != 0) {
//     cout << "Error calling pthread_setaffinity_np: " << rc;
//   }
// }

// for (t_id_t i = 0; i < thread_num; i++) {
//   if (thread_arr[i].joinable()) {
//     thread_arr[i].join();
//   }
// }
// cout << "done" << endl;
// }

int main(int argc, char *argv[]) {
  auto queue = new Msg_Queue(10);
  printf("init queue\n");
  struct Msg t;
  t.test = 100;
  printf("init t\n");
  struct Msg t2;
  t2.test = 10;
  if (queue->put(&t)) {
    printf("put success \n");
  } else {
    printf("put fail");
  }
  // if (queue->get(&t2)) {
  //   printf("get success\n");
  // } else {
  //   printf("get fail");
  // }
  // printf("t2.test = %d\n", t2.test);
  // auto manager = new QP_Server_Manager(10001);

  // while (1) {
  //   poll_server_recv(manager);
  // }

  return 0;
}