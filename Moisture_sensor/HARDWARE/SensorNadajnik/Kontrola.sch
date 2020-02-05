EESchema Schematic File Version 4
LIBS:Kontrola-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny84A-SSU U2
U 1 1 5BD816EA
P 5700 3500
F 0 "U2" H 5170 3546 50  0000 R CNN
F 1 "ATtiny84A-SSU" H 5170 3455 50  0000 R CNN
F 2 "Package_SO:SOIC-14_3.9x8.7mm_P1.27mm" H 5700 3500 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8183.pdf" H 5700 3500 50  0001 C CNN
	1    5700 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5BD817F6
P 3950 2850
F 0 "#PWR0101" H 3950 2600 50  0001 C CNN
F 1 "GND" H 3955 2677 50  0000 C CNN
F 2 "" H 3950 2850 50  0001 C CNN
F 3 "" H 3950 2850 50  0001 C CNN
	1    3950 2850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5BD81831
P 3950 2550
F 0 "#PWR0102" H 3950 2400 50  0001 C CNN
F 1 "+3.3V" H 3965 2723 50  0000 C CNN
F 2 "" H 3950 2550 50  0001 C CNN
F 3 "" H 3950 2550 50  0001 C CNN
	1    3950 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5BD8185B
P 3650 2900
F 0 "#PWR0103" H 3650 2650 50  0001 C CNN
F 1 "GND" H 3655 2727 50  0000 C CNN
F 2 "" H 3650 2900 50  0001 C CNN
F 3 "" H 3650 2900 50  0001 C CNN
	1    3650 2900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0104
U 1 1 5BD81861
P 3650 2550
F 0 "#PWR0104" H 3650 2400 50  0001 C CNN
F 1 "+3.3V" H 3665 2723 50  0000 C CNN
F 2 "" H 3650 2550 50  0001 C CNN
F 3 "" H 3650 2550 50  0001 C CNN
	1    3650 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5BD818A2
P 3950 2700
F 0 "C1" H 4042 2746 50  0000 L CNN
F 1 "100n" H 4042 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3950 2700 50  0001 C CNN
F 3 "~" H 3950 2700 50  0001 C CNN
	1    3950 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5BD81A09
P 3400 2750
F 0 "J1" H 3480 2742 50  0000 L CNN
F 1 "Conn_01x02" H 3480 2651 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3400 2750 50  0001 C CNN
F 3 "~" H 3400 2750 50  0001 C CNN
	1    3400 2750
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 5BD81A84
P 5700 2500
F 0 "#PWR0105" H 5700 2350 50  0001 C CNN
F 1 "+3.3V" H 5715 2673 50  0000 C CNN
F 2 "" H 5700 2500 50  0001 C CNN
F 3 "" H 5700 2500 50  0001 C CNN
	1    5700 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5BD81AAA
P 5700 4500
F 0 "#PWR0106" H 5700 4250 50  0001 C CNN
F 1 "GND" H 5705 4327 50  0000 C CNN
F 2 "" H 5700 4500 50  0001 C CNN
F 3 "" H 5700 4500 50  0001 C CNN
	1    5700 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2650 3650 2650
Wire Wire Line
	3650 2650 3650 2550
Wire Wire Line
	3600 2750 3650 2750
Wire Wire Line
	3950 2550 3950 2600
Wire Wire Line
	3950 2800 3950 2850
Wire Wire Line
	5700 2600 5700 2500
Wire Wire Line
	5700 4500 5700 4400
Wire Wire Line
	6300 2900 6600 2900
Text Label 6600 2900 1    50   ~ 0
czujnik
$Comp
L Connector_Generic:Conn_02x04_Odd_Even J3
U 1 1 5BD81ED9
P 7900 3050
F 0 "J3" H 7950 3367 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 7950 3276 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 7900 3050 50  0001 C CNN
F 3 "~" H 7900 3050 50  0001 C CNN
	1    7900 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2950 8350 2950
Wire Wire Line
	8200 3050 8350 3050
Wire Wire Line
	8200 3150 8350 3150
Wire Wire Line
	7700 3050 7550 3050
Wire Wire Line
	7700 3150 7550 3150
Wire Wire Line
	7700 3250 7550 3250
