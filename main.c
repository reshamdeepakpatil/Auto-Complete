#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"
#include "driver.h"


// Driver Code
int main(int argc, char *argv[])
{
    TrieNode *root = getNode('/'); // Create a trie

    add_words_to_trie(root, argv[1]);

    char search[50];

    printf("> > > > > Welcome to word suggestion < < < < <\n\n");
    while (1)
    {
        printf(">>> ");
        scanf("%s", search);
        to_lowercase(search);
        if (strcmp(search, "exit") == 0)
        {
            break;
        }

        int result = display_auto_suggestion(root, search);

        handle_result(root, result, argv[1], search);
    }
    return 0;
}
