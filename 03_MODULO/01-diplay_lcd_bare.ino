// --- Definição dos Pinos de Controle do Shift Register (CI 595) ---

#define SO_CLK_PIN 11      // Pino CLK (Clock) do Shift Register (SHCP ou SCK) – Sinal de sincronização.
#define SO_EN_PIN 10       // Pino EN (Enable) do Shift Register (STCP ou RCLK) – Pino de Latch/Trava. Usado para transferir os 8 bits da memória interna para as saídas.
#define SO_DATA_PIN 8      // Pino DATA (Dados) do Shift Register (DS ou SER) – Pino onde os bits são enviados serialmente (um por um).

// --- Definição dos Pinos de Controle do LCD ---
// Estes são os pinos de controle do LCD (RS e EN) ligados diretamente ao Arduino.
// Os pinos de dados (D4-D7) do LCD estão ligados às saídas do CI 595.
#define LCD_RS_PIN 7       // Pino RS (Register Select) do LCD – Seleciona se estamos enviando um Comando (LOW/0) ou um Dado/Caractere (HIGH/1).
#define LCD_EN_PIN 6       // Pino EN (Enable) do LCD – Usado para dar o "pulso de clock" que faz o LCD ler os dados nos seus pinos.

// -------------------------------------------------
// --- Funções de Controle do Shift Register (CI 595) ---

// Inicializa os pinos do Shift Register como saída.
void soInit(void) {
    pinMode(SO_EN_PIN, OUTPUT);
    pinMode(SO_CLK_PIN, OUTPUT);
    pinMode(SO_DATA_PIN, OUTPUT);
}
// -------------------------------------------------

// Função fundamental: Envia 8 bits de dados (byte) para o Shift Register (CI 595).
// O dado é enviado Bit a Bit (serialmente).
void soWrite(byte value) {
    int i;

    // O LCD 16x2 (e similares) geralmente tem seus pinos D4, D5, D6, D7 ligados aos pinos
    // Q4, Q5, Q6, Q7 do CI 595 (os 4 bits de dados) e os pinos RS e EN ligados aos
    // pinos Q0 e Q1 (os 2 bits de controle).

    // 0x01 = 00000001 (bit menos significativo em 1)
    // 0x80 = 10000000 (bit mais significativo em 1)

    // O código envia o Bit Mais Significativo (MSB) primeiro, o que é comum em comunicação serial.
    for ( i = 0 ; i < 8 ; i++) {
        // 1. Envia o bit para o pino de DADOS (SO_DATA_PIN)
        // (value & 0x80) isola o MSB (o bit mais à esquerda).
        // !! converte o resultado binário para HIGH(1) ou LOW(0) para o digitalWrite.
        digitalWrite(SO_DATA_PIN, !!(value & 0x80));

        // 2. Pulso de Clock: O pulso HIGH -> LOW no pino CLK (Clock)
        // faz o Shift Register aceitar o bit no pino de DADOS e deslocar os bits anteriores em uma posição.
        digitalWrite(SO_CLK_PIN, HIGH);
        digitalWrite(SO_CLK_PIN, LOW);

        // 3. Desloca o valor original para a esquerda (value <<= 1)
        // O próximo bit a ser enviado se torna o MSB para a próxima iteração do loop.
        value <<= 1;
    }

    // 4. Trava (Latch): Pulso HIGH -> LOW no pino EN (Enable/Latch)
    // Transfere o byte completo (8 bits) da memória interna do 595 para seus pinos de SAÍDA (Q0-Q7).
    digitalWrite(SO_EN_PIN, HIGH);
    digitalWrite(SO_EN_PIN, LOW);
}
// -------------------------------------------------

// Função auxiliar: Gera o pulso (HIGH -> LOW) no pino Enable do LCD.
// Este pulso notifica o LCD para ler os dados presentes nos seus pinos de dados (D4-D7).
void pulseEnablePin(){
    digitalWrite(LCD_EN_PIN, HIGH);
    digitalWrite(LCD_EN_PIN, LOW);
}
// -------------------------------------------------

