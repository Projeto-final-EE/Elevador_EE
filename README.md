# Firmware de Controle de um Elevador Controlado por Bluetooth

Este projeto consiste no desenvolvimento de um firmware de controle para um elevador controlado por Bluetooth, utilizando o microcontrolador PIC16F1827. O objetivo principal é criar um sistema eletrônico embarcado que permita controlar remotamente um elevador por meio de comunicação Bluetooth.

## Funcionalidades do Firmware

- Comunicação Bluetooth: O firmware estabelece uma conexão Bluetooth entre o microcontrolador PIC16F1827 e um dispositivo remoto, como um smartphone ou tablet, permitindo o controle do elevador por meio de comandos enviados via Bluetooth.

- Painel de led: Para indicar funcionamento, andares de paradas e andar atual.

- Controle de Movimento: O firmware é responsável por interpretar os comandos recebidos via Bluetooth e controlar o movimento do elevador de acordo com esses comandos. Ele é capaz de realizar as operações de subida, descida e paradas.

- Segurança: O firmware implementa medidas de segurança para garantir um funcionamento adequado do elevador, incluindo a verificação de limites de percurso.

- Interface de Status: O firmware fornece uma interface para monitorar o status do elevador. Isso pode incluir informações como a posição atual, o estado de movimento, a velocidade, temperatura e a disponibilidade do elevador.

## Componentes Utilizados

- Microcontrolador PIC16F1827.

- Módulo Bluetooth HC06.

- Sensores de fim de curso e temperatura.

- Motor com caixa de redução

- Painel de led para indicar funcionamento

## Desenvolvimento e Testes

O firmware foi desenvolvido utilizando a linguagem C e utilizando o ambiente de desenvolvimento MPLAB. Foram realizados testes para garantir o correto funcionamento do sistema, tanto em relação ao controle do elevador quanto à comunicação.

## Diagramas e Código-fonte

Este repositório contém os diagramas esquemáticos do circuito eletrônico, bem como o código-fonte do firmware desenvolvido. Esses recursos são disponibilizados para facilitar a compreensão do projeto e permitir a reprodução do sistema em outros contextos.
