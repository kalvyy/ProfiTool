#include <iostream>
#include <QCoreApplication>
#include "filesystem/directory_handler/directory_handler.h"


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    DirectoryHandler * h = createDirectoryHandler();
    DirectoryContent content;
    h->getDirectoryContent("/home/kalvy/Desktop", &content);
    destroyDirectoryHandler(h);

    std::cout << content.size<<std::endl;
    for(unsigned int i = 0; i < content.size; ++i)
    {
        DirectoryFile * df = &content.directoryFiles[i];
        std::cout << df->name << std::endl;
    }

    //QCoreApplication a(argc, argv);

    //return a.exec();
}
