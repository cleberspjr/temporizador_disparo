## Autor: Cleber Santos Pinto Júnior - https://github.com/cleberspjr


## Temporizador de um disparo
Este programa é desenvolvido para rodar em um microcontrolador Raspberry Pi Pico W e controla três LEDs (azul, vermelho e verde) com base em um botão que ao ser acionado liga as 3 LEDs e com um tempo especifico cada uma das LEDs vão apagando

## Funcionamento do programa
1. Configura os pinos dos LEDs como saída e o pino do botão como entrada com pull-up.
   Inicializa todos os LEDs apagados e prepara a interrupção do botão.
   O sistema fica em espera, aguardando o pressionamento do botão.

2. Quando o botão é pressionado, a função button_callback é acionada.
   Se o estado for ALL_OFF, todos os LEDs são acesos e um alarme de 3 segundos é configurado.
   O estado muda para ALL_ON, iniciando a sequência de desligamento dos LEDs.

3. Após 3 segundos, turn_off_callback desliga o LED azul e muda o estado para TWO_ON.
   Após mais 3 segundos, desliga o LED vermelho e muda para ONE_ON.
   Após outros 3 segundos, desliga o LED verde e muda para ALL_OFF.
   
4. O programa entra em um loop infinito, aguardando interrupções ou alarmes.
   O temporizador controla a transição entre os estados dos LEDs.
   O botão pode reiniciar a sequência se pressionado quando todos os LEDs estiverem apagados.

5. A sequência é: todos acesos → azul apagado → vermelho apagado → verde apagado.
   Após desligar todos os LEDs, aperta o botão, o ciclo recomeça, acendendo todos novamente.
   O intervalo entre cada transição é sempre de 3 segundos.
   
## MODO DE EXECUÇÃO

1. Clonar o Repositório:

```bash
git clone https: https://github.com/cleberspjr/temporizador_disparo
```

2. Configure o ambiente de desenvolvimento seguindo as instruções do Pico SDK

3. Abra o projeto no VS Code

4. Importe o projeto através da extensão Raspberry Pi Tools

5. Execute a simulação através do Wokwi ou da placa Bitdoglab

