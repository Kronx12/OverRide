#include <stdio.h>

void main(void) {
    size_t i;
    char buffer[100];

    fgets(buffer, 100, stdin);

    for (size_t i = 0; buffer[i]; i++)
        buffer[i] = tolower(buffer[i]);

    if (strlen(buffer) <= i) {
        printf(buffer);
        exit(0);
    }
}
