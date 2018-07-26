set (VTB_NODE_SOURCE main.c)

set (extra_libs lib storage config net rpc core)

add_executable (vtb-node main.c)

target_link_libraries (vtb-node ${extra_libs})