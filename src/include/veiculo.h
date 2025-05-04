#ifndef VEICULO_H
#define VEICULO_H

#include <iostream>
#include <string>

using namespace std;

class Veiculo {
    private:
        string placa; // Placa do veículo
        string modelo; // Modelo do veículo
        string tipo; // Comum, Prioritário ou de Emergência
    public:
        Veiculo()
        {
            placa = "";
            modelo = "";
            tipo = "";
        }
        ~Veiculo() 
        {
        }
        void set_dados()
        {
            cout << "Qual a placa do veiculo? ";
            getline(cin>>ws, placa);
            cout << "Qual o modelo do veiculo? ";
            getline(cin>>ws, modelo);
            cout << "Qual o tipo do veiculo? (Comum, Prioritario ou Emergencia) ";
            getline(cin>>ws, tipo);
        }
        void print_dados()
        {
            cout << "Placa: " << placa << endl;
            cout << "Modelo: " << modelo << endl;
            cout << "Tipo: " << tipo << endl;
        }
        string get_placa()
        {
            return placa;
        }
        string get_modelo()
        {
            return modelo;
        }
        string get_tipo()
        {
            return tipo;
        }
    };

#endif // VEICULO_H