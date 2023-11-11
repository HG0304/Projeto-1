#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Funcao para limpar o buffer e evitar erros na armazenagem dos dados e acumulo de lixo na memoria
void limparBuffer() {
    // Le e ignora os caracteres do buffer de entrada até encontrar "\n " ou atingir o final do arquivo (EOF)
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// funcao para criar uma nova tarefa
int NovaTarefa(ListadeTarefas *lt) {
    printf("\n_________________________________________\n");
    printf("____________Cadastrar Tarefa:_____________\n");

    // Tarefa criada na ultima posicao do array
    Task *newTask = &(lt -> Task[lt -> taskCount]);
    
    limparBuffer();
    printf("Descricao:\n-> ");
    // fgets para ler a string com espacos
    fgets(newTask -> descricao, sizeof(newTask -> descricao), stdin);

    // Removendo o \n do final da string
    newTask -> descricao[strcspn(newTask -> descricao, "\n")] = 0;    

    limparBuffer();
    printf("Categoria:\n-> ");
    fgets(newTask -> categoria, sizeof(newTask -> categoria), stdin);
    newTask -> categoria[strcspn(newTask -> categoria, "\n")] = 0;

    char prioridadeStr[11];
    do { // laco para garantir que a prioridade estara entre 0 e 10
        printf("digite uma prioridade entre 0 e 10:\n-> ");
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin);
        newTask -> prioridade = atoi(prioridadeStr);
    } while (newTask -> prioridade < 0 || newTask -> prioridade > 10);

    // status da tarefa criada
    newTask -> status = 0;
    // incrementa o contador de tarefas
    lt -> taskCount++;

    printf("Tarefa cadastrada com sucesso!\n");
  return 0;
}

// funcao para listar todas as tarefas existentes
int listTasks(ListadeTarefas lt) {
  printf("\n_________________________________________\n");
  printf("____________Lista de Tarefas:_____________\n");
  
  int print = 0;
  for (int i = 0; i < lt.taskCount; i++) { // Laço de repeticao para iterar sobre os dados da lista e printar eles
    printf("Tarefa %d:\n", i + 1);
    printf("\nDescricao: %s\n", lt.Task[i].descricao);
    printf("Categoria: %s\n", lt.Task[i].categoria);
    printf("Prioridade: %d\n", lt.Task[i].prioridade);
    if (lt.Task[i].status == 0) {
      printf("Status: Pendente\n");
    }
    else if (lt.Task[i].status == 1) {
      printf("Status: Em andamento\n");
    }
    else if (lt.Task[i].status == 2) {
      printf("Status: Concluida\n");
    }
    else if (lt.Task[i].status == 3) {
      printf("Status: Cancelada\n");
    }
    printf("\n");
    print++;
  }
  if (print == 0) {
    printf("Nao ha tarefas cadastradas\n");
  }
}

// funcao para editar uma tarefa
int editaTarefa(ListadeTarefas *lt){
    printf("\n_________________________________________\n");
    printf("____________Editar Tarefa:_____________\n");

    // lista todas as tarefas existentes para que o usuario possa escolher qual deseja editar com base no indice
    listTasks(*lt);

    limparBuffer();
    int index;
    printf("indique o indicie de qual tarefa voce deseja alterar:\n-> ");
    scanf("%d", &index);
    index--;

    // tarefa desejada armazenada na variavel EditTask para facilitar a manipulacao
    Task *EditTask = &(lt -> Task[index]);

    limparBuffer();

    printf("Agora digite qual campo deseja alterar:\n");
    printf("1 - Descricao\n");
    printf("2 - Categoria\n");
    printf("3 - Prioridade\n");
    printf("4 - Status\n");

    int opcao;
    printf("-> ");
    scanf("%d", &opcao);

    // switch case para escolher qual campo deseja alterar
    switch (opcao) {
    case 1:
      limparBuffer();
      printf("Descricao:\n-> ");
      fgets(EditTask -> descricao, sizeof(EditTask -> descricao), stdin);
      EditTask -> descricao[strcspn(EditTask -> descricao, "\n")] = 0;
      break;
    case 2:
      limparBuffer();
      printf("Categoria:\n-> ");
      fgets(EditTask -> categoria, sizeof(EditTask -> categoria), stdin);
      EditTask -> categoria[strcspn(EditTask -> categoria, "\n")] = 0;
      break;
    case 3:
      limparBuffer();
      char prioridadeStr[11];
      do { // laco para garantir que a prioridade estara entre 0 e 10
        printf("digite uma prioridade entre 0 e 10:\n-> ");
        fgets(prioridadeStr, sizeof(prioridadeStr), stdin);
        EditTask -> prioridade = atoi(prioridadeStr);
      } while (EditTask -> prioridade < 0 || EditTask -> prioridade > 10);
      break;
    case 4:
      limparBuffer();
      int prioridade_status;
      printf("Status:\n");
      printf("1 - Pendente\n");
      printf("2 - Em andamento\n");
      printf("3 - Concluida\n");
      printf("4 - Cancelada\n");
      printf("-> ");
      scanf("%d", &prioridade_status);
      prioridade_status--;
      EditTask -> status = prioridade_status;
      break;
    default:
      printf("Opcao invalida!\n");
      break;
    }
  return 0;
}

