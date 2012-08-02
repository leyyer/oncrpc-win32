#include <stdio.h>
#include <rpc/rpc.h>
#include <rpc/pmap_cln.h>
#include "nfs.h"

static void
nfs_program_3(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		GETATTR3args nfs3_getattr_3_arg;
		SETATTR3args nfs3_setattr_3_arg;
		LOOKUP3args nfs3_lookup_3_arg;
		ACCESS3args nfs3_access_3_arg;
		READLINK3args nfs3_readlink_3_arg;
		READ3args nfs3_read_3_arg;
		WRITE3args nfs3_write_3_arg;
		CREATE3args nfs3_create_3_arg;
		MKDIR3args nfs3_mkdir_3_arg;
		SYMLINK3args nfs3_symlink_3_arg;
		MKNOD3args nfs3_mknod_3_arg;
		REMOVE3args nfs3_remove_3_arg;
		RMDIR3args nfs3_rmdir_3_arg;
		RENAME3args nfs3_rename_3_arg;
		LINK3args nfs3_link_3_arg;
		READDIR3args nfs3_readdir_3_arg;
		READDIRPLUS3args nfs3_readdirplus_3_arg;
		FSSTAT3args nfs3_fsstat_3_arg;
		FSINFO3args nfs3_fsinfo_3_arg;
		PATHCONF3args nfs3_pathconf_3_arg;
		COMMIT3args nfs3_commit_3_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case NFS3_NULL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) nfs3_null_3;
		break;

	case NFS3_GETATTR:
		xdr_argument = xdr_GETATTR3args;
		xdr_result = xdr_GETATTR3res;
		local = (char *(*)()) nfs3_getattr_3;
		break;

	case NFS3_SETATTR:
		xdr_argument = xdr_SETATTR3args;
		xdr_result = xdr_SETATTR3res;
		local = (char *(*)()) nfs3_setattr_3;
		break;

	case NFS3_LOOKUP:
		xdr_argument = xdr_LOOKUP3args;
		xdr_result = xdr_LOOKUP3res;
		local = (char *(*)()) nfs3_lookup_3;
		break;

	case NFS3_ACCESS:
		xdr_argument = xdr_ACCESS3args;
		xdr_result = xdr_ACCESS3res;
		local = (char *(*)()) nfs3_access_3;
		break;

	case NFS3_READLINK:
		xdr_argument = xdr_READLINK3args;
		xdr_result = xdr_READLINK3res;
		local = (char *(*)()) nfs3_readlink_3;
		break;

	case NFS3_READ:
		xdr_argument = xdr_READ3args;
		xdr_result = xdr_READ3res;
		local = (char *(*)()) nfs3_read_3;
		break;

	case NFS3_WRITE:
		xdr_argument = xdr_WRITE3args;
		xdr_result = xdr_WRITE3res;
		local = (char *(*)()) nfs3_write_3;
		break;

	case NFS3_CREATE:
		xdr_argument = xdr_CREATE3args;
		xdr_result = xdr_CREATE3res;
		local = (char *(*)()) nfs3_create_3;
		break;

	case NFS3_MKDIR:
		xdr_argument = xdr_MKDIR3args;
		xdr_result = xdr_MKDIR3res;
		local = (char *(*)()) nfs3_mkdir_3;
		break;

	case NFS3_SYMLINK:
		xdr_argument = xdr_SYMLINK3args;
		xdr_result = xdr_SYMLINK3res;
		local = (char *(*)()) nfs3_symlink_3;
		break;

	case NFS3_MKNOD:
		xdr_argument = xdr_MKNOD3args;
		xdr_result = xdr_MKNOD3res;
		local = (char *(*)()) nfs3_mknod_3;
		break;

	case NFS3_REMOVE:
		xdr_argument = xdr_REMOVE3args;
		xdr_result = xdr_REMOVE3res;
		local = (char *(*)()) nfs3_remove_3;
		break;

	case NFS3_RMDIR:
		xdr_argument = xdr_RMDIR3args;
		xdr_result = xdr_RMDIR3res;
		local = (char *(*)()) nfs3_rmdir_3;
		break;

	case NFS3_RENAME:
		xdr_argument = xdr_RENAME3args;
		xdr_result = xdr_RENAME3res;
		local = (char *(*)()) nfs3_rename_3;
		break;

	case NFS3_LINK:
		xdr_argument = xdr_LINK3args;
		xdr_result = xdr_LINK3res;
		local = (char *(*)()) nfs3_link_3;
		break;

	case NFS3_READDIR:
		xdr_argument = xdr_READDIR3args;
		xdr_result = xdr_READDIR3res;
		local = (char *(*)()) nfs3_readdir_3;
		break;

	case NFS3_READDIRPLUS:
		xdr_argument = xdr_READDIRPLUS3args;
		xdr_result = xdr_READDIRPLUS3res;
		local = (char *(*)()) nfs3_readdirplus_3;
		break;

	case NFS3_FSSTAT:
		xdr_argument = xdr_FSSTAT3args;
		xdr_result = xdr_FSSTAT3res;
		local = (char *(*)()) nfs3_fsstat_3;
		break;

	case NFS3_FSINFO:
		xdr_argument = xdr_FSINFO3args;
		xdr_result = xdr_FSINFO3res;
		local = (char *(*)()) nfs3_fsinfo_3;
		break;

	case NFS3_PATHCONF:
		xdr_argument = xdr_PATHCONF3args;
		xdr_result = xdr_PATHCONF3res;
		local = (char *(*)()) nfs3_pathconf_3;
		break;

	case NFS3_COMMIT:
		xdr_argument = xdr_COMMIT3args;
		xdr_result = xdr_COMMIT3res;
		local = (char *(*)()) nfs3_commit_3;
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
nfsacl_program_3(struct svc_req *rqstp, SVCXPRT *transp)
{
	union {
		GETACL3args nfsacl3_getacl_3_arg;
		SETACL3args nfsacl3_setacl_3_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case NFSACL3_NULL:
		xdr_argument = xdr_void;
		xdr_result = xdr_void;
		local = (char *(*)()) nfsacl3_null_3;
		break;

	case NFSACL3_GETACL:
		xdr_argument = xdr_GETACL3args;
		xdr_result = xdr_GETACL3res;
		local = (char *(*)()) nfsacl3_getacl_3;
		break;

	case NFSACL3_SETACL:
		xdr_argument = xdr_SETACL3args;
		xdr_result = xdr_SETACL3res;
		local = (char *(*)()) nfsacl3_setacl_3;
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

int main(int argc, char *argv[])
{
	SVCXPRT *transp;
	int error = 0;

#ifdef WIN32
	rpc_nt_init();
#endif

	pmap_unset(NFS_PROGRAM, NFS_V3);
	pmap_unset(NFSACL_PROGRAM, NFSACL_V3);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf(stderr, "cannot create udp service.\n");
		error = -1;
		goto end;
	}
	if (!svc_register(transp, NFS_PROGRAM, NFS_V3, nfs_program_3, IPPROTO_UDP)) {
		fprintf(stderr, "unable to register (NFS_PROGRAM, NFS_V3, udp).\n");
		error = -2;
		goto end;
	}
	if (!svc_register(transp, NFSACL_PROGRAM, NFSACL_V3, nfsacl_program_3, IPPROTO_UDP)) {
		fprintf(stderr, "unable to register (NFSACL_PROGRAM, NFSACL_V3, udp).\n");
		error = -3;
		goto end;
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf(stderr, "cannot create tcp service.\n");
		error = -4;
		goto end;
	}
	if (!svc_register(transp, NFS_PROGRAM, NFS_V3, nfs_program_3, IPPROTO_TCP)) {
		fprintf(stderr, "unable to register (NFS_PROGRAM, NFS_V3, tcp).\n");
		error = -5;
		goto end;
	}
	if (!svc_register(transp, NFSACL_PROGRAM, NFSACL_V3, nfsacl_program_3, IPPROTO_TCP)) {
		fprintf(stderr, "unable to register (NFSACL_PROGRAM, NFSACL_V3, tcp).\n");
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
