
---
// =================================================================
// CÓDIGO DIDÁTICO: MANIPULAÇÃO DE REGISTRADORES COM VALORES BINÁRIOS
//
// OBJETIVO: Piscar um LED no pino digital 7 (PD7) usando os
// registradores DDRD e PORTD, com foco na visualização das MÁSCARAS
// binárias (B10000000) para facilitar a compreensão do iniciante.
// =================================================================

// -----------------------------------------------------------------
// 1. DEFINIÇÃO DE CONSTANTES E VARIÁVEIS
// -----------------------------------------------------------------

// Máscara binária para o pino D7 (o pino onde o LED estará).
// B10000000: Representa o bit 7 (PD7) como 1 e todos os outros (PD0 a PD6) como 0.
const byte MASCARA_LED = B10000000;

const long INTERVALO_PISCA = 1000; // Intervalo de oscilação em milissegundos.
unsigned long tempoAnterior = 0;   // Contador de tempo para controle não-bloqueante.

// -----------------------------------------------------------------
// 2. FUNÇÃO SETUP (CONFIGURAÇÃO INICIAL)
// -----------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  Serial.println("--- INICIANDO CONFIGURAÇÃO ---");

  // CONFIGURAÇÃO DA DIREÇÃO DA PORTA (DDRD)
  // O valor B10000000 configura apenas o pino D7 (bit mais à esquerda) como SAÍDA (1).
  // Todos os outros pinos do PORTD (D0 a D6) são implicitamente configurados como ENTRADA (0).
  DDRD = MASCARA_LED;  // B10000000
  Serial.print("DDRD configurado para SAÍDA em PD7: ");
  Serial.println(DDRD, BIN); // Imprime o valor em binário para visualização.

  // Desliga o LED inicialmente (Garantir estado LOW)
  // Operador &= (AND Bit a Bit com Negação): Garante que o bit 7 seja 0, sem afetar outros.
  // PORTD &= B01111111; //
  // O uso da MÁSCARA_LED Negada (~MASCARA_LED) para desligar.
  PORTD &= ~MASCARA_LED;
  Serial.print("PORTD inicial: ");
  Serial.println(PORTD, BIN);
  Serial.println("--------------------------------");
}

// -----------------------------------------------------------------
// 3. FUNÇÃO LOOP (LÓGICA PRINCIPAL)
// -----------------------------------------------------------------

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_PISCA) {
    tempoAnterior = tempoAtual;

    // -----------------------------------------------------------------
    // LÓGICA DE ALTERNÂNCIA (TOGGLE)
    // -----------------------------------------------------------------

    // 1. VERIFICAR o estado atual do bit D7 (LED)
    // O operador '&' (AND Bit a Bit) isola apenas o bit do LED. Se o resultado for TRUE, o LED está LIGADO.
    if (PORTD & MASCARA_LED) {
      // Se o LED estiver LIGADO, nós o DESLIGAMOS.
      // PORTD &= ~MASCARA_LED: 'AND' com a máscara de bits NEGADA (B01111111) para forçar o bit 7 a ZERO.
      PORTD &= ~MASCARA_LED;
      Serial.println("LED Desligado (Bit 7 = 0)");
    } else {
      // Se o LED estiver DESLIGADO, nós o LIGAMOS.
      // PORTD |= MASCARA_LED: 'OR' com a MASCARA_LED (B10000000) para forçar o bit 7 a UM.
      PORTD |= MASCARA_LED;
      Serial.println("LED Ligado (Bit 7 = 1)");
    }
  }

  // Monitoramento: Imprime o valor do registrador PORTD em binário.
  Serial.print("PORTD (Binário): ");
  Serial.println(PORTD, BIN);
}
