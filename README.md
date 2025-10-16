---

# **DIÁRIO DE BORDO – SISTEMA DE ATENDIMENTO UNIVERSITÁRIO**

### Disciplina: Estrutura de Dados

### Instituição: Universidade Federal do Paraná (UFPR)

### Alunos: Ian Almeida, André Ricardo, Esdras Emanuel

### Período: 2025

---

## 1. Introdução

Este diário de bordo apresenta o registro detalhado do desenvolvimento do Sistema de Atendimento Universitário, elaborado em linguagem C para a disciplina de Estrutura de Dados. O projeto teve como objetivo aplicar os conceitos de estruturas lineares e o uso prático de listas e filas dinâmicas.

O sistema simula o fluxo de atendimento de uma clínica universitária, permitindo o cadastro de pacientes, controle da fila de espera, atendimento e consulta de histórico por CPF. O trabalho foi realizado em conjunto pelos integrantes do grupo, com divisão equilibrada das tarefas e cooperação durante todas as etapas.

---

## 2. Objetivos

* Aplicar os conceitos teóricos de estruturas de dados lineares em um projeto prático.
* Desenvolver um sistema modularizado, funcional e estruturado em linguagem C.
* Implementar uma fila de atendimento dinâmica com controle de chegada, atendimento e cancelamento.
* Criar um módulo de histórico de atendimentos por CPF.
* Garantir validação de dados e horários através de funções específicas.

---

## 3. Estrutura do Sistema

O sistema foi dividido em módulos para facilitar o desenvolvimento e a manutenção:

| Arquivo            | Função Principal                                                               |
| ------------------ | ------------------------------------------------------------------------------ |
| `main.c`           | Controla o menu principal e o fluxo do programa.                               |
| `fila.c`           | Gerencia as operações de fila (chegada, atendimento, cancelamento e exibição). |
| `historico.c`      | Registra e consulta o histórico de atendimentos por CPF.                       |
| `validaDataHora.c` | Contém as funções responsáveis por validar data e hora.                        |
| `validaDataHora.h` | Declaração das funções de validação.                                           |

Essa organização modular permitiu que o trabalho fosse desenvolvido de forma colaborativa, com cada integrante responsável por partes específicas do código, mantendo a coerência e integridade geral do sistema.

---

## 4. Funcionalidades

O sistema oferece as seguintes opções principais no menu:

1. **Chegada (Entrar na Fila)** – Cadastra um novo paciente com nome, CPF e horário de chegada.
2. **Atendimento (Chamar Próximo)** – Remove o primeiro paciente da fila e registra o atendimento no histórico.
3. **Ver Fila** – Exibe a fila atual de pacientes aguardando atendimento.
4. **Consultar Histórico de um CPF** – Permite buscar os atendimentos anteriores de um paciente.
5. **Cancelar na Fila** – Remove um paciente da fila utilizando seu CPF.

---

## 5. Desenvolvimento do Projeto

### Etapa 1 – Planejamento

Definição das estruturas básicas de dados utilizando nós e ponteiros. Escolha da estrutura de lista dinâmica encadeada para representar tanto a fila quanto o histórico.
O grupo definiu a divisão de tarefas e organizou o cronograma de implementação.

### Etapa 2 – Implementação da Fila

Criação das funções para adicionar e remover elementos da fila.
Foram realizados testes para garantir a ordem FIFO (First In, First Out) e evitar erros de ponteiros nulos.

### Etapa 3 – Módulo de Histórico

Implementação de uma lista encadeada separada para registrar os atendimentos finalizados.
Adição da função de consulta por CPF, permitindo verificar atendimentos anteriores.

### Etapa 4 – Validação de Data e Hora

Desenvolvimento do módulo `validaDataHora.c`, com as funções:

* `validarData()` – Verifica o formato DD/MM/AAAA, meses válidos e anos bissextos.
* `validarHora()` – Confere o formato HH:MM e os intervalos de horas e minutos.
  Essas funções garantiram a integridade das informações inseridas pelo usuário.

### Etapa 5 – Integração e Testes

Integração de todos os módulos em um único sistema funcional.
Foram realizados testes com diferentes cenários de fila, horários inválidos e consultas de histórico.
A equipe ajustou ponteiros, mensagens e casos de erro até o funcionamento estável do sistema.

---

## 6. Desafios e Soluções

### 1. Gerenciamento de memória

Inicialmente, ocorreram falhas de segmentação causadas por uso incorreto de ponteiros.
O grupo solucionou o problema com verificações de alocação (`if (ptr != NULL)`) e liberação correta de memória (`free()`).

### 2. Entrada de dados inválida

Durante os testes, entradas incorretas causavam travamentos.
Foi criado o módulo `validaDataHora.c` para garantir que apenas datas e horários válidos fossem aceitos.

### 3. Integração entre módulos

Houve dificuldades na comunicação entre arquivos `.c` e `.h`, resolvidas com padronização dos cabeçalhos e inclusões corretas.

### 4. Sincronização entre fila e histórico

O desafio foi transferir corretamente os dados do paciente atendido para o histórico sem perder informações.
A equipe criou estruturas independentes para cada módulo, garantindo o funcionamento correto.

### 5. Testes e consistência

Casos como fila vazia ou CPF inexistente foram tratados com verificações adicionais e mensagens de retorno, evitando erros de execução.

---

## 7. Resultados Obtidos

O sistema foi finalizado com todas as funcionalidades planejadas e apresentou estabilidade durante os testes.
Foram confirmadas:

* Inserção e remoção corretas na fila.
* Armazenamento e consulta de histórico por CPF.
* Validação confiável de datas e horários.
* Interface textual funcional e de fácil uso.

O grupo conseguiu cumprir os objetivos definidos e demonstrar domínio prático sobre os conceitos de estrutura de dados.

---

## 8. Conclusão

O desenvolvimento do Sistema de Atendimento Universitário proporcionou aprendizado significativo sobre estruturas dinâmicas, modularização de código e manipulação de ponteiros.
O trabalho em equipe foi fundamental para o sucesso do projeto, permitindo a troca de conhecimentos e a resolução conjunta de problemas técnicos.

O sistema atingiu seus objetivos principais e serviu como uma aplicação prática dos conceitos estudados em sala de aula. Além disso, mostrou a importância de validar dados e planejar a arquitetura do código antes da implementação.

---

## 9. Possíveis Melhorias Futuras

* Implementar salvamento dos dados em arquivos externos (.txt ou .bin).
* Criar uma interface gráfica simples para interação mais intuitiva.
* Adicionar prioridade na fila por critérios como idade ou urgência.
* Melhorar a organização do histórico com filtros e ordenações.

---

## 10. Conclusão Geral

O projeto foi desenvolvido de forma colaborativa e estruturada.
Os integrantes participaram ativamente de todas as etapas, desde o planejamento até os testes finais.
Os desafios encontrados serviram como oportunidade de aprendizado, e as soluções aplicadas reforçaram o domínio sobre a linguagem C e os conceitos de estrutura de dados.

O resultado final é um sistema funcional, modular e coerente com os objetivos propostos pela disciplina, demonstrando o comprometimento e o trabalho em equipe dos alunos envolvidos.

---



