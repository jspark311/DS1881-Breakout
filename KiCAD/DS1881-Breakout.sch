EESchema Schematic File Version 4
LIBS:DS1881-Breakout-cache
EELAYER 26 0
EELAYER END
$Descr User 6299 5512
encoding utf-8
Sheet 1 1
Title "DS1881 Breakout"
Date "2019-08-20"
Rev "1"
Comp "Manuvr, inc"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2100 2650 0    39   ~ 0
SCL
Text Label 2100 2550 0    39   ~ 0
SDA
$Comp
L Device:C C1
U 1 1 5D1C4E25
P 2850 2250
F 0 "C1" H 2850 2350 39  0000 L CNN
F 1 "1uF" H 2850 2150 39  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2888 2100 50  0001 C CNN
F 3 "~" H 2850 2250 50  0001 C CNN
F 4 "490-1320-1-ND" H 2850 2250 50  0001 C CNN "Digikey_Num"
	1    2850 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5D1C4E71
P 3300 2250
F 0 "C2" H 3300 2350 39  0000 L CNN
F 1 "1uF" H 3300 2150 39  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3338 2100 50  0001 C CNN
F 3 "~" H 3300 2250 50  0001 C CNN
F 4 "490-1320-1-ND" H 3300 2250 50  0001 C CNN "Digikey_Num"
	1    3300 2250
	1    0    0    -1  
$EndComp
Text Label 3350 2050 0    39   ~ 0
Vcc
$Comp
L VianSonus2.0-parts:DS1881E-050+ U1
U 1 1 5D25C00E
P 1650 1900
F 0 "U1" H 1650 1600 50  0000 C CNN
F 1 "DS1881E-050+" H 1650 2274 50  0000 C CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 1650 2250 50  0001 C CNN
F 3 "" H 1650 2250 50  0001 C CNN
F 4 "DS1881E-050+-ND" H 1650 1900 50  0001 C CNN "Digikey_Num"
F 5 "DS1881E-050+" H 1650 1900 50  0001 C CNN "Manu_Num"
F 6 "Maxim Integrated" H 1650 1900 50  0001 C CNN "Manu_Name"
	1    1650 1900
	1    0    0    -1  
$EndComp
Text Label 2100 1850 0    39   ~ 0
Vcc
Text Label 2100 1950 0    39   ~ 0
GND
Text Label 2900 2050 0    39   ~ 0
ANAVcc
Text Label 3350 2500 0    39   ~ 0
GND
Text Label 2100 1750 0    39   ~ 0
ANAVcc
Wire Wire Line
	2900 2050 2850 2050
Wire Wire Line
	2850 2050 2850 2100
Wire Wire Line
	3350 2500 3300 2500
Wire Wire Line
	3300 2500 3300 2400
Wire Wire Line
	3300 2100 3300 2050
Wire Wire Line
	3300 2050 3350 2050
Wire Wire Line
	2900 2450 2850 2450
Wire Wire Line
	2850 2450 2850 2400
Text Label 1200 1700 2    39   ~ 0
H0
Text Label 1200 2300 2    39   ~ 0
H1
Text Label 1200 2100 2    39   ~ 0
L0
Text Label 1200 2700 2    39   ~ 0
L1
Text Label 1200 1900 2    39   ~ 0
W0
Text Label 1200 2500 2    39   ~ 0
W1
Text Label 2100 2450 0    39   ~ 0
~CE
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 5D304CB1
P 4600 2800
F 0 "J4" H 4573 2730 50  0000 R CNN
F 1 "Conn_01x03_Male" H 4573 2821 50  0000 R CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged12_RoundedPad1.0x1.5mm" H 4600 2800 50  0001 C CNN
F 3 "~" H 4600 2800 50  0001 C CNN
	1    4600 2800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 5D304DDC
P 4600 3150
F 0 "J5" H 4573 3080 50  0000 R CNN
F 1 "Conn_01x03_Male" H 4573 3171 50  0000 R CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged12_RoundedPad1.0x1.5mm" H 4600 3150 50  0001 C CNN
F 3 "~" H 4600 3150 50  0001 C CNN
	1    4600 3150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5D304E20
P 4600 2450
F 0 "J3" H 4573 2380 50  0000 R CNN
F 1 "Conn_01x03_Male" H 4573 2471 50  0000 R CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Bridged12_RoundedPad1.0x1.5mm" H 4600 2450 50  0001 C CNN
F 3 "~" H 4600 2450 50  0001 C CNN
	1    4600 2450
	-1   0    0    1   
$EndComp
Text Label 2100 2050 0    39   ~ 0
A0
Text Label 2100 2150 0    39   ~ 0
A1
Text Label 2100 2250 0    39   ~ 0
A2
Text Label 4400 2450 2    39   ~ 0
A0
Text Label 4400 2800 2    39   ~ 0
A1
Text Label 4400 3150 2    39   ~ 0
A2
Text Label 4400 3050 2    39   ~ 0
Vcc
Text Label 4400 2700 2    39   ~ 0
Vcc
Text Label 4400 2350 2    39   ~ 0
Vcc
Text Label 4400 2550 2    39   ~ 0
GND
Text Label 4400 2900 2    39   ~ 0
GND
Text Label 4400 3250 2    39   ~ 0
GND
Text Label 2900 2450 0    39   ~ 0
ANAGND
$Comp
L Connector:Conn_01x07_Male J2
U 1 1 5D305796
P 4850 1550
F 0 "J2" H 4956 2028 50  0000 C CNN
F 1 "Conn_01x07_Male" H 4956 1937 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4850 1550 50  0001 C CNN
F 3 "~" H 4850 1550 50  0001 C CNN
	1    4850 1550
	1    0    0    -1  
$EndComp
Text Label 5050 1350 0    39   ~ 0
GND
Text Label 5050 1250 0    39   ~ 0
Vcc
Text Label 5050 1450 0    39   ~ 0
ANAGND
Text Label 5050 1550 0    39   ~ 0
ANAVcc
Text Label 5050 1850 0    39   ~ 0
SCL
Text Label 5050 1750 0    39   ~ 0
SDA
Text Label 5050 1650 0    39   ~ 0
~CE
$Comp
L Connector:Conn_01x07_Male J1
U 1 1 5D305B05
P 4300 1550
F 0 "J1" H 4406 2028 50  0000 C CNN
F 1 "Conn_01x07_Male" H 4406 1937 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4300 1550 50  0001 C CNN
F 3 "~" H 4300 1550 50  0001 C CNN
	1    4300 1550
	1    0    0    -1  
$EndComp
Text Label 4500 1250 0    39   ~ 0
H0
Text Label 4500 1850 0    39   ~ 0
H1
Text Label 4500 1450 0    39   ~ 0
L0
Text Label 4500 1650 0    39   ~ 0
L1
Text Label 4500 1350 0    39   ~ 0
W0
Text Label 4500 1750 0    39   ~ 0
W1
Text Label 4500 1550 0    39   ~ 0
ANAGND
$EndSCHEMATC
