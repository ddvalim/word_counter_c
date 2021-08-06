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
    int words_counter[argc - 2];
    for (int i=0; i<argc-2; i++){
      words_counter[i] = 0;
    }
    if (argc < 3) {
        printf("Invalid arg count: %d\n", argc);
        exit(EXIT_FAILURE);
    }

    for(int i=2; i<argc; i++){
      f = fopen(argv[1], "rt");
      if (f == NULL) {
          printf("Could not open file %s\n", argv[1]);
          exit(EXIT_FAILURE);
      }

      fscanf(f, "%s", palavra);
      while (!feof(f))
      {
          if (palavra){
              words_counter[i-2] += substring_count(palavra, argv[i]);
          }
          fscanf(f, "%s", palavra);
      }

    fclose(f);
    }
    for(int i=2; i<argc; i++){
      printf("word %s count: %d\n", argv[i], words_counter[i-2]);
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]){
    conta_palavras(argc, argv);
}
