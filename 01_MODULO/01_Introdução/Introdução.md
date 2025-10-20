# Introdução aos Sistemas Embarcados e Arduino

## 1. Apresentação: Sistemas Embarcados

### O que são Sistemas Embarcados?
Um **Sistema Embarcado** (`Embedded System`) é um sistema eletrônico microprocessado (ou microcontrolado) que é projetado para realizar uma **função dedicada e específica** dentro de um dispositivo maior. Diferente de um computador pessoal, que é de propósito geral, um sistema embarcado é otimizado para a tarefa que executa.

| Característica | Detalhe | Exemplos |
| :--- | :--- | :--- |
| **Dedicado** | Executa uma ou um conjunto muito limitado de tarefas. | Máquina de lavar, controle remoto, GPS, wearables. |
| **Tempo Real** | Geralmente, deve responder a eventos externos em um tempo previsível e curto. | Airbag de carro, sistemas de controle industrial. |
| **Restrições** | Opera sob fortes restrições de custo, tamanho, consumo de energia e velocidade. | Dispositivos a bateria, sensores remotos. |
| **Integração** | O hardware e o software são indissociáveis, desenvolvidos em conjunto. | O firmware do sistema está gravado diretamente no chip de controle. |

## 2. O Microcontrolador no Contexto de Embarcados

O **Microcontrolador** (`MCU`) é o "cérebro" de um sistema embarcado. Podemos pensar nele como um computador completo em um único chip (Circuito Integrado).

| Componente | Microcontrolador (`MCU`) | Microprocessador (`MPU`) |
| :--- | :--- | :--- |
| **Estrutura** | `CPU`, Memória (`RAM` e `Flash`) e Periféricos em um único chip. | Apenas a `CPU`. A memória e periféricos são externos. |
| **Foco** | Controle de I/O, baixo consumo, tarefas em tempo real. | Alto poder de processamento, sistemas operacionais complexos. |
| **Uso Comum** | Controle de eletrodomésticos, sensores, automação simples. | PCs, Servidores, Smartphones (Núcleos ARM de alto desempenho). |

No nosso contexto (Arduino), estamos usando um Microcontrolador (família `ATmega`), que é perfeito para interagir diretamente com o mundo físico.

## 3. Sobre a Programação de Embarcados

A programação de sistemas embarcados requer uma abordagem diferente do desenvolvimento de aplicativos de PC:

* **Linguagem:** Principalmente **C/C++** (linguagens de baixo nível que permitem controle direto do hardware).
* **Controle de Hardware:** O programador interage diretamente com **Registradores** (locais de memória dentro do `MCU`) para ligar/desligar pinos, configurar temporizadores e interfaces de comunicação.
* **Compilação Cruzada (`Cross-Compilation`):** O código é escrito no seu PC (sistema *host*) e depois compilado para ser executado na arquitetura do microcontrolador (sistema *target*). O resultado final é o *firmware* que é gravado no `MCU`.

## 4. Sobre o Arduino

O Arduino é uma **Plataforma de Prototipagem Eletrônica de Código Aberto**. Ela simplifica o desenvolvimento de sistemas embarcados.

* **Hardware (Placa):** Placas padronizadas (`UNO`, `Mega`, etc.) que facilitam a conexão de periféricos e possuem um *bootloader* pré-instalado para carregamento fácil de código.
* **Software (IDE e Linguagem):** Uma `IDE` simples e uma linguagem de programação baseada em C/C++ com funções de alto nível (`digitalWrite`, `analogRead`) que abstraem a complexidade dos registradores.

O Arduino torna o embarcado acessível, permitindo que o foco seja na lógica de controle, e não nos detalhes complexos do hardware.

## 5. IDE do Arduino: Baixar e Instalar

A `IDE` (`Integrated Development Environment`) é o programa onde você escreve, compila e envia o código para a placa.

* **Baixar:** Acesse o site oficial do Arduino (arduino.cc) e procure a seção Software -> Downloads.
* **Instalar:**
    * Windows/macOS: Escolha a opção de instalador (ou a versão `.zip` para Windows). Siga o assistente de instalação.
    * Linux: Use o pacote do sistema ou o arquivo `.zip` fornecido.
* **Drivers:** A instalação geralmente inclui os drivers necessários para o computador reconhecer a placa quando ela for conectada via `USB`.

### Primeiros Passos na IDE

* **Verificar (Compilar):** Botão de Check (ou `Ctrl+R`). Converte o código-fonte em linguagem de máquina (*firmware*).
* **Carregar (Upload):** Botão de Seta (ou `Ctrl+U`). Envia o *firmware* compilado para o microcontrolador via `USB`.
* **`setup()`:** Função que roda uma única vez ao ligar ou resetar a placa (configuração inicial).
* **`loop()`:** Função que roda continuamente (a lógica principal do programa).

