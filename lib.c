#include "lib.h"
#include <stdio.h>

// funcao para listar todas as tarefas existentes
void listTasks(struct Task *tasks, int taskCount) {
  printf("\nLista de Tarefas:\n");
  for (int i = 0; i < taskCount; i++) { // Laço de repeticao para iterar sobre
                                        // os dados da lista e printar eles
    printf("Tarefa %d:\n", i + 1);
    printf("\nDescricao: %s\n", tasks[i].descricao);
    printf("Categoria: %s\n", tasks[i].categoria);
    printf("Prioridade: %d\n", tasks[i].prioridade);
    printf("\n");
  }
}

// para escrita e leitura em binario
extern struct Task tasks[100]; // Declarando as variaveis como extern
extern int taskCount;          // Declarando as variaveis como extern

// funcao para escrita do arquivo em binario
void Escreve_bin() {
  FILE *arquivo = fopen("tarefas", "wb"); // Abre o arquivo para escrita binario

  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return; // Retorna se nao for possível abrir o arquivo
  }

  // Escreve os dados das tarefas no arquivo
  size_t result = fwrite(tasks, sizeof(struct Task), taskCount, arquivo);

  // tratamento de erros
  if (result != taskCount) {
    perror("Erro ao escrever no arquivo\n");
    fclose(arquivo); // Fecha o arquivo para evitar algum problema com os dados
    return;
  }
  // Fecha o arquivo
  fclose(arquivo);
}

// funcao para ler o arquivo
void Ler_bin() {
  FILE *arquivo =
      fopen("tarefas", "rb"); // Abre o arquivo para leitura em binario

  // tratamento de erros
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  // antes de realizar a leitura do arquivo, precisamos obter o numero de
  // tarefas cadastradas nele, para isso vamos realizar 2 etapas: primeiro vamos
  // obter o tamanho do arquivo
  fseek(arquivo, 0, SEEK_END); // Move o cursor de leitura para o final do
                               // arquivo para obter o tamanho do arquivo.
  long tamanhoArquivo = ftell(arquivo); // Obtém o tamanho do arquivo em bytes
  fseek(
      arquivo, 0,
      SEEK_SET); //  Move o cursor de leitura de volta para o início do arquivo

  // depois calculamos o numero de tarefas com base no tamanho do arquivo
  taskCount = tamanhoArquivo / sizeof(struct Task);

  // Le os dados do arquivo e armazena no array original
  size_t result = fread(tasks, sizeof(struct Task), taskCount, arquivo);

  if (result != taskCount) {
    perror("Erro ao ler o arquivo");
    return;
  }
  printf("arquivo lido com sucesso");
  fclose(arquivo);
}

// Funcao para limpar o buffer e evitar erros na armazenagem dos dados e acumulo
// de lixo na memoria
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    // Le e ignora os caracteres do buffer de entrada até encontrar "\n " ou
    // atingir o final do arquivo (EOF)
  }
}