#include "trie.h"
#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


/*------------------------------Driver functions---------------------------------------*/



void to_lowercase(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        if ('A' <= string[i] && 'Z' >= string[i])
        {
            string[i] = tolower(string[i]);
        }
        i++;
    }
    return;
}

int countDigit(long int n)
{
    if (n == 0)
        return 1;
    int count = 0;
    while (n != 0) {
        n = n / 10;
        count++;
    }
    return count;
}

void add_words_to_trie(TrieNode *root, char *filename)
{

    FILE *fp = fopen(filename, "r");
    char word[20];
    int fq;
    if (fp == NULL)
        return;
    else
    {
        while ((fscanf(fp, "%s\t", word) != EOF) && (fscanf(fp, "%d\n", &fq) != EOF))
        {
            insert_trie(root, word, fq);
        }
    }
    fclose(fp);
    return;
}

void handle_result(TrieNode *root, int result, char *filename, char *search)
{
    if (result == 1 || result == -1)
    {
        if (result == -1)
            printf("No other strings found with this prefix\n");

        FILE *fp1 = fopen(filename, "r+");

        if (fp1 == NULL)
            return;
        else
        {
            long int feq;
            char word1[50];
            while ((fscanf(fp1, "%s\t", word1) != EOF) && (fscanf(fp1, "%ld\n", &feq) != EOF))
            {

                if (strcmp(word1, search) == 0)
                {
                    int c=countDigit(feq);
                    feq++;
                    fseek(fp1, -c-1, SEEK_CUR); // Move the file pointer back before the frequency value
                    fprintf(fp1, "%ld", feq);  // Write the updated frequency back to the file
                    break;
                }
            }
        }

        fclose(fp1);
    }
    else if (result == 0)
    {
        insert_trie(root, search, 1);
        FILE *fp3 = fopen(filename, "a");
        fprintf(fp3, "%s\t%d\n", search, 1); // Append the new word and frequency to the file
        fclose(fp3);
        printf("No string found with this prefix\n");
    }
    return;
}


/*---------------------Driver functions ends ----------------------*/