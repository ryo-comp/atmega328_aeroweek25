# Prática 0: "Hello World" do Embarcado (Piscar um LED com Botão)

## Objetivo
Configurar um microcontrolador (Arduino) para ler o estado de um botão (Entrada) e, em resposta, acender ou apagar um LED (Saída). Esta prática introduz a utilização do resistor *Pull-up* interno e a correta limitação de corrente para proteção de componentes.

## 1. Materiais Necessários

| Qtd | Componente | Observação |
| :---: | :--- | :--- |
| 1 | Placa Arduino Uno (ou compatível) | Com cabo $\text{USB}$. |
| 1 | Protoboard (Placa de Ensaio) | Para montagem do circuito. |
| 1 | LED (Díodo Emissor de Luz) | Qualquer cor. |
| 1 | Resistor (Limitador de Corrente) | **$220 \Omega$ a $330 \Omega$** (essencial para proteger o LED). |
| 1 | Push Button (Chave Táctil) | Botão de 4 pinos. |
| 3 | Jumpers ($\text{Macho-Macho}$) | Fios de conexão. |

## 2. Montagem do Circuito

O circuito deve ser montado na Protoboard **antes** de conectar o Arduino ao computador.

### 2.1. Conexão do LED (Pino 12)

O LED é um diodo e devemos ter atenção na forma como é montado (polaridade). Ele **DEVE** ser ligado com um resistor para limitar a corrente e evitar que queime.

1.  **LED:** Identifique o **Ânodo** (perna mais longa $\rightarrow$ Positivo) e o **Cátodo** (perna mais curta $\rightarrow$ Negativo).
2.  **Ligar o LED:**
    * Conecte o **Ânodo** ao **Pino Digital 12** do Arduino.
    * Conecte o **Cátodo** a uma extremidade do **Resistor de $220 \Omega$ a $330 \Omega$** (o resistor pode ser ligado em qualquer lado do LED, desde que esteja em série).
    * Conecte a outra extremidade do Resistor ao pino **$\text{GND}$ (Terra)** do Arduino.

> **Regra de Ouro do Embarcado:** **SEMPRE** use um resistor em série com o LED.

### 2.2. Conexão do Botão (Pino 2 ou 3)

Usaremos o recurso de **`\INPUT_PULLUP`** do Arduino, que habilita um resistor interno na entrada.

1.  **Botão:** Insira o *Push Button* na Protoboard.
2.  **Ligar o Botão:**
    * Conecte um lado (terminal) do botão ao pino **$\text{GND}$ (Terra)** do Arduino.
    * Conecte o lado oposto (terminal) do botão ao **Pino Digital 2** (ou 3) do Arduino.

> **Lógica do Pull-up Interno:**
> * **Botão Solto:** O pino é lido como **$\text{HIGH}$ (1)** por padrão.
> * **Botão Pressionado:** O pino é conectado ao $\text{GND}$, lido como **$\text{LOW}$ (0)**.

## 3. Código ($\text{Sketch}$)

Abra a $\text{IDE}$ do Arduino, crie um novo sketch e tente elaborar um código para executar a tarefa. É permitido consultar os materiais fornecidos e fazer pesquisa na internet.

## 4. Teste e Verificação

1. **Conecte e Configure**: Ligue o Arduino, selecione a Placa (Arduino Uno) e a Porta COM correta na IDE.
2. **Carregar**: Clique em Carregar(upload) para enviar o sketch para a placa.
3. **Execução**:
    Pressione o botão: O LED deve **acender**.
    Solte o botão: O LED deve **apagar**.
4. **Execução da Prática**:
    Verifique se o $\text{LED}$ está **desligado** por padrão.
    Pressione e Segure o botão. O $\text{LED}$ deve **acender**.
    Solte o botão. O $\text{LED}$ deve **apagar**.

## Prática Opcional 
Modifique a lógica no void loop() para que o $\text{LED}$ inverta o seu estado (liga se estiver desligado e vice-versa) cada vez que o botão for **pressionado e solto**. (Isso exigirá uma variável de estado e técnicas de detecção de borda).
