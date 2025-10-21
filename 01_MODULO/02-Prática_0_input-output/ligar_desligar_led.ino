/*
 * Prática 0: "Hello World" do Embarcado com Botão e LED
 * Objetivo: Ligar o LED ao pressionar o botão.
 */

// --- Definições dos Pinos ---
const int PINO_BOTAO = 2; // Pino para a entrada do botão (com pullup interno)
const int PINO_LED = 12;  // Pino para a saída do LED
int state = LOW;

void setup() {
    // 1. Configuração do LED como SAÍDA (Output)
    pinMode(PINO_LED, OUTPUT);

    // 2. Configuração do Botão como ENTRADA com PULLUP INTERNO
    // O pino ficará HIGH (Ligado) por padrão e LOW (Desligado) quando o botão for pressionado
    pinMode(PINO_BOTAO, INPUT_PULLUP);

    // Opcional: Iniciar o Monitor Serial para depuração
    Serial.begin(9600);
    Serial.println("Sistema Embarcado Pronto!");
}

void loop() {
    // 1. Leitura do estado do botão
    // Como usamos INPUT_PULLUP, a leitura será:
    // - HIGH (1) se o botão estiver solto.
    // - LOW (0) se o botão estiver pressionado (puxado para o GND).
    int estadoBotao = digitalRead(PINO_BOTAO);

    // Opcional: Exibir o estado no Monitor Serial
    // Serial.print("Estado do Botão: ");
    // Serial.println(estadoBotao);

    // 2. Lógica de Controle:
    // Se o estado for LOW (botão pressionado), o LED deve LIGAR (HIGH).
    if (estadoBotao == LOW) {
        state = ~state;
        // Botão Pressionado: LIGA o LED
        //digitalWrite(PINO_LED, HIGH);
        digitalWrite(PINO_LED, state);
    }
}
