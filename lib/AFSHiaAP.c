#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include "crypter.h"

static const char *dirpath = "/home/vagrant/shift4";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

	// DEKRIPSI	
		//eksepsi
		if(strcmp(de->d_name, ".")==0) continue;
    else if(strcmp(de->d_name, "..")==0) continue;

		//generate nama baru
		int i=0;
		char *nama_Baru = de->d_name;
		while(nama_Baru[i]){

				//cari di list
				int pos = cariDiList(&nama_Baru[i]);
				pos = ( pos + length - shift) % length;
				nama_Baru[i] = list[pos];

				i++;
		}

		sprintf(de->d_name, "%s", nama_Baru);
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

//nomor 2a
// void* gabungin(void *arg){
// 	//yuk gabungin videonya
// 	return;
// }

//nomor 2a
void makeDir(){
	// int err;
  //   pthread_t tid;

	struct stat st = {0};
	char *dir = "/home/vagrant/shift4/Videos";
	if(stat(dir, &st) == -1){
		mkdir(dir, 0660);
	}

	//buat thread untuk gabungin video
	// err = pthread_create( &tid, NULL, gabungin, NULL);
	// if(err){
	// 	fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
	// 	exit(EXIT_FAILURE);
	// }
	// pthread_join(tid, NULL);
}

int main(int argc, char *argv[])
{
	umask(0);
	length = strlen(list);

	//nomor2
	makeDir();

	return fuse_main(argc, argv, &xmp_oper, NULL);
}