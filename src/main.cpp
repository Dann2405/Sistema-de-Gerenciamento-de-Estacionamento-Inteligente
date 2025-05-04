#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <fstream>
#include "include/veiculo.h"

using namespace std;

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

string resp;

void menu();
void limparConsole();
void inserirVeiculo(queue<Veiculo> &filaEntrada);

int main()
{
    int op;
    queue<Veiculo> filaEntrada;

    do
    {
    menu(); // chama a função menu para exibir as opções
    cin >> op; // ler a opção escolhida pelo usuário
    cin.ignore(); // limpa o buffer de entrada

    limparConsole(); // limpa o console para uma melhor visualização

        switch (op)
        {
        case 1:
            inserirVeiculo(filaEntrada); // chama a função para inserir um veiculo na fila de entrada
            break;
        case 2:
            /* chamar a funcao de Visualizar o estado atual do estacionamento */
            break;
        case 3:
            /* chamar a funcao de Mover um veiculo da fila para uma vaga */
            break;
        case 4:
            /* chamar a funcao de Enviar um veiculo estacionado para a fila de saida */
            break;
        case 5:
            /* chamar a funcao de Realizar saida pela frente ou fundo */
            break;
        case 6:
            /* chamar a funcao de Visualizar historico salvo em arquivo */
            break;

        case 0:
            cout << "\nSaindo do sistema...";
            break;

        default:
            cout << "\nOpcao invalida! Tente novamente.";
            break;
        }

    } while (op != 0);
}

void limparConsole() {
    system(CLEAR_COMMAND);
}

void menu()
{
    cout << "\n================================================================";
    cout << "\n\tSistema de Controle de Gerenciamento de Estacionamento";
    cout << "\n================================================================\n";
    cout << "\n1. Inserir um novo carro na fila de entrada";
    cout << "\n2. Visualizar o estado atual do estacionamento";
    cout << "\n3. Mover um veiculo da fila para uma vaga";
    cout << "\n4. Enviar um veiculo estacionado para a fila de saida";
    cout << "\n5. Realizar saida pela frente ou fundo";
    cout << "\n6. Visualizar historico salvo em arquivo";
    cout << "\n0. Exit";
    cout << "\nEscolha uma opcao: ";
}

void inserirVeiculo(queue<Veiculo> &filaEntrada)
{
    Veiculo novoVeiculo; // Novo veiculo a ser inserido
    do
    {
        novoVeiculo.set_dados(); // Chama a função para definir os dados do veiculo
        filaEntrada.push(novoVeiculo); // Adiciona o veiculo a fila de entrada
        cout << "\nVeiculo inserido na fila de entrada com sucesso!";
        cout << "\nDeseja inserir outro veiculo? (Sim/Nao): ";
        getline(cin>>ws, resp);

    } while (resp == "Sim" or resp == "sim" or resp == "SIM" or resp == "S" or resp == "s");
}