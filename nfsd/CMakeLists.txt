set(NFSD_SRCS
	nfs_funcs.c
	nfs_svc.c
	nfs_xdr.c)
add_executable(nfsd ${NFSD_SRCS})
target_link_libraries(nfsd rpcsvc)
install(TARGETS nfsd DESTINATION "bin")
