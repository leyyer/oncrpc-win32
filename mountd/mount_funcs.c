#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include "mount.h"

/* Default timeout can be changed using reqp_control() */
static struct timeval TIMEOUT = { 25, 0 };

#define NOT_IMPLEMENT() fprintf(stderr, "%s:\tnot implemented\n", __FUNCTION__)
void *
mount1_null_1(void *argp, struct svc_req *reqp)
{
	static char res;

	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

mountres1 *
mount1_mnt_1(dirpath **argp, struct svc_req *reqp)
{
	static mountres1 res;
	
	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

mountlist *
mount1_dump_1(void *argp, struct svc_req *reqp)
{
	static mountlist res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

void *
mount1_umnt_1(dirpath *argp, struct svc_req **reqp)
{
	static char res;
	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

void *
mount1_umntall_1(void *argp, struct svc_req *reqp)
{
	static char res;
	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

exports *
mount1_export_1(void *argp, struct svc_req *reqp)
{
	static exports res;
	
	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

void *
mount3_null_3(void *argp, struct svc_req *svc)
{
	static char res;

	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

mountres3 *
mount3_mnt_3(dirpath *argp, struct svc_req *svc)
{
	static mountres3 res;
	fhandle3 *fp = &res.mountres3_u.mountinfo.fhandle;
	dirpath dp = NULL;
	int len;

	if (fp->fhandle3_val) {
		free(fp->fhandle3_val);
	}
	memset(&res, 0, sizeof res);
	if (argp)
		dp = *argp;
	if (dp == NULL) {
		goto end;
	}
	res.fhs_status = MNT3_OK;
	len = strlen(dp) + 1;
#ifdef WIN32
	/* ignore the leading '/' */
	if (dp[0] == '/') {
		fprintf(stderr, "mount_point: %s\n", dp);
		dp++;
		--len;
	}
	fp->fhandle3_val = _strdup(dp);
#else
	fp->fhandle3_val = strdup(dp);
#endif
	fp->fhandle3_len = len;
	fprintf(stderr, "mounting: %s\n", dp);
end:	
	return (&res);
}

mountlist *
mount3_dump_3(void *argp, struct svc_req *reqp)
{
	static mountlist res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

void *
mount3_umnt_3(dirpath *argp, struct svc_req *reqp)
{
	static char res;

	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

void *
mount3_umntall_3(void *argp, struct svc_req *reqp)
{
	static char res;
	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}

exports *
mount3_export_3(void *argp, struct svc_req *reqp)
{
	static exports res;
	
	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

