#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv){
    if (argc == 1) {
        // If no files are specified, this message will appear informing the user to enter some files names.
        printf("wzip: file1 [file2...]");
        exit(1);
    }
    for (int i = 1; i < argc; i++){
        // For each filename, open the respective file.
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL){
            printf("wzip: cannot open file\n");
            exit(1);
        }

        // Next, we get the total size of the file, using fseek.
        fseek(fp, 0, SEEK_END);
        int size = (unsigned long) ftell(fp);
        rewind(fp);

        // Now, we read all of the file's data into a character array using fread. We also record the data size and check that there is actually data in the file.
        char* data;
        data = (char*) malloc((size+1) * sizeof(char));
        if (data == NULL){
        printf("Error: Memory Allocation Failed");
        exit(1);
        }
        fread(data, 1, size, fp);
        int data_size = strlen(data);
        if (data_size == 0){
            printf("wzip: empty file");
            exit(0);
        }

        // We now create two different arrays, one of chars and the other of ints. This is essentially a custom made hashmap, where the matching indices for both arrays connect to each other.
        // For instance, if index 0 of the char array is 'a' and index 0 of the count array is 10 then there is a sequence of 10 'a's in a row.
        // The max size of the array is same size as our data set. This accounts for every single character in the file being unique. Otherwise, it must be less than that,
        char* char_array;
        char_array = (char*)malloc(data_size * sizeof(char));
        if (char_array == NULL){
            printf("Error: Memory Allocation Failed");
            exit(1);
        }

        int* count_array;
        count_array = (int*)malloc(data_size * sizeof(int));
        if (count_array == NULL){
            printf("Error: Memory Allocation Failed");
            exit(1);
        }

        // Now, we copy the first character of the data stream to the array, set the first index of the count array to zero and set up a constant called char_count.
        strcpy(&char_array[0], &data[0]);
        count_array[0] = 1;
        int char_count = 0;

        // This for loop checks every piece of data left after the first one.
        // If the previous character was a repetition, the character's count is increased by one. Otherwise, the constant char_count is increased, the new character is inserted into the array and the next index of the count_array is et to 1.
        for (int i = 1; i < data_size; i++){
            if  (data[i] == char_array[char_count]){
                count_array[char_count] += 1;
            } else {
                char_count++;
                strcpy(&char_array[char_count], &data[i]);
                count_array[char_count] = 1;
          }
        }
        // Finally, for every character, (which is counted by the char), we fwrite the binary representations of the char count and the character.
        for (int j = 0; j < char_count + 1; j++){
            fwrite(&count_array[j], sizeof(int), 1, stdout);
            fwrite(&char_array[j], sizeof(char), 1, stdout);
        }

        fclose(fp);
    }
    return 0;

}