// Envia apenas 4 bits (um "nibble") do comando/dado para o LCD.
// Esta função é usada para comunicação de 4 bits, que é o padrão para economizar pinos.
void pushNibble(byte value, int rs){
    // 1. Envia os 4 bits de dados e os 4 bits de controle/extra para o CI 595.
    // O valor contém o nibble (os 4 bits) a ser enviado ao LCD.
    soWrite(value);

    // 2. Define o pino RS do LCD (Comando ou Dado).
    digitalWrite(LCD_RS_PIN, rs);

    // 3. Notifica o LCD para ler os 4 bits que estão nas saídas do CI 595.
    pulseEnablePin();
}
// -------------------------------------------------

// Envia 8 bits (um byte) de dados ou comando para o LCD em dois pacotes de 4 bits.
void pushByte(byte value, int rs){
    // Envia o nibble MAIS SIGNIFICATIVO (F0 = 1111 0000).
    // Isola os 4 bits de alta ordem e envia.
    pushNibble((value & 0xF0), rs);

    // Envia o nibble MENOS SIGNIFICATIVO (0F = 0000 1111).
    // Isola os 4 bits de baixa ordem e os desloca 4 posições para a esquerda (<< 4)
    // para que eles fiquem nas posições D7-D4 do CI 595, prontas para serem lidas pelo LCD.
    pushNibble((value & 0x0F) << 4, rs);
}
// -------------------------------------------------

// Envia um comando de 8 bits para o LCD (Ex: Limpar display, Mover cursor).
void lcdCommand(byte value) {
    // LOW no RS indica que estamos enviando um comando.
    pushByte(value, LOW);
    delayMicroseconds(40); // Pequena espera para o LCD processar o comando.
}
// -------------------------------------------------

// Envia um caractere (dado) de 8 bits para o LCD para ser exibido.
void lcdChar(byte value) {
    // HIGH no RS indica que estamos enviando um dado (caractere).
    pushByte(value, HIGH);
    delayMicroseconds(50); // Espera um pouco maior para processar a escrita do caractere.
}
// -------------------------------------------------

// Imprime uma string (vetor de caracteres) no display.
void lcdString (const char msg[]) {
    int i = 0;
    // Loop que percorre o array de caracteres até encontrar o terminador nulo (0).
    while(msg[i] != 0) {
        // Envia cada caractere da string, um por um.
        lcdChar(msg[i]);
        i++;
    }
}

// -------------------------------------------------

// Posiciona o cursor para a próxima escrita.
void lcdPosition (byte line, byte col) {
    // O comando para posicionar o cursor (Set DDRAM Address) começa com 0x80.
    // Linha 0 (primeira linha): 0x80 + coluna (0x80 a 0x90).
    if (line == 0) {
        lcdCommand(0x80 + col);
    }
    // Linha 1 (segunda linha): 0xC0 + coluna (0xC0 a 0xD0).
    if (line == 1) {
        lcdCommand(0xC0 + col);
    }
    delayMicroseconds(46);
}
// -------------------------------------------------

// Executa comandos para limpar e resetar o display LCD.
void limparDisplay (void) {
    lcdCommand(0x03); // Comando para resetar a interface (parte da rotina de inicialização).
    delayMicroseconds(1500); // Espera longa, pois este comando leva tempo.

    lcdCommand(0x80); // Volta o cursor para a posição inicial (0,0).
    delayMicroseconds(40);

    lcdCommand(0x01); // Comando para Limpar o Display e resetar o cursor.
    delayMicroseconds(1500); // Espera longa.
}
// -------------------------------------------------

