-----------------------------------------------------------------------------------------------------------
|                                                                                                         |
|                                                                                                         |
|                                            UNIVERSIDADE DE AVEIRO                                       |
|                                                                                                         |
|                               Mestrado em Engenharia de Automação Industrial                            |
|                                                                                                         |
|                                      Projeto de Engenharia e Automação                                  |
|                                                                                                         |
|                                                                                                         |
|                                       Interface OBD para ATLASCAR II                                    |
|                                                                                                         |
|                                                                                                         |
|   Orientado por: Prof. Vitor Santos                           Realizado por: Luis Cristóvão             |
|                                                                              nº 80886                   |
|																							   			  |
|                                               JUNHO 2018                                                |
-----------------------------------------------------------------------------------------------------------

PT:

   No âmbito da Unidade curricular de PEA, foi desenvolvida uma inteface OBD para letura dos valores 
disponibilizados por a ECU (Engine Motor Control) do veiculo Mitsubishi I-MIEV, constituinte do projeto
ATLASCAR II http://atlas.web.ua.pt.

   O sistema está desenvolvido para a plataforma Raspberry PI 2, com um modulo de comunicação CAN 
(MCP2515). O código fonte está desenvolvido em C++, sendo possivel ler em tempo real os seguintes valores:
   - Estado da chave do carro,
   - Quilometros do carro,
   - Velocidade Atual,
   - Estado dos travões,
   - Posição Travão,
   - Posição Acelerador,
   - Mudança,
   - Posição do volante.

Ainda em desenvolvimento.


EN:
		
   Within the scope of the PEA curricular unit, an OBD interface was developed to ensure the values 
made available by the ECU (Engine Motor Control) of the vehicle Mitsubishi I-MIEV, constituent of the
project ATLASCAR II http://atlas.web.ua.pt.
		
   The system is designed for the Raspberry PI 2 platform, with a CAN communication module (MCP2515). 
The source code is developed in C ++, being able to read in real time the following values:
   - Car key status,
   - Kilometers from the car,
   - Current Speed,
   - Brake condition,
   - Position Brake,
   - Position Accelerator,
   - Change,
   - Steering wheel position.

Still in development.