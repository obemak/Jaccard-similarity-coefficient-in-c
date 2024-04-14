#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bzlib.h>

#define CHUNK_SIZE 4096


// the Jaccard similarity coefficient
double calculate_similarity(char** list1, char** list2, int size1, int size2) {


    // Convert lists to sets to get unique words
    char** set1 = malloc(size1 * sizeof(char*)); // Allocate memory for set1
    char** set2 = malloc(size2 * sizeof(char*)); // Allocate memory for set2
    int set1_count = 0, set2_count = 0; // Counters for set1 and set2

    // Loop through list1 to create set1
    for (int i = 0; i < size1; ++i) {
        int found = 0; // Flag to indicate if the word is already in the set
        // Check if the word already exists in set1
        for (int j = 0; j < set1_count; ++j) {
            if (strcmp(list1[i], set1[j]) == 0) {
                found = 1; // Word found in set1
                break;
            }
        }
        if (!found) {
            set1[set1_count++] = list1[i]; // Add unique word to set1
        }
    }

    // Loop through list2 to create set2
    for (int i = 0; i < size2; ++i) {
        int found = 0; // Flag to indicate if the word is already in the set
        // Check if the word already exists in set2
        for (int j = 0; j < set2_count; ++j) {
            if (strcmp(list2[i], set2[j]) == 0) {
                found = 1; // Word found in set2
                break;
            }
        }
        if (!found) {
            set2[set2_count++] = list2[i]; // Add unique word to set2
        }
    }

    // Calculate intersection of set1 and set2
    int intersection = 0;
    for (int i = 0; i < set1_count; ++i) {
        for (int j = 0; j < set2_count; ++j) {
            if (strcmp(set1[i], set2[j]) == 0) {
                intersection++; // Increment intersection count
                break;
            }
        }
    }
    
    // Calculate union size of set1 and set2
    int union_size = set1_count + set2_count - intersection;

    // Calculate Jaccard similarity coefficient
    double similarity_percentage = ((double) intersection / union_size) * 100;

    // Free allocated memory for sets
    free(set1);
    free(set2);

    // Return the Jaccard similarity coefficient
    return similarity_percentage;

}

int wordlist_find(char word, char wordlist_path){



    FILE *file = fopen(filename, "r");

    // If file doesent exist
    if (file == NULL) {

        perror("Error opening file");
        return;
    }

    char buffer[256]; // Buffer to store each line

    while (fgets(buffer, sizeof(buffer), file) != NULL) {

        printf("%s", buffer); // You can perform operations on the line here
        
    }

    fclose(file);

    return 0;

}





void processBz2File(const char *filename) {
    
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    BZFILE *bzfile = BZ2_bzReadOpen(&file, "r");
    if (!bzfile) {
        fprintf(stderr, "Error opening bz2 file.\n");
        fclose(file);
        return;
    }

    char buffer[CHUNK_SIZE];
    char line[CHUNK_SIZE];
    int bzerror, nbytes;
    int line_index = 0;

    while ((nbytes = BZ2_bzRead(&bzerror, bzfile, buffer, CHUNK_SIZE)) > 0) {
        for (int i = 0; i < nbytes; i++) {
            if (buffer[i] == '\n') {
                line[line_index] = '\0';
                printf("%s\n", line);
                line_index = 0;
            } else {
                line[line_index++] = buffer[i];
            }
        }
    }

    if (bzerror != BZ_OK && bzerror != BZ_STREAM_END) {
        fprintf(stderr, "Error reading bz2 file.\n");
    }

    BZ2_bzReadClose(&bzerror, bzfile);
    fclose(file);
}