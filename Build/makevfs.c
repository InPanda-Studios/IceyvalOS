#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    FILE *fp = fopen("build/input.txt", "r");
    FILE *fout = fopen("build/vfs.bin", "w+");
    
    char line[100];
    while (fgets(line, 100, fp)) {
        // remove newline character
        strtok(line, "\n");

        // write line to output file
        fprintf(fout, "%s\n", line);
        
        // append null bytes
        int i;
        for (i = 0; i < 1024; i++) {
            fputc(0, fout);
        }
        fprintf(fout, "\n");
    }
    fseek(fout, -1, SEEK_END); // move to the last byte of the file
    ftruncate(fileno(fout), ftell(fout)); // truncate the file to the current position
    fclose(fp);
    fclose(fout);
    return 0;
}
