Compra_Venda_Ingressos

Sistema de Gerenciamento de Eventos e Usuários

Este projeto é um sistema em C para gerenciamento de eventos e transações financeiras para diferentes tipos de usuários, com funcionalidades para login, cadastro, manipulação de saldo e controle de eventos.

Estrutura do Projeto
funcoes.h: Arquivo de cabeçalho contendo a definição da estrutura USUARIO.

funcoes.c: Arquivo com as funções principais, incluindo cadastro e login de usuários, manipulação de saldo, gerenciamento de eventos, e outras funcionalidades.

main.c: Arquivo principal que inicia o programa, gerencia o login dos usuários e direciona para os menus específicos de acordo com o tipo de usuário.


Funcionalidades Principais

1. Login e Cadastro
Login de Administrador: Acesso via CPF e senha do administrador. Após login bem-sucedido, o usuário é direcionado ao menu administrativo.
Login de Usuário Comum: Usuários podem fazer login com CPF e senha registrados e acessar o menu de usuário comum.
Cadastro de Usuário: Permite cadastrar novos usuários comuns no sistema.


2. Operações de Usuário
Visualizar Saldo: Exibe o saldo atual do usuário.
Consultar Extrato: Exibe o histórico de transações do usuário.
Depositar e Sacar: Funções para adicionar ou retirar fundos do saldo do usuário.
Compra de Ingresso: Permite a compra de ingressos para eventos, descontando o valor do saldo do usuário e registrando a compra no extrato.
Visualizar Eventos Comprados: Exibe uma lista de eventos comprados pelo usuário.


3. Operações do Administrador
Adicionar Evento: Administrador pode adicionar novos eventos ao sistema.
Atualizar Evento: Permite que o administrador atualize as informações de um evento existente.
Visualizar Eventos: Exibe todos os eventos disponíveis no sistema.
Requisitos
Compilador C: Certifique-se de que possui um compilador C instalado em seu sistema, como gcc.
Arquivo de Usuários (usuarios.dat): O sistema utiliza um arquivo binário para armazenar informações dos usuários.
Arquivo de Eventos (eventos.txt): O sistema utiliza um arquivo de texto para armazenar informações dos eventos.

Como Executar
Compile os arquivos copiando o código:
gcc main.c funcoes.c -o meu_programa

Execute o programa copiando código:.\meu_programa


Observações
Arquivos de Dados: Certifique-se de que usuarios.dat e eventos.txt estão disponíveis na pasta de execução do programa. Caso contrário, o sistema criará novos arquivos automaticamente.
Permissões de Escrita: O programa realiza gravações nos arquivos de dados; verifique se você possui permissão de escrita no diretório.
