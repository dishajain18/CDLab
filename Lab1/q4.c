#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_WORD_LEN 50

// Hash table structure
char *hashTable[TABLE_SIZE];

// Hash function
int hash(const char *str) {
    int hash = 0;
    int i=0;
    while (str[i]!='\0') {
        hash += str[i];
        i++;
    }
    return hash % TABLE_SIZE;
}

// SEARCH function
int search(const char *key) {
    int index = hash(key);
    int originalIndex = index;

    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index], key) == 0) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == originalIndex) {
            break; 
        }
    }
    return -1;
}

void insert(const char *str) {
    if (search(str) != -1) {
        printf("Verb '%s' is already in the hash table.\n", str);
        return;
    }

    int index = hash(str);
    while (hashTable[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }

    hashTable[index] = (char *)malloc(strlen(str) + 1);
    
    strcpy(hashTable[index], str);
    printf("Inserted '%s' at index %u\n", str, index);
}

int isVerb(const char *word) {

    const char *verbs[9] = {"run", "jump", "play", "eat", "write", "read", "sing", "talk", "walk"};

    for (int i = 0; i<9; i++) {
        if (strcmp(word, verbs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isAlpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

int main() {
   
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    char filename[100];
    printf("Enter the first filename to open for reading: \n");
	scanf("%[^\n]c", filename);
	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}

    char word[MAX_WORD_LEN];
    int index = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isAlpha(ch)) {
            word[index++] = ch;
        } else if (index > 0) {
            word[index] = '\0';
            index = 0;

            if (isVerb(word)) {
                insert(word);
            }
        }
    }

    // Handle the last word in the file
    if (index > 0) {
        word[index] = '\0';
        if (isVerb(word)) {
            insert(word);
        }
    }

    fclose(file);

    printf("\nHash table contents:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] != NULL) {
            printf("Index %d: %s\n", i, hashTable[i]);
        }
    }

    return 0;
}
