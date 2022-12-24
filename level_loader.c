#include <fcntl.h>
#include "level_loader.h"

int load_level(char* path)
{	
	int fd = open(path, O_RDONLY);
	if(fd == -1) return 1;
	return 0;
}

int save_level(char* path)
{
	int fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(fd == -1) return 1;
	close(fd);
	
	return 0;
}
