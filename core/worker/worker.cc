#include "worker.h"

Worker::Worker(Msg_Queue *recv, DtxType type) {
  msg_recv = recv;
  dtx_type = type;
}

void Worker::run() {
  void *buff = malloc(8);
  while (msg_recv->get(buff)) {
    // handle msg
    // deserialize
    struct Msg msg;
    int result = 0;
    struct SerializedRequest *propose = (struct SerializedRequest *)buff;
    memcpy(&result, propose->msg, 4);
    printf("receive %d\n", result);
    result += 10;
    struct SerializedReply reply;
    reply.size = 4;
    reply.msg = (char *)&result;
    propose->queue->put((void *)&result);
    // handle_msg((struct Msg_withQPnum *)msg);
  }
}

void Worker::handle_msg(Msg *msg) {
  switch (msg->type) {
    case MsgType::EXECUTE:
      /* code */
      struct Msg *reply = (struct Msg *)malloc(8);
      reply->type = MsgType::COMMIT;
      reply->test = msg->test + 1;

      break;
    case VALIDATE:

      break;
    case ABORT:
      break;
    case COMMIT:
      break;
    default:
      break;
  }
}
void run_worker(Worker *worker) { worker->run(); }