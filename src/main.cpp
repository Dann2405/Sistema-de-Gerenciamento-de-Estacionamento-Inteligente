#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <fstream>
#include <ctime>
#include "include/veiculo.h"
#include "include/fila_saida.h"
#include "include/ListaEstacionamento.h"

using namespace std;

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

string resp;

void menu();
void limparConsole();
void visualizarHistorico();
void logEvento(const string &evento);
void inserirVeiculo(queue<Veiculo> &filaEntrada);
void visualizarEstacionamento(const queue<Veiculo> &filaEntrada, const ListaEstacionamento &estacionamento, const FilaSaida &filaSaida); // Visualiza o estacionamento
void moverParaVaga(queue<Veiculo> &filaEntrada, ListaEstacionamento &estacionamento);
void enviarParaFilaSaida(ListaEstacionamento &estacionamento, FilaSaida &filaSaida);
void saidaVeiculos(FilaSaida &filaSaida);

int main()
{
    int op;
    queue<Veiculo> filaEntrada;            // Fila de entrada de veiculos
    ListaEstacionamento estacionamento(5); // Estacionamento com capacidade para 5 veiculos
    FilaSaida filaSaida;

    do
    {
        menu();       // chama a função menu para exibir as opções
        cin >> op;    // ler a opção escolhida pelo usuário
        cin.ignore(); // limpa o buffer de entrada

        limparConsole(); // limpa o console para uma melhor visualização

        switch (op)
        {
        case 1:
            inserirVeiculo(filaEntrada); // chama a função para inserir um veiculo na fila de entrada
            break;
        case 2:
            visualizarEstacionamento(filaEntrada, estacionamento, filaSaida); // chama a função para visualizar o estacionamento
            break;
        case 3:
            moverParaVaga(filaEntrada, estacionamento);
            break;
        case 4:
            enviarParaFilaSaida(estacionamento, filaSaida);
            break;
        case 5:
            saidaVeiculos(filaSaida); // chama a funcao de realizar saida pela frente ou fundo
            break;
        case 6:
            visualizarHistorico(); // chama a funcao de Visualizar historico salvo em arquivo .txt
            break;

        case 0:
            cout << "\nSaindo do sistema...";
            logEvento("Sistema encerrado pelo usuario.");
            break;

        default:
            cout << "\nOpcao invalida! Tente novamente.";
            break;
        }

    } while (op != 0);
}

void limparConsole()
{
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
    cout << "\n5. Realizar a saida de veiculo pela frente ou fundo";
    cout << "\n6. Visualizar historico salvo em arquivo";
    cout << "\n0. Exit";
    cout << "\nEscolha uma opcao: ";
}

void inserirVeiculo(queue<Veiculo> &filaEntrada)
{
    Veiculo novoVeiculo; // Novo veiculo a ser inserido
    do
    {
        novoVeiculo.set_dados();       // Chama a função para definir os dados do veiculo
        filaEntrada.push(novoVeiculo); // Adiciona o veiculo a fila de entrada
        cout << "\nVeiculo inserido na fila de entrada com sucesso!";
        cout << "\nDeseja inserir outro veiculo? (Sim/Nao): ";
        getline(cin >> ws, resp);

    } while (resp == "Sim" or resp == "sim" or resp == "SIM" or resp == "S" or resp == "s");

    logEvento("Veiculo inserido na fila de entrada: " + novoVeiculo.get_placa());

}
void visualizarEstacionamento(const queue<Veiculo> &filaEntrada, const ListaEstacionamento &estacionamento, const FilaSaida &filaSaida)
{
    cout << "\n================================================================";
    cout << "\n\tEstado Atual do Estacionamento";
    cout << "\n================================================================\n";

    // Mostrar fila de entrada
    cout << "\n--- Fila de Entrada ---\n";
    if (filaEntrada.empty())
    {
        cout << "Fila de entrada vazia!\n";
    }
    else
    {
        queue<Veiculo> filaCopia = filaEntrada; // Criado uma copia para nao alterar a original
        int contador = 1; // Contador para numerar os veiculos na fila

        while (!filaCopia.empty())
        {
            cout << contador << ". ";
            filaCopia.front().print_dados();
            filaCopia.pop();
            contador++;
        }
    }

    // Mostrar estacionamento
    cout << "\n--- Vagas Ocupadas ---\n";
    estacionamento.listar();

    // Mostrar fila de saida
    cout << "\n--- Fila de Saida ---\n";
    filaSaida.listar();

    cout << "\nPressione Enter para continuar...";
    cin.get();
}

