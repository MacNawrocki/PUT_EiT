#pragma once

//Ilo�� retransmisji zanim pakiet zostanie odrzucony
#define RETRANSMISSIONS 5
//Ilosc symulacji
#define SIMULATION_NUMBER 20
//Ilo�� nadajnik�w
#define SENDERS_NUMBER 10
//Czas po kt�rym zamknie si� kana�
#define TIME_GAP 0.1

#define START_PHASE 25

//Ilosc generatorow
#define GENERATOR_NUMBER 2+(SENDERS_NUMBER*2)
//Ziarno
#define SEED 95
//Mnoznik
#define MULTIPLY 58621
#define MODULO 2240598381

//#define L 0.012
