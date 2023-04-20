#include "worker.h"

Worker::Worker() {}

void Worker::run() {
  void *msg = malloc(8);
  while (msg_recv->get(msg)) {
    // handle msg
    // handle_msg((struct Msg_withQPnum *)msg);
    delete msg;
  }
}

// void Worker::handle_msg(Msg_with_QPnum *msg) {
//   switch (msg->msg->type) {
//     case EXECUTE:
//       /* code */
//       struct Msg *reply = (struct Msg *)malloc(8);
//       reply->type = MsgType::COMMIT;
//       reply->test = msg->msg->test + 1;

//       send->put((void *));
//       break;
//     case VALIDATE:
//       break;
//     case ABORT:
//       break;
//     case COMMIT:
//       break;
//     default:
//       break;
//   }
// }
void run_worker(Worker *worker) { worker->run(); }