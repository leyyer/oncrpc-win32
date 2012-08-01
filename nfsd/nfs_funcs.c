#include <stdio.h>
#include <rpc/rpc.h>
#include "nfs.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };
#define NOT_IMPLEMENT() fprintf(stderr, "%s: not implemented\n", __FUNCTION__)
void *
nfs3_null_3(void *argp, struct svc_req *svcreq)
{
	static char res;
	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

GETATTR3res *
nfs3_getattr_3(GETATTR3args *argp, struct svc_req *clnt)
{
	static GETATTR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


SETATTR3res *
nfs3_setattr_3(SETATTR3args *argp, struct svc_req *clnt)
{
	static SETATTR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


LOOKUP3res *
nfs3_lookup_3(LOOKUP3args *argp, struct svc_req *clnt)
{
	static LOOKUP3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


ACCESS3res *
nfs3_access_3(ACCESS3res *argp, struct svc_req *clnt)
{
	static ACCESS3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


READLINK3res *
nfs3_readlink_3(READLINK3res *argp, struct svc_req *clnt)
{
	static READLINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


READ3res *
nfs3_read_3(READ3args *argp, struct svc_req *clnt)
{
	static READ3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


WRITE3res *
nfs3_write_3(WRITE3args *argp, struct svc_req *clnt)
{
	static WRITE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

CREATE3res *
nfs3_create_3(CREATE3res *argp, struct svc_req *clnt)
{
	static CREATE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

MKDIR3res *
nfs3_mkdir_3(MKDIR3args *argp, struct svc_req *clnt)
{
	static MKDIR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


SYMLINK3res *
nfs3_symlink_3(SYMLINK3args *argp, struct svc_req *clnt)
{
	static SYMLINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


MKNOD3res *
nfs3_mknod_3(MKNOD3args *argp, struct svc_req *clnt)
{
	static MKNOD3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


REMOVE3res *
nfs3_remove_3(REMOVE3args *argp, struct svc_req *clnt)
{
	static REMOVE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


RMDIR3res *
nfs3_rmdir_3(RMDIR3args *argp, struct svc_req *clnt)
{
	static RMDIR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


RENAME3res *
nfs3_rename_3(RENAME3args *argp, struct svc_req *clnt)
{
	static RENAME3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


LINK3res *
nfs3_link_3(LINK3args *argp, struct svc_req *clnt)
{
	static LINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


READDIR3res *
nfs3_readdir_3(READDIR3args *argp, struct svc_req *clnt)
{
	static READDIR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


READDIRPLUS3res *
nfs3_readdirplus_3(READDIRPLUS3args *argp, struct svc_req *clnt)
{
	static READDIRPLUS3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


FSSTAT3res *
nfs3_fsstat_3(FSSTAT3args *argp, struct svc_req *clnt)
{
	static FSSTAT3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


FSINFO3res *
nfs3_fsinfo_3(FSINFO3args *argp, struct svc_req *req)
{
	static FSINFO3res res;
	nfs_fh3 *root;

	if (argp == NULL)
		goto end;
	root = &argp->fsroot;
	fprintf(stderr, "info: %s [%d]\n", root->data.data_val, root->data.data_len);
	memset(&res, 0, sizeof res);
end:
	return (&res);
}


PATHCONF3res *
nfs3_pathconf_3(PATHCONF3args *argp, struct svc_req *clnt)
{
	static PATHCONF3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


COMMIT3res *
nfs3_commit_3(COMMIT3args *argp, struct svc_req *clnt)
{
	static COMMIT3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


void *
nfsacl3_null_3(void *argp, struct svc_req *clnt)
{
	static char res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return ((void *)&res);
}


GETACL3res *
nfsacl3_getacl_3(GETACL3args *argp, struct svc_req *clnt)
{
	static GETACL3res res;
	
	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}


SETACL3res *
nfsacl3_setacl_3(SETACL3args *argp, struct svc_req *clnt)
{
	static SETACL3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

