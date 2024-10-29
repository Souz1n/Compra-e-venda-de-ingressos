#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

#define MAX_EVENTOS 5
#define ARQUIVO_BINARIO "usuarios.dat"
#define ARQUIVO_EVENTOS "eventos.txt"
#define ADM_CPF "123"
#define ADM_SENHA "123"

USUARIO usuario_logado;

typedef struct {
    char nome[100];
    char lugar[100];
    int quantidade;
    float preco;
} EVENTO;

EVENTO eventos[MAX_EVENTOS];
int total_eventos = 0;



void carregar_usuarios(USUARIO usuarios_fixos[], int *total_usuarios) {
    FILE *file = fopen(ARQUIVO_BINARIO, "rb");
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo de usuários");
        return;
    }
    *total_usuarios = fread(usuarios_fixos, sizeof(USUARIO), NUM_USUARIOS, file);
    fclose(file);
}

void salvar_usuario(USUARIO usuarios_fixos[], int total_usuarios) {
    FILE *file = fopen(ARQUIVO_BINARIO, "wb");
    if (file == NULL) {
        perror("Não foi possível abrir o arquivo para salvar usuários");
        return;
    }
    fwrite(usuarios_fixos, sizeof(USUARIO), total_usuarios, file);
    fclose(file);
}

void cadastrar_usuario(USUARIO usuarios_fixos[], int *total_usuarios) {
    if (*total_usuarios >= NUM_USUARIOS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }

    USUARIO novo_usuario;
    printf("Digite o CPF: ");
    fgets(novo_usuario.cpf, sizeof(novo_usuario.cpf), stdin);
    novo_usuario.cpf[strcspn(novo_usuario.cpf, "\n")] = 0;

    printf("Digite a senha: ");
    fgets(novo_usuario.senha, sizeof(novo_usuario.senha), stdin);
    novo_usuario.senha[strcspn(novo_usuario.senha, "\n")] = 0;

    printf("Digite o nome: ");
    fgets(novo_usuario.nome, sizeof(novo_usuario.nome), stdin);
    novo_usuario.nome[strcspn(novo_usuario.nome, "\n")] = 0;

    novo_usuario.reais = 0; // Inicializa o saldo em 0
    novo_usuario.is_admin = 0; // Define como usuário comum

    usuarios_fixos[*total_usuarios] = novo_usuario;
    (*total_usuarios)++;
    salvar_usuario(usuarios_fixos, *total_usuarios);
    printf("Usuário cadastrado com sucesso!\n");
}

int login_comum(USUARIO usuarios_fixos[], int *total_usuarios) {
    USUARIO usuario_temp;
    printf("Digite seu CPF: ");
    fgets(usuario_temp.cpf, sizeof(usuario_temp.cpf), stdin);
    usuario_temp.cpf[strcspn(usuario_temp.cpf, "\n")] = 0;

    printf("Digite sua senha: ");
    fgets(usuario_temp.senha, sizeof(usuario_temp.senha), stdin);
    usuario_temp.senha[strcspn(usuario_temp.senha, "\n")] = 0;

    for (int i = 0; i < *total_usuarios; i++) {
        if (strcmp(usuarios_fixos[i].cpf, usuario_temp.cpf) == 0 &&
            strcmp(usuarios_fixos[i].senha, usuario_temp.senha) == 0) {
            usuario_logado = usuarios_fixos[i];
            return 0; // Login bem-sucedido
        }
    }
    printf("CPF ou senha incorretos!\n");
    return -1; // Login falhou
}

int login_admin() {
    char cpf[13], senha[20];
    printf("Digite o CPF do admin: ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    printf("Digite a senha do admin: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = 0;

    // Verifica se o CPF e a senha correspondem ao administrador
    if (strcmp(cpf, ADM_CPF) == 0 && strcmp(senha, ADM_SENHA) == 0) {
        usuario_logado.is_admin = 1; // Define como administrador
        return 0; // Login bem-sucedido
    }

    printf("CPF ou senha do administrador incorretos!\n");
    return -1; // Login falhou
}

void visualizar_eventos(USUARIO *usuario) {
    int opcao;

    do {
        FILE *file = fopen("eventos.txt", "r");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de eventos.\n");
            return;
        }

        total_eventos = 0;
        printf("\nEventos disponiveis:\n");
        while (fscanf(file, "%99[^,],%99[^,],%f,%d\n",
                      eventos[total_eventos].nome,
                      eventos[total_eventos].lugar,
                      &eventos[total_eventos].preco,
                      &eventos[total_eventos].quantidade) == 4) {
            printf("%d - Nome: %s | Lugar: %s | Preco: %.2f | Quantidade: %d\n",
                   total_eventos + 1,
                   eventos[total_eventos].nome,
                   eventos[total_eventos].lugar,
                   eventos[total_eventos].preco,
                   eventos[total_eventos].quantidade);
            total_eventos++;
        }

        fclose(file);

        printf("\nDigite 0 para sair ou qualquer outro numero para sair: ");
        scanf("%d", &opcao);
        getchar();
    } while (opcao != 0);

    printf("Saindo da visualização de eventos.\n");
}

