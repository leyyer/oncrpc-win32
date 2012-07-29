set(RPCINFO_SRCS  rpcinfo.c getopt.c)
add_executable(rpcinfo ${RPCINFO_SRCS})
target_link_libraries(rpcinfo rpcsvc)
install(TARGETS rpcinfo DESTINATION "bin")

