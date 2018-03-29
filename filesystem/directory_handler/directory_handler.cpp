#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "directory_handler.h"


static const unsigned int DOT_DIRECTORY_AMOUNT = 2;

static unsigned int getAmountOfFilesInDirectory(const char * const directoryPath)
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

    resultDirectoryContent->size = getAmountOfFilesInDirectory(directoryPath);
    resultDirectoryContent->directoryFiles = (DirectoryFile *)malloc(sizeof(DirectoryFile) * resultDirectoryContent->size );

    struct dirent * currentProcessingFile = NULL;
    unsigned int index = 0;

    while(NULL != (currentProcessingFile = readdir(directoryHandle)))
    {
        if(0 != strcmp(currentProcessingFile->d_name, ".") &&
           0 != strcmp(currentProcessingFile->d_name, ".."))
        {
            DirectoryFile * currentDirectoryContent = &resultDirectoryContent->directoryFiles[index];

            strncpy(currentDirectoryContent->name, currentProcessingFile->d_name, MAX_NAME_LENGTH);
            currentDirectoryContent->fileType = currentProcessingFile->d_type;

            ++index;
        }
    }

    closedir(directoryHandle);
}


DirectoryHandler * createDirectoryHandler()
{
    DirectoryHandler * resultDirectoryHandler = (DirectoryHandler *)malloc(sizeof(DirectoryHandler));
    resultDirectoryHandler->getAmountOfFilesInDirectory = getAmountOfFilesInDirectory;
    resultDirectoryHandler->getDirectoryContent = getDirectoryContent;

    return resultDirectoryHandler;
}


void destroyDirectoryHandler(DirectoryHandler * handlerToDestroy)
{
    free(handlerToDestroy);
}
