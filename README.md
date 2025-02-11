# 🚀 Controle de Servo Motor com PWM 

Este projeto implementa o controle de um servomotor utilizando PWM no microcontrolador Raspberry Pi Pico W. O código simula o comportamento de um servo ajustando seus ângulos entre 0°, 90° e 180° e depois cria um movimento contínuo e suave entre esses ângulos.

## 🛠️ Requisitos

Raspberry Pi Pico W

Ambiente de desenvolvimento configurado com VS Code

Pico SDK instalado

Simulador Wokwi integrado ao VS Code

Repositório GitHub para versionamento

## 🎯Funcionamento

Configuração do PWM na GPIO 22 com frequência de 50Hz.

Definição dos pulsos PWM para posicionar o servo nos ângulos desejados:

⏳ 500µs → 0°

⏳ 1470µs → 90°

⏳ 2400µs → 180°

Movimentação suave do servo entre 0° e 180° com incremento de 5µs e atraso de 10ms.

## 📹Vídeo 

Após o experimento com a Ferramenta Educacional BitDogLab, foi observado que:

A intensidade da cor azul do LED RGB varia suavemente conforme o servo se move.

Quanto maior o ângulo do servo, mais forte o brilho azul.

O LED apaga completamente quando o servo está em 0° e acende no máximo em 180°

Link para o vídeo: [https://drive.google.com/file/d/1wdQQ01lokM3fChnW6TqUhbsESuxWQx0P/view?usp=sharing](https://drive.google.com/file/d/1wdQQ01lokM3fChnW6TqUhbsESuxWQx0P/view?usp=sharing)
