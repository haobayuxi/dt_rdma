#include "worker.h"

Worker::Worker(Msg_Queue *recv, DtxType type) {
  msg_recv = recv;
  dtx_type = type;
}

void Worker::run() {
  struct SerializedRequest *propose = (struct SerializedRequest *)malloc(8);
  while (1) {
    // if (msg_recv->get((void *)propose)) {
    // handle msg
    // deserialize
    // struct Msg msg;
    // int result = 0;
    // printf("got a message\n");
    // memcpy(&result, propose->msg, 4);
    printf("receive 10\n");
    // result += 10;
    // struct SerializedReply *reply = (struct SerializedReply *)malloc(8);
    // reply->size = 4;
    // reply->msg = (char *)&result;
    // propose->queue->put((void *)reply);
    // delete propose;
    // propose = NULL;
    // handle_msg((struct Msg_withQPnum *)msg);
    // }
    sleep(1);
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