#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, const char * argv[]) {
    
    FILE *fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return(1);
    }
	
	if (argc == 3) {
		long int offset;
		offset = atoi(argv[2]);
		if (fseek(fp, offset, SEEK_SET) != 0) {
			fprintf(stderr, "Seek failed %x\n", offset);
		}
	}

    unsigned char buff[16];
    unsigned int add;
    int n, i;
	
    for (add=0; ; add+=n) {
        n = fread((void *) buff, 1, 16, fp);
        if (n <= 0)
            break;
        
        printf("%08X: ", (unsigned int) add);
        
        for (i=0; i < n; ++i) {
            printf("%02X ", buff[i]);
        }
        for (   ; i < 16; ++i) {
            printf("   ");
        }
		
        printf(" :");
		
        for (i=0; i < n; ++i) {
            if (isprint(buff[i])) {
                printf("%c", buff[i]);
            } else {
                printf("-");
            }
        }
        for (  ; i < 16; ++i) {
            printf(" ");
        }
        printf(":\n");
    }
    return 0;
}
