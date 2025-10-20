// =================================================================
// CÓDIGO DE EXEMPLO: LEITURA ANALÓGICA - CORREÇÃO DE PRECISÃO
//
// OBJETIVO: Garantir que a constante de conversão (A2F) seja calculada
// com números de ponto flutuante (float) para evitar o erro de 'divisão
// de inteiros', que faria o resultado ser zero (0).
// =================================================================

// -----------------------------------------------------------------
// 1. DEFINIÇÃO DE CONSTANTES E VARIÁVEIS
// -----------------------------------------------------------------

// As constantes são definidas com o '.0' para forçar o compilador
// a tratá-las como FLOAT, garantindo a precisão da divisão.
#define POT_PIN A0
#define V_REF    5.0
#define ARESO 1024.0
#define ADC_MAX 1023

// Fator de Conversão de Analógico para Float (A2F)
const float A2F = V_REF / ARESO;

int    potVal = 0;   // Armazena o valor inteiro lido (0-ARESO)
float voltage = 0.0; // Armazena o valor da tensão calculada (0.0V - V_REF)

// -----------------------------------------------------------------
// 2. FUNÇÃO SETUP
// -----------------------------------------------------------------

void setup() {
    Serial.begin(9600);
    Serial.print("Fator A2F (V/unidade) = ");
    Serial.println(A2F, 6); // Imprime o fator com 6 casas decimais (ex: 0.004882)
    Serial.println("---");
}

// -----------------------------------------------------------------
// 3. FUNÇÃO LOOP (LÓGICA PRINCIPAL)
// -----------------------------------------------------------------

void loop() {
    // 1. LEITURA ANALÓGICA
    potVal = analogRead(POT_PIN); // Lê o potenciômetro

    Serial.print("Valor lido (ADC) = ");
    Serial.println(potVal);

    // 2. CONVERSÃO PARA TENSÃO (Simples multiplicação)
    // Tensão (V) = Valor Lido * Fator de Conversão (V/unidade)
    voltage = (float)potVal * A2F; // O (float) é opcional aqui, mas garante a segurança!
                                   // cast: https://www.w3schools.com/c/c_type_conversion.php

    Serial.print("Valor da tensão: ");
    Serial.println(voltage, 2); // Imprime a tensão com 2 casas decimais.
    Serial.println("V");
    Serial.println("---");

    delay(250); // Aguarda para não sobrecarregar a porta serial
}
