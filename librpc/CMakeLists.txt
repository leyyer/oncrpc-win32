set(RPCSVC_SRCS	CLNT_RAW.c 
	XDR.c 
	CLNT_TCP.c 
	CLNT_UDP.c 
	PMAP_RMT.c 
	RPC_PROT.c 
	SVC_AUTU.c 
	SVC_AUTH.c 
	SVC_RAW.c 
	SVC_RUN.c 
	SVC_TCP.c 
	SVC_UDP.c 
	XDR_MEM.c 
	XDR_REC.c 
	AUTH_NON.c 
	AUTH_UNI.c 
	AUTHUNIX.c 
	BINDRESV.c 
	CLNT_GEN.c 
	CLNT_PER.c 
	CLNT_SIM.c 
	GET_MYAD.c 
	GETRPCEN.c 
	GETRPCPO.c 
	PMAP_CLN.c 
	PMAP_GET.c 
	PMAP_GMA.c 
	PMAP_PRO.c 
	PMAP_PR.c 
	RPC_CALL.c 
	RPC_COMM.c 
	SVC_SIMP.c 
	XDR_ARRA.c 
	XDR_FLOA.c 
	XDR_REFE.c 
	XDR_STDI.c 
	SVC.c 
	BCOPY.c 
	NT.c)

add_library(rpcsvc SHARED ${RPCSVC_SRCS})
target_link_libraries(rpcsvc wsock32)
add_executable(portmap portmap.c)
target_link_libraries(portmap rpcsvc)
install(TARGETS rpcsvc portmap DESTINATION "bin")
