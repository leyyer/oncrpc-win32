#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <rpc/rpc.h>
#include "nfs.h"

/* Default timeout can be changed using reqp_control() */
static struct timeval TIMEOUT = { 25, 0 };
#define NOT_IMPLEMENT() fprintf(stderr, "%s:\tnot implemented\n", __FUNCTION__)

int
nfs3_null_3(void *argp, char *res, void (**f)(void *))
{
	*res = 0;
	return 0;
}

static int
GetFileAttr(const char *name, fattr3 *attr)
{
	HANDLE hf;
	WIN32_FIND_DATA fdata;
	DWORDLONG dwLong = MAXDWORD;
	
	if ((hf = FindFirstFile(name, &fdata)) == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "FindFistFile: %s, error %d\n", name, GetLastError());
		return -1;
	}
	FindClose(hf);
	attr->type = (fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? NF3DIR : NF3REG;
	attr->mode = (fdata.dwFileAttributes & FILE_ATTRIBUTE_READONLY)  ? 0644 : 0666;
	attr->size = fdata.nFileSizeHigh * (dwLong + 1) + fdata.nFileSizeLow;
	attr->used = attr->size;

	return 0;
}

int
nfs3_getattr_3(GETATTR3args *argp, GETATTR3res *res, void (**f)(void *))
{
	const char *dp;
	int len;
	
	dp  = argp->object.data.data_val;
	len = argp->object.data.data_len;

	fprintf(stderr, "getattr[%d]: %s\n", len, dp);
	if (GetFileAttr(dp, &res->GETATTR3res_u.resok.obj_attributes) < 0) {
		fprintf(stderr, "getattr failed\n");
		res->status = NFS3ERR_IO;
		return 0;
	}
	res->status = NFS3_OK;
	return 0;
}

