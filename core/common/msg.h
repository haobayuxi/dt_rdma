#pragma once
#include <vector>

#include "msg_queue.h"

enum DtxType {
  OCC = 0,
  Meerkat,
  Yuxi,
};

enum BenchMark {
  Micro = 0,
  Tatp,
};

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