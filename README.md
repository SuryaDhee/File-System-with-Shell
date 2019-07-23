# File System with Shell


#### Running a test program 

##### Use this to run on terminal
```gcc shell.c h1.c h2.c -I. -o to && ./to <Virtual_Disk_Name> <Size_in_MB>```

### Organisation:
The file system is maintained in blocks, with file support. Each file corresponds to a specific inode in the disk.
File allocation is done by searching for contiguous blocks of memory. 


### Functionality Supported:

#### Commands : 
  
* create : Create a file
* open : Open a file
* list : List of file names
* ibitmap : Output the Inode Bitmap
* clear : Clear Contents of Virtual Disk
* quit / exit : Exit the Virtual Disk
* help : Show list of commands

### Layout:
* The disk is laid out as follows:
1 block of data = 4 KB
1 inode entry = 16B (8B filename,2B file head pointer,2B file block size,4B file size in B).

* Block 0:
This is the super block. It stores Meta Data that can be used to identify the file system. Eg:- Name of filesystem - Surun

* Block 1: 
This contains the inode bitmap.

* Block 2:
This Contains the data bitmap.

* Blocks 3 to 130:
These contain the INode Data

* Blocks 131 - End:
These are the actual data blocks.
