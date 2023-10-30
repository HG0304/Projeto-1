#include "lib.h"
#include <stdio.h>
#include <string.h>

Task tasks[100];        // Array para armazenar as 100 tarefas
int taskCount = 0;      // Iniciamos um contador de tarefas

int main() {
  Ler_bin();

  // Inicio da logica do menu
  while (1) { // imprime o menu
    printf("\n________________________________________\n");
    printf("\nMenu:\n");
    printf("1. Cadastrar tarefa\n");
    printf("2. Editar tarefa\n");
    printf("3. Listar tarefas\n");
    printf("4. Filtrar tarefa por prioridade\n");
    printf("5. Filtrar tarefa por estado\n");
    printf("6. Filtrar tarefa por categoria\n");
    printf("7. Filtrar tarefa por prioridade e categoria\n");
    printf("8. Deletar tarefa\n");
    printf("9. Sair\n");
    printf("\n________________________________________\n");

    int choice;
    printf("Escolha uma opcao: ");
    scanf("%d", &choice);

    // Cria um Switch Case para funcionamento do menu
    switch (choice) {
    // cadastro de tarefas
    case 1:
      if (taskCount < 100) {
        printf("Cadastrar Tarefa:\n");

        Task newTask; // nova tarefa criada
        printf("Descricao: ");
        scanf(" %[^\n]", newTask.descricao);

        printf("Categoria: ");
        scanf(" %[^\n]", newTask.categoria);

        do { // laco para garantir que a prioridade estara entre 0 e 10
          printf("digite uma prioridade entre 0 e 10: \n");
          scanf("%d", &newTask.prioridade);

          if (newTask.prioridade < 0 || newTask.prioridade > 10)
            printf("Por favor digite um nemuro entre 1 e 10 ");
        } while (newTask.prioridade < 0 || newTask.prioridade > 10);

        tasks[taskCount] = newTask; // cadastra a nova tarefa no indicie do contador
        taskCount++; // incremeta o contador da terafas

        printf("Tarefa cadastrada com sucesso!\n");
        Escreve_bin(); // escreve no arquivo
      } else {
        printf("A lista de tarefas esta cheia!\n");
      }
      break;
    case 2: // editar tarefa

    case 3: // listar tarefas
      if (taskCount > 0) {
        listTasks(tasks, taskCount);
      } else {
        printf("A lista de tarefas está vazia!\n");
      }
      break;

    case 4: // Filtrar tarefa por prioridade
      
    case 5: // Filtrar tarefa por estado

    case 6: // Filtrar tarefa por categoria

    case 7: // Filtrar tarefa por prioridade e categoria

    case 8: // deletar tarefa
      if (taskCount > 0) {

        listTasks(tasks, taskCount); // impressao de todas as terefas para o
                                     // usuario saber qual ele quer deletar

        int deleteIndex;
        printf("Digite o numero da tarefa a ser deletada (1-%d): ", taskCount);
        scanf("%d", &deleteIndex);
        limparBuffer();

        if (deleteIndex >= 1 && deleteIndex <= taskCount) {
          for (int i = deleteIndex - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
          }
          taskCount--;
          printf("Tarefa deletada com sucesso!\n");
          Escreve_bin(); // escreve no arquivo
        } else {
          printf("Numero de tarefa inválido!\n");
        }
      } else {
        printf("A lista de tarefas está vazia!\n");
      }
      break;
    case 9:  // sair
      printf("Saindo do programa.\n");
      Escreve_bin();
      return 0;
    default:
      printf("Opçao inválida! Tente novamente.\n");
      break;
    }
  }
  return 0;
}