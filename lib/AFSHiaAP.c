#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "crypter.h"

static const char *dirpath = "/home/vagrant/shift4";
int status=0;

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
		mkdir(dir, 0777);
	}

	//buat thread untuk gabungin video
	// err = pthread_create( &tid, NULL, gabungin, NULL);
	// if(err){
	// 	fprintf(stderr,"Error - pthread_create() return code: %d\n",err);
	// 	exit(EXIT_FAILURE);
	// }
	// pthread_join(tid, NULL);
}

int remove_directory(const char *path)
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;

   if (d)
   {
      struct dirent *p;

      r = 0;

      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;

          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) continue;

          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf)
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);

             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                {
                   r2 = remove_directory(buf);
                }
                else
                {
                   r2 = unlink(buf);
                }
             }

             free(buf);
          }

          r = r2;
      }

      closedir(d);
   }

   if (!r){
      r = rmdir(path);
   }

   return r;
}

int isSubstring(char *s1, char *s2) 
{ 
    int M = strlen(s1); 
    int N = strlen(s2); 
  
	int i;
    /* A loop to slide pat[] one by one */
    for (i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) 
                break; 
  
        if (j == M) 
            return i; 
    } 
  
    return -1; 
}

// int getNameLength(char *path){
// 	int i=strlen(path); pos=0;
// 	while(path[--i]!='/' && i!=0) pos++;
// 	return pos;
// }

// void* myJoin(void *arg){
//     char* fname = (char *) arg;
//     status=0;

//     int i;
//     char target[4096], source[4096];

//     fname[strlen(fname)-4]=0;
//     mymemset(target);
//     sprintf(target, "%s/g[xO#Y/%s", dirpath, fname);

//     strcat(fname,"`");
//     for(i=0;;i++){
//         char mynum[1000];
//         mymemset(mynum);
//         sprintf(mynum,"%03d",i);
//         encrypt(mynum);

//         mymemset(source);
//         sprintf(source,"%s/%s%s", dirpath, fname, mynum);
//         if(copy_file(target,source, 0)) break;
//     }
// }

static void *xmp_init(struct fuse_conn_info *conn, struct fuse_config *cfg){
	length = strlen(list);
	decrypt("/home/vagrant/shift4/");
	makeDir();

	// DIR *dp;
	// struct dirent *de;
	// int i=0;
	// pthread_t tid[1000];

	// (void) offset;
	// (void) fi;

	// dp = opendir(fpath);
	// if (dp == NULL)
	// 	return -errno;

	// while ((de = readdir(dp)) != NULL) {
	// 	if(ext_match(p->d_name, "`PPP")){
	// 			status=1;
	// 			pthread_create(&(tid[i++]), NULL, myJoin, (void *) p->d_name);
	// 			while(status);
	// 	}
	// }

	// while(--i){
	// 		pthread_join(tid[i],NULL);
	// }

	// closedir(dp);
	return NULL;
}

