# Sistema de Agendamento de Consultas - Clínica Universitária

## 📋 Descrição do Projeto

Este projeto implementa um **Sistema de Agendamento de Consultas** para uma clínica universitária, desenvolvido em linguagem C. O sistema utiliza estruturas de dados eficientes, incluindo **listas encadeadas com cabeçalho**, para gerenciar o cadastro de pacientes e agendamentos de consultas.

## 🎯 Objetivo Geral

Desenvolver uma aplicação funcional em C que utilize listas lineares para armazenamento, manipulação e exibição de dados relacionados ao agendamento de consultas em uma clínica universitária, integrando teoria e prática de estrutura de dados.

## 👥 Público-Alvo

- **Estudantes** e **professores** da universidade
- **Administradores** da clínica universitária

## 🏗️ Estrutura do Projeto

### Arquivos do Sistema
```
sistema_agendamento/
├── main.c                 // Menu principal e controle do sistema
├── paciente.c            // Lógica de cadastro de pacientes
├── paciente.h            // Definições de estruturas de pacientes
├── agendamento.c         // Controle de agendamentos
├── agendamento.h         // Definições de estruturas de agendamentos
├── lista.c               // Implementação das listas encadeadas
├── lista.h               // Definições das estruturas de lista
├── validaDataHora.c      // Validação de data e hora
├── validaCpf.c           // Validação de CPF
├── validaSala.c          // Validação de sala
└── App.exe               // Executável gerado
```

### Estruturas de Dados Principais
- **Listas encadeadas com cabeçalho** para histórico de agendamentos
- **Estruturas dinâmicas** para pacientes e agendamentos
- **Sistema de validação** integrado para dados de entrada

## ⚙️ Compilação e Execução

### Compilação
```bash
gcc lista.c agendamento.c paciente.c main.c validaDataHora.c validaCpf.c validaSala.c -o App.exe
```

### Execução
```bash
./App.exe
```

## 📋 Funcionalidades Implementadas

### ✅ Cadastro de Pacientes
- **Nome completo**
- **CPF** (com validação)
- **Matrícula** universitária
- **Curso** do estudante/professor

### ✅ Gestão de Agendamentos
- **Cadastro de agendamento** (CPF, sala, data, hora)
- **Listagem por CPF** - consulta de agendamentos individuais
- **Listagem por sala** - visualização por local de atendimento
- **Remoção de agendamento** (por CPF + data)
- **Histórico completo** de agendamentos

### ✅ Validações e Restrições
- **Validação de CPF** - algoritmo verificador
- **Validação de data/hora** - formato e consistência temporal
- **Validação de sala** - existência e disponibilidade
- **Prevenção de conflitos** de horário

## 🎮 Como Usar o Sistema

### Menu Principal
O sistema apresenta um menu interativo com as seguintes opções:

1. **Cadastrar Paciente**
2. **Cadastrar Agendamento**
3. **Consultar Agendamentos por CPF**
4. **Consultar Agendamentos por Sala**
5. **Remover Agendamento**
6. **Histórico Completo**
7. **Sair**

### Fluxo de Uso Típico
1. **Cadastrar pacientes** no sistema
2. **Realizar agendamentos** vinculados aos CPFs cadastrados
3. **Consultar agendamentos** por diferentes critérios
4. **Gerenciar cancelamentos** quando necessário
5. **Visualizar histórico** completo das atividades

## 🔧 Tecnologias e Estruturas

### Linguagem
- **C puro** - Para máxima eficiência e controle de memória

### Estruturas de Dados
- **Listas encadeadas com cabeçalho** - Para histórico eficiente
- **Alocação dinâmica** - Gerenciamento otimizado de memória
- **Estruturas aninhadas** - Organização lógica dos dados

### Módulos de Validação
- **validaCpf.c** - Algoritmo verificador de CPF
- **validaDataHora.c** - Controle de datas e horários
- **validaSala.c** - Gestão de salas disponíveis

## 📊 Vantagens da Implementação

### Eficiência com Listas com Cabeçalho
- **Acesso O(1) ao tamanho** da lista de agendamentos
- **Inserções otimizadas** no histórico
- **Busca eficiente** por diferentes critérios
- **Gerenciamento dinâmico** de memória

### Robustez do Sistema
- **Validação completa** de dados de entrada
- **Tratamento de erros** abrangente
- **Prevenção de vazamentos** de memória
- **Interface amigável** e intuitiva

## 🐛 Solução de Problemas

### Compilação
```bash
# Se encontrar erros de compilação, verifique:
gcc --version
# Certifique-se de que todos os arquivos .c estão no diretório
```

### Execução
- **"Arquivo não encontrado"**: Verifique se o App.exe foi gerado na compilação
- **Entrada inválida**: O sistema valida todos os dados inseridos
- **Erro de memória**: Reinicie o aplicativo se necessário

## 📝 Documentação Adicional

### Diário de Bordo
- **Relatos semanais** do desenvolvimento
- **Divisão de tarefas** entre membros do grupo
- **Dificuldades e soluções** encontradas

### Apresentação Oral
- **Cada membro** explica uma função implementada
- **Demonstração** da lógica e estrutura de dados utilizada
- **Justificativa** das escolhas de implementação

## 👨‍💻 Autoria e Desenvolvimento

### Equipe de Desenvolvimento
- IAN ALMEIDA
- ESDRAS EMANUEL
- ANDRÉ RICARDO

### Metodologia
- **Desenvolvimento colaborativo**
- **Revisão de código** entre pares
- **Testes iterativos** das funcionalidades
- **Documentação contínua**

---

**⚠️ Importante**: Este sistema foi desenvolvido como trabalho acadêmico da disciplina de Estrutura de Dados, demonstrando a aplicação prática de listas lineares em um contexto real de desenvolvimento de software.

**📅 Prazo de Entrega**: 2 semanas a partir da data de publicação do trabalho
