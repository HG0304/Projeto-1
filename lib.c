#include "lib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

// Funcao para limpar o buffer e evitar erros na armazenagem dos dados e acumulo de lixo na memoria
void limparBuffer() {
  int c;
  // Le e ignora os caracteres do buffer de entrada até encontrar "\n " ou atingir o final do arquivo (EOF)
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// funcao para criar uma nova tarefa
int NovaTarefa(ListadeTarefas *lt) {
    printf("\n_________________________________________\n");
    printf("____________Cadastrar Tarefa:_____________\n");

    // Tarefa criada na ultima posicao do array contido na struct ListadeTarefas
    Task *newTask = &(lt -> Task[lt -> taskCount]);
    
    limparBuffer();
    printf("Descricao:\n-> ");
    // fgets para ler a string com espacos
    fgets(newTask -> descricao, sizeof(newTask -> descricao), stdin);

    // Removendo o \n do final da string
    newTask -> descricao[strcspn(newTask -> descricao, "\n")] = 0;    

    // O mesmo processo para a categoria
    limparBuffer();
    printf("Categoria:\n-> ");
    fgets(newTask -> categoria, sizeof(newTask -> categoria), stdin);
    newTask -> categoria[strcspn(newTask -> categoria, "\n")] = 0;

    // O proxima bloco de codigo serve para garantir que a prioridade sera um numero inteiro entre 0 e 10
    int prioridade;
    do {
        printf("digite uma prioridade entre 0 e 10:\n-> ");
        scanf("%d", &prioridade);
        newTask -> prioridade = prioridade;
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
  
  // Laço de repeticao para iterar sobre os dados da lista e printar eles
  // a variavel print serve para garantir que a mensagem de erro nao sera printada caso nao haja tarefas cadastradas
  int print = 0;
  for (int i = 0; i < lt.taskCount; i++) { 
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
  // caso nao haja tarefas cadastradas, a mensagem de erro sera printada
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

    // switch case para escolher qual campo deseja alterar onde cada case corresponde a um campo
    switch (opcao) {
    case 1:
      // Edita a descricao da tarefa
      limparBuffer();
      printf("Descricao:\n-> ");
      fgets(EditTask -> descricao, sizeof(EditTask -> descricao), stdin);
      EditTask -> descricao[strcspn(EditTask -> descricao, "\n")] = 0;
      break;
    case 2:
       // Edita a categoria da tarefa
      limparBuffer();
      printf("Categoria:\n-> ");
      fgets(EditTask -> categoria, sizeof(EditTask -> categoria), stdin);
      EditTask -> categoria[strcspn(EditTask -> categoria, "\n")] = 0;
      break;
    case 3:
      // Edita a prioridade da tarefa
      limparBuffer();
      int prioridade;
      do { // laco para garantir que a prioridade estara entre 0 e 10
        printf("digite uma prioridade entre 0 e 10:\n-> ");
        scanf("%d", &prioridade);
        EditTask -> prioridade = prioridade;
      } while (EditTask -> prioridade < 0 || EditTask -> prioridade > 10);
      break;
    case 4:
      // Edita o status da tarefa
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

    // array para armazenar as tarefas filtradas
    Task prioridade_filter[100];
    
    // variavel para armazenar a prioridade desejada
    int target_prioridade;
    printf("digite uma prioridade entre 0 e 10:\n-> ");
    scanf("%d", &target_prioridade);

    // laco que itera sobre as tarefas e verifica se a prioridade da tarefa e igual a prioridade desejada
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

        // tarefa filtrada armazenada no array prioridade_filter
        prioridade_filter[print] = lt.Task[i];

        // incrementa a variavel print para garantir que a mensagem de erro nao sera printada caso nao haja tarefas com a prioridade desejada
        print++;
      }
    }
    if (print == 0) {
    printf("Nao ha tarefas com essa prioridade\n");
    }
    else {
      // caso haja tarefas com a prioridade desejada, o usuario pode escolher se deseja salvar as tarefas filtradas em um arquivo txt
      printf("Voce deseja salvar as terefas encontradas em um arquivo txt?\n");
      printf("Digite 1 para sim e 2 para não\n-> ");

      limparBuffer();
      int opcao;
      scanf("%d", &opcao);
      if (opcao == 1) {
        // funcao para exportar as tarefas filtradas para um arquivo txt
        char filtro[11] = "prioridade";
        exporta_txt(prioridade_filter, filtro, print);
        printf("Suas tarefas foram salvas com sucesso\n");
        printf("Voce pode encontrar o arquivo na pasta Tarefas\n");
      }
    }
  return 0;
}

// Função de comparação para qsort
int comparar_prioridade(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskB->prioridade - taskA->prioridade;
}

// funcao para filtrar tarefas por status
int status(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Status:_____________\n");

  // array para armazenar as tarefas filtradas
  Task status_filter[100];

  int target_status;
  printf("Digite o numero da prioridade que deseja filtrar:\n");
  printf("1 - Pendente\n");
  printf("2 - Em andamento\n");
  printf("3 - Concluida\n");
  printf("4 - Cancelada\n");
  printf("-> ");
  scanf("%d", &target_status);
  // decrementa a variavel target_status para que ela corresponda ao indice do array
  target_status--;

  // laco que itera sobre as tarefas e verifica se o status da tarefa e igual ao status desejado
  int print = 0;
  for (int i = 0; i < lt.taskCount; i++) {
    if(target_status == lt.Task[i].status){
      // tarefa filtrada armazenada no array status_filter
      status_filter[print] = lt.Task[i];
      print++;
    }
  }
  // qsort para ordenar as tarefas filtradas por prioridade
  qsort(status_filter, print, sizeof(Task), comparar_prioridade);

  if (print == 0) {
    printf("Nao ha tarefas com esse status\n");
  } else {
    // printa as tarefas filtradas e ordenadas por prioridade
    for(int i = 0; i < print; i++){
    printf("Tarefa %d:\n", i + 1);
    printf("\nDescricao: %s\n", status_filter[i].descricao);
    printf("Categoria: %s\n", status_filter[i].categoria);
    printf("Prioridade: %d\n", status_filter[i].prioridade);
    if (status_filter[i].status == 0)
    {
      printf("Status: Pendente\n");
    }
    else if (status_filter[i].status == 1)
    {
      printf("Status: Em andamento\n");
    }
    else if (status_filter[i].status == 2)
    {
      printf("Status: Concluida\n");
    }
    else if (status_filter[i].status == 3)
    {
      printf("Status: Cancelada\n");
    }
    printf("\n");
  }
  printf("Voce deseja salvar as terefas encontradas em um arquivo txt?\n");
  printf("Digite 1 para sim e 2 para não\n-> ");

  limparBuffer();
  int opcao;
  scanf("%d", &opcao);
  if (opcao == 1) {
    char filtro[11] = "Estado";
    exporta_txt(status_filter, filtro, print);
    printf("Suas tarefas foram salvas com sucesso\n");
    printf("Voce pode encontrar o arquivo na pasta Tarefas\n");
    }
  }
  return 0;
}

// funcao para filtrar tarefas por categoria
// a logica e a mesma da funcao status
int categoria(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Categoria:_____________\n");

  Task categoria_filter[100];

  char target_categoria[100];
  limparBuffer();
  printf("Digite a categoria que deseja filtrar:\n-> ");
  fgets(target_categoria, sizeof(target_categoria), stdin);
  target_categoria[strcspn(target_categoria, "\n")] = 0;

  // laco que itera sobre as tarefas e verifica se a categoria da tarefa e igual a categoria desejada
  int print = 0;
  for (int i = 0; i < lt.taskCount; i++){
    if (strcmp(lt.Task[i].categoria, target_categoria) == 0){
      categoria_filter[print] = lt.Task[i];
      print++;
    }
  }
  if (print == 0) {
    printf("Nao ha tarefas com essa categoria\n");
  } else {
    // printa as tarefas filtradas e ordenadas por prioridade
      for(int i = 0; i < print; i++){
      printf("Tarefa %d:\n", i + 1);
      printf("\nDescricao: %s\n", categoria_filter[i].descricao);
      printf("Categoria: %s\n", categoria_filter[i].categoria);
      printf("Prioridade: %d\n", categoria_filter[i].prioridade);
      if (categoria_filter[i].status == 0)
      {
        printf("Status: Pendente\n");
      }
      else if (categoria_filter[i].status == 1)
      {
        printf("Status: Em andamento\n");
      }
      else if (categoria_filter[i].status == 2)
      {
        printf("Status: Concluida\n");
      }
      else if (categoria_filter[i].status == 3)
      {
        printf("Status: Cancelada\n");
      }
      printf("\n");
      }
      printf("Voce deseja salvar as terefas encontradas em um arquivo txt?\n");
      printf("Digite 1 para sim e 2 para não\n-> ");

      limparBuffer();
      int opcao;
      scanf("%d", &opcao);
      if (opcao == 1) {
        char filtro[11] = "Categoria";
        exporta_txt(categoria_filter, filtro, print);
        printf("Suas tarefas foram salvas com sucesso\n");
        printf("Voce pode encontrar o arquivo na pasta Tarefas\n");
      }
    }
  return 0;
}

// funcao para filtrar tarefas por prioridade e categoria
// a logica e a mesma da funcao status, porem com dois parametros para filtrar
int prioridade_categoria(ListadeTarefas lt){
  printf("\n_________________________________________\n");
  printf("____________Filtrar por Prioridade e Categoria:_____________\n");

  Task prioridade_categoria_filter[100];

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
  for (int i = 0; i < lt.taskCount; i++) {
    if (strcmp(lt.Task[i].categoria, target_categoria) == 0 && lt.Task[i].prioridade == target_prioridade){
      prioridade_categoria_filter[print] = lt.Task[i];
      print++;
      }
    }
  if (print == 0) {
  printf("Nao ha tarefas com essa categoria e/ou prioridade\n");
  } else {
    for (int i = 0; i < print; i++) {
      // strcmp para comparar as strings
      printf("Tarefa %d:\n", i + 1);
      printf("\nDescricao: %s\n", prioridade_categoria_filter[i].descricao);
      printf("Categoria: %s\n", prioridade_categoria_filter[i].categoria);
      printf("Prioridade: %d\n", prioridade_categoria_filter[i].prioridade);
      if (prioridade_categoria_filter[i].status == 0)
      {
        printf("Status: Pendente\n");
      }
      else if (prioridade_categoria_filter[i].status == 1)
      {
        printf("Status: Em andamento\n");
      }
      else if (prioridade_categoria_filter[i].status == 2)
      {
        printf("Status: Concluida\n");
      }
      else if (prioridade_categoria_filter[i].status == 3)
      {
        printf("Status: Cancelada\n");
      }
      printf("\n");
      }
      printf("Voce deseja salvar as terefas encontradas em um arquivo txt?\n");
      printf("Digite 1 para sim e 2 para não\n-> ");

      limparBuffer();
      int opcao;
      scanf("%d", &opcao);
      if (opcao == 1) {
        char filtro[21] = "Prioridade_Categoria";
        exporta_txt(prioridade_categoria_filter, filtro, print);
        printf("Suas tarefas foram salvas com sucesso\n");
        printf("Voce pode encontrar o arquivo na pasta Tarefas\n");
      }
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
  // decrementa a variavel index para que ela corresponda ao indice do array
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
  // sobrescreve a tarefa deletada com a tarefa seguinte
  for (int i = index; i < lt -> taskCount; i++){
    lt -> Task[i] = lt -> Task[i + 1];
  }
  // decrementa o contador de tarefas
  lt -> taskCount--;
  return 0;
}

// Funcao para escrita do arquivo em binario
int Escreve_bin(ListadeTarefas *lt) {
  FILE *arquivo = fopen("Tarefas/ListaDeTarefas.bin", "wb"); // Abre o arquivo para escrita binario

  // Tratamento de erros
  if (arquivo == NULL) {
    // perror para printar a mensagem de erro
    perror("Erro ao abrir o arquivo");
    return 1;
  }

  // Escreve os dados das tarefas no arquivo
  for (int i = 0; i < lt->taskCount; i++) {
    // Verifica se a tarefa existe
    // evitando que o arquivo seja escrito com lixo na memoria
    if (lt -> Task[i].descricao[0] != '\0') {
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

  printf("Tarefas carregadas com sucesso!\n");
  fclose(arquivo);
  return 0;
}

// Funcao para escrita do arquivos .txt
// Os parametros da funcao sao o array com as tarefas filtradas, o nome do arquivo e o tamanho do array
int exporta_txt(Task filter[100], char* filtro, int len) {
  // Cria o arquivo com o nome da variavel filtro
  char path[100];
  sprintf(path, "Tarefas/%s.txt", filtro);
  FILE *arquivo = fopen(path, "w");

  printf("arquivo criado com sucesso");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return 1;
  }

  // Escreve os dados das tarefas armazenadas no array das tarefas filtradas no arquivo
  for (int i = 0; i < len; i++) {
    char estado[15];
    if (filter[i].status == 0){
      strcpy(estado, "Pendente");
    }
    else if (filter[i].status == 1) {
      strcpy(estado, "Em andamento");
    }
    else if (filter[i].status == 2) {
      strcpy(estado, "Concluida");
    }
    else if (filter[i].status == 3) {
      strcpy(estado, "Cancelada");
    }
    fprintf(arquivo, "Tarefa %d:\nPrioridade: %d | Categoria: %s | Status: %s | Descrição: %s\n",
            i + 1,
            filter[i].prioridade,
            filter[i].categoria,
            estado,
            filter[i].descricao
            );
  }

  printf("arquivo escrito com sucesso");
  fclose(arquivo);
  return 0;
}