$Comp
L power:GND #PWR0107
U 1 1 5BD82691
P 7350 3000
F 0 "#PWR0107" H 7350 2750 50  0001 C CNN
F 1 "GND" H 7355 2827 50  0000 C CNN
F 2 "" H 7350 3000 50  0001 C CNN
F 3 "" H 7350 3000 50  0001 C CNN
	1    7350 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 2950 7350 3000
Wire Wire Line
	7350 2950 7700 2950
Text Label 7550 3050 0    50   ~ 0
CE
Text Label 7550 3150 0    50   ~ 0
SCK
Text Label 7550 3250 0    50   ~ 0
MISO
Text Label 8350 3050 0    50   ~ 0
CSN
Text Label 8350 3150 0    50   ~ 0
MOSI
Text Label 8450 3250 0    50   ~ 0
IRQ
Text Label 8350 2950 0    50   ~ 0
VCC_R
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J4
U 1 1 5BD82AFD
P 7900 3800
F 0 "J4" H 7950 4117 50  0000 C CNN
F 1 "Conn_02x03_Odd_Even" H 7950 4026 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 7900 3800 50  0001 C CNN
F 3 "~" H 7900 3800 50  0001 C CNN
	1    7900 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3700 7700 3700
Wire Wire Line
	7700 3800 7500 3800
Wire Wire Line
	7700 3900 7500 3900
Wire Wire Line
	8200 3800 8400 3800
Wire Wire Line
	6300 3600 6600 3600
Wire Wire Line
	6300 3500 6600 3500
Wire Wire Line
	6300 3400 6600 3400
$Comp
L Device:Crystal_Small Y1
U 1 1 5BD84547
P 6750 3850
F 0 "Y1" V 6704 3938 50  0000 L CNN
F 1 "8M" V 6795 3938 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 6750 3850 50  0001 C CNN
F 3 "~" H 6750 3850 50  0001 C CNN
	1    6750 3850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5BD8466F
P 7000 3750
F 0 "C5" H 7092 3796 50  0000 L CNN
F 1 "22p" H 7092 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7000 3750 50  0001 C CNN
F 3 "~" H 7000 3750 50  0001 C CNN
	1    7000 3750
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5BD84DEC
P 7000 3950
F 0 "C6" H 7092 3996 50  0000 L CNN
F 1 "22p" H 7092 3905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7000 3950 50  0001 C CNN
F 3 "~" H 7000 3950 50  0001 C CNN
	1    7000 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	6650 3750 6750 3750
Wire Wire Line
	6900 3750 6750 3750
Connection ~ 6750 3750
Wire Wire Line
	7100 3750 7100 3950
Wire Wire Line
	6750 3950 6900 3950
Wire Wire Line
	6650 3950 6750 3950
Connection ~ 6750 3950
Text Label 7500 3700 0    50   ~ 0
MISO
Text Label 7500 3800 0    50   ~ 0
SCK
Text Label 7500 3900 0    50   ~ 0
~RESET
Text Label 8400 3800 0    50   ~ 0
MOSI
$Comp
L power:GND #PWR0108
U 1 1 5BD87B1A
P 8450 4000
F 0 "#PWR0108" H 8450 3750 50  0001 C CNN
F 1 "GND" H 8455 3827 50  0000 C CNN
F 2 "" H 8450 4000 50  0001 C CNN
F 3 "" H 8450 4000 50  0001 C CNN
	1    8450 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 5BD87B20
P 8450 3600
F 0 "#PWR0109" H 8450 3450 50  0001 C CNN
F 1 "+3.3V" H 8465 3773 50  0000 C CNN
F 2 "" H 8450 3600 50  0001 C CNN
F 3 "" H 8450 3600 50  0001 C CNN
	1    8450 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3700 8450 3700
Wire Wire Line
	8450 3600 8450 3700
Wire Wire Line
	8200 3900 8450 3900
Wire Wire Line
	8450 3900 8450 4000
$Comp
L power:GND #PWR0110
U 1 1 5BD89E6E
P 7100 4100
F 0 "#PWR0110" H 7100 3850 50  0001 C CNN
F 1 "GND" H 7105 3927 50  0000 C CNN
F 2 "" H 7100 4100 50  0001 C CNN
F 3 "" H 7100 4100 50  0001 C CNN
	1    7100 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3950 7100 4100
Connection ~ 7100 3950
$Comp
L power:GND #PWR0111
U 1 1 5BD8B47D
P 4400 2850
F 0 "#PWR0111" H 4400 2600 50  0001 C CNN
F 1 "GND" H 4405 2677 50  0000 C CNN
F 2 "" H 4400 2850 50  0001 C CNN
F 3 "" H 4400 2850 50  0001 C CNN
	1    4400 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5BD8B489
