#pragma once
#include <vector>

#include "common/common.h"
#include "msg_queue.h"

enum MsgType {
  EXECUTE = 0,
  VALIDATE,
  COMMIT,
  ABORT,
};

struct SerializedRequest {
  char* msg;
  Msg_Queue* queue;
};

struct SerializedReply {
  char* msg;
  int size;
};

struct Msg {
  int test;
  MsgType type;
  std::vector<int> read_set;
  std::vector<int> write_set;
};