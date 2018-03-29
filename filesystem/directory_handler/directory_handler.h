#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H


#include <limits.h>

//Max file/directory name and place for '\0'
#define MAX_NAME_LENGTH (NAME_MAX + 1)

typedef struct
{
    char name[MAX_NAME_LENGTH];
    unsigned char fileType;
} DirectoryFile;


//DIRECTORY CONTENT
typedef struct
{
    unsigned int size;
    DirectoryFile * directoryFiles;
} DirectoryContent;


//DIRECTORY HANDLER
typedef struct
{
    unsigned int (*getAmountOfFilesInDirectory)(const char * const directoryPath);
    void (*getDirectoryContent)(const char * const directoryPath, DirectoryContent * resultDirectoryContent);
} DirectoryHandler;


DirectoryHandler * createDirectoryHandler();
void destroyDirectoryHandler(DirectoryHandler * handlerToDestroy);


#endif // DIRECTORYHANDLER_H