## 6. Bibliotecas (`Libraries`)

Bibliotecas são coleções de código pré-escrito (em C/C++) que facilitam a interação com hardware e protocolos complexos.

* **Função:** Simplificam o trabalho. Ex: Em vez de manipular registradores complexos para controlar um `LCD`, você simplesmente chama a função `lcd.print("Ola");` da biblioteca `LiquidCrystal`.
* **Instalação:** Podem ser incluídas via Gerenciador de Bibliotecas na própria `IDE` (Sketch -> Incluir Biblioteca -> Gerenciar Bibliotecas) ou adicionadas manualmente como arquivos `.zip`.
* **Uso no Código:** O uso de uma biblioteca é feito com a diretiva:
    ```cpp
    #include <NomeDaBiblioteca.h>
    ```

## 7. Tipos de Dados e Operações Bit a Bit

Em sistemas embarcados, a memória é limitada, então é importante usar os tipos de dados mais eficientes e manipular bits diretamente.

### Tipos de Dados Binários (mais comuns no Arduino)

| Tipo | Tamanho (Bytes) | Faixa de Valores (Exemplo) |
| :--- | :--- | :--- |
| `bool` | 1 | `true` ou `false` |
| `byte` (`unsigned char`) | 1 | 0 a 255 |
| `int` | 2 | -32.768 a 32.767 |
| `unsigned int` | 2 | 0 a 65.535 |
| `long` | 4 | ± 2 bilhões |

### Operações Lógicas Binárias (Bit a Bit)

Essas operações são fundamentais para controlar **Registradores**, onde cada bit corresponde a um estado específico de um pino ou periférico.

| Operador | Nome | Função | Exemplo |
| :--- | :--- | :--- | :--- |
| `&` | `AND` (E) | O resultado é 1 se ambos os bits forem 1. Usado para limpar ou testar bits específicos. | `0101 & 0011 = 0001` |
| `\|` | `OR` (OU) | O resultado é 1 se pelo menos um dos bits for 1. Usado para ativar (*setar*) bits. | `0101 \| 0010 = 0111` |
| `^` | `XOR` (OU Exclusivo) | O resultado é 1 se os bits forem diferentes. Usado para inverter (*toggle*) o estado de um bit. | `0101 ^ 0010 = 0111` |
| `~` | `NOT` (Negação) | Inverte o valor de todos os bits (0 -> 1 e 1 -> 0). Usado para criar máscaras de limpeza. | `~0101 = 1010` |
| `<<` | Deslocamento à Esquerda | Desloca os bits para a esquerda (multiplica por potências de 2). Usado para criar máscaras de forma eficiente: `(1 << PINO)`. | `0001 << 2 = 0100` |

## 8. Arquitetura Interna do Microcontrolador (ATmega)

A arquitetura do microcontrolador (como o `ATmega328P` usado no Arduino `UNO`) segue o modelo de um computador, mas altamente integrado.

| Bloco | Função |
| :--- | :--- |
| **`CPU`** (Unidade Central de Processamento) | O núcleo que executa as instruções do programa (código). Responsável por cálculos lógicos e aritméticos. |
| **Memória `FLASH`** (Memória de Programa) | Onde o código (*firmware*) é armazenado permanentemente. **Não volátil**. (Ex: O programa `setup()` e `loop()`). |
| **Memória `SRAM`** (Memória de Dados) | Memória de acesso rápido e **volátil**. Usada para armazenar variáveis temporárias e a pilha de execução. Perde o conteúdo quando a energia é desligada. |
| **`EEPROM`** (Memória de Dados Persistente) | Memória **não volátil**, usada para armazenar configurações ou dados que devem ser mantidos mesmo sem energia (Ex: Último valor de calibração). |
| **Periféricos de Entrada/Saída (`I/O`)** | Módulos especializados que interagem com o mundo externo: |
| | - **Portas Digitais (`GPIO`):** Para ligar/desligar dispositivos (`ON/OFF`). |
| | - **`ADC`** (Conversor Analógico-Digital): Lê tensões analógicas de sensores e as converte em valores digitais. |
| | - **Temporizadores (`Timers`):** Usados para gerar `PWM`, criar atrasos precisos e contar eventos. |
| | - **Interfaces de Comunicação:** `SPI`, `I2C` (`Wire`), `USART` (`Serial`) para comunicação com outros chips ou dispositivos. |
| **Barramentos** | Conjunto de fios internos que conecta a `CPU` à Memória e aos Periféricos, permitindo a transferência de dados e endereços. |
