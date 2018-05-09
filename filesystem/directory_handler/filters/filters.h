#ifndef FILTERS_H
#define FILTERS_H


bool extensionFilter(const struct dirent * directoryEntry, const char * extension);
bool substringFilter(const struct dirent * directoryEntry, const char * substring);


#endif // FILTERS_H
