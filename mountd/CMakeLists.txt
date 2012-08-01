set(MOUNTD_SRCS
	mount_funcs.c
	mount_svc.c
	mount_xdr.c)
add_executable(mountd ${MOUNTD_SRCS})
target_link_libraries(mountd rpcsvc)
install(TARGETS mountd DESTINATION "bin")