P 4400 2700
F 0 "C3" H 4492 2746 50  0000 L CNN
F 1 "100n" H 4492 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4400 2700 50  0001 C CNN
F 3 "~" H 4400 2700 50  0001 C CNN
	1    4400 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2800 4400 2850
$Comp
L power:GND #PWR0112
U 1 1 5BD8BBDC
P 4750 2850
F 0 "#PWR0112" H 4750 2600 50  0001 C CNN
F 1 "GND" H 4755 2677 50  0000 C CNN
F 2 "" H 4750 2850 50  0001 C CNN
F 3 "" H 4750 2850 50  0001 C CNN
	1    4750 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5BD8BBE8
P 4750 2700
F 0 "C4" H 4842 2746 50  0000 L CNN
F 1 "100n" H 4842 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4750 2700 50  0001 C CNN
F 3 "~" H 4750 2700 50  0001 C CNN
	1    4750 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2800 4750 2850
$Comp
L NASZALIB:DMG2305UX T1
U 1 1 5BD8C487
P 7850 4650
F 0 "T1" H 7955 4696 50  0000 L CNN
F 1 "DMG2305UX" H 7955 4605 50  0000 L CNN
F 2 "NASZELIB:SOT23_NASZE" H 7850 4650 50  0001 C CNN
F 3 "" H 7850 4650 50  0001 C CNN
	1    7850 4650
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0113
U 1 1 5BD8C5A0
P 7550 4550
F 0 "#PWR0113" H 7550 4400 50  0001 C CNN
F 1 "+3.3V" H 7565 4723 50  0000 C CNN
F 2 "" H 7550 4550 50  0001 C CNN
F 3 "" H 7550 4550 50  0001 C CNN
	1    7550 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5BD909E0
P 7550 4800
F 0 "R3" H 7609 4846 50  0000 L CNN
F 1 "1k" H 7609 4755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7550 4800 50  0001 C CNN
F 3 "~" H 7550 4800 50  0001 C CNN
	1    7550 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4550 7550 4650
Wire Wire Line
	7550 4650 7650 4650
Wire Wire Line
	7550 4650 7550 4700
Connection ~ 7550 4650
Wire Wire Line
	7550 4900 7550 5000
Wire Wire Line
	7550 5000 7850 5000
Wire Wire Line
	7850 5000 7850 4950
Connection ~ 7850 5000
Wire Wire Line
	8050 4650 8250 4650
$Comp
L Device:R_Small R4
U 1 1 5BD941E7
P 7850 5200
F 0 "R4" H 7909 5246 50  0000 L CNN
F 1 "100k" H 7909 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7850 5200 50  0001 C CNN
F 3 "~" H 7850 5200 50  0001 C CNN
	1    7850 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 5300 7850 5400
Wire Wire Line
	7850 5400 7550 5400
Wire Wire Line
	7850 5000 7850 5100
Text Label 8250 4650 0    50   ~ 0
VCC_R
Text Label 7550 5400 2    50   ~ 0
~ZAS_RADIO
Wire Wire Line
	4400 2400 4400 2600
Wire Wire Line
	4750 2400 4750 2600
Text Label 4750 2400 0    50   ~ 0
VCC_R
Text Label 4400 2400 0    50   ~ 0
VCC_R
$Comp
L Device:CP_Small C2
U 1 1 5BEB00EC
P 4350 1850
F 0 "C2" H 4438 1896 50  0000 L CNN
F 1 "100u" H 4438 1805 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B_Pad1.50x2.35mm_HandSolder" H 4350 1850 50  0001 C CNN
F 3 "~" H 4350 1850 50  0001 C CNN
	1    4350 1850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5BEB01FA
P 4350 2050
F 0 "#PWR0114" H 4350 1800 50  0001 C CNN
F 1 "GND" H 4355 1877 50  0000 C CNN
F 2 "" H 4350 2050 50  0001 C CNN
F 3 "" H 4350 2050 50  0001 C CNN
	1    4350 2050
	1    0    0    -1  
$EndComp
Text Label 4350 1500 0    50   ~ 0
VCC_R
Wire Wire Line
	4350 1500 4350 1750
Wire Wire Line
	4350 1950 4350 2050
