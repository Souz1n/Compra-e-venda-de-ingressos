#ifndef funcoes_h 
#define funcoes_h

typedef struct {
    char cpf[13];
    char senha[20];
    char nome[50];
    float reais;
    int is_admin;
} USUARIO;

extern USUARIO usuario_logado; // Declare usuario_logado como extern

void meus_eventos();
void comprar_ingresso();
void saldo(USUARIO *usuario);
void registrar_extrato(USUARIO *usuario, const char *tipo, float valor);
void extrato();
void usuario();
void sacar();
void depositar();
void carregar_eventos();
void atualizar_evento();
void adicionar_evento();
void menu_adm(USUARIO *usuario);
void menu_comum(USUARIO *usuario);
int login_admin();
int login_comum(USUARIO usuarios_fixos[], int *total_usuarios);
void carregar_usuarios(USUARIO usuarios_fixos[], int *total_usuarios);
void salvar_usuario(USUARIO usuarios_fixos[], int total_usuarios);
void cadastrar_usuario(USUARIO usuarios_fixos[], int *total_usuarios);
void registrar_evento_comprado(const char *nome_evento);  // Adicione esta linha
void visualizar_eventos_comprados();
#define NUM_USUARIOS 50

#endif // funcoes_h
