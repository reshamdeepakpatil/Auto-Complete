#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


/*-----------------Global Variables--------------------*/

container buffer[10];
int g_buffer_index = 0;

/*-----------------------------------------------------*/






/*-------------------Sorting and printing---------------------*/

int add_to_buffer(char *word, int freq)
{
    if (g_buffer_index == 5)
        return 0;
    buffer[g_buffer_index].arr = (char *)malloc(sizeof(char) * strlen(word));
    strcpy(buffer[g_buffer_index].arr, word);
    buffer[g_buffer_index].freq = freq;
    g_buffer_index++;
    return 1;
}

void empty_buffer()
{
    for (int i = 0; i < g_buffer_index; i++)
    {
        free(buffer[i].arr);
        buffer[i].freq = 0;
    }
    g_buffer_index = 0;
}

void swap(container *a, container *b)
{
    container t = *a;
    *a = *b;
    *b = t;
}

// making the partition of array by using last element as pivot
int partition(int low, int high)
{
    int pivot = buffer[high].freq;

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        //  current element is smaller than pivot
        if (buffer[j].freq > pivot)
        {
            i++;
            swap(&buffer[i], &buffer[j]);
        }
    }
    swap(&buffer[i + 1], &buffer[high]);
    return (i + 1);
}



void sort(int l, int h)
{
    int low = l;
    int high = h;
    if (low < high)
    {
        // p is partitioning index such that arr[p] is now at right place
        int p = partition(low, high);

        sort(low, p - 1);
        sort(p + 1, high);
    }
}

void sort_and_print()
{
    sort(0, g_buffer_index - 1);
    int index = g_buffer_index;
    if(index > 5){
        index = 5;
    }
    for (int i = 0; i < index; i++)
    {
        printf("%s\n", buffer[i].arr);
    }
}

/*-------------------Sorting and printing ends---------------------*/







/*---------------------------------Trie functions----------------------------------*/

TrieNode *getNode(char ch)
{
    TrieNode *pNode = (TrieNode *)malloc(sizeof(TrieNode));
    pNode->isWordEnd = 0;
    pNode->data = ch;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}




void insert_trie(TrieNode *root, char *key, int freq)
{
    TrieNode *temp = root;

    for (int level = 0; level < strlen(key); level++)
    {
        int index = key[level] - 'a';
        if (!temp->children[index])
            temp->children[index] = getNode(level);

        temp = temp->children[index];
    }

    // making the last node's isWordEnd value true
    temp->isWordEnd = freq;
}


bool search(TrieNode *root, char *key)
{
    int length = strlen(key);
    TrieNode *temp = root;
    for (int level = 0; level < length; level++)
    {
        int index = key[level] - 'a';

        if (!temp->children[index])
            return false;

        temp = temp->children[index];
    }

    return (temp != NULL && temp->isWordEnd);
}


bool isLastNode(TrieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}


void auto_suggestion_helper(TrieNode *root, char *currPrefix, int k)
{
    // string is found with given prefix
    if (root->isWordEnd)
    {
        if (!add_to_buffer(currPrefix, root->isWordEnd))
            return;
    }


    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currPrefix[k] = (97 + i);

            k++;
            currPrefix[k] = '\0';
            auto_suggestion_helper(root->children[i], currPrefix, k);
            k--;
        }
    }
}



int display_auto_suggestion(TrieNode *root, char *query)
{
    TrieNode *temp = root;

    
    int level;
    int n = strlen(query);
    
    for (level = 0; level < n; level++)
    {
        int index = query[level] - 'a';

        // string not found with given prefix
        if (!temp->children[index])
            return 0;

        temp = temp->children[index];
    }

    // If prefix is present as a word.
    bool isWord = (temp->isWordEnd > 0);
    if (isWord)
    {
        temp->isWordEnd++;
    }

    // prefix is last node of tree
    bool isLast = isLastNode(temp);

    // prefix is present as word but there is no subtree to it
    if (isWord && isLast)
    {
        return -1;
    }

    
    if (!isLast)
    {
        char prefix[100];
        for (int i = 0; i < n; i++)
        {
            prefix[i] = query[i];
        }
        prefix[n] = '\0';

        auto_suggestion_helper(temp, prefix, n);

        sort_and_print();   // sort and print the auto suggestions

        empty_buffer();   // reset the buffer

        return 1;
    }
}

/*---------------------------------Trie functions ends----------------------------------*/




