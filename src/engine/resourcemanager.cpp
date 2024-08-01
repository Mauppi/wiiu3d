#include "resourcemanager.h"
#include <string>
#include <whb/log.h>
#include <string.h>

FileResource ResourceManager_LoadResource(const char *path) {

    bool containsAlready = false;
    int containIndex = 0;

    for (int i = 0; i < loadedResources.size(); i++) {
        if (strcmp(loadedResources[i].path.c_str(), std::string(path).c_str()) == 0) {
            containsAlready = true;
            containIndex = i;
            break;
        }
    }

    if (containsAlready) {
        WHBLogPrintf("Resource already loaded: %s", path);
        return loadedResources[containIndex];
    }
    
    FileResource resource;

    resource.path = std::string(path);

    FILE *file = fopen(std::string("fs:/vol/content/").append(path).c_str(), "rb");

    if (!file) {
        WHBLogPrintf("Loading alternative: %s", path);
        file = fopen(std::string("/vol/content/").append(path).c_str(), "rb");
    }

    if (!file) {
        WHBLogPrintf("Could not load resource: %s", path);
        return resource;
    }

    size_t size = 0;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, 0, SEEK_SET);
    resource.size = size;

    char *data = new char[size];
    fread(data, 1, size, file);
    fclose(file);

    resource.data = data;
    resource.loaded = true;

    loadedResources.push_back(resource);

    return resource;
}

bool freeresource(int index) {
    free(loadedResources[index].data);
    loadedResources.erase(loadedResources.begin() + index);
    return true;
}

bool ResourceManager_FreeResource(const char *path) {

    for (int i = 0; i < loadedResources.size(); i++) {
        if (loadedResources[i].path == path) {
            return freeresource(i);
        }
    }

    return false;
}

bool ResourceManager_FreeResource(int index) {

    return freeresource(index);
}