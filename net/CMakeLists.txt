set (net_source
     net.c)

add_library (net STATIC ${net_source})

target_link_libraries (net lib config storage)