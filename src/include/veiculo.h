#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>

using namespace std;

class Veiculo
{
private:
    string placa; // Placa do veículo
    string tipo;  // Comum, Prioritário ou de Emergência
public:
    Veiculo()
    {
        placa = "";
        tipo = "";
    }
    ~Veiculo()
    {
    }
    void set_dados()
    {
        cout << "\n--- INSERIR UM NOVO VEICULO ---\n";
        cout << "Qual a placa do veiculo? ";
        getline(cin>>ws, placa);
        cout << "Informe o tipo de veiculo:\n";
        cout << "1. Comum\n";
        cout << "2. Prioritario\n";
        cout << "3. Emergencia\n";
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;
        cin.ignore(); // Limpa o buffer de entrada

        switch (opcao)
        {
            case 1:
                tipo = "Comum";
                break;
            case 2:
                tipo = "Prioritario";
                break;
            case 3:
                tipo = "Emergencia";
                break;
            default:
                cout << "Opcao invalida. Tipo definido como 'Comum'.\n";
                tipo = "Comum";
        }
    }

    void print_dados() const
    {
        cout << "Placa: " << placa << endl;
        cout << "Tipo: " << tipo << endl;
    }

    string get_placa() const
    {
        return placa;
    }

    string get_tipo() const
    {
        return tipo;
    }

    void set_placa(const string &placa_veiculo)
    {
        placa = placa_veiculo;
    }

    void set_tipo(const string &tipo_veiculo)
    {
        tipo = tipo_veiculo;
    }
};

#endif // VEICULO_H