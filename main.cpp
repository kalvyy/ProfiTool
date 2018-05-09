#include <iostream>
#include <QCoreApplication>
#include "filesystem/directory_handler/directory_handler.h"


char filter(const struct dirent * fileEntry)
{
    return fileEntry->d_name[0] != '.';
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    DirectoryHandler * h = createDirectoryHandler();
    DirectoryContent content;
    h->getDirectoryContent("/home/kalvy/Desktop", &content);
    destroyDirectoryHandler(&h);


    std::cout << content.size<<std::endl;
    for(unsigned int i = 0; i < content.size; ++i)
    {
        std::cout << content.directoryEntries[i].d_name << std::endl;
    }
    free(content.directoryEntries);


    //QCoreApplication a(argc, argv);

    //return a.exec();
}
