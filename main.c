#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

// Déclarations des fonctions externes que vous testez
extern size_t _ft_strlen(const char *str);
extern size_t _ft_strcpy(char *dest, const char *src);
extern int _ft_strcmp(const char *str1, const char *str2);
extern ssize_t _ft_write(int fd, const void *buf, size_t count);
extern ssize_t _ft_read(int fd, void *buf, size_t count);
extern char *_ft_strdup(const char *str);

void check_errno() {
    if (errno != 0) {
        perror("Error reported");
        errno = 0; // Réinitialiser errno après l'avoir utilisée
    }
}

// Fonction pour tester _ft_strlen
void test_strlen() {
    printf("Testing _ft_strlen...\n");

    // Tres grande string
    char *bigStr = malloc(1000000);
    memset(bigStr, 'A', 1000000);
    bigStr[999999] = '\0';
    size_t resultBig = _ft_strlen(bigStr);
    printf("Length of big string: %zu (Expected: %lu)\n\n", resultBig, strlen(bigStr));
    check_errno();
    free(bigStr);

    // Test avec une chaîne vide
    printf("Testing with an empty string...\n");
    const char *emptyStr = "";
    size_t resultEmpty = _ft_strlen(emptyStr);
    printf("Length of \"\": %zu (Expected: %lu)\n\n", resultEmpty, strlen(emptyStr));
    check_errno();

    // Test avec une chaîne normale
    printf("Testing with a string...\n");
    const char *testStr = "Hello, World!";
    size_t result = _ft_strlen(testStr);
    printf("Length of \"%s\": %zu (Expected: %lu)\n\n", testStr, result, strlen(testStr));
    check_errno();


    // Test avec une chaîne NULL
    printf("Testing with a NULL string...\n");
    const char *nullStr = NULL;
    size_t resultNull = _ft_strlen(nullStr);
    printf("Length of NULL: %zu (Expected: %d)\n\n", resultNull, 0);
    check_errno();
}


/* 
                        NE PAS OUBLIER DE FAIRE ERRNO POUR FT_STRCPY
*/

// Fonction pour tester _ft_strcpy
void test_strcpy() {
    printf("Testing _ft_strcpy...\n");

    // Test avec une chaîne très grande
    printf("Testing with a very large string...\n");
    char *bigStr = malloc(1001);
    memset(bigStr, 'A', 1000);
    bigStr[1000] = '\0';
    char bigDest[1001];
    _ft_strcpy(bigDest, bigStr);
    printf("Source: \"%s\"\nCopied: \"%s\"\n\n", bigStr, bigDest);
    free(bigStr);
    check_errno();

    // Test avec une chaîne vide
    printf("Testing with an empty string...\n");
    char emptySrc[] = "";
    char emptyDest[50];
    _ft_strcpy(emptyDest, emptySrc);
    printf("With empty string:\n");
    printf("Source: \"%s\"\nCopied: \"%s\"\n\n", emptySrc, emptyDest);
    check_errno();

    strcpy(emptyDest, emptySrc); // Copie avec la fonction standard (pour comparaison
    printf("With empty string (standard strcpy):\n");
    printf("Source: \"%s\"\nCopied: \"%s\"\n\n", emptySrc, emptyDest);

    // Test avec une chaîne normale
    printf("Testing with a normal string...\n");
    char src[] = "Copy this string!";
    char dest[50]; // Assurez-vous que la destination est assez grande
    _ft_strcpy(dest, src);
    printf("Source: \"%s\"\nCopied: \"%s\"\n\n", src, dest);
    check_errno();

    // Test avec une chaîne NULL
    printf("Testing with a NULL string...\n");
    char *nullSrc = NULL;
    char nullDest[50];
    _ft_strcpy(nullDest, nullSrc);
    printf("With NULL string:\n");
    printf("Source: \"%s\"\nCopied: \"%s\"\n\n", nullSrc, nullDest);
    check_errno();

    printf("The standard strcpy function would segfault here.\n\n");
}

