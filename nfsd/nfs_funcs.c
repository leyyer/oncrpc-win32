#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <rpc/rpc.h>
#include "nfs.h"

/* Default timeout can be changed using reqp_control() */
static struct timeval TIMEOUT = { 25, 0 };
#define NOT_IMPLEMENT() fprintf(stderr, "%s:\tnot implemented\n", __FUNCTION__)
void *
nfs3_null_3(void *argp, struct svc_req *svcreq)
{
	static char res;
	res = 0;
	NOT_IMPLEMENT();
	return ((void *)&res);
}
static int GetFileAttr(const char *name, fattr3 *attr)
{
	HANDLE hf;
	WIN32_FIND_DATA fdata;
	DWORDLONG dwLong = MAXDWORD;
	
	if ((hf = FindFirstFile(name, &fdata)) == INVALID_HANDLE_VALUE) {
		return -1;
	}
	FindClose(hf);
	attr->type = (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? NF3DIR : NF3REG;
	attr->mode = (fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY)  ? 0644 : 0666;
	attr->size = fdata.nFileSizeHigh * (dwLong + 1) + fdata.nFileSizeLow;
	attr->used = attr->size;

	return 0;
}


GETATTR3res *
nfs3_getattr_3(GETATTR3args *argp, struct svc_req *reqp)
{
	static GETATTR3res res;
	const char *dp;
	int len;
	
	memset(&res, 0, sizeof res);
	dp  = argp->object.data.data_val;
	len = argp->object.data.data_len;

	fprintf(stderr, "getattr[%d]: %s\n", len, dp);
	if (GetFileAttr(dp, &res.GETATTR3res_u.resok.obj_attributes) < 0) {
		res.status = NFS3ERR_IO;
		return (&res);
	}
	
	res.status = NFS3_OK;

	return (&res);
}

SETATTR3res *
nfs3_setattr_3(SETATTR3args *argp, struct svc_req *reqp)
{
	static SETATTR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

LOOKUP3res *
nfs3_lookup_3(LOOKUP3args *argp, struct svc_req *reqp)
{
	static LOOKUP3res res;
	LOOKUP3resok *okp = &res.LOOKUP3res_u.resok;
	char fileName[1024] = {0};

	if (okp->object.data.data_val)
		free(okp->object.data.data_val);
	
	memset(&res, 0, sizeof res);
	_snprintf_s(fileName, sizeof fileName, sizeof fileName -1,
	            "%s/%s", argp->what.dir.data.data_val, argp->what.name);

	if (GetFileAttr(fileName, &okp->obj_attributes.post_op_attr_u.attributes) < 0) {
		res.status = NFS3ERR_IO;
		return (&res);
	}

	okp->obj_attributes.attributes_follow = TRUE;

	okp->object.data.data_len = strlen(fileName) + 1;
	okp->object.data.data_val = _strdup(fileName);
	okp->dir_attributes.attributes_follow = FALSE;
	fprintf(stderr, "lookup: %s\n", fileName);

	return (&res);
}

ACCESS3res *
nfs3_access_3(ACCESS3args *argp, struct svc_req *reqp)
{
	static ACCESS3res res;
	nfs_fh3 *fhp = &argp->object;
	
	memset(&res, 0, sizeof res);
	fprintf(stderr, "access: %s %d\n", fhp->data.data_val, argp->access);
	res.status = NFS3_OK;
	res.ACCESS3res_u.resok.access = ACCESS3_READ | ACCESS3_LOOKUP | ACCESS3_MODIFY | ACCESS3_EXTEND | ACCESS3_DELETE;
	
	return (&res);
}


READLINK3res *
nfs3_readlink_3(READLINK3res *argp, struct svc_req *reqp)
{
	static READLINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

READ3res *
nfs3_read_3(READ3args *argp, struct svc_req *reqp)
{
	static READ3res res;
	READ3resok *okp = &res.READ3res_u.resok;
	HANDLE hf;
	int bytesRead = 0;
	PLARGE_INTEGER off = (PLARGE_INTEGER)&argp->offset;

	if (okp->data.data_val) {
		free(okp->data.data_val);
	}
	memset(&res, 0, sizeof res);
	fprintf(stderr, "read: %s\n", argp->file.data.data_val);
	if ((hf = CreateFile(argp->file.data.data_val,
	                     GENERIC_READ,
	                     FILE_SHARE_READ,
	                     NULL,
	                     OPEN_EXISTING,
	                     FILE_ATTRIBUTE_NORMAL,
	                     NULL)) == INVALID_HANDLE_VALUE) {
		res.status = NFS3ERR_IO;
		fprintf(stderr, "read: can't open file %d\n", GetLastError());
		return (&res);
	}
	if (SetFilePointerEx(hf, *off, NULL, FILE_BEGIN) == 0) {
		res.status = NFS3ERR_IO;
		CloseHandle(hf);
		return (&res);
	}
	okp->data.data_val = calloc(1, argp->count);
	okp->data.data_len = argp->count;
	if (ReadFile(hf, okp->data.data_val,
	             argp->count,
	             &okp->count,
	             NULL) == 0) {
		int error = GetLastError();
		if (error == ERROR_HANDLE_EOF) {
			okp->eof = 1;
			goto here;
		}
		res.status = NFS3ERR_IO;
		CloseHandle(hf);
		return (&res);
	}
	fprintf(stderr, "reading: %d bytes\n", okp->count);
	okp->eof = okp->count < argp->count ? 1 : 0;
here:
	CloseHandle(hf);
	res.status = NFS3_OK;
	return (&res);
}

WRITE3res *
nfs3_write_3(WRITE3args *argp, struct svc_req *reqp)
{
	static WRITE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

CREATE3res *
nfs3_create_3(CREATE3res *argp, struct svc_req *reqp)
{
	static CREATE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

MKDIR3res *
nfs3_mkdir_3(MKDIR3args *argp, struct svc_req *reqp)
{
	static MKDIR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

SYMLINK3res *
nfs3_symlink_3(SYMLINK3args *argp, struct svc_req *reqp)
{
	static SYMLINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

MKNOD3res *
nfs3_mknod_3(MKNOD3args *argp, struct svc_req *reqp)
{
	static MKNOD3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

REMOVE3res *
nfs3_remove_3(REMOVE3args *argp, struct svc_req *reqp)
{
	static REMOVE3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

RMDIR3res *
nfs3_rmdir_3(RMDIR3args *argp, struct svc_req *reqp)
{
	static RMDIR3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

RENAME3res *
nfs3_rename_3(RENAME3args *argp, struct svc_req *reqp)
{
	static RENAME3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

LINK3res *
nfs3_link_3(LINK3args *argp, struct svc_req *reqp)
{
	static LINK3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

READDIR3res *
nfs3_readdir_3(READDIR3args *argp, struct svc_req *reqp)
{
	static READDIR3res res;
	char fileName[1024] = {0};
	entry3 **itor, *enp, *next;
	fileid3 xid = 0;
	HANDLE hfn;
	WIN32_FIND_DATA fnd;
	dirlist3 *reply = &res.READDIR3res_u.resok.reply;

	enp = reply->entries;
	while (enp) {
		next = enp->nextentry;
		free(enp->name);
		free(enp);
		enp = next;
	}
	memset(&res, 0, sizeof res);
	_snprintf_s(fileName, sizeof fileName, sizeof fileName - 1,
	            "%s/*", argp->dir.data.data_val);

	itor = &reply->entries;
	hfn = FindFirstFile(fileName, &fnd);
	if (hfn == INVALID_HANDLE_VALUE) {
		res.status = NFS3ERR_IO;
		return (&res);
	}
	enp = calloc(1, sizeof *enp);
	enp->fileid = ++xid;
	enp->name = _strdup(fnd.cFileName);
	*itor = enp;
	itor = &enp->nextentry;
	
	fprintf(stderr, "readdir: %s\n", enp->name);
	while (FindNextFile(hfn, &fnd)) {
		enp = calloc(1, sizeof *enp);
		enp->fileid = ++xid;
		enp->name = _strdup(fnd.cFileName);
		*itor = enp;
		itor = &enp->nextentry;
		fprintf(stderr, "readdir: %s\n", enp->name);
	}
	FindClose(hfn);
	reply->eof = TRUE;
	res.status = NFS3_OK;
	return (&res);
}

READDIRPLUS3res *
nfs3_readdirplus_3(READDIRPLUS3args *argp, struct svc_req *reqp)
{
	static READDIRPLUS3res res;
	HANDLE find;
	WIN32_FIND_DATA data;
	char fileName[1024] = {0};
	dirlistplus3 *reply = &res.READDIRPLUS3res_u.resok.reply;
	entryplus3 *enp, *next, **itor;
	fileid3 xid = 0;

	enp = reply->entries;
	while (enp) {
		next = enp->nextentry;
		free(enp->name);
		free(enp);
		enp = next;
	}

	memset(&res, 0, sizeof res);
	fprintf(stderr, "readirplus: dircount %u, maxcount %u\n", argp->dircount, argp->maxcount);
	_snprintf_s(fileName, sizeof fileName, sizeof fileName - 1,
	            "%s/*", argp->dir.data.data_val);
	find = FindFirstFile(fileName, &data);
	if (find == INVALID_HANDLE_VALUE) {
		res.status = NFS3ERR_IO;
		fprintf(stderr, "readdir+: failed\n");
		goto end;
	}
	res.status = NFS3_OK;
	fprintf(stderr,"readdir+: %s\n", data.cFileName);
	itor = &reply->entries;
	enp = calloc(1, sizeof *enp);
	enp->name = _strdup(data.cFileName);
	enp->fileid = ++xid;
	*itor = enp;
	itor = &enp->nextentry;
	while (FindNextFile(find, &data)) {
		fprintf(stderr, "readdir+: %s\n", data.cFileName);
		enp = calloc(1, sizeof *enp);
		enp->name = _strdup(data.cFileName);
		enp->fileid = ++xid;
		*itor = enp;
		itor = &enp->nextentry;
	}
	reply->eof = TRUE;
	FindClose(find);
end:
	return (&res);
}

FSSTAT3res *
nfs3_fsstat_3(FSSTAT3args *argp, struct svc_req *reqp)
{
	static FSSTAT3res res;
	const char *fn;

	memset(&res, 0, sizeof res);
	fn = argp->fsroot.data.data_val;
	if (GetDiskFreeSpaceEx(fn,
	                       (PULARGE_INTEGER)&res.FSSTAT3res_u.resok.abytes,
	                       (PULARGE_INTEGER)&res.FSSTAT3res_u.resok.tbytes,
	                       (PULARGE_INTEGER)&res.FSSTAT3res_u.resok.fbytes)) { /* ok */
		res.status = NFS3_OK;
	} else { /* failed */
		res.status = NFS3ERR_NOTSUPP;
		fprintf(stderr, "fsstat: error_code %d\n", GetLastError());
	}
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
	fprintf(stderr, "%s[%d]: %s\n", __FUNCTION__, root->data.data_len, root->data.data_val);
	memset(&res, 0, sizeof res);
	res.status = NFS3_OK;
	res.FSINFO3res_u.resok.obj_attributes.attributes_follow = FALSE;
	res.FSINFO3res_u.resok.rtmax  = 32768;
	res.FSINFO3res_u.resok.rtpref = 32768;
	res.FSINFO3res_u.resok.rtmult = 4096;
	res.FSINFO3res_u.resok.wtmax  = 32768;
	res.FSINFO3res_u.resok.wtpref = 32768;
	res.FSINFO3res_u.resok.wtpref = 4096;
	res.FSINFO3res_u.resok.dtpref = 4096;
	res.FSINFO3res_u.resok.maxfilesize = 2048i64*1024*1024*1024LL;
	res.FSINFO3res_u.resok.time_delta.seconds = 1;
	res.FSINFO3res_u.resok.properties = FSF3_CANSETTIME;
end:
	return (&res);
}

PATHCONF3res *
nfs3_pathconf_3(PATHCONF3args *argp, struct svc_req *reqp)
{
	static PATHCONF3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

COMMIT3res *
nfs3_commit_3(COMMIT3args *argp, struct svc_req *reqp)
{
	static COMMIT3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

void *
nfsacl3_null_3(void *argp, struct svc_req *reqp)
{
	static char res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return ((void *)&res);
}

GETACL3res *
nfsacl3_getacl_3(GETACL3args *argp, struct svc_req *reqp)
{
	static GETACL3res res;
	
	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

SETACL3res *
nfsacl3_setacl_3(SETACL3args *argp, struct svc_req *reqp)
{
	static SETACL3res res;

	memset(&res, 0, sizeof res);
	NOT_IMPLEMENT();
	return (&res);
}

