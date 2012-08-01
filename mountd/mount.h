#include <rpc/types.h>
#define MNTPATHLEN 1024
#define MNTNAMLEN 255
#define FHSIZE3 64

typedef struct {
	u_int fhandle3_len;
	char *fhandle3_val;
} fhandle3;
#ifdef __cplusplus
extern "C" {
bool_t xdr_fhandle3(...);
}
#else
bool_t xdr_fhandle3();
#endif


typedef char *dirpath;
#ifdef __cplusplus
extern "C" {
bool_t xdr_dirpath(...);
}
#else
bool_t xdr_dirpath();
#endif


typedef char *name;
#ifdef __cplusplus
extern "C" {
bool_t xdr_name(...);
}
#else
bool_t xdr_name();
#endif


enum mountstat3 {
	MNT3_OK = 0,
	MNT3ERR_PERM = 1,
	MNT3ERR_NOENT = 2,
	MNT3ERR_IO = 5,
	MNT3ERR_ACCES = 13,
	MNT3ERR_NOTDIR = 20,
	MNT3ERR_INVAL = 22,
	MNT3ERR_NAMETOOLONG = 63,
	MNT3ERR_NOTSUPP = 10004,
	MNT3ERR_SERVERFAULT = 10006,
};
typedef enum mountstat3 mountstat3;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountstat3(...);
}
#else
bool_t xdr_mountstat3();
#endif


typedef struct mountbody *mountlist;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountlist(...);
}
#else
bool_t xdr_mountlist();
#endif


struct mountbody {
	name ml_hostname;
	dirpath ml_directory;
	mountlist ml_next;
};
typedef struct mountbody mountbody;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountbody(...);
}
#else
bool_t xdr_mountbody();
#endif


typedef struct groupnode *groups;
#ifdef __cplusplus
extern "C" {
bool_t xdr_groups(...);
}
#else
bool_t xdr_groups();
#endif


struct groupnode {
	name gr_name;
	groups gr_next;
};
typedef struct groupnode groupnode;
#ifdef __cplusplus
extern "C" {
bool_t xdr_groupnode(...);
}
#else
bool_t xdr_groupnode();
#endif


typedef struct exportnode *exports;
#ifdef __cplusplus
extern "C" {
bool_t xdr_exports(...);
}
#else
bool_t xdr_exports();
#endif


struct exportnode {
	dirpath ex_dir;
	groups ex_groups;
	exports ex_next;
};
typedef struct exportnode exportnode;
#ifdef __cplusplus
extern "C" {
bool_t xdr_exportnode(...);
}
#else
bool_t xdr_exportnode();
#endif


struct mountres3_ok {
	fhandle3 fhandle;
	struct {
		u_int auth_flavors_len;
		int *auth_flavors_val;
	} auth_flavors;
};
typedef struct mountres3_ok mountres3_ok;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountres3_ok(...);
}
#else
bool_t xdr_mountres3_ok();
#endif


struct mountres3 {
	mountstat3 fhs_status;
	union {
		mountres3_ok mountinfo;
	} mountres3_u;
};
typedef struct mountres3 mountres3;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountres3(...);
}
#else
bool_t xdr_mountres3();
#endif


enum mountstat1 {
	MNT1_OK = 0,
	MNT1ERR_PERM = 1,
	MNT1ERR_NOENT = 2,
	MNT1ERR_IO = 5,
	MNT1ERR_ACCES = 13,
	MNT1ERR_NOTDIR = 20,
	MNT1ERR_INVAL = 22,
	MNT1ERR_NAMETOOLONG = 63,
	MNT1ERR_NOTSUPP = 10004,
	MNT1ERR_SERVERFAULT = 10006,
};
typedef enum mountstat1 mountstat1;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountstat1(...);
}
#else
bool_t xdr_mountstat1();
#endif

#define FHSIZE 32

typedef char fhandle1[FHSIZE];
#ifdef __cplusplus
extern "C" {
bool_t xdr_fhandle1(...);
}
#else
bool_t xdr_fhandle1();
#endif


struct mountres1_ok {
	fhandle1 fhandle;
};
typedef struct mountres1_ok mountres1_ok;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountres1_ok(...);
}
#else
bool_t xdr_mountres1_ok();
#endif


struct mountres1 {
	mountstat1 fhs_status;
	union {
		mountres1_ok mountinfo;
	} mountres1_u;
};
typedef struct mountres1 mountres1;
#ifdef __cplusplus
extern "C" {
bool_t xdr_mountres1(...);
}
#else
bool_t xdr_mountres1();
#endif


#define MOUNT_PROGRAM ((u_long)100005)
#define MOUNT_V1 ((u_long)1)
#define MOUNT1_NULL ((u_long)0)
#ifdef __cplusplus
extern "C" {
extern void *mount1_null_1(...);
}
#else
extern void *mount1_null_1();
#endif /* __cplusplus */
#define MOUNT1_MNT ((u_long)1)
#ifdef __cplusplus
extern "C" {
extern mountres1 *mount1_mnt_1(...);
}
#else
extern mountres1 *mount1_mnt_1();
#endif /* __cplusplus */
#define MOUNT1_DUMP ((u_long)2)
#ifdef __cplusplus
extern "C" {
extern mountlist *mount1_dump_1(...);
}
#else
extern mountlist *mount1_dump_1();
#endif /* __cplusplus */
#define MOUNT1_UMNT ((u_long)3)
#ifdef __cplusplus
extern "C" {
extern void *mount1_umnt_1(...);
}
#else
extern void *mount1_umnt_1();
#endif /* __cplusplus */
#define MOUNT1_UMNTALL ((u_long)4)
#ifdef __cplusplus
extern "C" {
extern void *mount1_umntall_1(...);
}
#else
extern void *mount1_umntall_1();
#endif /* __cplusplus */
#define MOUNT1_EXPORT ((u_long)5)
#ifdef __cplusplus
extern "C" {
extern exports *mount1_export_1(...);
}
#else
extern exports *mount1_export_1();
#endif /* __cplusplus */
#define MOUNT_V3 ((u_long)3)
#define MOUNT3_NULL ((u_long)0)
#ifdef __cplusplus
extern "C" {
extern void *mount3_null_3(...);
}
#else
extern void *mount3_null_3();
#endif /* __cplusplus */
#define MOUNT3_MNT ((u_long)1)
#ifdef __cplusplus
extern "C" {
extern mountres3 *mount3_mnt_3(...);
}
#else
extern mountres3 *mount3_mnt_3();
#endif /* __cplusplus */
#define MOUNT3_DUMP ((u_long)2)
#ifdef __cplusplus
extern "C" {
extern mountlist *mount3_dump_3(...);
}
#else
extern mountlist *mount3_dump_3();
#endif /* __cplusplus */
#define MOUNT3_UMNT ((u_long)3)
#ifdef __cplusplus
extern "C" {
extern void *mount3_umnt_3(...);
}
#else
extern void *mount3_umnt_3();
#endif /* __cplusplus */
#define MOUNT3_UMNTALL ((u_long)4)
#ifdef __cplusplus
extern "C" {
extern void *mount3_umntall_3(...);
}
#else
extern void *mount3_umntall_3();
#endif /* __cplusplus */
#define MOUNT3_EXPORT ((u_long)5)
#ifdef __cplusplus
extern "C" {
extern exports *mount3_export_3(...);
}
#else
extern exports *mount3_export_3();
#endif /* __cplusplus */

