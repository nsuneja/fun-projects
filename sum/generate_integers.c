#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
    
    if (argc < 2) {
	printf("usage:: ./generate_integers <num of integers>\n");
	exit(0);
    }

    FILE *fp = fopen("dump.bin","wb");
    if(fp == NULL) {
    	printf("error creating file");
    	return -1;
    }

    unsigned long num = atoi(argv[1]);
    unsigned int i=0;
    for (i=1; i <= num; i++) {
    	fwrite(&i,sizeof(unsigned int),1,fp);
    }
 
    fclose(fp);
    return 0;
}