void adicionar_evento(USUARIO *usuario) {
    if (total_eventos >= MAX_EVENTOS) {
        printf("Limite máximo de eventos alcançado.\n");
        return;
    }

    EVENTO novo_evento;

    printf("Digite o nome do evento: ");
    fgets(novo_evento.nome, sizeof(novo_evento.nome), stdin);
    novo_evento.nome[strcspn(novo_evento.nome, "\n")] = 0; // Remove a nova linha

    printf("Digite o lugar: ");
    fgets(novo_evento.lugar, sizeof(novo_evento.lugar), stdin);
    novo_evento.lugar[strcspn(novo_evento.lugar, "\n")] = 0;

    printf("Digite o preco: ");
    scanf("%f", &novo_evento.preco);
    getchar(); // Limpar o buffer

    printf("Digite a quantidade disponivel: ");
    scanf("%d", &novo_evento.quantidade);
    getchar(); // Limpar o buffer

    eventos[total_eventos++] = novo_evento; // Adiciona o novo evento ao array
    printf("\nEvento adicionado com sucesso!\n");

    FILE *file = fopen("eventos.txt", "a");
    if (file == NULL) {
        printf("\nErro ao abrir o arquivo para salvar o evento.\n");
        return;
    }

    fprintf(file, "%s,%s,%.2f,%d\n", novo_evento.nome, novo_evento.lugar, novo_evento.preco, novo_evento.quantidade);
    fclose(file);

}

void atualizar_evento(USUARIO *usuario) {
    carregar_eventos(); 
    if (total_eventos == 0) {
        printf("Nenhum evento encontrado para atualizar.\n");
        return;
    }

    // Exibe os eventos existentes
    printf("Eventos disponíveis:\n");
    for (int i = 0; i < total_eventos; i++) {
        printf("%d - Nome: %s | Lugar: %s | Preço: %.2f | Quantidade: %d\n",
               i + 1, eventos[i].nome, eventos[i].lugar, eventos[i].preco, eventos[i].quantidade);
    }

    int evento_selecionado;
    printf("Escolha o numero do evento que deseja atualizar: ");
    scanf("%d", &evento_selecionado);
    getchar(); // Limpar o buffer

    if (evento_selecionado < 1 || evento_selecionado > total_eventos) {
        printf("Evento inválido.\n");
        return;
    }

    // Ajuste o índice para 0
    EVENTO *evento = &eventos[evento_selecionado - 1];

    // Atualiza as informações do evento
    printf("Atualizando informacoes do evento:\n");

    printf("Novo nome (atual: %s): ", evento->nome);
    fgets(evento->nome, sizeof(evento->nome), stdin);
    evento->nome[strcspn(evento->nome, "\n")] = 0; // Remove a nova linha

    printf("Novo lugar (atual: %s): ", evento->lugar);
    fgets(evento->lugar, sizeof(evento->lugar), stdin);
    evento->lugar[strcspn(evento->lugar, "\n")] = 0;

    printf("Novo preco (atual: %.2f): ", evento->preco);
    scanf("%f", &evento->preco);
    getchar(); // Limpar o buffer

    printf("Nova quantidade (atual: %d): ", evento->quantidade);
    scanf("%d", &evento->quantidade);
    getchar(); // Limpar o buffer

    // Salvar os eventos atualizados no arquivo
    FILE *file = fopen("eventos.txt", "w"); // Abre o arquivo em modo de escrita
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar as atualizacoes.\n");
        return;
    }

    for (int i = 0; i < total_eventos; i++) {
        fprintf(file, "%s,%s,%.2f,%d\n", eventos[i].nome, eventos[i].lugar, eventos[i].preco, eventos[i].quantidade);
    }
    fclose(file);

    printf("Evento atualizado com sucesso!\n");
}


void depositar() {
    float valor;
    printf("Digite o valor para depositar: ");
    scanf("%f", &valor);
    getchar();

    if (valor > 0) {
        usuario_logado.reais += valor;
        registrar_extrato(&usuario_logado, "Deposito", valor);
        salvar_usuario(&usuario_logado, 1);
        printf("Deposito de R$ %.2f realizado com sucesso!\n", valor);
    } else {
        printf("Valor invalido!\n");
    }
}

void sacar() {
    float valor;
    printf("Digite o valor do saque: ");
    scanf("%f", &valor);
    getchar();

    if (valor > usuario_logado.reais) {
        printf("Saldo insuficiente!\n");
    } else if (valor > 0) {
        usuario_logado.reais -= valor;
        registrar_extrato(&usuario_logado, "Saque", valor);
        printf("Saque de R$ %.2f realizado com sucesso!\n", valor);
    } else {
        printf("Valor invalido!\n");
    }
}

void registrar_extrato(USUARIO *usuario, const char *tipo, float valor) {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "extrato_%s.txt", usuario->cpf);
    FILE *file = fopen(nome_arquivo, "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de extrato!\n");
        return;
    }

    fprintf(file, "%s: %.2f | Saldo atual: %.2f\n", tipo, valor, usuario->reais);
    fclose(file);
    printf("Registro do extrato atualizado com sucesso!\n");
}

