int createSFS( char* filename, int nbytes, int* f_exist);

int readData( int disk, int blockNum, void* block);

int writeData(int disk, int blockNum, void* block);

int writeFile(int disk, char* filename, void* block);

int readFile(int disk, char* filename, void* block);

int deleteAll(int disk, int nbytes);

int fileExist(int disk, char* filename);
