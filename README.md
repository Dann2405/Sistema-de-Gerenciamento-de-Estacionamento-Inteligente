# Sistema de Gerenciamento de Estacionamento Inteligente

Projeto desenvolvido como trabalho para a disciplina de Estrutura de Dados, utilizando C++. O objetivo deste programa é simular o controle de fluxo de veículos em um estacionamento universitário, organizando filas de entrada e saída, alocação de vagas e movimentação interna dos veículos com base em sua prioridade (Comum, Prioritário, Emergência). O sistema aplica conceitos de **fila simples**, **fila dupla (deque)**, **lista ligada** e **vetores** para representar a lógica de funcionamento do estacionamento.

## Funcionalidades

* **Cadastro de Veículos:** Registra placa e tipo (Comum, Prioritário, Emergência).
* **Fila de Entrada (FIFO):** Gerencia a chegada dos veículos ao estacionamento.
* **Lista de Estacionamento:** Controla veículos atualmente estacionados.
* **Fila de Saída (Deque):** Simula a saída por diferentes portões, com remoção pela frente ou fundo.
* **Gerenciamento de Vagas:** Vetor representa as vagas disponíveis, com controle de ocupação.
* **Priorização de Veículos:** Veículos de emergência furam a fila, e prioritários têm precedência.
* **Histórico de Movimentações:** Todas as operações são registradas em um arquivo de log.
* **Menu Interativo:** Simulação completa com opções para realizar todas as operações.

## Requisitos

* Compilador C++ (por exemplo, g++)
* IDLE (por exemplo, VS Code)

## Compilação

Para compilar o projeto, abra o terminal no diretório onde se encontra o arquivo fonte (`main.cpp`) e execute o comando:

```bash
g++ -o estacionamento .\src\main.cpp
```

## Execução

Após a compilação, execute o programa com o comando:

```bash
./estacionamento
```

## Exemplo de Uso

No menu interativo, você poderá:

* Inserir um novo carro na fila de entrada
* Visualizar o estado atual do estacionamento
* Mover um veículo da fila para uma vaga
* Enviar um veículo estacionado para a fila de saída
* Realizar saída pela frente ou fundo
* Visualizar histórico salvo em arquivo

## Desenvolvedores

* Camila Ramos Gomes
* Daniel Soares Oliveira Santos
* Rauan Brandão Batista
