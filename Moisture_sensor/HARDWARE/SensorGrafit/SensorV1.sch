EESchema Schematic File Version 4
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
L Connector_Generic:Conn_01x03 J1
U 1 1 5BC63EF6
P 5250 3250
F 0 "J1" H 5170 2925 50  0000 C CNN
F 1 "Conn_01x03" H 5170 3016 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Horizontal" H 5250 3250 50  0001 C CNN
F 3 "~" H 5250 3250 50  0001 C CNN
	1    5250 3250
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small 10k1
U 1 1 5BC63FCD
P 5850 3150
F 0 "10k1" V 5654 3150 50  0000 C CNN
F 1 "R_Small" V 5745 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5850 3150 50  0001 C CNN
F 3 "~" H 5850 3150 50  0001 C CNN
	1    5850 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 3150 5450 3150
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5BC6412A
P 6550 3150
F 0 "J2" H 6630 3142 50  0000 L CNN
F 1 "Conn_01x02" H 6630 3051 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Horizontal" H 6550 3150 50  0001 C CNN
F 3 "~" H 6550 3150 50  0001 C CNN
	1    6550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 3150 6150 3150
Wire Wire Line
	5450 3250 6150 3250
Wire Wire Line
	6150 3250 6150 3150
Connection ~ 6150 3150
Wire Wire Line
	6150 3150 6350 3150
Wire Wire Line
	5450 3350 6350 3350
Wire Wire Line
	6350 3350 6350 3250
$EndSCHEMATC