// funcao para filtrar tarefas por prioridade
int prioridade(ListadeTarefas lt){
    printf("\n_________________________________________\n");
    printf("____________Filtrar por Prioridade:_____________\n");

    int target_prioridade;
    printf("digite uma prioridade entre 0 e 10:\n-> ");
    scanf("%d", &target_prioridade);

    int print = 0;
    for (int i = 0; i < lt.taskCount; i++){
      if (lt.Task[i].prioridade == target_prioridade)
      {
        printf("Tarefa %d:\n", i + 1);
        printf("\nDescricao: %s\n", lt.Task[i].descricao);
        printf("Categoria: %s\n", lt.Task[i].categoria);
        printf("Prioridade: %d\n", lt.Task[i].prioridade);
        if (lt.Task[i].status == 0){
          printf("Status: Pendente\n");
        }
        else if (lt.Task[i].status == 1){
          printf("Status: Em andamento\n");
        }
        else if (lt.Task[i].status == 2){
          printf("Status: Concluida\n");
        }
        else if (lt.Task[i].status == 3){
          printf("Status: Cancelada\n");
        }
        printf("\n");
        print++;
      }
    }
    if (print == 0) {
    printf("Nao ha tarefas com essa prioridade\n");
    }
  return 0;
}

// funcao para filtrar tarefas por status
int status(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Status:_____________\n");

  int target_status;
  printf("Digite o numero da prioridade que deseja filtrar:\n");
  printf("1 - Pendente\n");
  printf("2 - Em andamento\n");
  printf("3 - Concluida\n");
  printf("4 - Cancelada\n");
  printf("-> ");
  scanf("%d", &target_status);
  target_status--;

  int print = 0;
  for (int i = 0; i < lt.taskCount; i++)
  {
    if (lt.Task[i].status == target_status)
    {
      printf("Tarefa %d:\n", i + 1);
      printf("\nDescricao: %s\n", lt.Task[i].descricao);
      printf("Categoria: %s\n", lt.Task[i].categoria);
      printf("Prioridade: %d\n", lt.Task[i].prioridade);
      if (lt.Task[i].status == 0)
      {
        printf("Status: Pendente\n");
      }
      else if (lt.Task[i].status == 1)
      {
        printf("Status: Em andamento\n");
      }
      else if (lt.Task[i].status == 2)
      {
        printf("Status: Concluida\n");
      }
      else if (lt.Task[i].status == 3)
      {
        printf("Status: Cancelada\n");
      }
      printf("\n");
      print++;
    }
  }
  if (print == 0) {
    printf("Nao ha tarefas com esse status\n");
  }
  return 0;
}

// funcao para filtrar tarefas por categoria
int categoria(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Categoria:_____________\n");

  char target_categoria[100];
  limparBuffer();
  printf("Digite a categoria que deseja filtrar:\n-> ");
  fgets(target_categoria, sizeof(target_categoria), stdin);
  target_categoria[strcspn(target_categoria, "\n")] = 0;

  int print = 0;
  for (int i = 0; i < lt.taskCount; i++)
  {
    if (strcmp(lt.Task[i].categoria, target_categoria) == 0)
    {
      printf("Tarefa %d:\n", i + 1);
      printf("\nDescricao: %s\n", lt.Task[i].descricao);
      printf("Categoria: %s\n", lt.Task[i].categoria);
      printf("Prioridade: %d\n", lt.Task[i].prioridade);
      if (lt.Task[i].status == 0)
      {
        printf("Status: Pendente\n");
      }
      else if (lt.Task[i].status == 1)
      {
        printf("Status: Em andamento\n");
      }
      else if (lt.Task[i].status == 2)
      {
        printf("Status: Concluida\n");
      }
      else if (lt.Task[i].status == 3)
      {
        printf("Status: Cancelada\n");
      }
      printf("\n");
      print++;
    }
  }
  if (print == 0) {
    printf("Nao ha tarefas com essa categoria\n");
    }
  return 0;
}

