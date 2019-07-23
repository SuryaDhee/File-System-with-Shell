# Shell

# Surun  

###### (Surya + Varun ;) )
#### Running a test program 

##### Use this to run on terminal
```gcc shell.c h1.c h2.c -I. -o to && ./to```

### Organisation:
The file system is maintained in blocks, with file support. Each file corresponds to a specific inode in the disk.
File allocation is done by searching for contiguous blocks of memory. 

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


### Functionality Supported:
* ``` int createSFS(char* filename, int nbytes)```
Creates a disk with the name 'filename' of bytes 'nbytes' and returns the resultant file descriptor

* ```int readData( int disk, int blockNum, void* block)```
Accepts the file descriptor 'disk' and reads 4 KB of data starting at 'blockNum' block of data into 'block' buffer.Returns appropriate error code.

* ```int writeData(int disk, int blockNum, void* block)``` writes that data in the block to the disk block blockNum. 
Writes data stored in 'block' data buffer at 'blockNum' block of data memory stored in virtual disk pointed by file descriptor 'disk'. Returns appropriate error code.

* ```int writeFile(int disk, char* filename, void* block)```
Accepts file descriptor 'disk' and creates a new file with 'filename' with data from 'block' buffer.Does not check for existence of files with same name.Returns appropriate error code.

* ``` int readFile(int disk, char* filename, void* block)```
Accepts file descriptor 'disk' and reads data of file 'filename' into 'block' buffer.Returns appropriate error code.

* ```  void print_inodeBitmaps(int fileSystemId)```
Prints inode bitmap for FileSystem with 'fileSystemId' file descriptor virtual-disk.

* ```   void print_dataBitmaps(int fileSystemId)```
Prints data bitmap for FIleSystem with 'fileSystemId' file descriptor virtual-disk.

* ```   void print_FileList(int fileSystemId)```
Prints list of files. 'fileSystemId' is the file descriptor of virtual-disk.
