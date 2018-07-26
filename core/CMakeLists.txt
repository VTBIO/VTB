set (core_source
     transaction.c
     vtb.c)

add_library (core STATIC ${core_source})

target_link_libraries (core lib config net rpc storage)