#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv){
    // First, we define a char* buffer. This buffer will be used if the user only submits a keyword, rather than a keyword and a series of strings.
    char* buffer;
    // We also define 256 as a default size for our buffer
    size_t number = 256;
    buffer = (char*)malloc(number * sizeof(char));
    if (buffer == NULL){
            printf("Memory Error.");
            exit(1);
        }
    // test is a character pointer that will be used to determine if a string is inside another string.
    char* test;
    // If there is no argument, simply the filename, do nothing.
    if (argc == 1 || strcmp(argv[1],"") == 0) {
        return 0;
    } // if there is a filename and only a keyword, begin this process.
    else if (argc == 2 && strcmp(argv[1],"") != 0){
        // First we define a 2d array of char (or an array of strings, in another way to put it)
        char** string_array;
        int count = 0;
        // At first, it is the size of 1 string of the default buffer length of 256.
        string_array = (char**)malloc(strlen(buffer) * count+1);
        if (string_array == NULL){
            printf("Memory Error.");
            exit(1);
        }
        // The getline function will place a given line from input into the buffer. If that line is greater than number, that specific line buffer will be reallocated automatically.
        // This will continue until the user enters an empty line (aka, buffer equals "\n").
        while (getline(&buffer, &number, stdin) != -1 && strcmp(buffer,"\n") != 0){
                // Out test pointer will point to the first occurence of that string in the input line.
                test = strstr(buffer, argv[1]);
                // If the pointer exists (and therefore the string exists in the line), then the following occurs:
                if (test) {
                    // First, both dimensions of the 2D array are realloced to accommondate a new line (with the string array reallocated based on the size of the buffer, which due to getline may be bigger than 256);
                    string_array = (char**)realloc(string_array, strlen(buffer) * (count+1));
                    if (string_array == NULL){
                        printf("Memory Error.");
                        exit(1);
                    }
                    string_array[count] = (char*)realloc(string_array[count], strlen(buffer) * (count+1));
                    if (string_array[count] == NULL){
                        printf("Memory Error.");
                        exit(1);
                    }
                // Then we add the string that contains the keyword to the realloced string array and increment the count.
                    strcpy(string_array[count],buffer);
                    count++;
                }
        }
        // If count is greater than 0 (and therefore, at least one line has the keyword in it) this will print out all the lines in the string array.
        if (count != 0) {
            for (int i = 0; i < count; i++){
                printf("%s", string_array[i]);
            }
        }
        return 0;
    } // In the event that there is a the filename, keyword and any more arguments, then for every argument, the program will open the files with the same names as the arguments and scan all of their lines for the keyword.
    // The process is similar except that instead of waiting until the buffer reads an empty line, it keeps going until the fgets equals NULL (which happens at end of file)
    else {
        for (int i = 2; i < argc; i++){
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL){
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            while (fgets(buffer, 256, fp) != NULL){
                test = strstr(buffer, argv[1]);
                if (test) {
                    printf("%s", buffer);
            }
        }
            // Finally, we close the file.
            fclose(fp);
            printf("\n");
        }
    }
    return 0;
}
