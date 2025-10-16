Este é o seu Diário de Bordo **revisado**, focado no **Sistema de Atendimento de Plantão Psicológico**.

Mantenho a estrutura e a riqueza de detalhes do seu texto original, ajustando o contexto para o tema da psicologia universitária, o que torna o documento ainda mais específico e coeso com a proposta de uma clínica universitária.

---

# 📋 DIÁRIO DE BORDO – SISTEMA DE ATENDIMENTO UNIVERSITÁRIO
## **(Plantão Psicológico)**

### Disciplina: Estrutura de Dados

### Instituição: Universidade Federal do Paraná (UFPR)

### Alunos: Ian Almeida, André Ricardo, Esdras Emanuel

### Período: 2025

---

## 1. Introdução

Este diário de bordo apresenta o registro detalhado do desenvolvimento do **Sistema de Atendimento de Plantão Psicológico Universitário**, elaborado em linguagem C para a disciplina de Estrutura de Dados. O projeto teve como objetivo aplicar os conceitos de estruturas lineares e o uso prático de listas e **filas dinâmicas**.

O sistema simula o fluxo de atendimento em um serviço de **Plantão Psicológico** de uma clínica universitária, permitindo o cadastro de usuários em busca de apoio imediato, o controle da fila de espera, o registro do atendimento e a consulta de histórico por CPF. O trabalho foi realizado em conjunto pelos integrantes do grupo, com divisão equilibrada das tarefas e cooperação durante todas as etapas.

---

## 2. Objetivos

* Aplicar os conceitos teóricos de estruturas de dados lineares em um projeto prático.
* Desenvolver um sistema modularizado, funcional e estruturado em linguagem C.
* Implementar uma **fila de atendimento dinâmica** com controle de chegada, chamada (atendimento) e cancelamento.
* Criar um módulo de **histórico de atendimentos** por CPF para consultas de apoio anteriores.
* Garantir validação de dados e horários através de funções específicas para manter a integridade dos registros.

---

## 3. Estrutura do Sistema

O sistema foi dividido em módulos para facilitar o desenvolvimento e a manutenção, refletindo uma arquitetura limpa:

| Arquivo | Função Principal |
| :--- | :--- |
| `main.c` | Controla o **menu principal** e o fluxo geral do programa. |
| `fila.c` | Gerencia as operações da fila do plantão (chegada, atendimento, cancelamento e exibição). |
| `historico.c` | **Registra e consulta o histórico** de atendimentos psicológicos por CPF. |
| `validaDataHora.c` | Contém as funções responsáveis por **validar data e hora** de forma precisa. |
| `validaDataHora.h` | Declaração das funções de validação. |

Essa organização modular permitiu que o trabalho fosse desenvolvido de forma colaborativa, com cada integrante responsável por partes específicas do código, mantendo a coerência e integridade geral do sistema.

---

## 4. Funcionalidades

O sistema oferece as seguintes opções principais no menu para gerenciar o Plantão Psicológico:

1.  **Chegada (Entrar na Fila)** – Cadastra um novo usuário/paciente com nome, CPF e horário de chegada ao serviço.
2.  **Atendimento (Chamar Próximo)** – Remove o primeiro usuário da fila (ordem de chegada) e registra o início e fim do acolhimento no histórico.
3.  **Ver Fila** – Exibe a fila atual de usuários aguardando o acolhimento no plantão.
4.  **Consultar Histórico de um CPF** – Permite buscar os atendimentos (acolhimentos) anteriores de um usuário, importante para a continuidade do cuidado.
5.  **Cancelar na Fila** – Remove um usuário da fila utilizando seu CPF, caso desista do atendimento imediato.

---

## 5. Desenvolvimento do Projeto

### Etapa 1 – Planejamento
Definição das estruturas básicas de dados utilizando **nós** e **ponteiros**. Escolha da estrutura de **lista dinâmica encadeada** para representar tanto a fila (com lógica **FIFO**) quanto o histórico. O grupo definiu a divisão de tarefas e organizou o cronograma de implementação.

