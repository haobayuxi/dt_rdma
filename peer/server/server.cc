
#include "server.h"

#include <iostream>
#include <thread>

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
  int thread_num = 1;
  std::unordered_map<int, Msg_Queue *> worker_queues;
  for (int i = 0; i < thread_num; i++) {
    auto queue = new Msg_Queue(100);
    worker_queues.insert(std::make_pair(i, queue));
    auto worker = new Worker(queue, DtxType::Meerkat);
    std::thread(run_worker, &worker);
    // run_worker(worker);
  }
  // auto manager = new QP_Server_Manager(10001, worker_queues);
  // std::thread(poll_server_send, manager);
  // // std::thread();
  // poll_server_recv(manager);
  while (1) {
    sleep(1);
  }

  return 0;
}