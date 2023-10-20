#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

int  inputgii(const char *prompt, int *input);
int  inputgsi(const char *prompt, char **input);
int  is_character_type(const char *test, int (*is_type)(int));
int  inputgsin(const char *prompt, char **input, size_t max_length);
void strsnl(char *to_strip);

/**
 * @brief Strips the newline in a newline terminated string.
 *
 * @param to_strip A char array to strip
 */
void
strsnl(char *to_strip)
{
    to_strip[strcspn(to_strip, "\n")] = '\0';
}

/**
 * @brief Gets int input from stdin, loops until complete
 *
 * @param prompt Prompt to print to user
 * @param input Pointer to integer variable for storage
 * @return int Returns 1 on success, 0 on failure
 */
int
inputgii(const char *prompt, int *input)
{
    size_t  size = 0;
    ssize_t read = 0;
    char   *temp = NULL;

    for (;;)
    {
        printf("%s: ", prompt);
        read = getline(&temp, &size, stdin);
        strsnl(temp);

        if (0 <= read && is_character_type(temp, &isdigit))
        {
            sscanf(temp, "%d", input);
            free(temp);
            return 1;
        }
        else
        {
            printf("Could not fetch int input.\n");
        }
    }
    return 0;
}

/**
 * @brief Gets string input from stdin, loops until complete
 *
 * @param prompt Prompt to print to user
 * @param input Pointer to string array for storage
 * @return int Returns 1 on success, 0 on failure
 */
int
inputgsi(const char *prompt, char **input)
{
    size_t  size = 0;
    ssize_t read = 0;
    char   *temp = NULL;

    for (;;)
    {
        printf("%s: ", prompt);
        read = getline(&temp, &size, stdin);
        strsnl(temp);

        if (0 <= read && is_character_type(temp, &isalpha))
        {
            *input = strdup(temp);
            free(temp);
            return 1;
        }
        else
        {
            printf("Could not fetch str input.\n");
        }
    }
    free(temp);
    return 0;
}

/**
 * @brief Gets string input from stdin limited to n characters, loops until complete
 *
 * @param prompt Prompt to print to user
 * @param input Pointer to string array for storage
 * @param max_length A size_t representing the max length
 * @return int Returns 1 on success, 0 on failure
 */
int
inputgsin(const char *prompt, char **input, size_t max_length)
{
    size_t  size = 0;
    ssize_t read = 0;
    char   *temp = NULL;

    for (;;)
    {
        printf("%s (up to %zu characters): ", prompt, max_length);
        read = getline(&temp, &size, stdin);
        strsnl(temp);

        if (max_length >= read && is_character_type(temp, &isalpha))
        {
            *input = strdup(temp);
            free(temp);
            return 1;
        }
        else
        {
            printf("Input length or content is invalid.\n");
        }
    }
    free(temp);
    return 0;
}

/**
 * @brief Checks if a string contains all the specified string comparison
 *
 * @param test A char array to test for type
 * @param is_type A string comparison function to run
 * @return int Returns 1 on true, 0 on false
 */
int
is_character_type(const char *test, int (*is_type)(int))
{
    for (int idx = 0; test[idx] != '\0'; idx++)
    {
        if (!is_type(test[idx]))
        {
            return 0;
        }
    }
    return 1;
}
