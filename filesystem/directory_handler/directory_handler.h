#ifndef DIRECTORYHANDLER_H
#define DIRECTORYHANDLER_H


#include <dirent.h>


typedef char (*FilterFunction)(const struct dirent * fileEntry);

typedef struct
{
    unsigned int size;
    struct dirent * directoryEntries;
} DirectoryContent;


//DIRECTORY HANDLER
typedef struct
{
    unsigned int (*getAmountOfEntriesInDirectory)(const char * const directoryPath);
    void (*getDirectoryContent)(const char * const directoryPath, DirectoryContent * resultDirectoryContent,
            FilterFunction filter);
} DirectoryHandler;


DirectoryHandler * createDirectoryHandler();
void destroyDirectoryHandler(DirectoryHandler ** handlerToDestroy);


#endif // DIRECTORYHANDLER_H