void moverParaVaga(queue<Veiculo> &filaEntrada, ListaEstacionamento &estacionamento)
{
    if (filaEntrada.empty())
    {
        cout << "\nFila de entrada vazia! Nao tem veiculos para estacionar\n";
        return;
    }

    if (estacionamento.estaCheio())
    {
        cout << "\nEstacionamento cheio! Nao tem vagas disponiveis\n";
        return;
    }

    // Mostrar proximo veiculo na fila de entrada
    Veiculo proximo = filaEntrada.front();
    cout << "\nProximo veiculo na fila de entrada: \n";
    proximo.print_dados();

    // Encontrar proxima vaga livre
    int proximaVaga = estacionamento.proximaVagaLivre();

    if (proximaVaga == -1)
    {
        cout << "\nErro ao encontrar vaga disponivel!\n";
        return;
    }

    cout << "\nVaga sugerida: " << proximaVaga << "\n";

    // Perguntar se deseja escolher outra vaga
    cout << "\nDeseja escolher outra vaga? (Sim/Nao): ";
    getline(cin >> ws, resp);

    if (resp == "Sim" or resp == "sim" or resp == "SIM" or resp == "S" or resp == "s")
    {
        int vagaEscolhida;
        cout << "\nDigite o numero da vaga desejada (1-" << 5 << "): "; // Limite de 5 vagas (pode ser alterado)
        cin >> vagaEscolhida;
        cin.ignore();

        if (estacionamento.vagaOcupada(vagaEscolhida))
        {
            cout << "\nVaga " << vagaEscolhida << " ja esta ocupada! Usando vaga sugerida " << proximaVaga << " em vez disso\n";
        }
        else if (vagaEscolhida < 1 or vagaEscolhida > 5) // Limite de 5 vagas (pode ser alterado)
        {
            cout << "\nVaga invalida! Usando vaga sugerida " << proximaVaga << " em vez disso\n";
        }
        else
        {
            proximaVaga = vagaEscolhida;
        }
    }

    // Estacionar o veiculo
    if (estacionamento.inserir(proximo, proximaVaga))
    {
        filaEntrada.pop(); // Remove da fila de entrada

        cout << "\nVeiculo estacionado com sucesso na vaga " << proximaVaga << "!\n";
        logEvento("Veiculo estacionado na vaga " + to_string(proximaVaga) + ": " + proximo.get_placa());
    }
    else
    {
        cout << "\nFalha ao estacionar o veiculo. Tente novamente.\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.get();
}

void enviarParaFilaSaida(ListaEstacionamento &estacionamento, FilaSaida &filaSaida)
{
    if (estacionamento.estaVazio()) // Verifica se o estacionamento esta vazio
    {
        cout << "\nEstacionamento vazio! Nao ha veiculos para enviar a fila de saida\n";
        return;
    }

    // Listar veiculos estacionados
    cout << "\n--- Veiculos Estacionados ---\n";
    estacionamento.listar();

    // Solicitar placa do veiculo a ser movido
    string placa;
    cout << "\nDigite a placa do veiculo que deseja enviar para a fila de saida: ";
    getline(cin, placa);

    // Busca o veiculo
    Veiculo *veiculo = estacionamento.buscarVeiculo(placa);

    if (veiculo == nullptr) // Se o veiculo nao for encontrado
    {
        cout << "\nVeiculo com placa " << placa << " nao encontrado no estacionamento!\n";
        return;
    }

    // Criar uma copia do veiculo antes de remove-lo
    Veiculo veiculoParaSaida = *veiculo;
    int vaga = estacionamento.buscarVaga(placa); // Busca a vaga do veiculo

    // Remover do estacionamento
    if (estacionamento.remover(placa)) // Se o veiculo for removido com sucesso
    {
        // Adicionar a fila de saida por prioridade
        filaSaida.inserirPorPrioridade(veiculoParaSaida);

        cout << "\nVeiculo com placa: " << placa << "\nremovido da vaga: " << vaga << " e enviado para a fila de saida com sucesso!\n";
        logEvento("Veiculo enviado para fila de saida: " + veiculoParaSaida.get_placa());
    }
    else
    {
        cout << "\nFalha ao remover o veiculo do estacionamento\n" ;
    }
}

// Realiza a saida de veiculos pela frente ou fundo
void saidaVeiculos(FilaSaida &filaSaida)
{
    if (filaSaida.estaVazio())
    {
        cout << "Fila de saida esta vazia! Nenhum veiculo para sair." << endl;
        return;
    }

    int opcao;
    cout << "\nDeseja remover o veiculo pela:\n";
    cout << "1. Frente\n";
    cout << "2. Fundo\n";
    cout << "Escolha uma opção: ";
    cin >> opcao;
    cin.ignore();

    Veiculo v;

    if (opcao == 1)
    {
        v = filaSaida.removerFrente();
        if (v.get_placa() != "")
        {
            cout << "\nVeiculo removido pela frente:\n";
            v.print_dados();
            logEvento("Veiculo saiu pela frente: " + v.get_placa()); // caso seja a frente
        }
        else
        {
            cout << "\nNenhum veiculo foi removido (fila vazia).\n";
        }
    }
    else if (opcao == 2)
    {
        v = filaSaida.removerFundo();
        if (v.get_placa() != "")
        {
            cout << "\nVeiculo removido pelo fundo:\n";
            v.print_dados();
            logEvento("Veiculo saiu pelo fundo: " + v.get_placa()); // caso seja o fundo
        }
        else
        {
            cout << "\nNenhum veiculo foi removido (fila vazia).\n";
        }
    }
    else
    {
        cout << "\nOpçao invalida!\n";
    }

    cout << "\nPressione Enter para continuar...";
    cin.get();
}

// Função para registrar eventos no arquivo de log
void logEvento(const string &evento)
{
    ofstream logFile("log.txt", ios::app); // Abre o arquivo em modo de anexar

    if (logFile.is_open())
    {
        time_t now = time(0);                  // Hora atual
        string dt = ctime(&now);               // Converte para string formatada
        dt.pop_back();                         // Remove o '\n' do final

        logFile << "[" << dt << "] " << evento << endl;

        logFile.close();
    }
    else
    {
        cout << "Erro ao abrir o arquivo de log!" << endl;
    }
}

// Função para vizualizar o histórico
void visualizarHistorico()
{
    ifstream logFile("log.txt");

    if (!logFile)
    {
        cout << "\nErro ao abrir o arquivo de log!\n";
        return;
    }

    string linha;
    while (getline(logFile, linha))
    {
        cout << linha << endl;
    }

    logFile.close();
    cout << "\nPressione Enter para continuar...";
    cin.get();
}