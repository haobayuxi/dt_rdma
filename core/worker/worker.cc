#include "worker.h"

Worker::Worker(Msg_Queue *recv, DtxType type) {
  msg_recv = recv;
  dtx_type = type;
}

void Worker::run() {
  struct SerializedRequest *propose = (struct SerializedRequest *)malloc(8);
  printf("worker start\n");
  while (msg_recv->get((void *)propose)) {
    // handle msg
    // deserialize
    struct Msg msg;
    int result = 0;

    memcpy(&result, propose->msg, 4);
    printf("receive %d\n", result);
    result += 10;
    struct SerializedReply reply;
    reply.size = 4;
    reply.msg = (char *)&result;
    propose->queue->put((void *)&result);
    delete propose;
    propose = NULL;
    // handle_msg((struct Msg_withQPnum *)msg);
  }
}

void Worker::handle_msg(Msg *msg) {
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