#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int substring_count(char *string, char *substring)
{
  int i, j, l1, l2;
  int count = 0;

  l1 = strlen(string);
  l2 = strlen(substring);

  for (i = 0; i < l1 - l2 + 1; i++)
  {
    if (strstr(string + i, substring) == string + i)
    {
      count++;
      i = i + l2 - 1;
    }
  }

  return count;
}

int main(int argc, char *argv[])
{
  MPI_Init(NULL, NULL);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  if (world_size < 2) {
    fprintf(stderr, "Must at least two processes for this example\n");
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (argc < 3)
  {
    printf("Invalid arg count: %d\n", argc);
    exit(EXIT_FAILURE);
  }
  if(world_rank == 0 ){
    for (int i=2; i < argc; i++){
      MPI_Send(&i, 1, MPI_INT, i-1 % world_size, 0, MPI_COMM_WORLD);
    }
  } else {
    int i;
    MPI_Recv(&i, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("Process %i responsavel por %s\n", world_rank, argv[i]);
    FILE *f;
    
    char palavra[256];
    int words_counter = 0;
    f = fopen(argv[1], "rt");
    if (f == NULL)
    {
      printf("Could not open file %s\n", argv[1]);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    fscanf(f, "%s", palavra);
    while (!feof(f))
    {
      if (palavra)
      {
        words_counter += substring_count(palavra, argv[i]);
      }
      fscanf(f, "%s", palavra);
    }

    fclose(f);
    printf("word %s count: %d\n", argv[i], words_counter);
  

  }
  

  MPI_Finalize();

}
