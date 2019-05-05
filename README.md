# SoalShift_modul3_A01

index |
--- | 
[nomor 1](#no1) |
[nomor 2](#no2) |
[nomor 3](#no3) |
[nomor 4](#no4) |
[nomor 5](#no5) |

### <a name="no1" ></a>Nomor 1
---
Semua nama file dan folder harus terenkripsi
Enkripsi yang Atta inginkan sangat sederhana, yaitu Caesar cipher. Namun, Kusuma mengatakan enkripsi tersebut sangat mudah dipecahkan. Dia menyarankan untuk character list diekspansi,tidak hanya alfabet, dan diacak. Berikut character list yang dipakai:

`qE1~ YMUR2"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\8s;g<{3.u*W-0`

Misalkan ada file bernama “halo” di dalam folder “INI_FOLDER”, dan key yang dipakai adalah 17, maka:
“INI_FOLDER/halo” saat belum di-mount maka akan bernama “n,nsbZ]wio/QBE#”, saat telah di-mount maka akan otomatis terdekripsi kembali menjadi “INI_FOLDER/halo” .
Perhatian: Karakter ‘/’ adalah karakter ilegal dalam penamaan file atau folder dalam *NIX, maka dari itu dapat diabaikan
  
#### **PENJELASAN**
Pertama-tama kita perlu membuat fungsi pengenkripsinya. dalam hal ini kami membuat satu file header enkripsi. 

```c
int encrypt(char *dir_name){
    struct dirent *de;  
    char dir_Temp[100];
    char dir_Baru[100];
    int i;

    DIR *dr = opendir(dir_name); 
    
    if (dr == NULL) { 
        return 0; 
    } 

    while ((de = readdir(dr)) != NULL) {
        memset(dir_Temp, 0, sizeof dir_Temp);
        memset(dir_Baru, 0, sizeof dir_Baru);

        strcat(dir_Temp, dir_name);
        strcat(dir_Baru, dir_name);

        //eksepsi
        if(strcmp(de->d_name, ".")==0) continue;
        else if(strcmp(de->d_name, "..")==0) continue;

        // strcat(dir_Temp,de->d_name);

        strcat(strcat(dir_Temp,de->d_name), "/");
        //encrypt sub folder
        encrypt(dir_Temp);

        //generate nama baru
        memset(dir_Temp, 0, sizeof dir_Temp);

        strcat(strcat(dir_Temp,dir_name), de->d_name);

        i=0;
        char *nama_Baru = de->d_name;
        while(nama_Baru[i]){

            //cari di list
            int pos = cariDiList(&nama_Baru[i]);
            pos = ( pos + length + shift) % length;
            nama_Baru[i] = list[pos];

            i++;
        }

        strcat(dir_Baru,nama_Baru);
        
        rename(dir_Temp, dir_Baru);
    }
  
    closedir(dr);
    return 0;     
}
```
Fungsi di atas kami lakukan secara rekursif untuk mengenkripsi semua nama file dan folder di dalam folder `/home/[user]/shift4/`.

proses pengubahan nama sesuai kamus kita ada dalam fungsi di bawah ini dengan passing parameter berupa nama yang hendak dienkripsi.

```c
int cariDiList(char *x){
    int i;
    for (i = 0; i < length; i++){
        if( *x == list[i]) return i;
    }
    
    return 0;
}
```

adapun proses pendekripsian yang bisa dilakukan pada fungsi read_dir di bagian file system yang kami buat.

```c
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  ...

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

	...
}
```

### <a name="no2" ></a>Nomor 2
---
#### **PENJELASAN**
belum

### <a name="no3" ></a>Nomor 3
---
#### **PENJELASAN**

Langkah yang dilakukan adalah :
Pada saat melakukan pembacaan direktori, perlu mengecek user dan group permissionnya. jika `!strcmp(pw->pw_name, "chipset") || !strcmp(pw->pw_name, "ic_controller") && (!strcmp(gr->gr_name, "rusak"))` maka perlu dihapus filenya dan dilakukan penulisan keterangan di filemiris. 
di bawah ini kode untuk string yang akan digunakan sebagai keterangan tersebut
```c
strftime(ftime, 36, "%d.%m.%Y %H:%M:%S", localtime(&st.st_atime)); 
sprintf(fdata, "%s %d %d %s\n", de->d_name, st.st_uid, st.st_gid, ftime);
```


### <a name="no4" ></a>Nomor 4
---
#### **PENJELASAN**

Yang perlu kita lakukan adalah membuat folder YOUTUBER dengan mode `750` begitu pulu semua folder di subdirektori folder YOUTUBER.
```c
if(isSubstring(name,"/YOUTUBER")!=-1){
			mode = 0750;
res = mkdir(fpath, mode);
}
else if(isSubstring("YOUTUBER/", name)!=-1){
	mode = 0750;
res = mkdir(fpath, mode);
	}
```

Selain itu perlu menjadikan semua file di dalam Folder YOUTUBER dengan penambahan ekstensi `.iz1` dan mode `640`. 
```c
if(isSubstring("YOUTUBER/",name)!=-1){
	mode = 0640;
	strcat(fpath,".iz1");
		res = creat(fpath, mode);
}
```

dan jika hendak merubah file tersebut, maka akan memunculkan error 
```c
char *argv[5] = {"zenity", "--error","--text=File ekstensi iz1 tidak boleh diubah permissionnya.","--title=Tidak bisa merubah", NULL};
execv("/usr/bin/zenity", argv);
```

### <a name="no5" ></a>Nomor 5
---
#### **PENJELASAN**
tidak ada
