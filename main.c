#include "lib.h"
#include <stdio.h>
#include <string.h>

struct Task tasks[100]; // Array para armazenar as 100 tarefas
int taskCount = 0;      // Iniciamos um contador de tarefas

int main() {
  Ler_bin();

  // Inicio da logica do menu
  while (1) { // imprime o menu
    printf("\nMenu:\n");
    printf("1. Cadastrar tarefa\n");
    printf("2. Deletar tarefa\n");
    printf("3. Listar tarefas\n");
    printf("4. Sair\n");

    int choice;
    printf("Escolha uma opcao: ");
    scanf("%d", &choice);
    limparBuffer();

    // Cria um Switch Case para funcionamento do menu
    switch (choice) {
    // cadastro de tarefas
    case 1:
      if (taskCount < 100) {
        printf("Cadastrar Tarefa:\n");

        struct Task newTask; // nova tarefa criada
        printf("Descricao: ");
        scanf(" %[^\n]", newTask.descricao);
        limparBuffer();

        printf("Categoria: ");
        scanf(" %[^\n]", newTask.categoria);
        limparBuffer();

        do { // laco para garantir que a prioridade estara entre 0 e 10
          printf("digite uma prioridade entre 0 e 10: \n");
          scanf("%d", &newTask.prioridade);
          limparBuffer();

          if (newTask.prioridade < 0 || newTask.prioridade > 10)
            printf("Por favor digite um nemuro entre 1 e 10 ");
        } while (newTask.prioridade < 0 || newTask.prioridade > 10);

        tasks[taskCount] =
            newTask; // cadastra a nova tarefa no indicie do contador
        taskCount++; // incremeta o contador da terafas

        printf("Tarefa cadastrada com sucesso!\n");
        Escreve_bin(); // escreve no arquivo
      } else {
        printf("A lista de tarefas esta cheia!\n");
      }
      break;

    // Inicia a logica de deletar uma tarefa
    case 2:
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

    // Inicia a logica de listar as tarefas
    case 3:
      if (taskCount > 0) {
        listTasks(tasks, taskCount);
      } else {
        printf("A lista de tarefas está vazia!\n");
      }
      break;

    // Encerra o programa
    case 4:
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