$Comp
L uchwyt_baterii:DS1092-04-B6P U1
U 1 1 5BEB5DD6
P 3600 1850
F 0 "U1" H 3678 1896 50  0000 L CNN
F 1 "DS1092-04-B6P" H 3678 1805 50  0000 L CNN
F 2 "uchwyt_baterii:DS1092-04-B6P" H 3725 1350 50  0001 C CNN
F 3 "" H 3725 1350 50  0001 C CNN
	1    3600 1850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0115
U 1 1 5BEB6216
P 3600 1600
F 0 "#PWR0115" H 3600 1450 50  0001 C CNN
F 1 "+3.3V" H 3615 1773 50  0000 C CNN
F 2 "" H 3600 1600 50  0001 C CNN
F 3 "" H 3600 1600 50  0001 C CNN
	1    3600 1600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5BEB71C8
P 3600 2050
F 0 "#PWR0116" H 3600 1800 50  0001 C CNN
F 1 "GND" H 3605 1877 50  0000 C CNN
F 2 "" H 3600 2050 50  0001 C CNN
F 3 "" H 3600 2050 50  0001 C CNN
	1    3600 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2050 3600 2000
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5BEBC084
P 3600 3650
F 0 "J2" H 3680 3692 50  0000 L CNN
F 1 "Conn_01x03" H 3680 3601 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 3600 3650 50  0001 C CNN
F 3 "~" H 3600 3650 50  0001 C CNN
	1    3600 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3550 3150 3550
Wire Wire Line
	3400 3650 3150 3650
$Comp
L Device:R_Small R1
U 1 1 5BEC1434
P 2700 3700
F 0 "R1" V 2504 3700 50  0000 C CNN
F 1 "0" V 2595 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2700 3700 50  0001 C CNN
F 3 "~" H 2700 3700 50  0001 C CNN
	1    2700 3700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5BEC15DE
P 2700 4000
F 0 "R2" V 2504 4000 50  0000 C CNN
F 1 "0" V 2595 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2700 4000 50  0001 C CNN
F 3 "~" H 2700 4000 50  0001 C CNN
	1    2700 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 3750 2950 3750
Wire Wire Line
	2950 3750 2950 3700
Wire Wire Line
	2950 3700 2800 3700
Wire Wire Line
	2950 3750 2950 4000
Wire Wire Line
	2950 4000 2800 4000
Connection ~ 2950 3750
Wire Wire Line
	2600 3700 2350 3700
$Comp
L power:GND #PWR0117
U 1 1 5BEC5B9E
P 2350 4050
F 0 "#PWR0117" H 2350 3800 50  0001 C CNN
F 1 "GND" H 2355 3877 50  0000 C CNN
F 2 "" H 2350 4050 50  0001 C CNN
F 3 "" H 2350 4050 50  0001 C CNN
	1    2350 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 4000 2350 4000
Wire Wire Line
	2350 4000 2350 4050
Text Label 2350 3700 0    50   ~ 0
pinHL
Text Label 3150 3550 0    50   ~ 0
GEN
Text Label 3150 3650 0    50   ~ 0
czujnik
Wire Wire Line
	6300 4100 6550 4100
Wire Wire Line
	6300 4000 6500 4000
Wire Wire Line
	6300 3300 6600 3300
Wire Wire Line
	6300 3200 6600 3200
Wire Wire Line
	6300 3100 6600 3100
Wire Wire Line
	6300 3000 6600 3000
Text Label 6600 3000 0    50   ~ 0
pinHL
Text Label 6600 3100 0    50   ~ 0
CSN
Text Label 6600 3200 0    50   ~ 0
CE
Text Label 6600 3300 0    50   ~ 0
SCK
Text Label 6600 3400 0    50   ~ 0
MISO
Text Label 6600 3500 0    50   ~ 0
MOSI
Text Label 6600 3600 0    50   ~ 0
~ZAS_RADIO
Text Label 6500 4000 0    50   ~ 0
GEN
Wire Wire Line
	6650 3750 6650 3800
Wire Wire Line
	6650 3800 6300 3800
Wire Wire Line
	6650 3950 6650 3900
Wire Wire Line
	6650 3900 6300 3900
Text Label 6550 4100 0    50   ~ 0
~RESET
Wire Wire Line
	3600 1700 3600 1600
Wire Wire Line
	8200 3250 8450 3250
Wire Wire Line
	3650 2750 3650 2900
$EndSCHEMATC
