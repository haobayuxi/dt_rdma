#include "worker.h"

Worker::Worker(Msg_Queue *recv, DtxType type) {
  msg_recv = recv;
  dtx_type = type;
}

void Worker::run() {
  void *msg = (void *)malloc(8);
  struct SerializedRequest *propose = NULL;

  while (1) {
    if (msg_recv->get(msg)) {
      // handle msg
      // deserialize
      // struct Msg msg;
      propose = *(struct SerializedRequest **)msg;
      char *result = (char *)malloc(4);
      memcpy(result, propose->msg, 4);
      printf("receive %d\n", (int)*result);
      *result += 10;
      struct SerializedReply *reply = (struct SerializedReply *)malloc(8);
      reply->size = 4;
      reply->msg = result;
      // result need to be free

      if (propose->queue->put(&reply)) {
        // printf("put success \n");
      }
      // free(propose);
      propose = NULL;
      // handle_msg((struct Msg_withQPnum *)msg);
    }
    // sleep(1);
  }
}

void Worker::handle_msg(Msg *msg, Msg_Queue *queue) {
  //   switch (msg->type) {
  //     case MsgType::EXECUTE:
  //       /* code */
  //       struct Msg *reply = (struct Msg *)malloc(8);
  //       reply->type = MsgType::COMMIT;
  //       reply->test = msg->test + 1;

  //       break;
  //     case MsgType::VALIDATE:

  //       break;
  //     case MsgType::ABORT:
  //       break;
  //     case MsgType::COMMIT:
  //       break;
  //     default:
  //       break;
  //   }
}
void run_worker(Worker *worker) { worker->run(); }