#include <LiquidCrystal_I2C.h> // Inclui a biblioteca necessária para controlar o LCD via protocolo I2C.

// Define o objeto 'lcd' da classe LiquidCrystal_I2C.
// Os parâmetros são:
// 1. 0x27: Endereço I2C do módulo LCD (pode variar, sendo 0x27 ou 0x3F os mais comuns).
// 2. 20: Número de colunas do display LCD (20 caracteres de largura).
// 3. 4: Número de linhas do display LCD (4 linhas de altura).
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
    // --- Inicialização do LCD ---

    lcd.init(); // Inicializa a interface I2C e o display LCD.
    // A chamada lcd.init() geralmente é repetida para garantir a inicialização correta
    // em alguns módulos I2C, embora tecnicamente uma vez deva ser suficiente.
    lcd.init();

    // --- Configurações Iniciais ---

    lcd.backlight(); // Liga a luz de fundo (backlight) do display LCD.

    // Define a posição do cursor (coluna, linha) onde a próxima escrita começará.
    // Coluna 0, Linha 0 (a contagem começa em 0).
    lcd.setCursor(0, 0);

    // Imprime a primeira mensagem na posição definida.
    lcd.print("AeroWeek 2025");

    // Define a posição do cursor na Linha 1 (a segunda linha).
    // Coluna 0, Linha 1.
    lcd.setCursor(5, 1);

    // Imprime uma segunda mensagem na Linha 1.
    lcd.print("21/10/25");
}


void loop()
{
    // Esta função está vazia, o que significa que o display LCD
    // exibirá apenas as mensagens definidas no setup() e não será atualizado.
    // Em projetos futuros, a lógica principal (como leitura de sensores) iria aqui.
}