### Etapa 2 – Implementação da Fila
Criação das funções para adicionar (chegada) e remover (atendimento) elementos da fila. Foram realizados testes para garantir a ordem **FIFO (First In, First Out)** e evitar erros de ponteiros nulos no gerenciamento da fila do plantão.

### Etapa 3 – Módulo de Histórico
Implementação de uma lista encadeada separada para registrar os **acolhimentos finalizados**. Adição da função de consulta por CPF, permitindo verificar as intervenções de plantão anteriores.

### Etapa 4 – Validação de Data e Hora
Desenvolvimento do módulo `validaDataHora.c`, com as funções `validarData()` e `validarHora()`. Essas funções garantiram a **integridade temporal** das informações (data/hora de chegada e atendimento), essenciais para o registro clínico.

### Etapa 5 – Integração e Testes
Integração de todos os módulos em um único sistema funcional. Foram realizados testes com diferentes cenários de fila, horários inválidos e consultas de histórico. A equipe ajustou ponteiros, mensagens e casos de erro até o **funcionamento estável** do sistema.

---

## 6. Desafios e Soluções

### 1. Gerenciamento de memória
*Solução:* O grupo solucionou falhas de segmentação com verificações de alocação (`if (ptr != NULL)`) e a **liberação correta de memória** (`free()`) em todas as operações de remoção e término do programa.

### 2. Entrada de dados inválida
*Solução:* Foi criado e implementado o módulo dedicado `validaDataHora.c` para garantir que apenas **datas e horários válidos** fossem aceitos, reforçando a robustez do sistema.

### 3. Sincronização entre fila e histórico
*Solução:* O desafio de transferir dados do paciente atendido para o histórico sem perda foi resolvido criando **estruturas de dados independentes** para cada módulo (`Fila` e `Historico`), mas com funções que copiam os dados do nó da fila para um novo nó do histórico no momento do atendimento.

### 4. Testes e consistência
*Solução:* Casos de borda (como fila vazia ou CPF inexistente) foram tratados com **verificações condicionais** e mensagens de retorno claras, evitando erros de execução e melhorando a usabilidade.

---

## 7. Resultados Obtidos

O sistema de Plantão Psicológico foi finalizado com todas as funcionalidades planejadas e apresentou **estabilidade** durante os testes.

* **Inserção e remoção** corretas na fila (lógica FIFO).
* **Armazenamento e consulta** do histórico de acolhimentos por CPF.
* **Validação confiável** de datas e horários, garantindo a integridade dos registros.
* Interface textual funcional e de fácil uso.

O grupo conseguiu cumprir os objetivos definidos e demonstrar domínio prático sobre os conceitos de estrutura de dados aplicados a um contexto real de atendimento.

---

## 8. Conclusão

O desenvolvimento do Sistema de Plantão Psicológico proporcionou aprendizado significativo sobre **estruturas dinâmicas**, **modularização de código** e **manipulação de ponteiros**. O trabalho em equipe foi fundamental para o sucesso do projeto.

O sistema atingiu seus objetivos principais e serviu como uma aplicação prática dos conceitos estudados em sala de aula, ressaltando a importância de **validar dados** e **planejar a arquitetura** do código.

---

## 9. Possíveis Melhorias Futuras

* Implementar salvamento dos dados em **arquivos externos** (.txt ou .bin) para persistência dos dados entre execuções.
* Adicionar **prioridade** na fila por critérios de urgência definidos pelo profissional (ex: risco).
* Melhorar a organização do histórico com filtros por data ou ordenações.

---

## 10. Conclusão Geral

O projeto foi desenvolvido de forma **colaborativa e estruturada**. O resultado final é um sistema funcional, modular e coerente com os objetivos propostos pela disciplina, demonstrando o comprometimento e o trabalho em equipe dos alunos envolvidos.

---
