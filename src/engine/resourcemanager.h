#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <vector>

struct FileResource
{
    char *data;
    size_t size;
    std::string path;
    bool loaded = false;
};

inline std::vector<FileResource> loadedResources;

FileResource ResourceManager_LoadResource(const char *path);
bool ResourceManager_FreeResource(const char *path);
bool ResourceManager_FreeResource(int index);

#endif