void extrato() {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "extrato_%s.txt", usuario_logado.cpf);

    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Nenhum extrato disponivel para este usuario.\n");
        return;
    }

    char linha[200];
    printf("Extrato de transacoes:\n");
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }

    fclose(file);
}

void carregar_eventos() {
    FILE *file = fopen("eventos.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de eventos.\n");
        return;
    }

    total_eventos = 0; // Reinicia a contagem de eventos
    while (fscanf(file, "%99[^,],%99[^,],%f,%d\n",
                  eventos[total_eventos].nome,
                  eventos[total_eventos].lugar,
                  &eventos[total_eventos].preco,
                  &eventos[total_eventos].quantidade) == 4) {
        total_eventos++;
    }

    fclose(file);
}

void menu_adm(USUARIO *usuario) {
    printf("\nMENU ADMINISTRADOR - Bem vindo%s\n", "\nADM\n");
    printf("CPF: %s\n", usuario->cpf);

    int selecionar;

    while (1) {
        printf("\n1 - Adicionar evento\n");
        printf("2 - Atualizar evento\n");
        printf("3 - Carregar eventos\n");
        printf("8 - Sair\n");

        printf("\nEscolha uma opcao: \n");
        scanf("%d", &selecionar);
        getchar();

        switch (selecionar) {
            case 1:
                adicionar_evento(usuario);
                break;
            case 2:
                atualizar_evento(usuario);
                break;
            case 3:
                visualizar_eventos(usuario);
                break;
            case 8:
                return;
            default:
                printf("\nOpcao invalida tente novamente\n");
        }    
    }
}

void menu_comum(USUARIO *usuario) {
    int opcao;
    do {
        printf("\nMenu Principal Bem vindo %s\n", usuario->nome);
        printf("CPF: %s\n", usuario->cpf);
        printf("\n1 - Consultar saldo\n");
        printf("2 - Consultar extrato\n");
        printf("3 - Consultar eventos\n");
        printf("4 - Depositar\n");
        printf("5 - Sacar\n");
        printf("6 - Comprar ingresso\n");
        printf("7 - Meus eventos\n");
        printf("8 - Sair\n");

        printf("\nEscolha uma opcao: \n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                saldo(usuario);
                break;
            case 2:
                extrato(usuario);
                break;
            case 3:
                visualizar_eventos(usuario);
                break;
            case 4:
                depositar(usuario);
                break;
            case 5:
                sacar(usuario);
                break;
            case 6:
                comprar_ingresso(usuario);
                break;
            case 7:
                visualizar_eventos_comprados(usuario);
                break;
            case 8:
                return;
            default:
                printf("Opcao invalida tente novamente\n");
        }
        // Salva o usuário após cada operação
        salvar_usuario(&usuario_logado, 1);

    } while (opcao != 0);
}

// Função para mostrar o saldo do usuário logado
void saldo(USUARIO *usuario) {
    printf("Saldo atual de %s (CPF: %s): R$ %.2f\n", usuario->nome, usuario->cpf, usuario->reais);
}

// Função para comprar ingressos
void comprar_ingresso() {
    float valor_ingresso;
    printf("Digite o valor do ingresso que deseja comprar: R$ ");
    scanf("%f", &valor_ingresso);
    getchar(); // Consumir o caractere de nova linha após scanf

    char nome_evento[100];

    printf("Digite o nome do evento: ");
    fgets(nome_evento, sizeof(nome_evento), stdin);
    nome_evento[strcspn(nome_evento, "\n")] = 0;


    if (valor_ingresso <= 0) {
        printf("Valor inválido! O valor do ingresso deve ser maior que zero.\n");
        return;
    }

    if (usuario_logado.reais < valor_ingresso) {
        printf("Saldo insuficiente para comprar o ingresso!\n");
        return;
    }

    registrar_evento_comprado(nome_evento); 
    usuario_logado.reais -= valor_ingresso; // Subtrai o valor do ingresso do saldo
    registrar_extrato(&usuario_logado, "Compra de ingresso", valor_ingresso); // Registra a compra no extrato
    salvar_usuario(&usuario_logado, 1);
    printf("Compra de ingresso no valor de R$ %.2f realizada com sucesso!\n", valor_ingresso);
}

void registrar_evento_comprado(const char *nome_evento) {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "eventos_comprados_%s.txt", usuario_logado.cpf);

    FILE *file = fopen(nome_arquivo, "a");
    if (file == NULL) {
        printf("Erro ao registrar o evento comprado!\n");
        return;
    }

    fprintf(file, "Evento: %s\n", nome_evento);
    fclose(file);
    printf("Registro do evento '%s' atualizado com sucesso!\n", nome_evento);
}

// Função para visualizar eventos comprados
void visualizar_eventos_comprados() {
    char nome_arquivo[50];
    sprintf(nome_arquivo, "eventos_comprados_%s.txt", usuario_logado.cpf);

    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Você ainda não comprou ingressos para nenhum evento.\n");
        return;
    }

    char linha[200];
    printf("Eventos comprados:\n");
    while (fgets(linha, sizeof(linha), file) != NULL) {
        printf("%s", linha);
    }

    fclose(file);
}
