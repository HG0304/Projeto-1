// Struct que define as tarefas
typedef struct {
  char descricao[300];
  char categoria[100];
  int prioridade;
  int status;
} Task;

// Struct que armazena as tarefas
typedef struct {
  Task Task[100]; // array que armazena as 100 tarefas
  int taskCount;  // contador de tarefas
} ListadeTarefas;

// Funções
int NovaTarefa(ListadeTarefas *lt);
int editaTarefa(ListadeTarefas *lt);
int listTasks(ListadeTarefas lt);
void Escreve_bin();
void Ler_bin();
void limparBuffer();
int prioridade(ListadeTarefas lt);

// To do
// int status(Task *tasks, int taskCount);
// int categoria(Task *tasks, int taskCount);
// int exportar(Task *tasks, int taskCount);