static void xmp_destroy(void *private_data){
	char *dir = "/home/vagrant/shift4/Videos";
	remove_directory(dir);
	encrypt("/home/vagrant/shift4/");
	// return NULL;
}

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

	DIR *d;
	struct dirent *de;

	(void) offset;
	(void) fi;

	d = opendir(fpath);
	if (d == NULL)
		return -errno;

	chdir(fpath);
	while ((de = readdir(d)) != NULL) {
		struct stat st;
		stat(de->d_name, &st);
		struct passwd *pw = getpwuid(st.st_uid);
		struct group *gr = getgrgid(st.st_gid);

		char *loc = "/home/vagrant/shift4/filemiris.txt";
		
		// if (!S_ISDIR(st.st_mode)){
		if( !strcmp(pw->pw_name, "chipset") || !strcmp(pw->pw_name, "ic_controller")){	
			if(!strcmp(gr->gr_name, "rusak")){			

				FILE *file = fopen(loc, "a"); 
				if (file == NULL){ 
							puts("Could not open files"); 
							exit(0); 
				}

				char fdata[100];
				char ftime [37];
				strftime(ftime, 36, "%d.%m.%Y %H:%M:%S", localtime(&st.st_atime)); 

				// menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses di filemiris.txt
				sprintf(fdata, "%s %d %d %s\n", de->d_name, st.st_uid, st.st_gid, ftime);
				fprintf(file, "%s", fdata);
					remove(de->d_name);
				fclose(file);
				continue;
			}
		}
		// }

		// if( !strcmp(pw->pw_name, "chipset") || !strcmp(pw->pw_name, "ic_controller")){
		// 	continue;
			// strcmp("rusak", gr->gr_name)==0;
			// while ((c = fgetc(fp1)) != EOF) 
			// 	fputc(c, fp3);
			// FILE *file = fopen(loc, "a"); 
			// if (file == NULL){ 
			// 			puts("Could not open files"); 
			// 			exit(0); 
			// }

			// char fdata[100];
			// char ftime [37];
			// strftime(ftime, 36, "%d.%m.%Y %H:%M:%S", localtime(&st.st_atime)); 

			//menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses di filemiris.txt
			// sprintf(fdata, "%s %d %d %s\n", pw->pw_name, st.st_uid, st.st_gid, ftime);
			// fprintf(file, "%s", fdata);

			// res = rmdir(fpath);

		// 	fclose(file);
		// }

		// memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	
	

	closedir(d);
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

static int xmp_mkdir(const char *path, mode_t mode)
{
    int res = 0;
    char fpath[1000];
    char name[1000];

    sprintf(name,"%s",path);
	sprintf(fpath, "%s%s",dirpath,name);

    if(isSubstring(name,"/YOUTUBER")!=-1){
			mode = 0750;
    	res = mkdir(fpath, mode);
    }
		else if(isSubstring("YOUTUBER/", name)!=-1){
			mode = 0750;
    	res = mkdir(fpath, mode);
		}
    else{
    	res = mkdir(fpath, mode);
    }
    if (res == -1)
        return -errno;

    return 0;
}

static int xmp_rmdir(const char *name){
	char path[1000];
	sprintf(path, "%s%s",dirpath,name);
	int res;
	DIR *d = opendir(path);
    
	if(d){
		closedir(d);
	}else{
		return -errno;
	}

	res = rmdir(path);
	
	if(res == -1)
		return -errno;

	return 0;
}

static int xmp_create(const char* path, mode_t mode, struct fuse_file_info* fi)
{
	int res = 0;
    char fpath[1000];
    char name[1000];

    sprintf(name,"%s",path);
	sprintf(fpath, "%s%s",dirpath,name);

    if(isSubstring("YOUTUBER/",name)!=-1){
			mode = 0640;
			strcat(fpath,".iz1");
				res = creat(fpath, mode);
    }
    else{
    	res = creat(fpath, mode);
    }
	
    if(res == -1)
		return -errno;

    close(res);
    return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    int res = 0;
		int child;
    char fpath[1000];
    char name[1000];

    sprintf(name,"%s",path);
		sprintf(fpath, "%s%s",dirpath,name);

    if(isSubstring("YOUTUBER/", name)!=-1){
			child=fork();
			if(child==0){
				char *argv[5] = {"zenity", "--error","--text=File ekstensi iz1 tidak boleh diubah permissionnya.","--title=Tidak bisa merubah", NULL};
					execv("/usr/bin/zenity", argv);
			}
    }
    else{
	 		res = chmod(fpath, mode);
    }
	
    if(res == -1)
			return -errno;

    close(res);
    return 0;
}


static int xmp_opendir(const char *name, struct fuse_file_info *fi)
{
	// char path[1000];
	// struct stat st;

	// sprintf(path, "%s%s",dirpath,name);
	// int res;
	// DIR *d = opendir(path);
    
	// if(d){
	// 	closedir(d);
	// }else{
	// 	return -errno;
	// }
	
	// char *loc = "/home/vagrant/shift4/filemiris.txt";

	// if(stat(loc, &st) != -1){
	// 	struct passwd *pw = getpwuid(st.st_uid);
	// 	struct group *gr = getgrgid(st.st_gid);

	// 	if( (strcmp("chipset", pw->pw_name)==0 || strcmp("ic_controller", pw->pw_name)==0 ) && strcmp("rusak", gr->gr_name)==0){
			
	// 		char c;

	// 		// while ((c = fgetc(fp1)) != EOF) 
  //     // 	fputc(c, fp3);

	// 		char fdata[100];
	// 		char ftime [37];
	// 		strftime(ftime, 36, "%d.%m.%Y %H:%M:%S", localtime(&st.st_atime));

	// 		FILE *file = fopen(loc, "w"); 
	// 		if (file == NULL){ 
	// 					puts("Could not open files"); 
	// 					exit(0); 
	// 		} 

	// 		//menyimpan nama file, group ID, owner ID, dan waktu terakhir diakses di filemiris.txt
	// 		sprintf(fdata, "%s %d %d %s\n", pw->pw_name, st.st_uid, st.st_gid, ftime);
	// 		fprintf(file, "%s", fdata);

	// 		res = rmdir(path);

	// 		fclose(file);
	// 	}
	// }
	
	// if(res == -1)
	// 	return -errno;

	return 0;
}

static struct fuse_operations xmp_oper = {
	.init       = xmp_init,
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.create 	= xmp_create,
	.mkdir		= xmp_mkdir,
	.rmdir 		= xmp_rmdir,
	.chmod		= xmp_chmod,
	// .opendir		= xmp_opendir,
	.destroy    = xmp_destroy,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}