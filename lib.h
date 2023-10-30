// Struct que define as tarefas
typedef struct {
  char descricao[100];
  char categoria[300];
  int prioridade;
  int status;
} Task;

// Funções
void listTasks(Task *tasks, int taskCount);
void Escreve_bin();
void Ler_bin();
void limparBuffer();

// To do
int editaTarefa(Task *tasks, int taskCount);
int prioridade(Task *tasks, int taskCount);
int status(Task *tasks, int taskCount);
int categoria(Task *tasks, int taskCount);
int exportar(Task *tasks, int taskCount);