int
nfs3_setattr_3(SETATTR3args *argp, SETATTR3res * res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

static void lookup_var_free(void *arg)
{
	LOOKUP3res *res = arg;
	LOOKUP3resok *okp = &res->LOOKUP3res_u.resok;
	
	if (okp->object.data.data_val) {
		free(okp->object.data.data_val);
	}
}

int
nfs3_lookup_3(LOOKUP3args *argp, LOOKUP3res * res, void (**f)(void *))
{
	LOOKUP3resok *okp = &res->LOOKUP3res_u.resok;
	char fileName[1024] = {0};

	_snprintf_s(fileName, sizeof fileName, sizeof fileName -1,
	            "%s/%s", argp->what.dir.data.data_val, argp->what.name);
	if (GetFileAttr(fileName, &okp->obj_attributes.post_op_attr_u.attributes) < 0) {
		res->status = NFS3ERR_IO;
		return 0;
	}
	res->status = NFS3_OK;
	okp->obj_attributes.attributes_follow = TRUE;
	okp->object.data.data_len = strlen(fileName) + 1;
	okp->object.data.data_val = _strdup(fileName);
	okp->dir_attributes.attributes_follow = FALSE;
	*f = lookup_var_free;
	fprintf(stderr, "lookup: %s\n", fileName);
	return (0);
}

int
nfs3_access_3(ACCESS3args *argp, ACCESS3res *res, void (**f)(void *))
{
	nfs_fh3 *fhp = &argp->object;
	
	fprintf(stderr, "access: %s %d\n", fhp->data.data_val, argp->access);
	res->status = NFS3_OK;
	res->ACCESS3res_u.resok.access = ACCESS3_READ | ACCESS3_LOOKUP | ACCESS3_MODIFY | ACCESS3_EXTEND | ACCESS3_DELETE;
	return (0);
}

int
nfs3_readlink_3(READLINK3res *argp, READLINK3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

static void
readvar_free(void *argp)
{
	READ3res *res = argp;
	READ3resok *okp = &res->READ3res_u.resok;
	free(okp->data.data_val);
}

int
nfs3_read_3(READ3args *argp, READ3res *res, void (**f)(void *))
{
	READ3resok *okp = &res->READ3res_u.resok;
	HANDLE hf;
	int bytesRead = 0;
	PLARGE_INTEGER off = (PLARGE_INTEGER)&argp->offset;

	fprintf(stderr, "read: %s\n", argp->file.data.data_val);
	if ((hf = CreateFile(argp->file.data.data_val,
	                     GENERIC_READ,
	                     FILE_SHARE_READ,
	                     NULL,
	                     OPEN_EXISTING,
	                     FILE_ATTRIBUTE_NORMAL,
	                     NULL)) == INVALID_HANDLE_VALUE) {
		res->status = NFS3ERR_IO;
		fprintf(stderr, "read: can't open file %d\n", GetLastError());
		return 0;
	}
	if (SetFilePointerEx(hf, *off, NULL, FILE_BEGIN) == 0) {
		res->status = NFS3ERR_IO;
		CloseHandle(hf);
		return 0;
	}
	okp->data.data_val = calloc(1, argp->count);
	okp->data.data_len = argp->count;
	*f = readvar_free;
	if (ReadFile(hf, okp->data.data_val,
	             argp->count,
	             &okp->count,
	             NULL) == 0) {
		int error = GetLastError();
		if (error == ERROR_HANDLE_EOF) {
			okp->eof = 1;
			goto here;
		}
		res->status = NFS3ERR_IO;
		CloseHandle(hf);
		return 0;
	}
	fprintf(stderr, "reading: %d bytes\n", okp->count);
	okp->eof = okp->count < argp->count ? 1 : 0;
here:
	CloseHandle(hf);
	res->status = NFS3_OK;
	return 0;
}

int
nfs3_write_3(WRITE3args *argp, WRITE3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_create_3(CREATE3res *argp, CREATE3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_mkdir_3(MKDIR3args *argp, MKDIR3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_symlink_3(SYMLINK3args *argp, SYMLINK3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_mknod_3(MKNOD3args *argp, MKNOD3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_remove_3(REMOVE3args *argp, REMOVE3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_rmdir_3(RMDIR3args *argp, RMDIR3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_rename_3(RENAME3args *argp, RENAME3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_link_3(LINK3args *argp, LINK3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

static void
readdirvar_free(void *argp)
{
	READDIR3res *res = argp;
	entry3 *enp, *next;

	enp = res->READDIR3res_u.resok.reply.entries;
	while (enp) {
		next = enp->nextentry;
		free(enp->name);
		free(enp);
		enp = next;
	}
}

int
nfs3_readdir_3(READDIR3args *argp, READDIR3res *res, void (**f)(void *))
{
	char fileName[1024] = {0};
	entry3 **itor, *enp;
	fileid3 xid = 0;
	HANDLE hfn;
	WIN32_FIND_DATA fnd;
	dirlist3 *reply = &res->READDIR3res_u.resok.reply;

	_snprintf_s(fileName, sizeof fileName, sizeof fileName - 1,
	            "%s/*", argp->dir.data.data_val);

	itor = &reply->entries;
	hfn = FindFirstFile(fileName, &fnd);
	if (hfn == INVALID_HANDLE_VALUE) {
		res->status = NFS3ERR_IO;
		return 0;
	}
	enp = calloc(1, sizeof *enp);
	enp->fileid = ++xid;
	enp->name = _strdup(fnd.cFileName);
	*itor = enp;
	itor = &enp->nextentry;
	*f = readdirvar_free;
	
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
	res->status = NFS3_OK;
	return 0;
}

static readdirplus_free(void *argp)
{
	READDIRPLUS3res *res = argp;
	entryplus3 *enp, *next;

	enp = res->READDIRPLUS3res_u.resok.reply.entries;
	while (enp) {
		next = enp->nextentry;
		free(enp->name);
		free(enp);
		enp = next;
	}
}

int
nfs3_readdirplus_3(READDIRPLUS3args *argp, READDIRPLUS3res *res, void (**f)(void *))
{
	HANDLE find;
	WIN32_FIND_DATA data;
	char fileName[1024] = {0};
	dirlistplus3 *reply = &res->READDIRPLUS3res_u.resok.reply;
	entryplus3 *enp, **itor;
	fileid3 xid = 0;

	fprintf(stderr, "readirplus: dircount %u, maxcount %u\n", argp->dircount, argp->maxcount);
	_snprintf_s(fileName, sizeof fileName, sizeof fileName - 1,
	            "%s/*", argp->dir.data.data_val);
	find = FindFirstFile(fileName, &data);
	if (find == INVALID_HANDLE_VALUE) {
		res->status = NFS3ERR_IO;
		fprintf(stderr, "readdir+: failed\n");
		goto end;
	}
	res->status = NFS3_OK;
	fprintf(stderr,"readdir+: %s\n", data.cFileName);
	itor = &reply->entries;
	enp = calloc(1, sizeof *enp);
	enp->name = _strdup(data.cFileName);
	enp->fileid = ++xid;
	*itor = enp;
	itor = &enp->nextentry;
	*f = readdirplus_free;
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
	return 0;
}

int
nfs3_fsstat_3(FSSTAT3args *argp, FSSTAT3res *res, void (**f)(void *))
{
	const char *fn;

	fn = argp->fsroot.data.data_val;
	if (GetDiskFreeSpaceEx(fn,
	                       (PULARGE_INTEGER)&res->FSSTAT3res_u.resok.abytes,
	                       (PULARGE_INTEGER)&res->FSSTAT3res_u.resok.tbytes,
	                       (PULARGE_INTEGER)&res->FSSTAT3res_u.resok.fbytes)) { /* ok */
		res->status = NFS3_OK;
	} else { /* failed */
		res->status = NFS3ERR_NOTSUPP;
		fprintf(stderr, "fsstat: error_code %d\n", GetLastError());
	}
	return (0);
}

int
nfs3_fsinfo_3(FSINFO3args *argp, FSINFO3res *res, void (**f)(void *))
{
	nfs_fh3 *root;

	root = &argp->fsroot;
	fprintf(stderr, "%s[%d]: %s\n", __FUNCTION__, root->data.data_len, root->data.data_val);
	res->status = NFS3_OK;
	res->FSINFO3res_u.resok.obj_attributes.attributes_follow = FALSE;
	res->FSINFO3res_u.resok.rtmax  = 32768;
	res->FSINFO3res_u.resok.rtpref = 32768;
	res->FSINFO3res_u.resok.rtmult = 4096;
	res->FSINFO3res_u.resok.wtmax  = 32768;
	res->FSINFO3res_u.resok.wtpref = 32768;
	res->FSINFO3res_u.resok.wtpref = 4096;
	res->FSINFO3res_u.resok.dtpref = 4096;
	res->FSINFO3res_u.resok.maxfilesize = 2048i64*1024*1024*1024LL;
	res->FSINFO3res_u.resok.time_delta.seconds = 1;
	res->FSINFO3res_u.resok.properties = FSF3_CANSETTIME;
	return 0;
}

int
nfs3_pathconf_3(PATHCONF3args *argp, PATHCONF3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfs3_commit_3(COMMIT3args *argp, COMMIT3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfsacl3_null_3(void *argp, char *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

int
nfsacl3_getacl_3(GETACL3args *argp, GETACL3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return (0);
}

int
nfsacl3_setacl_3(SETACL3args *argp, SETACL3res *res, void (**f)(void *))
{
	NOT_IMPLEMENT();
	return 0;
}

