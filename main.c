#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

#define NUM_USUARIOS 50

USUARIO usuario_logado;

int main() {
    USUARIO usuarios_fixos[NUM_USUARIOS];

    int total_usuarios = 0; // Inicialmente, temos 0 usuários
    carregar_usuarios(usuarios_fixos, &total_usuarios); // Carregar os usuários do arquivo

    while (1) {
        int tipo_usuario;
        printf("\nSelecione o tipo de usuario para fazer login ou cadastrar:\n");
        printf("1 - Administrador\n");
        printf("2 - Usuario Comum\n");
        printf("3 - Cadastrar novo usuario\n");
        printf("Opcao: ");
        scanf("%d", &tipo_usuario);
        getchar(); // Consumir o caractere de nova linha após scanf

        int login_resultado = -1;
        switch (tipo_usuario) {
            case 1:
                login_resultado = login_admin();
                break;
            case 2:
                login_resultado = login_comum(usuarios_fixos, &total_usuarios);
                break;
            case 3:
                cadastrar_usuario(usuarios_fixos, &total_usuarios);
                continue; // Voltar ao início após cadastro
            default:
                printf("Opcao invalida, tente novamente!\n");
                continue; // Volta ao início para escolher o tipo de usuário novamente
        }

        if (login_resultado == -1) {
            continue; // Tenta fazer login novamente se falhar
        }

        // Chama o menu apropriado com base no tipo de usuário
        if (usuario_logado.is_admin) {
            menu_adm(&usuario_logado);
        } else {
            menu_comum(&usuario_logado);
        }

        // Após exibir o menu, saia do loop
        printf("Saindo...\n");
        exit(0); // Encerra o programa
    }

    

    return 0;
}
