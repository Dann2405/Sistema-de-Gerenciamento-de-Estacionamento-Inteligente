#ifndef LISTAESTACIONAMENTO_H
#define LISTAESTACIONAMENTO_H

#include <iostream>
#include <string>
#include "veiculo.h"

struct NoEstacionamento
{
    Veiculo veiculo;           // Dadps do veiculo
    int numeroVaga;            // Numero de vaga
    NoEstacionamento *proximo; // Ponteiro para o próximo nó

    NoEstacionamento(Veiculo v, int vaga)
    {
        veiculo = v;       // Inicializa o veículo
        numeroVaga = vaga; // Inicializa o número da vaga
        proximo = nullptr; // Inicializa o ponteiro como nulo
    }
};

class ListaEstacionamento
{
private:
    NoEstacionamento *inicio; // Ponteiro para o inicio da lista
    int qtdVeiculos;          // Quantidade de veiculos na lista
    int capacidadeTotal;      // Capacidade total do estacionamento
public:
    ListaEstacionamento(int capacidade = 20)
    {
        inicio = nullptr;             // Inicializa o ponteiro como nulo
        qtdVeiculos = 0;              // Inicializa a quantidade de veiculos como 0
        capacidadeTotal = capacidade; // Inicializa a capacidade total do estacionamento
    }
    ~ListaEstacionamento()
    {
        NoEstacionamento *atual = inicio;    // Ponteiro para o nó atual
        NoEstacionamento *proximo = nullptr; // Ponteiro para o proximo nó

        while (atual != nullptr) // Enquanto o nó atual não for nulo
        {
            proximo = atual->proximo; // Armazena o proximo nó
            delete atual;             // Deleta o nó atual
            atual = proximo;          // Move para o próximo nó
        }
    }
    bool inserir(Veiculo veiculo, int vaga)
    {
        if (vaga <= 0 or vaga > capacidadeTotal) // Verifica se a vaga é valida
        {
            cout << "Vaga invalida! As vagas vao de 1 a " << capacidadeTotal << "\n";
            return false;
        }
        if (vagaOcupada(vaga))
        {
            cout << "Vaga " << vaga << " ja ocupada!\n";
            return false;
        }
        if (estaCheio()) // Verifica se o estacionamento esta cheio
        {
            cout << "Estacionamento cheio!\n";
            return false;
        }
        if (buscarVeiculo(veiculo.get_placa()) != nullptr) // Verifica se o veiculo ja esta estacionado
        {
            cout << "Ja existe um veiculo com a placa " << veiculo.get_placa() << " estacionado!\n";
            return false;
        }

        // Cria um novo nó com o veículo e a vaga
        NoEstacionamento *novoNo = new NoEstacionamento(veiculo, vaga);

        // Se a lista estiver vazia, o novo nó sera o inicio
        if (inicio == nullptr)
        {
            inicio = novoNo;
        }
        else
        {
            // Caso contrario, percorre a lista até o final e adiciona o novo nó
            NoEstacionamento *atual = inicio;
            while (atual->proximo != nullptr)
            {
                atual = atual->proximo;
            }
            atual->proximo = novoNo;
        }
        qtdVeiculos++;
        return true;
    }
    bool remover(const string &placa)
    {
        if(estaVazio())
        {
            cout << "\nEstacionamento vazio!\n";
            return false;
        }

        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual
        NoEstacionamento *anterior = nullptr; // Ponteiro para o nó anterior

        while (atual != nullptr and atual->veiculo.get_placa() != placa) // Percorre a lista até encontrar o veiculo com uma plca especifica
        {
            anterior = atual; // Armazena o nó anterior
            atual = atual->proximo; // Move para o proximo nó
        }

        if (atual == nullptr) // Se o nó atual for nulo, o veiculo não foi encontrado
        {
            cout << "Veiculo com a placa " << placa << " nao encontrado!\n";
            return false;
        }

        if (anterior == nullptr) // Se o nó anterior for nulo, o veiculo esta no inicio da lista
        {
            inicio = atual->proximo; // Move o inicio para o proximo nó
        }
        else
        {
            anterior->proximo = atual->proximo; // Remove o nó atual da lista
        }

        //libera memoria do nó atual
        delete atual; // Deleta o nó atual
        qtdVeiculos--; // Decrementa a quantidade de veiculos

        return true;
    }

