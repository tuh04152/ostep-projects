#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
    // If the only argument is the program name, exit the program immediately.
    if (argc == 1) {
        return 0;
    }
    // Otherwise for every argument after the program name, we open the files using the arguments as filenames
    printf("\n");
    for (int i = 1; i < argc; i++){
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL){
            printf("wcat: cannot open file\n");
            exit(1);
        }
        // Next we define a buffer and default size. The getline will function, of course, realloc this buffer if it is too small for the line input.
        char* buffer;
        size_t number = 256;
        buffer = (char*)malloc(256 * sizeof(char));
        if (buffer == NULL){
            printf("Memory Error.");
            exit(1);
        }
        // Every line in the file is printed (as getline returns -1 at EOF)
        while (getline(&buffer, &number, fp) != -1){
        printf("%s", buffer);
        }
        // Finally, we close the file and print two newline characters to separate all the files.
        fclose(fp);
        printf("\n\n");
        }

    return 0;
}
