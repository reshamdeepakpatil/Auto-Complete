#include <stdbool.h>
#define ALPHABET_SIZE (26)



/*----------------Typedef and struct-------------------*/

typedef struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char data;
    int isWordEnd;
}TrieNode;

typedef struct container
{
    char *arr;
    int freq;
} container;

/*------------------------------------------------------*/


TrieNode * getNode(char ch);
void insert_trie(TrieNode *root, char *key, int freq);
bool search(TrieNode *root, char *key);
int display_auto_suggestion(TrieNode *root, char *query);






