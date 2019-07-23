/*

 Surya Dheeshjith : surya.dheeshjith@gmail.com
 
*/
#include <sys/types.h>
#include <h1.h>
#include <h2.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros

#define streq(a, b) (strcmp((a), (b)) == 0)
#define MAX sizeof(char*)*4*1024


void do_open(int file_descriptor, int args, char *arg1, char *arg2);
void do_inodemap(int file_descriptor, int args, char *arg1, char *arg2);
void do_help(int file_descriptor, int args, char *arg1, char *arg2);
void do_create(int file_descriptor, int args, char *arg1, char *arg2);
void do_list(int file_descriptor, int args, char *arg1, char *arg2);
void do_datamap(int file_descriptor, int args, char *arg1, char *arg2);
void do_clear(int file_descriptor, int args, char *arg1, int nbytes);

// Main execution

int ret;



int main(int argc, char *argv[]) {
    
  
    int size = -1;
    int *file_exist = (int *) malloc(sizeof(int));
    int file_descriptor;
    *file_exist = 0;
    
    char* filename=(char*)malloc(sizeof(char*)*1000);
    
    if (argc < 2 || argc>3) {
        fprintf(stderr, "Usage: %s <Virtual disk name> <size in MB>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    
    strcpy(filename,argv[1]);
    strcat(filename,".dat");
    
    
    if(argc == 2)
    {
        file_descriptor=createSFS(filename,size,file_exist);
        if(*file_exist == 0)
        {
            fprintf(stderr, "Virtual Disk does not exist\n");
            return EXIT_FAILURE;
        }
        else
            size = *file_exist;
            
    }
    else if(argc == 3)
    {
        size = atoi(argv[2]);
        size*=1024*1024;
        file_descriptor=createSFS(filename,size,file_exist);
    }
    
    if(file_descriptor<0)
    {
        printf("Error : Error creating FileSystem. Exiting..\n");
        return EXIT_FAILURE;
    }
    else
    {
        if(*file_exist > 0)
        {
            printf("\nWelcome back!\n");
        }
        else
            printf("Welcome.\n");
    }
    
   
    
    while (1) {
        char line[MAX], cmd[MAX], arg1[MAX], arg2[MAX];
        
        fprintf(stderr, "Surun> ");
        fflush(stderr);
        
        if (fgets(line, BUFSIZ, stdin) == NULL) {
            break;
        }
        
        int args = sscanf(line, "%s %s %s", cmd, arg1, arg2);   // Command
        if (args == 0) {
            continue;
        }
        
        if (streq(cmd, "open")) {
            do_open(file_descriptor,args, arg1, arg2);
        } else if (streq(cmd, "ibitmap")) {
            do_inodemap(file_descriptor, args, arg1, arg2);
        }  else if (streq(cmd, "list")) {
            do_list(file_descriptor, args, arg1, arg2);
        } else if (streq(cmd, "clear")) {
            do_clear(file_descriptor,args, arg1, size);
        } else if (streq(cmd, "create")) {
            do_create(file_descriptor,args, arg1, arg2);
        } else if (streq(cmd, "help")) {
            do_help(file_descriptor, args, arg1, arg2);
        } else if (streq(cmd, "exit") || streq(cmd, "quit")) {
            break;
        } else {
            printf("Unknown command: %s", line);
            printf("Type 'help' for a list of commands.\n");
        }
    }
    
    return 0;
}

void do_open(int file_descriptor, int args, char *arg1, char *arg2) {
    if (args != 2) {
        printf("Usage: open <filename>\n");
        return;
    }
    
    
    char *data=malloc(sizeof(char*)*4*1024); //4KB block
    //char *subfile=malloc(sizeof(char*)*4*1024); //4KB block
    
    ret=readFile(file_descriptor,arg1,(void*)data);
    
    
    if(ret>=0)
    {
        printf("Data read : \n%s\n",data);
    }
    else
    {
        //printf("Error!\nReturned %d",ret);
        printf("Error! File not found!\n");
    }
}

void do_inodemap(int file_descriptor, int args, char *arg1, char *arg2) {
    if (args != 1) {
        printf("Usage: ibitmap\n");
        return;
    }
    
    print_inodeBitmaps(file_descriptor);
}

void do_datamap(int file_descriptor, int args, char *arg1, char *arg2) {
    if (args != 1) {
        printf("Usage: dmap\n");
        return;
    }
    
     print_dataBitmaps(file_descriptor);
}

void do_list(int file_descriptor, int args, char *arg1, char *arg2) {
    if (args != 1) {
        printf("Usage: list\n\n\n");
        return;
    }
    
    print_FileList(file_descriptor);
}



void do_create(int file_descriptor, int args, char *arg1, char *arg2) {
    if (args != 2) {
        printf("Usage: create <filename>\n");
        return;
    }
    
    if(fileExist(file_descriptor,arg1)==1)
    {
        printf("File Already Exists!\n");
        return;
    }
    
    
    char *data=malloc(sizeof(char*)*4*1024); //4KB block
    //char *subfile=malloc(sizeof(char*)*4*1024); //4KB block
    
    printf("\nContent: ");
    fgets(data, sizeof(char*)*4*1024, stdin);
    
    ret = writeFile(file_descriptor,arg1,(void*)data);
    
    if (ret >= 0) {
        printf("created\n");
    } else {
        printf("create failed! Returned %d\n",ret);
    }
}

void do_clear(int file_descriptor, int args, char *arg1, int nbytes)
{
    if (args != 1) {
        printf("Usage: clear\n");
        return;
    }
    
    deleteAll(file_descriptor,nbytes);
}



void do_help(int file_descriptor, int args, char *arg1, char *arg2) {
    printf("Commands are:\n");
    printf("    list\n");
    printf("    ibitmap\n");
    printf("    create  <filename>\n");
    printf("    open    <filename>\n");
    printf("    clear\n");
    printf("    help\n");
    printf("    quit\n");
    printf("    exit\n");
}

