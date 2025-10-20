# Prática 4: Controle de Motor DC com PWM e MOSFET

## Objetivo
Demonstrar e implementar a ideia de controle de velocidade (e ligar/desligar) de um motor DC de média/alta potência utilizando a Modulação por Largura de Pulso (`PWM`) gerada pelo microcontrolador (Arduino) e um transistor MOSFET como chave eletrônica de potência.

### Conceitos-Chave
* **PWM (Pulse Width Modulation):** Técnica para simular uma tensão analógica variável a partir de um sinal digital (onda quadrada), alterando o *duty cycle*.
* **MOSFET (Metal-Oxide-Semiconductor Field-Effect Transistor):** Componente que atua como chave eletrônica. O sinal de baixa corrente do Arduino (porta `GATE`) controla a passagem de alta corrente da fonte de alimentação externa para o motor (entre `DRAIN` e `SOURCE`).
* **Diodo Flyback:** Diodo essencial para proteger o MOSFET. Motores são cargas indutivas, e ao serem desligados, geram um pico de tensão reversa (*back EMF*) que pode danificar o transistor.

---

## 1. Material Necessário
| Componente | Especificação Sugerida | Notas |
| :--- | :--- | :--- |
| **Microcontrolador** | Arduino Uno ou similar | Para geração do sinal `PWM`. |
| **Transistor MOSFET**| IRF520, IRF540, ou IRFZ44N | MOSFET de canal N, idealmente "Logic Level" se a tensão do `GATE` for 5V. |
| **Motor DC** | Motor de 3V a 12V | Use um motor que exija mais corrente do que o Arduino pode fornecer (acima de 40mA). |
| **Fonte Externa** | Bateria ou Fonte DC | Tensão compatível com o motor (ex: 9V ou 12V). **Não use a fonte do Arduino para o motor!**|
| **Diodo** | 1N4001, 1N4004 ou similar | Diodo Retificador para proteção (Diodo Flyback). |
| **Resistor** | 10k $\Omega$ | Resistor *Pull-down* (Opcional, mas recomendado para o `GATE`). |
| **Potenciômetro** | 10k $\Omega$ | Para controle manual da velocidade (entrada analógica). |
| **Outros** | Protoboard, Jumpers | |

---

## 2. Montagem do Circuito

O circuito deve ser montado garantindo que as fontes de alimentação estejam isoladas, mas que seus terras (`GND`) estejam conectados.

### Diagrama de Conexão (Esquemático Básico)

1.  **Conexão de Terramentos (GND):** **Crucial!** Conecte o `GND` da fonte externa (do motor) ao pino `GND` do Arduino. Isso estabelece uma referência de tensão comum.
2.  **Motor e Diodo Flyback:**
    * Conecte o **terminal positivo** do motor ao **polo positivo** da fonte externa.
    * Conecte o **terminal negativo** do motor ao pino **`DRAIN`** do MOSFET.
    * Conecte o **Diodo Flyback** em paralelo com o motor. O lado da faixa do diodo (catodo) vai no positivo do motor, e o outro lado (anodo) vai no negativo/`DRAIN`.
3.  **MOSFET como Chave:**
    * Conecte o pino **`SOURCE`** do MOSFET ao **`GND`** comum (do Arduino e da fonte externa).
    * Conecte o pino **`GATE`** do MOSFET ao pino digital `PWM` do Arduino (ex: `D9`).
    * Opcional: Adicione um resistor de `10k$\Omega$` do pino `GATE` para o `GND` como *pull-down*.
4.  **Entrada de Controle:**
    * Conecte o **potenciômetro** aos `5V` e `GND` do Arduino.
    * Conecte o pino central do potenciômetro a um pino analógico do Arduino (ex: `A0`).

---

## 3. Desenvolvimento do Código (Sketch)

O código deve ler o potenciômetro (entrada analógica) e usar seu valor para determinar o *duty cycle* do `PWM` enviado ao `MOSFET`.

### Passos de Programação

1.  **Definir Pinos:** Defina constantes para o pino do potenciômetro (entrada) e o pino de controle do motor (saída `PWM`).
2.  **Leitura e Mapeamento:**
    * Leia o valor do potenciômetro (faixa de $\text{0}$ a $\text{1023}$).
    * Use a função `map()` para converter este valor para a faixa de `PWM` (`0` a `255`).
    * **Fórmula da Conversão:** `valor_PWM = map(valor_pot, 0, 1023, 0, 255);`
3.  **Controle PWM:** Use a função `analogWrite()` no pino do MOSFET para aplicar o valor `PWM` calculado.
