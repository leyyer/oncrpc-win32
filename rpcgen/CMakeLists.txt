set(RPCGEN_SRCS
	rpc_main.c
	rpc_hout.c
	rpc_cout.c
	rpc_pars.c
	rpc_scan.c
	rpc_util.c
	rpc_svco.c
	rpc_clnt.c)
add_executable(rpcgen ${RPCGEN_SRCS})
target_link_libraries(rpcgen rpcsvc)
install(TARGETS rpcgen DESTINATION "bin")

