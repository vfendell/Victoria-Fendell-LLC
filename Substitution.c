#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
bool validate_key(string key);
string substitute(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check if program was run with one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Validate key
    string key = argv[1];
    if (!validate_key(key))
    {
        printf("Key must contain 26 alphabetic characters!\n");
        return 1;
    }
    // Get plaintext from user
    string plaintext = get_string("Plaintext: ");

    // Encrypt plaintext
    string ciphertext = substitute(plaintext, key);

    // Output ciphertext
    printf("ciphertext: %s\n", ciphertext);

    free(ciphertext);

    return 0;
}

// Function to validate key
bool validate_key(string key)
{
    // Check key length
    if (strlen(key) != 26)
    {
        return false;
    }

    // Array to check for duplicate characters
    bool used[26] = {false};

    // check if characters are alphabetic and unique
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        // Convert character to uppercase
        int index = toupper(key[i]) - 'A';

        // Check for duplicates
        if (used[index])
        {
            return false;
        }

        // Mark letter as used
        used[index] = true;
    }

    return true;
}

// Function to substitute plaintext with key
string substitute(string plaintext, string key)
{
    int n = strlen(plaintext);

    string ciphertext = malloc(n + 1);
    if (ciphertext == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int index = islower(plaintext[i]) ? plaintext[i] - 'a' : plaintext[i] - 'A';

            // Substitute character based on key
            if (islower(plaintext[i]))
            {
                ciphertext[i] = tolower(key[index]);
            }
            else
            {
                ciphertext[i] = toupper(key[index]);
            }
        }
        else
        {
            // Non-alphabetic characters remain unchanged
            ciphertext[i] = plaintext[i];
        }
    }

    // Null-terminate the ciphertext
    ciphertext[n] = '\0';

    return ciphertext;
}
