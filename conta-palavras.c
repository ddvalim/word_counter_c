#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int substring_count(char* string, char* substring) {
  int i, j, l1, l2;
  int count = 0;

  l1 = strlen(string);
  l2 = strlen(substring);

  for(i = 0; i < l1 - l2 + 1; i++) {
    if(strstr(string + i, substring) == string + i) {
      count++;
      i = i + l2 -1;
    }
  }

  return count;
}

int conta_palavras(int argc, char *argv[]) {
    FILE *f;
    char palavra[256];
    int words_counter = 0;

    if (argc != 3) {
        printf("Invalid arg count: %d\n", argc);
        exit(EXIT_FAILURE);
    }

    f = fopen(argv[1], "rt");
    if (f == NULL) {
        printf("Could not open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%s", palavra);
    while (!feof(f))
    {
        if (palavra){
            words_counter += substring_count(palavra, argv[2]);
        }
        fscanf(f, "%s", palavra);
    }

    fclose(f);
    printf("word %s count: %d\n", argv[2], words_counter);
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    conta_palavras(argc, argv);
}
