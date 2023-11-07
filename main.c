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
      break;
    case 3: // listar tarefas
      listTasks(lt);
      break;
    case 4: // Filtrar tarefa por prioridade
      prioridade(lt);
      break;
    case 5: // Filtrar tarefa por estado
      status(lt);
      break;
    case 6: // Filtrar tarefa por categoria
      categoria(lt);
      break;
    case 7: // Filtrar tarefa por prioridade e categoria

    case 8: // deletar tarefa
      
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