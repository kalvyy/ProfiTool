#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filesystem/directory_handler/directory_handler.h"


static const unsigned int DOT_DIRECTORY_AMOUNT = 2;

static unsigned int getAmountOfEntriesInDirectory(const char * const directoryPath)
{
    DIR * directoryHandle = opendir(directoryPath);
    if(NULL == directoryHandle)
    {
        return 0;
    }

    unsigned int contentCounter = 0;
    struct dirent * currentFile = NULL;
    while(NULL != (currentFile = readdir(directoryHandle)))
    {
        ++contentCounter;
    }
    closedir(directoryHandle);

    return contentCounter - DOT_DIRECTORY_AMOUNT;
}


static void getDirectoryContent(const char * const directoryPath, DirectoryContent * resultDirectoryContent)
{
    DIR * directoryHandle = opendir(directoryPath);
    if(NULL == directoryHandle || NULL == resultDirectoryContent)
    {
        return;
    }

    unsigned int maxContentSize = 1;
    resultDirectoryContent->directoryEntries = (struct dirent *)malloc(sizeof(struct dirent) * maxContentSize);
    resultDirectoryContent->size = 0;

    struct dirent * currentProcessingEntry = NULL;
    while(NULL != (currentProcessingEntry = readdir(directoryHandle)))
    {
        if(resultDirectoryContent->size >= maxContentSize)
        {
            maxContentSize *= 2;
            struct dirent * reallocResult = (struct dirent *)realloc(
                                resultDirectoryContent->directoryEntries,
                                sizeof(struct dirent) * maxContentSize);
            if(NULL == reallocResult)
            {
                free(resultDirectoryContent->directoryEntries);
                resultDirectoryContent->directoryEntries = NULL;
                resultDirectoryContent->size = 0;
                break;
            }
            resultDirectoryContent->directoryEntries = reallocResult;
        }
        resultDirectoryContent->directoryEntries[resultDirectoryContent->size] = *currentProcessingEntry;
        ++resultDirectoryContent->size;
    }

    closedir(directoryHandle);
}


DirectoryHandler * createDirectoryHandler()
{
    DirectoryHandler * resultDirectoryHandler = (DirectoryHandler *)malloc(sizeof(DirectoryHandler));
    resultDirectoryHandler->getAmountOfEntriesInDirectory = getAmountOfEntriesInDirectory;
    resultDirectoryHandler->getDirectoryContent = getDirectoryContent;

    return resultDirectoryHandler;
}


void destroyDirectoryHandler(DirectoryHandler ** handlerToDestroy)
{
    free(*handlerToDestroy);
    *handlerToDestroy = NULL;
}
