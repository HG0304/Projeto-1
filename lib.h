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
void limparBuffer();
int prioridade(ListadeTarefas lt);
int status(ListadeTarefas lt);
int categoria(ListadeTarefas lt);
int prioridade_categoria(ListadeTarefas lt);
int deletar(ListadeTarefas *lt);
int Escreve_bin(ListadeTarefas *lt);
int Ler_bin(ListadeTarefas *lt);
int exporta_txt(Task filter[100], char* filtro, int len);
int comparar_prioridade(const void *a, const void *b);