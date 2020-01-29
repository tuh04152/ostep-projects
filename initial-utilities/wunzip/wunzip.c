#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv){
    if (argc == 1) {
        // If no files are specified, this message will appear informing the user to enter some files names.
        printf("wunzip: file1 [file2...]");
        exit(1);
    }
    for (int i = 1; i < argc; i++){
        // For each filename, open the respective file.
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL){
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        // We create two buffers, one for a char and one for an int. The exact, precise nature of of encrypted files allow the next part to function.
        int count_buffer;
        char char_buffer;
        // As long as fread equals one (aka, an integer can be placed into the count_buffer), also read the character directly after it and write that character to stdout a number of times equal to the read integer.
        while (fread(&count_buffer, sizeof(int), 1, fp) == 1){
            fread(&char_buffer, sizeof(char), 1,fp);
            for (int i = 0; i < count_buffer; i++){
                fwrite(&char_buffer, sizeof(char), 1, stdout);
            }
        }

        fclose(fp);
    }
    return 0;

}
