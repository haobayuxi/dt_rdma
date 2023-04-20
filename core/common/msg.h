
enum MsgType {
  EXECUTE = 0,
  VALIDATE,
  COMMIT,
  ABORT,
};

struct SerializedBuff {
  char *msg;
  int qp_num;
};

struct Msg {
  int test;
  MsgType type;
};