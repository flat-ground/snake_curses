#include "level_loader.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ncurses.h>


char str[100];

int load_level(char* path)
{	
	int fd = open(path, O_RDONLY);
	if(fd == -1) return 1;
	return 0;
}

int save_level(char* path, int row, int col)
{
	int fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
	if(fd == -1) return 1;
	
	int i = 0;
	for(i = 0; i < row; i++){
		mvinstr(i,0, str);
		write(fd, str, col);
		write(fd, "\n", 1);
		
	}		
	
	close(fd);
	
	return 0;
}
