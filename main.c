#include "lib.h"
#include <stdio.h>
#include <string.h>

int main() {
  //Ler_bin();
  int choice;
  ListadeTarefas lt;
  lt.taskCount = 0;
  
  // Inicio da logica do menu
  do {
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

    
    printf("Escolha uma opcao: ");
    scanf("%d", &choice);

    // Cria um Switch Case para funcionamento do menu
    switch (choice) {
    case 1:
      // cadastro de tarefas
      NovaTarefa(&lt);
      break;
    case 2: // editar tarefa
      editaTarefa(&lt);
    case 3: // listar tarefas
      listTasks(lt);
      break;

    case 4: // Filtrar tarefa por prioridade
      
    case 5: // Filtrar tarefa por estado

    case 6: // Filtrar tarefa por categoria

    case 7: // Filtrar tarefa por prioridade e categoria

    case 8: // deletar tarefa
      // if (taskCount > 0) {

      //   listTasks(lt); // impressao de todas as terefas para o
      //                                // usuario saber qual ele quer deletar

      //   int deleteIndex;
      //   printf("Digite o numero da tarefa a ser deletada (1-%d): ", taskCount);
      //   scanf("%d", &deleteIndex);
      //   limparBuffer();

      //   if (deleteIndex >= 1 && deleteIndex <= taskCount) {
      //     for (int i = deleteIndex - 1; i < taskCount - 1; i++) {
      //       tasks[i] = tasks[i + 1];
      //     }
      //     taskCount--;
      //     printf("Tarefa deletada com sucesso!\n");
      //     Escreve_bin(); // escreve no arquivo
      //   } else {
      //     printf("Numero de tarefa inválido!\n");
      //   }
      // } else {
      //   printf("A lista de tarefas está vazia!\n");
      // }
      // break;
    case 9:  // sair
      printf("Saindo do programa.\n");
      //Escreve_bin();
      return 0;
    default:
      printf("Opçao inválida! Tente novamente.\n");
      break;
    }
  } while (choice != 9);
  
  return 0;
}