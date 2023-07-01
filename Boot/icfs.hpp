typedef struct VFSEntry
{
      char src[256];
      bool openable;
      bool isDir;
} VFSEntry;
VFSEntry mainFile;