// Fonction pour tester _ft_strcmp
void test_strcmp() {
    printf("Testing _ft_strcmp...\n");

    // Test avec 2 chaines vides
    printf("Testing with two empty strings...\n");
    const char *emptyStr1 = "";
    const char *emptyStr2 = "";
    int cmpResultEmpty = _ft_strcmp(emptyStr1, emptyStr2);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n", emptyStr1, emptyStr2, cmpResultEmpty, 0);
    check_errno();

    // Test avec une chaîne vide et une chaîne non-vide
    printf("Testing with an empty string and a non-empty string...\n");
    const char *emptyStr = "";
    const char *nonEmptyStr = "Hello, World!";
    int cmpResultEmptyStr = _ft_strcmp(emptyStr, nonEmptyStr);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n", emptyStr, nonEmptyStr, cmpResultEmptyStr, strcmp(emptyStr, nonEmptyStr));
    check_errno();

    // Test avec une chaîne non-vide et une chaîne vide
    printf("Testing with a non-empty string and an empty string...\n");
    int cmpResultStrEmpty = _ft_strcmp(nonEmptyStr, emptyStr);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n", nonEmptyStr, emptyStr, cmpResultStrEmpty, strcmp(nonEmptyStr, emptyStr));
    check_errno();
    
    // Test avec deux chaînes identiques
    const char *str1 = "Hello, World!";
    const char *str2 = "Hello, World!";
    const char *str3 = "Hello, dushbcsui!";

    printf("Testing with two identical strings...\n");
    int cmpResult1 = _ft_strcmp(str1, str2);
    int realCmpResult = strcmp(str1, str2);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n", str1, str2, cmpResult1, realCmpResult);
    check_errno();

    // Test avec deux chaînes différentes
    printf("Testing with two different strings...\n");
    int cmpResult2 = _ft_strcmp(str1, str3);
    int realCmpResult2 = strcmp(str1, str3);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n", str1, str3, cmpResult2, realCmpResult2);
    check_errno();

    // Test avec deux chaînes différentes (inversées)
    printf("Testing with two different strings (reversed)...\n");
    int cmpResult3 = _ft_strcmp(str3, str1);
    int realCmpResult3 = strcmp(str3, str1);
    printf("Comparison between '%s' and '%s' returned %d (Expected: %d)\n\n", str3, str1, cmpResult3, realCmpResult3);
    check_errno();

    // Test avec des chaînes NULL
    printf("Testing with NULL strings...\n");
    const char *nullStr = NULL;
    int cmpResultNull = _ft_strcmp(nullStr, nullStr);
    // int realCmpResultNull = strcmp(nullStr, nullStr);
    printf("Comparison between NULL and NULL returned %d (Expected: %d)\n\n", cmpResultNull, 0);
    check_errno();

    // Test avec une chaîne NULL et une chaîne non-NULL
    printf("Testing with a NULL string and a non-NULL string...\n");
    int cmpResultNullStr = _ft_strcmp(nullStr, str1);
    printf("Comparison between NULL and '%s' returned %d (Expected: %d)\n\n", str1, cmpResultNullStr, -1);
    check_errno();

    // Test avec une chaîne non-NULL et une chaîne NULL
    printf("Testing with a non-NULL string and a NULL string...\n");
    int cmpResultStrNull = _ft_strcmp(str1, nullStr);
    printf("Comparison between '%s' and NULL returned %d (Expected: %d)\n\n", str1, cmpResultStrNull, -1);
    check_errno();
}

// Fonction pour tester _ft_strdup
void test_strdup() {
    printf("Testing _ft_strdup...\n");

    // Test avec une chaîne normale
    printf("Testing with a normal string...\n");
    const char *original = "Duplicate me!";
    char *duplicate = _ft_strdup(original);
    printf("Original: \"%s\"\nDuplicate: \"%s\"\n", original, duplicate);
    check_errno();
    free(duplicate); // Important : libérer la mémoire allouée par _ft_strdup
    printf("\n");

    // Test avec une chaîne vide
    printf("Testing with an empty string...\n");
    const char *emptyStr = "";
    char *emptyDup = _ft_strdup(emptyStr);
    printf("Original: \"%s\"\nDuplicate: \"%s\"\n", emptyStr, emptyDup);
    check_errno();
    free(emptyDup); // Important : libérer la mémoire allouée par _ft_strdup
    printf("\n");

    // Test avec une grande chaîne
    printf("Testing with a large string...\n");
    char *bigStr = malloc(1000);
    memset(bigStr, 'A', 1000);
    bigStr[999] = '\0';
    char *bigDup = _ft_strdup(bigStr);
    printf("Original: \"%s\"\nDuplicate: \"%s\"\n", bigStr, bigDup);
    check_errno();
    free(bigStr); // Important : libérer la mémoire allouée par _ft_strdup
    free(bigDup); // Important : libérer la mémoire allouée par _ft_strdup
    printf("\n");

    // Test avec une chaîne NULL
    printf("Testing with a NULL string...\n");
    const char *nullStr = NULL;
    char *nullDup = _ft_strdup(nullStr);
    printf("Original: \"%s\"\nDuplicate: \"%s\"\n", nullStr, nullDup);
    check_errno();
    free(nullDup); // Important : libérer la mémoire allouée par _ft_strdup
    printf("\n");
}


