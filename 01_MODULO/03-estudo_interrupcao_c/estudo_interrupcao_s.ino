const int LED_LOOP = 13;   // LED0: LED que oscila no loop principal (teste de funcionamento).
const int LED_ISR  = 12;   // LED1: LED que é controlado pela interrupção (ISR).
const int BOTAO_PIN = 2;   // BOTÃO: Pino digital com capacidade de interrupção (INT0 no pino 2 do Uno).
volatile bool estadoLed = false;
const long INTERVALO_PISCA = 1000; // Intervalo de oscilação do LED_LOOP em milissegundos.
unsigned long tempoAnterior = 0;   // Armazena o último momento em que o LED_LOOP foi atualizado.

void toggleLedISR() {
  estadoLed = !estadoLed;
  digitalWrite(LED_ISR, estadoLed);
}

void setup() {
  pinMode(LED_LOOP, OUTPUT);
  pinMode(LED_ISR, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BOTAO_PIN), toggleLedISR, FALLING);
}

void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_PISCA) {
    tempoAnterior = tempoAtual;
    digitalWrite(LED_LOOP, !digitalRead(LED_LOOP));
  }
}