    Veiculo *buscarVeiculo(const string &placa)
    {
        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual

        while (atual != nullptr) // Percorre a lista até encontrar o veiculo com yuma placa especifica
        {
            if (atual->veiculo.get_placa() == placa) // Se o veiculo for encontrado
            {
                return &(atual->veiculo); // Retorna o endereço do veiculo
            }
            atual = atual->proximo; // Move para o proximo nó
        }

        return nullptr; // Se o veiculo não for encontrado, retorna nulo
    }

    int buscarVaga(const string &placa)
    {
        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual

        while(atual != nullptr) // Percorre a lista até encontrar o veiculo com uma placa especifica
        {
            if (atual->veiculo.get_placa() == placa) // Se o veiculo for encontrado
            {
                return atual->numeroVaga; // Retorna o numero da vaga
            }
            atual = atual->proximo; // Move para o proximo nó
        }

        return -1; // Se o veiculo não for encontrado, retorna -1
    }

    int proximaVagaLivre() const
    {
        bool *vagasOcupadas = new bool[static_cast<std::size_t>(capacidadeTotal + 1)]();  // Vetor de booleanos para verificar as vagas ocupadas

        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual
        while (atual != nullptr) // Percorre a lista de veiculos
        {
            vagasOcupadas[atual->numeroVaga] = true; // Marca a vaga como ocupada
            atual = atual->proximo; // Move para o proximo nó
        }

        int vagaLivre = -1; // Inicializa a vaga livre como -1
        for (int i = 1; i <= capacidadeTotal; i++) // Percorre o vetor de vagas ocupadas
        {
            if (!vagasOcupadas[i]) // Se a vaga não estiver ocupada
            {
                vagaLivre = i; // Armazena a vaga livre
                break; // Sai do loop
            }
        }

        delete[] vagasOcupadas; // Libera a memoria do vetor de vagas ocupadas
        return vagaLivre; // Retorna a vaga livre
    }

    bool estaCheio() const // Verifica se o estacionamento esta cheio
    {
        return qtdVeiculos >= capacidadeTotal; // Retorna verdadeiro se a quantidade de veiculos for maior ou igual a capacidade total
    }
    bool estaVazio() const // Verifica se o estacionamento esta vazio
    {
        return qtdVeiculos == 0; // Retorna verdadeiro se a quantidade de veiculos for igual a 0
    }
    int getQuantidadeVeiculos() const // Retorna a quantidade de veiculos estacionados
    {
        return qtdVeiculos; // Retorna a quantidade de veiculos
    }
    void listar() const // Lista todos os veiculos estacionados
    {
        if(estaVazio()) // Verifica se o estacionamento está vazio
        {
            cout << "\nEstacionamento vazio!\n";
            return;
        }

        cout << "\n--- Veiculos Estacionados ---\n";
        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual
        while(atual != nullptr) // Percorre a lista de veiculos
        {
            cout << "Vaga " << atual->numeroVaga << ": "; // Imprime o numero da vaga
            atual->veiculo.print_dados(); // Imprime os dados do veiculo
            cout << "\n";
            atual = atual->proximo; // Move para o proximo nó
        }

        cout << "\nTotal de veiculos estacionados: " << qtdVeiculos << " de " << capacidadeTotal << " vagas\n"; // Imprime a quantidade de veiculos
    }

    bool vagaOcupada(int vaga) const // Verifica se uma vaga especifica esta ocupada
    {
        NoEstacionamento *atual = inicio; // Ponteiro para o nó atual
        while (atual != nullptr) // Percorre a lista de veiculos
        {
            if (atual->numeroVaga == vaga) // Se a vaga estiver ocupada
            {
                return true; // Retorna verdadeiro
            }
            atual = atual->proximo; // Move para o proximo nó
        }
        return false; // Retorna falso se a vaga não estiver ocupada
    }
};
#endif // LISTAESTACIONAMENTO_H