void test_write() {
    printf("Testing _ft_write...\n");

    // Test avec stdout
    printf("Testing with stdout...\n");
    const char *stdoutMsg = "This message is printed by _ft_write.\n";
    ssize_t stdoutValue = _ft_write(1, stdoutMsg, strlen(stdoutMsg));
    printf("Return value: %zd\n", stdoutValue);
    check_errno();

    // Test avec un message normal (le vrai)
    printf("Testing with a normal message (the real one)...\n");
    const char *msg = "This message is printed by _ft_write.\n";
    ssize_t value = write(1, msg, strlen(msg));
    printf("Return value: %zd\n", value);
    check_errno();
    printf("\n");

    // Test avec un file descriptor ouvert
    printf("Testing with an open file descriptor...\n");
    FILE *file = fopen("test.txt", "w");
    ssize_t fileValue = _ft_write(fileno(file), msg, strlen(msg));
    printf("Return value: %zd\n", fileValue);
    fclose(file);
    check_errno();
    printf("\n");

    // Test avec un fichier invalide
    printf("Testing with an invalid file descriptor...\n");
    ssize_t invalidValue = _ft_write(42, msg, strlen(msg));
    printf("Return value: %zd\n", invalidValue);
    check_errno();
    printf("\n");

    // Test avec la fonction write standard
    printf("Testing with the standard write function...\n");
    ssize_t realInvalidValue = write(42, msg, strlen(msg));
    printf("Expected return value: %zd\n", realInvalidValue);
    check_errno();
    printf("\n");

    // Test avec un message vide
    printf("Testing with an empty message...\n");
    const char *emptyMsg = "";
    ssize_t emptyValue = _ft_write(1, emptyMsg, strlen(emptyMsg));
    printf("Return value: %zd\n", emptyValue);
    check_errno();
    printf("\n");

    // Test avec un message vide (le vrai)
    printf("Testing with an empty message (the real one)...\n");
    ssize_t realEmptyValue = write(1, emptyMsg, strlen(emptyMsg));
    printf("Return value: %zd\n", realEmptyValue);
    check_errno();
    printf("\n");

    // Test avec un message NULL
    printf("Testing with a NULL message...\n");
    const char *nullMsg = NULL;
    ssize_t nullValue = _ft_write(1, nullMsg, 0);
    printf("Return value: %zd\n", nullValue);
    check_errno();
    printf("\n");

    // Test avec un message NULL (le vrai)
    printf("Testing with a NULL message (the real one)...\n");
    ssize_t realNullValue = write(1, nullMsg, 0);
    printf("Return value: %zd\n", realNullValue);
    check_errno();
    printf("\n");
}

void test_read() {
    printf("Testing _ft_read...\n");
    
    // Test avec stdin
    printf("Testing with stdin...\n");
    char buffer[128];
    printf("Please type something and press Enter: ");
    fflush(stdout); // Assurez-vous que le message ci-dessus est affiché avant la lecture

    ssize_t bytes_read = _ft_read(0, buffer, sizeof(buffer) - 1); // Lire à partir de stdin (fd 0)
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Termine correctement la chaîne lue
        printf("Read %zd bytes: %s\n", bytes_read, buffer);
    } else if (bytes_read == 0) {
        printf("End of file reached or no input.\n");
    } else {
        printf("Error occurred during read.\n");
    }
    check_errno();
    printf("\n");
    
    // Test avec un fichier
    printf("Testing with a file...\n");
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    ssize_t fileBytesRead = _ft_read(fileno(file), buffer, sizeof(buffer) - 1);
    if (fileBytesRead > 0) {
        buffer[fileBytesRead] = '\0'; // Termine correctement la chaîne lue
        printf("Read %zd bytes from file: %s\n", fileBytesRead, buffer);
    } else if (fileBytesRead == 0) {
        printf("End of file reached or no input.\n");
    } else {
        printf("Error occurred during read.\n");
    }
    fclose(file);
    printf("\n");
    check_errno();
    printf("\n");

    // Test avec un file descriptor invalide
    printf("Testing with an invalid file descriptor...\n");
    ssize_t invalidBytesRead = _ft_read(42, buffer, sizeof(buffer) - 1);
    if (invalidBytesRead > 0) {
        buffer[invalidBytesRead] = '\0'; // Termine correctement la chaîne lue
        printf("Read %zd bytes from invalid file descriptor: %s\n", invalidBytesRead, buffer);
    } else if (invalidBytesRead == 0) {
        printf("End of file reached or no input.\n");
    } else {
        printf("Error occurred during read.\n");
    }
    check_errno();
    printf("\n");
}


int main() {
    printf("Starting tests...\n\n");
    printf("====================================\n\n");
    test_strlen();
    printf("====================================\n\n");
    test_strcpy();
    printf("====================================\n\n");
    test_strcmp();
    printf("====================================\n\n");
    test_write();
    printf("====================================\n\n");
    test_read();
    printf("====================================\n\n");
    test_strdup();
    printf("====================================\n\n");
    printf("Tests finished.\n");
    return 0;
}
