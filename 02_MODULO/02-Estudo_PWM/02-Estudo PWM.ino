// https://docs.arduino.cc/learn/microcontrollers/analog-output/
// https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm/

// =================================================================
// DEMOSTRAÇÃO PWM: SOFTWARE vs. HARDWARE (ATmega328/Arduino Uno)
//
// PWM do PINO 13: Gerado por SOFTWARE (lento e ineficiente, ocupa o CPU)
// PWM do PINO 3: Gerado por HARDWARE (eficiente, não ocupa o loop())
// =================================================================

// Pinos PWM nativos (Timer 2): D3 (OC2B) e D11 (OC2A)
// OC2A e OC2B refere-se às saídas dos elementos de hardware interno
// ao MCU que produz o PWM.
void setup()
{
    // ------------------------------------
    // 1. CONFIGURAÇÃO PWM POR SOFTWARE (Pino 13)
    // ------------------------------------
    pinMode(13, OUTPUT);

    // ------------------------------------
    // 2. CONFIGURAÇÃO PWM POR HARDWARE (Pino 3 - OC2B)
    // ------------------------------------

    // O pino 3 está ligado ao registrador OC2B (Output Compare Register B)
    pinMode(3, OUTPUT);

    // TCCR2A: Configura o Modo Fast PWM e o Comportamento do pino.
    // _BV(COM2B1) : Clear OC2B on Compare Match (non-inverting mode)
    // _BV(WGM21) | _BV(WGM20) : Modo Fast PWM (WGM2 = 3)
    TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

    // TCCR2B: Configura o Prescaler e Inicia o Timer.
    // Prescaler 64: Frequência do PWM = 16MHz / 64 / 256 ≈ 976.56Hz
    // CS22 = Prescaler 64
    // O 256 vem da contagem no Timer2, 0 a 255.
    TCCR2B = _BV(CS22);

    // OCR2B: Define o Ciclo de Trabalho (Duty Cycle) para o Pino 3 (OC2B)
    // 180 (valor de 0 a 255) : Duty Cycle ≈ (180+1) / 256 ≈ 70.7%
    //OCR2B = 180;
    OCR2B = 220;

    // Obs: O pino 11 (OC2A) é controlado por OCR2A.
}


void loop()
{
    // Este loop demonstra a LENTA e INEFICIENTE geração de PWM por software.
    // O CPU fica "preso" nos delays, sem poder fazer mais nada.

    // 1. PWM por Software no Pino 13 (frequência de 1KHz, 10% de Duty Cycle)
    // Período total = 100us (HIGH) + 900us (LOW) = 1000us (1ms), ou seja, 1KHz

    digitalWrite(13, HIGH);
    delayMicroseconds(100);
    digitalWrite(13, LOW);
    delayMicroseconds(900);

    // 2. O PWM por Hardware (Pino 3) está sendo gerado AUTOMATICAMENTE
    // pelo hardware (Timer 2) sem nenhuma instrução neste loop!
}
