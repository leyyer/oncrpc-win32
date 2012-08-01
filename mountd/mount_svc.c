#include <stdio.h>
#include <rpc/rpc.h>
#include <rpc/pmap_cln.h>
#include "mount.h"

static void mount_program_1();
static void mount_program_3();

void main()
{
	SVCXPRT *transp;

#ifdef WIN32
	rpc_nt_init();
#endif

	(void)pmap_unset(MOUNT_PROGRAM, MOUNT_V1);
	(void)pmap_unset(MOUNT_PROGRAM, MOUNT_V3);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create udp service.\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V1, mount_program_1, IPPROTO_UDP)) {
		(void)fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V1, udp).\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V3, mount_program_3, IPPROTO_UDP)) {
		(void)fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V3, udp).\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create tcp service.\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V1, mount_program_1, IPPROTO_TCP)) {
		(void)fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V1, tcp).\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
	if (!svc_register(transp, MOUNT_PROGRAM, MOUNT_V3, mount_program_3, IPPROTO_TCP)) {
		(void)fprintf(stderr, "unable to register (MOUNT_PROGRAM, MOUNT_V3, tcp).\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
	svc_run();
	(void)fprintf(stderr, "svc_run returned\n");
#ifdef WIN32
	rpc_nt_exit();
#endif
	exit(1);
}

#ifdef MULTITHREAD
struct call_params {
	struct svc_req *rqstp;
	SVCXPRT        *transp;
	void           *arg;
	char *(*local)();
	bool_t (*xdr_argument)(), (*xdr_result)();
};
static void mount_program_1_a ();
static void mount_program_3_a ();
#endif

static void
mount_program_1(rqstp, transp)
	struct svc_req *rqstp;
	SVCXPRT *transp;
{
	union {
		dirpath mount1_mnt_1_arg;
		dirpath mount1_umnt_1_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();


#ifdef MULTITHREAD
	DWORD TID = 0;
	HANDLE threadHandle = NULL;
	struct call_params	*params;
#endif
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

#ifdef MULTITHREAD
	params = (struct call_params*) malloc (sizeof(struct call_params));

	params->rqstp = (struct svc_req*) malloc (sizeof(struct svc_req));
	bcopy(rqstp, params->rqstp, sizeof(struct svc_req));

	params->transp = transp;

	params->arg = malloc (sizeof(argument));
	bcopy(&argument, params->arg, sizeof(argument));

	params->local = local;

	params->xdr_argument = xdr_argument;
	params->xdr_result = xdr_result;

	threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mount_program_1_a, params, 0, &TID);
	if (!threadHandle)
		mount_program_1_a(&params);
}

static void
mount_program_1_a(params)
struct call_params *params;
{
	struct svc_req *rqstp;
	SVCXPRT *transp;
	void *argument;
	void (*destroy_proc)();

	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();


	argument = params->arg;
	rqstp = params->rqstp;
	transp = params->transp;
	xdr_argument = params->xdr_argument;
	xdr_result = params->xdr_result;
	local = params->local;
	destroy_proc = transp->xp_ops->xp_destroy;
	transp->xp_ops->xp_destroy = xprt_unregister;
#endif

	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
#ifdef MULTITHREAD
	free(params->rqstp);
	free(params);
#endif
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
#ifdef MULTITHREAD
	free(argument);
	transp->xp_ops->xp_destroy = destroy_proc;
#endif
}


static void
mount_program_3(rqstp, transp)
	struct svc_req *rqstp;
	SVCXPRT *transp;
{
	union {
		dirpath mount3_mnt_3_arg;
		dirpath mount3_umnt_3_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	fprintf(stderr, "mount_program dispatched\n");
#ifdef MULTITHREAD
	DWORD TID = 0;
	HANDLE threadHandle = NULL;
	struct call_params	*params;
#endif
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

#ifdef MULTITHREAD
	params = (struct call_params*) malloc (sizeof(struct call_params));

	params->rqstp = (struct svc_req*) malloc (sizeof(struct svc_req));
	bcopy(rqstp, params->rqstp, sizeof(struct svc_req));

	params->transp = transp;

	params->arg = malloc (sizeof(argument));
	bcopy(&argument, params->arg, sizeof(argument));

	params->local = local;

	params->xdr_argument = xdr_argument;
	params->xdr_result = xdr_result;

	threadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mount_program_3_a, params, 0, &TID);
	if (!threadHandle)
		mount_program_3_a(&params);
}

static void
mount_program_3_a(params)
struct call_params *params;
{
	struct svc_req *rqstp;
	SVCXPRT *transp;
	void *argument;
	void (*destroy_proc)();

	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();


	argument = params->arg;
	rqstp = params->rqstp;
	transp = params->transp;
	xdr_argument = params->xdr_argument;
	xdr_result = params->xdr_result;
	local = params->local;
	destroy_proc = transp->xp_ops->xp_destroy;
	transp->xp_ops->xp_destroy = xprt_unregister;
#endif

	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
#ifdef MULTITHREAD
	free(params->rqstp);
	free(params);
#endif
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
#ifdef WIN32
		rpc_nt_exit();
#endif
		exit(1);
	}
#ifdef MULTITHREAD
	free(argument);
	transp->xp_ops->xp_destroy = destroy_proc;
#endif
}

