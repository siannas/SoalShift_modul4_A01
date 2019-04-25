#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int shift = 1;
int encrypt(char *dir_name);
int decrypt(char *dir_name);

char *list =  "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
int length;

int cariDiList(char *x){
    int i;
    for (i = 0; i < length; i++){
        if( *x == list[i]) return i;
    }
    
    return 0;
}

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

        strcat(strcat(dir_Temp,de->d_name), "/");

        //encrypt sub folder
        encrypt(dir_Temp);


        //generate nama baru
        i=0;
        char *nama_Baru = de->d_name;
        while(nama_Baru[i]){

            //cari di list
            int pos = cariDiList(&nama_Baru[i]);
            pos = ( pos + shift) % length;
            nama_Baru[i] = list[pos];

            i++;
        }

        strcat(strcat(dir_Baru,nama_Baru), "/");

        //rename
        rename(dir_Temp, dir_Baru);
    }
  
    closedir(dr);
    return 0;     
}

int decrypt(char *dir_name){
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

        strcat(strcat(dir_Temp,de->d_name), "/");

        //encrypt sub folder
        decrypt(dir_Temp);


        //generate nama baru
        i=0;
        char *nama_Baru = de->d_name;
        while(nama_Baru[i]){

            //cari di list
            int pos = cariDiList(&nama_Baru[i]);
            pos = ( pos + length - shift) % length;
            nama_Baru[i] = list[pos];

            i++;
        }

        strcat(strcat(dir_Baru,nama_Baru), "/");

        //rename
        rename(dir_Temp, dir_Baru);
    }
  
    closedir(dr);
    return 0;     
}