set (rpc_source
     rpc.c)

add_library (rpc STATIC ${rpc_source})

target_link_libraries (rpc lib config storage)