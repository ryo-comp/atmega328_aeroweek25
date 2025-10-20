// =================================================================
// CÓDIGO DE EXEMPLO: INTERRUPÇÕES EXTERNAS (ATmega328 / Arduino Uno)
//
// OBJETIVO: Demonstrar o funcionamento não-bloqueante de uma
// interrupção externa (botão) enquanto o loop principal executa
// uma tarefa independente (piscar um LED).
// =================================================================

// -----------------------------------------------------------------
// 1. DEFINIÇÃO DE PINOS E VARIÁVEIS GLOBAIS
// -----------------------------------------------------------------

// Usamos 'const int' para pinos, pois eles não mudam durante a execução.
const int LED_LOOP = 13;   // LED0: LED que oscila no loop principal (teste de funcionamento).
const int LED_ISR  = 12;   // LED1: LED que é controlado pela interrupção (ISR).
const int BOTAO_PIN = 2;   // BOTÃO: Pino digital com capacidade de interrupção (INT0 no pino 2 do Uno).

// Variável de estado do LED controlado pela interrupção.
// A palavra-chave 'volatile' indica ao compilador que esta
// variável pode ser alterada a qualquer momento por algo 'externo'
// ao loop normal (neste caso, a Interrupção).
volatile bool estadoLed = false;
/*
 * O compilador C/C++ (e o ATmega328) otimiza o código assumindo que
 * variáveis só mudam dentro do loop() ou de funções normais. A
 * palavra-chave volatile força o compilador a sempre ler o valor
 * da variável diretamente da memória (RAM) a cada uso, garantindo
 * que a mudança feita pela toggleLedISR() (que é assíncrona) seja
 * sempre vista pelo loop() principal.
 */

// Variável para evitar o uso de 'delay()' no loop principal.
const long INTERVALO_PISCA = 1000; // Intervalo de oscilação do LED_LOOP em milissegundos.
unsigned long tempoAnterior = 0;   // Armazena o último momento em que o LED_LOOP foi atualizado.

// -----------------------------------------------------------------
// 2. ROTINA DE SERVIÇO DE INTERRUPÇÃO (ISR)
// -----------------------------------------------------------------

// Função que é executada IMEDIATAMENTE quando a interrupção ocorre.
// Deve ser rápida e curta para não bloquear o programa principal.
void toggleLedISR() {
  // O uso da lógica booleana '!' (NOT) inverte o estado atual.
  estadoLed = !estadoLed;

  // ATENÇÃO: Embora 'digitalWrite' funcione, em ambientes profissionais
  // é recomendável usar a manipulação direta de registradores (PORTB, PORTD)
  // dentro de uma ISR para a execução mais rápida. Para fins didáticos,
  // 'digitalWrite' é aceitável, mas o mais rápido é ideal.
  digitalWrite(LED_ISR, estadoLed);
}

// -----------------------------------------------------------------
// 3. FUNÇÃO SETUP (CONFIGURAÇÃO INICIAL)
// -----------------------------------------------------------------

void setup() {
  // Inicialização das portas
  pinMode(LED_LOOP, OUTPUT);
  pinMode(LED_ISR, OUTPUT);

  // O pino do botão é configurado como INPUT_PULLUP. Isso ativa o resistor
  // interno para manter o pino HIGH (5V), facilitando a conexão
  // do botão (que conectará o pino ao GND/LOW quando pressionado).
  // pinMode(BOTAO_PIN, INPUT_PULLUP);
  // OBS: Como o FALLING será usado, o Arduino assume que a borda de descida será o acionamento.

  // Configuração da Interrupção Externa
  // - digitalPinToInterrupt(BOTAO_PIN): Converte o pino digital (2) para o número da Interrupção (0).
  // - toggleLedISR: Nome da função a ser chamada (ISR).
  // - FALLING: Ocorre quando o pino muda de HIGH para LOW (pressionar o botão, se usando PULLUP).
  attachInterrupt(digitalPinToInterrupt(BOTAO_PIN), toggleLedISR, FALLING);

  /*
   *   Comentário sobre modos:
   * LOW: Dispara quando o pino está em nível BAIXO. (Perigoso: pode disparar continuamente).
   * CHANGE: Dispara sempre que o estado do pino muda (LOW para HIGH, ou HIGH para LOW).
   * RISING: Dispara na transição de LOW para HIGH (borda de subida).
   * FALLING: Dispara na transição de HIGH para LOW (borda de descida).
   */
}

// -----------------------------------------------------------------
// 4. FUNÇÃO LOOP (CÓDIGO PRINCIPAL)
// -----------------------------------------------------------------

void loop() {
  // Implementação de um pisca-pisca não-bloqueante para o LED_LOOP (sem usar delay).
  // O uso de 'millis()' é preferível em sistemas embarcados para permitir que
  // o processador execute outras tarefas (como ler sensores ou verificar interrupções)
  // em vez de ficar 'parado' no delay().

  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= INTERVALO_PISCA) {
    tempoAnterior = tempoAtual;

    // Inverte o estado atual do LED no pino 13
    digitalWrite(LED_LOOP, !digitalRead(LED_LOOP));
    // obs: o resultado de digitalRead(LED_LOOP) é LOW ou HIGH.
  }

  // A interrupção garante que, mesmo durante a execução deste bloco
  // de código, o botão será detectado imediatamente, demonstrando o
  // funcionamento assíncrono.
}