// funcao para filtrar tarefas por prioridade e categoria
int prioridade_categoria(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Prioridade e Categoria:_____________\n");

  char target_categoria[100];
  limparBuffer();
  printf("Digite a categoria que deseja filtrar:\n-> ");
  fgets(target_categoria, sizeof(target_categoria), stdin);
  target_categoria[strcspn(target_categoria, "\n")] = 0;

  int target_prioridade;
  do { // laco para garantir que a prioridade estara entre 0 e 10
    printf("digite uma prioridade entre 0 e 10:\n-> ");
    scanf("%d", &target_prioridade);
  } while (target_prioridade < 0 || target_prioridade > 10);
  
  int print = 0;
  for (int i = 0; i < lt.taskCount; i++)
  {
    if (strcmp(lt.Task[i].categoria, target_categoria) == 0 && lt.Task[i].prioridade == target_prioridade)
    {
      printf("Tarefa %d:\n", i + 1);
      printf("\nDescricao: %s\n", lt.Task[i].descricao);
      printf("Categoria: %s\n", lt.Task[i].categoria);
      printf("Prioridade: %d\n", lt.Task[i].prioridade);
      if (lt.Task[i].status == 0)
      {
        printf("Status: Pendente\n");
      }
      else if (lt.Task[i].status == 1)
      {
        printf("Status: Em andamento\n");
      }
      else if (lt.Task[i].status == 2)
      {
        printf("Status: Concluida\n");
      }
      else if (lt.Task[i].status == 3)
      {
        printf("Status: Cancelada\n");
      }
      printf("\n");
      print++;
    }
  }
  if (print == 0) {
  printf("Nao ha tarefas com essa categoria e/ou prioridade\n");
  }
  return 0;
}

// funcao para deletar uma tarefa
int deletar(ListadeTarefas *lt) {
  printf("\n_________________________________________\n");
  printf("____________Deletar Tarefa:_____________\n");

  // lista todas as tarefas existentes para que o usuario possa escolher qual deseja deletar com base no indice
  listTasks(*lt);

  limparBuffer();
  int index;
  printf("Indique o indicie de qual tarefa voce deseja deletar:\n-> ");
  scanf("%d", &index);
  index--;

  // tarefa desejada armazenada na variavel DeleteTask para facilitar a manipulacao
  Task *DeleteTask = &(lt -> Task[index]); 

  // tratamento de erros
  if (DeleteTask == NULL) {
    perror("Erro ao deletar tarefa");
    return -1;
  }
  // trata o caso de deletar uma tarefa que nao existe
  if (index >= lt -> taskCount) {
    printf("Tarefa nao existe!\n");
    return -1;
  }

  limparBuffer();

  printf("A tarefa %d foi deletada com sucesso!\n", index + 1);
  for (int i = index; i < lt -> taskCount; i++){
    lt -> Task[i] = lt -> Task[i + 1];
  }
  lt -> taskCount--;
  return 0;
}

// Funcao para escrita do arquivo em binario
int Escreve_bin(ListadeTarefas *lt) {
  FILE *arquivo = fopen("Tarefas/ListaDeTarefas.bin", "wb"); // Abre o arquivo para escrita binario

  // Tratamento de erros
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return 1;
  }

  // Escreve os dados das tarefas no arquivo
  for (int i = 0; i < lt->taskCount; i++) {
    if (lt -> Task[i].descricao[0] != '\0') { // Verifica se a tarefa foi criada
      fwrite(&(lt -> Task[i]), sizeof(Task), 1, arquivo);
    }
  }

  // Fecha o arquivo
  fclose(arquivo);
  return 0;
}

// funcao para ler o arquivo
int Ler_bin(ListadeTarefas *lt) {
  FILE *arquivo = fopen("Tarefas/ListaDeTarefas.bin", "rb"); // Abre o arquivo para leitura em binario

  // tratamento de erros
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return 1;
  }

  // antes de realizar a leitura do arquivo, precisamos obter o numero de
  // tarefas cadastradas nele, para isso vamos realizar 2 etapas: primeiro vamos
  // obter o tamanho do arquivo
  fseek(arquivo, 0, SEEK_END);          // Move o cursor de leitura para o final do arquivo para obter o tamanho do arquivo.
  long tamanhoArquivo = ftell(arquivo); // Obtém o tamanho do arquivo em bytes
  fseek(arquivo, 0, SEEK_SET);          // Move o cursor de leitura de volta para o início do arquivo

  // depois calculamos o numero de tarefas com base no tamanho do arquivo
  lt -> taskCount = tamanhoArquivo / sizeof(Task);

  // Le os dados do arquivo e armazena no array original
  fread(lt, sizeof(Task), lt -> taskCount, arquivo);

  printf("arquivo lido com sucesso");
  fclose(arquivo);
  return 0;
}
