#include <stdio.h>
#include <rpc/rpc.h>
#include <rpc/pmap_cln.h>
#include "mount.h"

static void
mount_program_1(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		dirpath mount1_mnt_1_arg;
		dirpath mount1_umnt_1_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case MOUNT1_NULL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) mount1_null_1;
		break;
	case MOUNT1_MNT:
		xdr_argument = xdr_dirpath;
		xdr_result = xdr_mountres1;
		local = (char *(*)()) mount1_mnt_1;
		break;
	case MOUNT1_DUMP:
		xdr_argument = xdr_void;
		xdr_result = xdr_mountlist;
		local = (char *(*)()) mount1_dump_1;
		break;
	case MOUNT1_UMNT:
		xdr_argument = xdr_dirpath;
		xdr_result = xdr_void;
		local = (char *(*)()) mount1_umnt_1;
		break;
	case MOUNT1_UMNTALL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) mount1_umntall_1;
		break;
	case MOUNT1_EXPORT:
		xdr_argument = xdr_void;
		xdr_result = xdr_exports;
		local = (char *(*)()) mount1_export_1;
		break;
	default:
		svcerr_noproc(transp);
		return;
	}
	bzero((char *)&argument, sizeof(argument));
	if (!svc_getargs(transp, xdr_argument, &argument)) {
		svcerr_decode(transp);
		return;
	}

	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
}

static void
mount_program_3(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		dirpath mount3_mnt_3_arg;
		dirpath mount3_umnt_3_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case MOUNT3_NULL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) mount3_null_3;
		break;
	case MOUNT3_MNT:
		xdr_argument = xdr_dirpath;
		xdr_result = xdr_mountres3;
		local = (char *(*)()) mount3_mnt_3;
		break;
	case MOUNT3_DUMP:
		xdr_argument = xdr_void;
		xdr_result = xdr_mountlist;
		local = (char *(*)()) mount3_dump_3;
		break;
	case MOUNT3_UMNT:
		xdr_argument = xdr_dirpath;
		xdr_result = xdr_void;
		local = (char *(*)()) mount3_umnt_3;
		break;
	case MOUNT3_UMNTALL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) mount3_umntall_3;
		break;
	case MOUNT3_EXPORT:
		xdr_argument = xdr_void;
		xdr_result = xdr_exports;
		local = (char *(*)()) mount3_export_3;
		break;
	default:
		svcerr_noproc(transp);
		return;
	}
	memset(&argument, 0, sizeof argument);
	if (!svc_getargs(transp, xdr_argument, &argument)) {
		svcerr_decode(transp);
		return;
	}

	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	SVCXPRT *transp;
	int error = 0;

#ifdef WIN32
	rpc_nt_init();
#endif

	pmap_unset(MOUNT_PROGRAM, MOUNT_V1);
	pmap_unset(MOUNT_PROGRAM, MOUNT_V3);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf(stderr, "cannot create udp service.\n");
		error = -1;
		goto end;
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V1, mount_program_1, IPPROTO_UDP)) {
		fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V1, udp).\n");
		error = -2;
		goto end;
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V3, mount_program_3, IPPROTO_UDP)) {
		fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V3, udp).\n");
		error = -3;
		goto end;
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf(stderr, "cannot create tcp service.\n");
		error = -4;
		goto end;
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V1, mount_program_1, IPPROTO_TCP)) {
		fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V1, tcp).\n");
		error = -5;
		goto end;
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V3, mount_program_3, IPPROTO_TCP)) {
		fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V3, tcp).\n");
		error = -6;
		goto end;
	}
	svc_run();
	fprintf(stderr, "svc_run returned\n");
end:
#ifdef WIN32
	rpc_nt_exit();
#endif
	return error;
	
}
