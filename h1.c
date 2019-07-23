/*
 
 Surya Dheeshjith : surya.dheeshjith@gmail.com
 
 */

#include <h1.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define dataBitmapOffset  8 * 1024

/*
	File System Offsets	in Bytes
*/


///////////***************//////////
#define superOffset  0 * 1024
#define inodeBitmapOffset   4 * 1024
#define inodeDataOffset  12 * 1024
#define dataOffset  ( 12 + 4 * 128 ) * 1024
///////////***************//////////

void print_inodeBitmaps(int fileSystemId)
{
    int i,j,num,rem,k=0,bin[8],nnum;
	char* inode_map;
	int bytes_to_read=4*1024; //4KB
	inode_map=(char*)malloc(sizeof(char*)*bytes_to_read);
	if(lseek(fileSystemId,inodeBitmapOffset,SEEK_SET)<0) return ; //Error reaching offset
	if(read(fileSystemId,(void*)inode_map,bytes_to_read) == -1) return; //Error reading from file
	printf("Inode bitmap\n");
    
	for(i=0;i<bytes_to_read;i++)
	{
        
        k=0;
        num = inode_map[i];
        if(num!=0)
        {
            num=abs(num);
            
            if(num!=128)
            {
                nnum=num;
                while(1)
                {
                    if(num*2==128)
                    {
                        nnum += 128;
                        break;
                    }
                    nnum += num*2;
                    num = num*2;
                    
                }
                num=nnum;
            }
            
            while(num)
            {
                //printf("%d",inode_map[i]);
                rem = num%2;
                bin[k]=rem;
                k++;
                num = num/2;
            }
        
        
         
            while(k<8)
            {
                bin[k++]=0;
            }
            
            for(j=7;j>=0;j--)
            printf("%d",bin[j]);
        }
        else
            printf("%d",inode_map[i]);
	}
	printf("\n");
}

void print_dataBitmaps(int fileSystemId)
{
	char* data_map;
	int i;
	int bytes_to_read=4*1024; //4KB
	data_map=(char*)malloc(sizeof(char*)*bytes_to_read);
	if(lseek(fileSystemId,dataBitmapOffset,SEEK_SET)<0) return ; //Error reaching offset
	if(read(fileSystemId,(void*)data_map,bytes_to_read) == -1) return; //Error reading from file
	printf("Data bitmap\n");
	for(i=0;i<bytes_to_read;i++)
	{
		printf("%d",data_map[i]);
	}
	printf("\n");
}

void print_FileList(int disk)
{	
	
    
    
    int i,found;
    int fourKB=1024*4;
    int starting,file_size,n_blocks=0;
    char *name,*word;
    word=(char*)malloc(sizeof(char)*16);
    name=(char*)malloc(sizeof(char)*8);
    found=0;
    for(i=inodeDataOffset;i<dataOffset;i+=16)
    {
        if(lseek(disk,i,SEEK_SET)<0) return;
        if(read(disk,(void*)word,16)!=16) return; //Inode block size
        memcpy((void*)name,(void*)word,8); //Extract file name
        // printf("Read : %s\n",name);
        if(strcmp(name,""))
        {
            found=1;
            memcpy((void*)(&starting),(void*)(word+8),2);
            memcpy((void*)(&n_blocks),(void*)(word+10),2);
            memcpy((void*)(&file_size),(void*)(word+12),4);
            printf("File name : %s\n",name);
            printf("Starting block of file : %d\n",starting);
            printf("Number of blocks : %d\n",n_blocks);
            printf("Size of file : %dB\n",file_size);
            printf("\n\n");
        }
    }
}
