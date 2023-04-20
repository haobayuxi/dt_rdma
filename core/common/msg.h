#include <vector>
#pragma once

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

struct SerializedBuff {
  char* msg;
  Msg_Queue* queue;
};

struct Msg {
  int test;
  MsgType type;
  std::vector<int> read_set;
  std::vector<int> write_set;
};