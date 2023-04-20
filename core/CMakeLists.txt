

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CONNECTION_SRC
        connection/rdma.cc
        connection/rdma_transport.cc
        )

set(COMMON_SRC
        common/msg_queue.cc
        )

set(SCHEDULER_SRC
        scheduler/corotine_scheduler.cc
        )

set(WORKER_SRC
        worker/worker.cc
        )

add_library(yuxi STATIC
        ${CONNECTION_SRC}
        ${COMMON_SRC}
        ${WORKER_SRC}
        )

set_target_properties(yuxi PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(yuxi ibverbs pthread boost_coroutine boost_context boost_system jsoncpp)