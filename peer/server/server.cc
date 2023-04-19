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

void push(lf_queue * queue) {
  int i = 0;
  while (1) {
    lf_queue_push(queue,&i);
    i++;
    sleep(1);
  }
}


int main(int argc, char *argv[]) {
   lf_queue * queue = (lf_queue *)malloc(sizeof(lf_queue));
  auto ret = lf_queue_init(queue, 0, 4, 1024 * 1024 * 8);
  printf("ret init = %d\n",ret);
  // auto manager = new QP_Server_Manager(10001, queue);
  // std::thread(push, queue);
  int i = 3;
  ret = lf_queue_push(queue,&i);
  printf("ret push = %d\n",ret);
  // poll_server_recv(manager);
  void * result = malloc(4);
  while(1) { 
    if (lf_queue_pop(queue, result) == 0){
      printf("result = %d\n", result);
    }
    sleep(1);
    }
  // for (;;) {
    // server_recv(manager);
    // printf("get a msg = %s\n", buf);
    // count++;
    // char *response = gen_test_string(msg_len, count);
    // server_send(handler, response, msg_len);
    // free(buf);
    // free(response);
  // }

  return 0;
  
}#include "server.h"

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

void push(lf_queue * queue) {
  int i = 0;
  while (1) {
    lf_queue_push(queue,&i);
    i++;
    sleep(1);
  }
}


int main(int argc, char *argv[]) {
   lf_queue * queue = (lf_queue *)malloc(sizeof(lf_queue));
  auto ret = lf_queue_init(queue, 0, 4, 1024 * 1024 * 8);
  printf("ret init = %d\n",ret);
  // auto manager = new QP_Server_Manager(10001, queue);
  // std::thread(push, queue);
  int i = 3;
  ret = lf_queue_push(queue,&i);
  printf("ret push = %d\n",ret);
  // poll_server_recv(manager);
  void * result = malloc(4);
  while(1) { 
    if (lf_queue_pop(queue, result) == 0){
      printf("result = %d\n", result);
    }
    sleep(1);
    }
  // for (;;) {
    // server_recv(manager);
    // printf("get a msg = %s\n", buf);
    // count++;
    // char *response = gen_test_string(msg_len, count);
    // server_send(handler, response, msg_len);
    // free(buf);
    // free(response);
  // }

  return 0;
  
}