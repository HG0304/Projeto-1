// Criamos o Struct que ira receber as tarefas
struct Task {
  char descricao[100];
  char categoria[300];
  int prioridade;
};

void listTasks(struct Task *tasks, int taskCount);

void Escreve_bin();

void Ler_bin();

void limparBuffer();