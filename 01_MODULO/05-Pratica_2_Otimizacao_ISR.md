
# Prática 1: Otimizando a Interrupção
    No código do LED controlado por interrupção, usamos a função digitalWrite() dentro da Rotina de Serviço de Interrupção (ISR). Vimos que esta função é mais lenta e menos eficiente para código crítico de tempo, como em uma ISR.
    O desafio é substituir o digitalWrite() pela manipulação direta de registradores (PORT) para o pino D12, tornando o código da interrupção o mais rápido e eficiente possível.
## Passos previstos
    **Passo 1**: Mapeamento de Pinos e Registradores (Onde está o D12?)
        1. Localize a Tabela: Pesquise a tabela de pinagem do Arduino Uno (ou ATmega328) para descobrir a qual Porta Lógica (PORT) o pino digital D12 está conectado.
        Dica: Lembre-se que as portas lógicas no ATmega328 são nomeadas PORTB, PORTC e PORTD.
        
        2. Identifique o Bit: Uma vez identificada a porta, descubra qual Bit dentro desse registrador corresponde ao pino D12.
        Exemplo: O pino D7 que usamos na outra atividade correspondia ao Bit 7 do PORTD (PD7). Qual é o Bit do pino D12?
        
    **Passo 2**: Adaptando a Lógica de Bits
    No código de exemplo do PORTD, usamos os operadores bit a bit (|, &, ~) para ligar e desligar o LED. Agora, precisamos criar a máscara correta para o pino D12.
        1. Criação da Máscara: Crie uma constante (máscara binária) que isole o bit correspondente ao pino D12. Por exemplo:
        const byte MASCARA_LED_ISR = Bxxxxxxxx;
        2. Configuração do Setup: No setup(), use o registrador de direção (DDR) correspondente (DDRX, onde X pode ser B, C e D) para garantir que o pino D12 seja configurado como SAÍDA.
        Use o operador | (OR Bit a Bit) para configurar o bit desejado do registrador como 1 (Saída) e manter os outros inalterados.
        
    **Passo 3**: Reescrevendo a ISR (Otimização)
A função toggleLedISR() alterna o valor do bit (crítica de tempo).
    1. Substituição da Função: Substitua a linha “digitalWrite(LED_ISR, estadoLed);” dentro da função de ISR pela manipulação direta do registrador PORTX(onde X pode ser B, C e D).
    2. Otimização Final: Em vez de usar a variável volatile bool estadoLed e as estruturas if/else, utilize o método mais rápido para alternar o estado do LED (toggle), que é o operador XOR Bit a Bit (^), i. e., “PORTX ^= MASCARA_LED_ISR;”.
    
    **Passo 4**: Validação e Documentação
        1. Teste: Carregue o novo código no Arduino e verifique se o LED no pino D12 acende e apaga corretamente ao pressionar o botão (pino D2/INT0).
        2. Reflexão: por que a manipulação de registradores (PORTB) foi usada em vez de digitalWrite() e por que o operador XOR (^) é ideal aqui?
