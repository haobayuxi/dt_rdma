
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SERVER_SOURCE 
# ../connection/rdma_transport.h
# ../connection/rdma_transport.cc
# ../connection/rdma.h
# ../connection/rdma.cc
client.cc)
add_executable(client ${SERVER_SOURCE})
target_link_libraries(client jsoncpp yuxi)
