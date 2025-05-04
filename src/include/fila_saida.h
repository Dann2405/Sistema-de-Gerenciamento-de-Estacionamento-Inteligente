#ifndef FILASAIDA_H
#define FILASAIDA_H

#include <iostream>
#include <deque>
#include "veiculo.h"

using namespace std;

class FilaSaida
{
private:
    deque<Veiculo> fila;

public:
    FilaSaida()
    {
    }
    ~FilaSaida()
    {
    }
    void push_front(Veiculo veiculo) // Adiciona um veiculo na frente d fila (saida pioritaria)
    {
        fila.push_front(veiculo);
    }
    void push_back(Veiculo veiculo) // Adiciona um veiculo no final da fila
    {
        fila.push_back(veiculo);
    }
    Veiculo pop_front() // Remove um veiculo da frente da fila
    {
        if (fila.empty())
        {
            cout << "Fila de saida vazia!\n";
            return Veiculo(); // Retorna um objeto Veiculo vazio
        }
        Veiculo veiculo = fila.front();
        fila.pop_front();
        return veiculo;
    }
    Veiculo pop_back() // Remove um veiculo do final da fila
    {
        if (fila.empty())
        {
            cout << "Fila de saida vazia!\n";
            return Veiculo(); // Retorna um objeto Veiculo vazio
        }
        Veiculo veiculo = fila.back();
        fila.pop_back();
        return veiculo;
    }

    bool vazio() const // Verifica se a fila esta vazia
    {
        return fila.empty();
    }

    int tamanho() const // Retorna o tamanho da fila
    {
        return fila.size();
    }

    void listar() const // Imprime os veiculos da fila
    {
        if (fila.empty())
        {
            cout << "Fila de saida vazia!\n";
            return;
        }
        cout << "Fila de saida:\n";
        int contador = 1;
        for (const auto &veiculo : fila) // Percorre a fila de veiculos
        {
            cout << "Veiculo " << contador << ". ";
            veiculo.print_dados();
            cout << "\n";
            contador++;
        }
    }

    void inserirPorPrioridade(Veiculo veiculo)
    {
        string tipo = veiculo.get_tipo(); // Pega o tipo de veiculo

        if (fila.empty())
        {
            fila.push_back(veiculo); // Se estiver vazia, insere direto
            return;
        }

        if (tipo == "Emergencia")
        {
            fila.push_front(veiculo); // Veículos de emergência têm prioridade máxima
        }
        else if (tipo == "Prioritario")
        {
            // Insere após os de Emergência
            auto it = fila.begin();
            while (it != fila.end() and it->get_tipo() == "Emergencia")
            {
                ++it;
            }
            fila.insert(it, veiculo); // Insere antes dos veículos comuns
        }
        else
        {
            fila.push_back(veiculo); // Veículos comuns vão ao fim
        }
    }
    
    bool estaVazio() const {
        return fila.empty();
    }

    Veiculo removerFrente() {
        if (!fila.empty()) {
            Veiculo v = fila.front();
            fila.pop_front();
            return v;
        }
        return Veiculo(); // retorna veículo "vazio"
    }

    Veiculo removerFundo() {
        if (!fila.empty()) {
            Veiculo v = fila.back();
            fila.pop_back();
            return v;
        }
        return Veiculo(); // retorna veículo "vazio"
    }
};

#endif // FILASAIDA_H