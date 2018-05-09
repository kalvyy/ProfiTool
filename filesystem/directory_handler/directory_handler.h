#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H


#include <dirent.h>


typedef struct
{
    unsigned int size;
    struct dirent * directoryEntries;
} DirectoryContent;


//DIRECTORY HANDLER
typedef struct
{
    unsigned int (*getAmountOfEntriesInDirectory)(const char * const directoryPath);
    void (*getDirectoryContent)(const char * const directoryPath, DirectoryContent * resultDirectoryContent);
} DirectoryHandler;


DirectoryHandler * createDirectoryHandler();
void destroyDirectoryHandler(DirectoryHandler ** handlerToDestroy);


#endif // DIRECTORYHANDLER_H
