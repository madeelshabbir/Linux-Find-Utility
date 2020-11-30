#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
unsigned char typeCnvtr(const char* t){
	if(strcmp(t,"d") == 0)
		return DT_DIR;
	else if(strcmp(t, "f") == 0)
		return DT_REG;
	else if(strcmp(t, "s") == 0)
		return DT_SOCK;
	else if(strcmp(t, "l") == 0)
		return DT_LNK;
	else if(strcmp(t, "b") == 0)
		return DT_BLK;
	else if(strcmp(t, "c") == 0)
		return DT_CHR;
	else if(strcmp(t, "p") == 0)
		return DT_FIFO;
	else
		exit(0);

}
void searchFile(const char* fName, char* dir, bool mode){
	DIR* inp;
	if((inp = opendir(dir)) == NULL){
		return;
	}
	struct dirent* data;
	while((data = readdir(inp)) != NULL){
		if(mode){
			if(strcmp(data->d_name, fName) == 0)
				printf("%s%s\n",dir,fName);
		}
		else{
			if(data->d_type == typeCnvtr(fName))
				if(strcmp(data->d_name, ".") != 0 && strcmp(data->d_name, "..") != 0)
					printf("%s%s\n", dir, data->d_name);
		}
		if(strcmp(data->d_name,"..") != 0 && strcmp(data->d_name,".") != 0)
			if(data->d_type == DT_DIR){
				char bf[512];
				bf[0] = '\0';
				strcat(bf, dir);
				strcat(bf, data->d_name);
				strcat(bf, "/");
				searchFile(fName, bf, mode);
			}
	}
	closedir(inp);
}
int main(int argc, char* argv[]){
	bool mode;
	char fName[100];
	if(argc < 3){
		printf("Invalid Command!\n");
		exit(1);
	}
	if(strcmp(argv[argc - 2],"-name") == 0)
		mode = true;
	else if(strcmp(argv[argc - 2],"-type") == 0)
		mode = false;
	else{
		printf("Invalid Command!\n");
		exit(1);
	}
	char dir[512] = "./";
	if(argc == 4){
		strcpy(dir, argv[argc - 3]);
		if(strcmp(dir, ".") == 0){
			strcat(dir,"/");
		}
	}
	if(mode)
		searchFile(argv[argc - 1], dir, mode);
	else
		searchFile(argv[argc - 1], dir, mode);
	exit(0);
}