// Rotina de inicialização do LCD, crucial para estabelecer a comunicação de 4 bits.
void lcdInit (void) {
    // A inicialização sempre começa em modo 8 bits (0x30).
    // Estes comandos de 8 bits são enviados três vezes para garantir que o LCD entre no modo correto.
    pushNibble(0x30, LOW);
    delay(5);

    pushNibble(0x30, LOW);
    delayMicroseconds(160);

    pushNibble(0x30, LOW);
    delayMicroseconds(160);

    // Mudança para o modo de comunicação de 4 bits (0x20).
    pushNibble(0x20, LOW);
    delayMicroseconds(100);

    // --- Configurações Finais de Operação (agora em modo 4 bits) ---

    lcdCommand(0x28);  // Comando: 4 bits, 2 linhas, matriz de 5x8 pontos.
    lcdCommand(0x06);  // Comando: Entry Mode Set (Modo incremental do cursor).
    lcdCommand(0x0F);  // Comando: Display On/Off Control (Display e cursor ON, com blink).
    limparDisplay();   // Limpa o display e posiciona o cursor em (0,0).
}
// -------------------------------------------------

// Função para escrever caracteres personalizados (Custom Characters) na memória CGRAM do LCD.
void escreveCGRAM (byte address, byte *pCh) {

    // O comando Set CGRAM Address (Escrita na memória CGRAM) começa com 0x40.
    // O endereço CGRAM (address) é o 0x40 + (ID do caractere * 8).
    lcdCommand(address);
    delayMicroseconds(40);

    // Envia os 8 bytes de dados (o padrão de pixels) para a memória CGRAM.
    for (int i = 0 ; i < 8 ; i++) {
        lcdChar(*pCh); // Envia o byte de padrão de pixels.
        pCh++;         // Avança para o próximo byte no array (próxima linha do desenho).
    }

    // Volta para a memória DDRAM (a memória principal de exibição) após escrever o caractere.
    limparDisplay();
}
// -------------------------------------------------

// Rotina para definir e armazenar caracteres personalizados (Custom Characters).
void criarCHAR (void) {
    // Posições de memória CGRAM disponíveis (8 posições para caracteres personalizados).
    // 0x40 (ID 0), 0x48 (ID 1), 0x50 (ID 2), etc.
    byte memPosition[8] = {0x40, 0x48, 0x50, 0x58, 0x60, 0x68, 0x70, 0x78};

    // Definição dos padrões de pixels (8 bytes por caractere).
    byte sino[8]       = {0x04, 0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04};
    byte flor[8]       = {0x11, 0x0E, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x04};
    byte smil[8]       = {0x00, 0x0A, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00};
    // Exemplo de notação binária (equivalente a hexadecimal) para a bomba:
    byte bomba[8]      = {0b10101, 0b10101, 0b01010, 0b00100, 0b01010, 0b11011, 0b01110, 0b00100};

    // Escreve o padrão do sino na ID 0 (endereço 0x40).
    escreveCGRAM(0x40, sino);

    // Escreve o padrão da flor na ID 1 (endereço 0x48).
    escreveCGRAM(0x48, flor);

    // Escreve o padrão do smile na ID 2 (endereço 0x50).
    escreveCGRAM(0x50, smil);

    // Escreve o padrão da bomba na ID 3 (endereço 0x58).
    escreveCGRAM(0x58, bomba);
}
// -------------------------------------------------


void setup () {
    // Inicia a comunicação serial para debug (comentado, mas comum em setup).
    //Serial.begin(9600);

    // Inicia os pinos do Shift Register.
    soInit();

    // Define os pinos de controle do LCD (RS e EN) como saída.
    pinMode(LCD_RS_PIN, OUTPUT);
    pinMode(LCD_EN_PIN, OUTPUT);
    delay(15); // Espera inicial obrigatória para o LCD ligar.

    // Inicia a rotina de comunicação e configuração do LCD.
    lcdInit();

    // Cria os caracteres personalizados para uso futuro.
    criarCHAR();

    lcdString("AeroWeek25.");
    lcdPosition(1,0);
    lcdString("21-10-25");
}

// Nota: A função loop() está ausente neste exemplo, pois o foco era apenas nas funções de inicialização.
// Se fosse um sketch completo, o código de execução contínua (como um contador) estaria aqui.
// int main() está presente, mas não é o padrão do Arduino IDE; é ignorado se estiver presente,
// ou seria o ponto de entrada se este fosse um projeto C/C++ puro.
void loop() {
    // A função main() em um ambiente Arduino é geralmente oculta e chama setup() uma vez e loop() continuamente.

}
