EESchema Schematic File Version 4
EELAYER 30 0
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
L power:GND #PWR03
U 1 1 61DFC811
P 1600 1650
F 0 "#PWR03" H 1600 1400 50  0001 C CNN
F 1 "GND" H 1605 1477 50  0000 C CNN
F 2 "" H 1600 1650 50  0001 C CNN
F 3 "" H 1600 1650 50  0001 C CNN
	1    1600 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 6717D3ED
P 1350 1250
F 0 "#PWR01" H 1350 1100 50  0001 C CNN
F 1 "+12V" V 1350 1500 50  0000 C CNN
F 2 "" H 1350 1250 50  0001 C CNN
F 3 "" H 1350 1250 50  0001 C CNN
	1    1350 1250
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 692E12E0
P 3950 1350
F 0 "#PWR02" H 3950 1200 50  0001 C CNN
F 1 "+5V" V 3950 1550 50  0000 C CNN
F 2 "" H 3950 1350 50  0001 C CNN
F 3 "" H 3950 1350 50  0001 C CNN
	1    3950 1350
	0    1    1    0   
$EndComp
Connection ~ 3150 1350
Wire Wire Line
	2750 1350 3150 1350
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 66D2CE52
P 2650 1550
F 0 "J3" V 2900 1500 50  0000 C CNN
F 1 "5V Jump" V 2800 1500 50  0000 C CNN
F 2 "0_my_footprints:myPinHeader_1x02" H 2650 1550 50  0001 C CNN
F 3 "~" H 2650 1550 50  0001 C CNN
	1    2650 1550
	0    -1   1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 67022BE0
P 2500 1350
F 0 "D1" H 2500 1133 50  0000 C CNN
F 1 "1N4003" H 2500 1225 50  0000 C CNN
F 2 "0_my_footprints:myDiodeSchotsky" H 2500 1350 50  0001 C CNN
F 3 "~" H 2500 1350 50  0001 C CNN
	1    2500 1350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6718228E
P 3150 1800
F 0 "#PWR05" H 3150 1550 50  0001 C CNN
F 1 "GND" H 3155 1627 50  0000 C CNN
F 2 "" H 3150 1800 50  0001 C CNN
F 3 "" H 3150 1800 50  0001 C CNN
	1    3150 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 671A6D4E
P 3150 1500
F 0 "C1" H 3268 1546 50  0001 L CNN
F 1 "100uf" H 3300 1500 50  0000 L CNN
F 2 "0_my_footprints2:CP_my100uf" H 3188 1350 50  0001 C CNN
F 3 "~" H 3150 1500 50  0001 C CNN
	1    3150 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 671A6D48
P 2350 1650
F 0 "#PWR04" H 2350 1400 50  0001 C CNN
F 1 "GND" H 2355 1477 50  0000 C CNN
F 2 "" H 2350 1650 50  0001 C CNN
F 3 "" H 2350 1650 50  0001 C CNN
	1    2350 1650
	1    0    0    -1  
$EndComp
$Comp
L cnc3018_Library:BUCK01 M1
U 1 1 67182287
P 2000 1500
F 0 "M1" H 2150 1500 50  0001 C CNN
F 1 "BUCK01" H 1900 1500 50  0000 C CNN
F 2 "0_my_footprints2:buck-mini360" H 1950 1800 50  0001 C CNN
F 3 "" H 1950 1800 50  0001 C CNN
	1    2000 1500
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 692F3A66
P 900 1350
F 0 "J1" H 900 1600 50  0000 C CNN
F 1 "12 IN" H 900 1500 50  0000 C CNN
F 2 "0_my_footprints:myPheonix2x3.81_right" H 900 1350 50  0001 C CNN
F 3 "~" H 900 1350 50  0001 C CNN
	1    900  1350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 1350 1350 1350
Wire Wire Line
	1100 1450 1350 1450
Wire Wire Line
	1350 1450 1350 1650
Wire Wire Line
	1350 1650 1600 1650
Connection ~ 1600 1650
Wire Wire Line
	1350 1250 1350 1350
Connection ~ 1350 1350
Wire Wire Line
	1350 1350 1600 1350
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 692FCF72
P 3850 1700
F 0 "J4" H 3850 1950 50  0000 C CNN
F 1 "5V Test" H 3850 1850 50  0000 C CNN
F 2 "0_my_footprints:myPinSocket_1x02" H 3850 1700 50  0001 C CNN
F 3 "~" H 3850 1700 50  0001 C CNN
	1    3850 1700
	1    0    0    1   
$EndComp
Wire Wire Line
	3150 1350 3650 1350
Wire Wire Line
	3650 1600 3650 1350
Connection ~ 3650 1350
Wire Wire Line
	3650 1350 3950 1350
Wire Wire Line
	3650 1700 3150 1700
Wire Wire Line
	3150 1650 3150 1700
Connection ~ 3150 1700
Wire Wire Line
	3150 1700 3150 1800
$Comp
L Device:R R1
U 1 1 692C8E57
P 5500 1900
F 0 "R1" V 5600 1850 50  0000 L CNN
F 1 "1K" V 5500 1850 50  0000 L CNN
F 2 "0_my_footprints:myResistor" V 5430 1900 50  0001 C CNN
F 3 "~" H 5500 1900 50  0001 C CNN
	1    5500 1900
	0    1    -1   0   
$EndComp
Text GLabel 5850 1900 2    50   Input ~ 0
DRIVE_ROD
Text GLabel 5150 1900 0    50   Input ~ 0
S_DRIVE
Text GLabel 5150 2400 0    50   Input ~ 0
SENSOR_LOW
Text GLabel 6100 2400 2    50   Input ~ 0
ROD_LOW
$Comp
L Device:C C2
U 1 1 694827BA
P 5550 2550
F 0 "C2" H 5300 2450 50  0000 L CNN
F 1 "2.2uf" H 5250 2550 50  0000 L CNN
F 2 "0_my_footprints:myCapTantulum2" H 5588 2400 50  0001 C CNN
F 3 "~" H 5550 2550 50  0001 C CNN
	1    5550 2550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 694827C0
P 5250 2550
F 0 "R6" H 5350 2550 50  0000 L CNN
F 1 "100K" V 5250 2550 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5180 2550 50  0001 C CNN
F 3 "~" H 5250 2550 50  0001 C CNN
	1    5250 2550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 694827CC
P 5800 2400
F 0 "R4" V 5900 2350 50  0000 L CNN
F 1 "1K" V 5800 2400 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5730 2400 50  0001 C CNN
F 3 "~" H 5800 2400 50  0001 C CNN
	1    5800 2400
	0    1    -1   0   
$EndComp
Wire Wire Line
	5950 2400 6100 2400
Wire Wire Line
	5650 1900 5850 1900
Wire Wire Line
	5350 1900 5150 1900
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 694D6097
P 5700 1250
F 0 "J2" H 6000 1350 50  0000 C CNN
F 1 "SENSOR_ASSY" H 6050 1250 50  0000 C CNN
F 2 "0_my_footprints:myJSTx03" H 5700 1250 50  0001 C CNN
F 3 "~" H 5700 1250 50  0001 C CNN
	1    5700 1250
	1    0    0    -1  
$EndComp
Text GLabel 5500 1250 0    50   Input ~ 0
DRIVE_ROD
Text GLabel 5500 1150 0    50   Input ~ 0
ROD_LOW
Text GLabel 5500 1350 0    50   Input ~ 0
ROD_HIGH
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 69591300
P 1250 4650
F 0 "J7" H 1600 4550 50  0000 C CNN
F 1 "WS2812_B" H 1600 4650 50  0000 C CNN
F 2 "0_my_footprints:myJSTx03" H 1250 4650 50  0001 C CNN
F 3 "~" H 1250 4650 50  0001 C CNN
	1    1250 4650
	-1   0    0    -1  
$EndComp
Text GLabel 1450 5400 2    50   Input ~ 0
PUMP+
Text GLabel 1450 5500 2    50   Input ~ 0
PUMP-
Text GLabel 1900 4750 2    50   Input ~ 0
WS2812B
$Comp
L power:GND #PWR023
U 1 1 695C7DB1
P 1450 4650
F 0 "#PWR023" H 1450 4400 50  0001 C CNN
F 1 "GND" V 1450 4450 50  0000 C CNN
F 2 "" H 1450 4650 50  0001 C CNN
F 3 "" H 1450 4650 50  0001 C CNN
	1    1450 4650
	0    -1   1    0   
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 695D58B6
P 1600 2650
F 0 "#PWR08" H 1600 2500 50  0001 C CNN
F 1 "+5V" V 1600 2850 50  0000 C CNN
F 2 "" H 1600 2650 50  0001 C CNN
F 3 "" H 1600 2650 50  0001 C CNN
	1    1600 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 695EAB91
P 2100 2850
F 0 "#PWR010" H 2100 2600 50  0001 C CNN
F 1 "GND" V 2100 2650 50  0000 C CNN
F 2 "" H 2100 2850 50  0001 C CNN
F 3 "" H 2100 2850 50  0001 C CNN
	1    2100 2850
	1    0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR09
U 1 1 695EF873
P 3400 2700
F 0 "#PWR09" H 3400 2550 50  0001 C CNN
F 1 "+3V3" V 3400 2900 50  0000 C CNN
F 2 "" H 3400 2700 50  0001 C CNN
F 3 "" H 3400 2700 50  0001 C CNN
	1    3400 2700
	-1   0    0    -1  
$EndComp
Text GLabel 2500 2850 1    50   Input ~ 0
S_DRIVE
Text GLabel 2900 2850 1    50   Input ~ 0
SENSOR_LOW
Text GLabel 2700 2850 1    50   Input ~ 0
SENSOR_HIGH
Text GLabel 2300 3850 3    50   Input ~ 0
WS2812B
$Comp
L Device:C C3
U 1 1 696B0578
P 1150 2900
F 0 "C3" H 850 2950 50  0000 L CNN
F 1 "0.1uf" H 800 2850 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 1188 2750 50  0001 C CNN
F 3 "~" H 1150 2900 50  0001 C CNN
	1    1150 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2650 1600 2750
Wire Wire Line
	1600 2750 1150 2750
Connection ~ 1600 2750
Wire Wire Line
	1600 2750 1600 2850
$Comp
L power:GND #PWR012
U 1 1 696BF015
P 1150 3050
F 0 "#PWR012" H 1150 2800 50  0001 C CNN
F 1 "GND" V 1150 2850 50  0000 C CNN
F 2 "" H 1150 3050 50  0001 C CNN
F 3 "" H 1150 3050 50  0001 C CNN
	1    1150 3050
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 696C8FB0
P 3750 2900
F 0 "C4" H 4000 3000 50  0000 L CNN
F 1 "0.1uf" H 3950 2900 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 3788 2750 50  0001 C CNN
F 3 "~" H 3750 2900 50  0001 C CNN
	1    3750 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 696C8FB6
P 3750 3050
F 0 "#PWR013" H 3750 2800 50  0001 C CNN
F 1 "GND" V 3750 2850 50  0000 C CNN
F 2 "" H 3750 3050 50  0001 C CNN
F 3 "" H 3750 3050 50  0001 C CNN
	1    3750 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3400 2700 3400 2750
Wire Wire Line
	3750 2750 3400 2750
Connection ~ 3400 2750
Wire Wire Line
	3400 2750 3400 2850
$Comp
L power:+5V #PWR0101
U 1 1 6943AF93
P 1450 4550
F 0 "#PWR0101" H 1450 4400 50  0001 C CNN
F 1 "+5V" V 1450 4750 50  0000 C CNN
F 2 "" H 1450 4550 50  0001 C CNN
F 3 "" H 1450 4550 50  0001 C CNN
	1    1450 4550
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 69443C96
P 1600 4750
F 0 "R18" V 1500 4700 50  0000 L CNN
F 1 "330" V 1600 4750 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 1530 4750 50  0001 C CNN
F 3 "~" H 1600 4750 50  0001 C CNN
	1    1600 4750
	0    1    -1   0   
$EndComp
Wire Wire Line
	1900 4750 1750 4750
$Comp
L power:GND #PWR014
U 1 1 694827AE
P 5400 2700
F 0 "#PWR014" H 5400 2450 50  0001 C CNN
F 1 "GND" H 5405 2527 50  0000 C CNN
F 2 "" H 5400 2700 50  0001 C CNN
F 3 "" H 5400 2700 50  0001 C CNN
	1    5400 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2400 5250 2400
Connection ~ 5250 2400
Wire Wire Line
	5250 2400 5550 2400
Connection ~ 5550 2400
Wire Wire Line
	5550 2400 5650 2400
Wire Wire Line
	5250 2700 5400 2700
Connection ~ 5400 2700
Wire Wire Line
	5400 2700 5550 2700
Text GLabel 5150 3150 0    50   Input ~ 0
SENSOR_HIGH
Text GLabel 6100 3150 2    50   Input ~ 0
ROD_HIGH
$Comp
L Device:C C5
U 1 1 6939CEB0
P 5550 3300
F 0 "C5" H 5300 3200 50  0000 L CNN
F 1 "2.2uf" H 5250 3300 50  0000 L CNN
F 2 "0_my_footprints:myCapTantulum2" H 5588 3150 50  0001 C CNN
F 3 "~" H 5550 3300 50  0001 C CNN
	1    5550 3300
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6939CEB6
P 5250 3300
F 0 "R3" H 5350 3300 50  0000 L CNN
F 1 "100K" V 5250 3300 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5180 3300 50  0001 C CNN
F 3 "~" H 5250 3300 50  0001 C CNN
	1    5250 3300
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6939CEBC
P 5800 3150
F 0 "R2" V 5900 3100 50  0000 L CNN
F 1 "1K" V 5800 3150 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5730 3150 50  0001 C CNN
F 3 "~" H 5800 3150 50  0001 C CNN
	1    5800 3150
	0    1    -1   0   
$EndComp
Wire Wire Line
	5950 3150 6100 3150
$Comp
L power:GND #PWR06
U 1 1 6939CEC3
P 5400 3450
F 0 "#PWR06" H 5400 3200 50  0001 C CNN
F 1 "GND" H 5405 3277 50  0000 C CNN
F 2 "" H 5400 3450 50  0001 C CNN
F 3 "" H 5400 3450 50  0001 C CNN
	1    5400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3150 5250 3150
Connection ~ 5250 3150
Wire Wire Line
	5250 3150 5550 3150
Connection ~ 5550 3150
Wire Wire Line
	5550 3150 5650 3150
Wire Wire Line
	5250 3450 5400 3450
Connection ~ 5400 3450
Wire Wire Line
	5400 3450 5550 3450
Wire Wire Line
	5350 5100 5200 5100
Wire Wire Line
	4750 5000 4750 5100
Connection ~ 4750 5000
Connection ~ 5650 5600
Wire Wire Line
	4750 5600 5650 5600
Wire Wire Line
	4750 5400 4750 5600
Wire Wire Line
	4750 4900 4750 5000
Connection ~ 5050 4250
Wire Wire Line
	4750 4250 5050 4250
Wire Wire Line
	4750 4600 4750 4250
$Comp
L Device:R R7
U 1 1 6952A593
P 4750 4750
F 0 "R7" V 4650 4700 50  0000 L CNN
F 1 "100K" V 4750 4750 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4680 4750 50  0001 C CNN
F 3 "~" H 4750 4750 50  0001 C CNN
	1    4750 4750
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 69528E35
P 4750 5250
F 0 "R10" V 4650 5200 50  0000 L CNN
F 1 "33K" V 4750 5250 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4680 5250 50  0001 C CNN
F 3 "~" H 4750 5250 50  0001 C CNN
	1    4750 5250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 5000 4000 5000
$Comp
L Device:R R9
U 1 1 694D6E85
P 4150 5000
F 0 "R9" V 4050 4950 50  0000 L CNN
F 1 "220" V 4150 5000 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4080 5000 50  0001 C CNN
F 3 "~" H 4150 5000 50  0001 C CNN
	1    4150 5000
	0    -1   1    0   
$EndComp
Wire Wire Line
	5950 5600 6450 5600
Connection ~ 5950 5600
Wire Wire Line
	5950 5700 5950 5600
Connection ~ 5650 4250
Connection ~ 5300 4250
Wire Wire Line
	5300 4250 5650 4250
Wire Wire Line
	5300 4250 5050 4250
$Comp
L power:GND #PWR011
U 1 1 69474A8E
P 5050 4550
F 0 "#PWR011" H 5050 4300 50  0001 C CNN
F 1 "GND" V 5050 4350 50  0000 C CNN
F 2 "" H 5050 4550 50  0001 C CNN
F 3 "" H 5050 4550 50  0001 C CNN
	1    5050 4550
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 69474A88
P 5050 4400
F 0 "C6" H 5000 4800 50  0000 L CNN
F 1 "10uf" H 5000 4700 50  0000 L CNN
F 2 "0_my_footprints:CP_my10uf" H 5088 4250 50  0001 C CNN
F 3 "~" H 5050 4400 50  0001 C CNN
	1    5050 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 69472D8A
P 5300 4550
F 0 "#PWR015" H 5300 4300 50  0001 C CNN
F 1 "GND" V 5300 4350 50  0000 C CNN
F 2 "" H 5300 4550 50  0001 C CNN
F 3 "" H 5300 4550 50  0001 C CNN
	1    5300 4550
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 69472D84
P 5300 4400
F 0 "C7" H 5300 4800 50  0000 L CNN
F 1 "0.1uf" H 5250 4700 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 5338 4250 50  0001 C CNN
F 3 "~" H 5300 4400 50  0001 C CNN
	1    5300 4400
	1    0    0    -1  
$EndComp
Text GLabel 3900 5000 0    50   Input ~ 0
PUMP
Wire Wire Line
	6250 4250 5650 4250
Connection ~ 6250 4250
Wire Wire Line
	6250 4200 6250 4250
Wire Wire Line
	5650 4250 5650 4500
Wire Wire Line
	6850 4250 6250 4250
Wire Wire Line
	5650 5600 5950 5600
Wire Wire Line
	5650 5500 5650 5600
Connection ~ 6850 4650
Wire Wire Line
	6850 4650 6850 4750
Connection ~ 6450 4950
Wire Wire Line
	6400 4950 6450 4950
Wire Wire Line
	6450 4950 6550 4950
Wire Wire Line
	6450 5100 6450 4950
Wire Wire Line
	6450 5600 6850 5600
Connection ~ 6450 5600
$Comp
L Device:R R8
U 1 1 69448AEE
P 6250 4950
F 0 "R8" V 6150 4900 50  0000 L CNN
F 1 "100" V 6250 4950 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 6180 4950 50  0001 C CNN
F 3 "~" H 6250 4950 50  0001 C CNN
	1    6250 4950
	0    -1   1    0   
$EndComp
Wire Wire Line
	6100 5300 6100 4950
Wire Wire Line
	5950 5300 6100 5300
Wire Wire Line
	6450 5400 6450 5600
Wire Wire Line
	6850 5600 6850 5150
Wire Wire Line
	7050 4650 6850 4650
Connection ~ 6850 4350
Wire Wire Line
	7050 4350 6850 4350
$Comp
L Device:R R11
U 1 1 69417B11
P 6450 5250
F 0 "R11" V 6350 5200 50  0000 L CNN
F 1 "10K" V 6450 5250 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 6380 5250 50  0001 C CNN
F 3 "~" H 6450 5250 50  0001 C CNN
	1    6450 5250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 693D2296
P 5950 5700
F 0 "#PWR018" H 5950 5450 50  0001 C CNN
F 1 "GND" H 5955 5527 50  0000 C CNN
F 2 "" H 5950 5700 50  0001 C CNN
F 3 "" H 5950 5700 50  0001 C CNN
	1    5950 5700
	-1   0    0    -1  
$EndComp
$Comp
L Driver_FET:IR2104 U1
U 1 1 693C10DF
P 5650 5000
F 0 "U1" H 5700 5000 50  0000 C CNN
F 1 "IR2104" H 5650 5100 50  0000 C CNN
F 2 "0_my_footprints:myDip8" H 5650 5000 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/ir2104.pdf?fileId=5546d462533600a4015355c7c1c31671" H 5650 5000 50  0001 C CNN
	1    5650 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4250 6850 4350
Text GLabel 7050 4350 2    50   Input ~ 0
PUMP+
$Comp
L Transistor_FET:IRLZ44N Q1
U 1 1 61C50415
P 6750 4950
F 0 "Q1" H 7050 5050 50  0000 L CNN
F 1 "IRF520N" H 6950 4950 50  0000 L CNN
F 2 "0_my_footprints:myThreeLegged" H 7000 4875 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irlz44n.pdf" H 6750 4950 50  0001 L CNN
	1    6750 4950
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D2
U 1 1 61BE277E
P 6850 4500
F 0 "D2" V 6804 4580 50  0000 L CNN
F 1 "1N5818" V 6850 4600 50  0000 L CNN
F 2 "0_my_footprints:myDiodeSchotsky" H 6850 4325 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 6850 4500 50  0001 C CNN
	1    6850 4500
	0    -1   1    0   
$EndComp
$Comp
L power:+12V #PWR025
U 1 1 61C07060
P 6250 4200
F 0 "#PWR025" H 6250 4050 50  0001 C CNN
F 1 "+12V" H 6265 4373 50  0000 C CNN
F 2 "" H 6250 4200 50  0001 C CNN
F 3 "" H 6250 4200 50  0001 C CNN
	1    6250 4200
	-1   0    0    -1  
$EndComp
Text GLabel 7050 4650 2    50   Input ~ 0
PUMP-
Text GLabel 2400 3850 3    50   Input ~ 0
PUMP
$Comp
L power:GND #PWR017
U 1 1 695E7E52
P 3400 3850
F 0 "#PWR017" H 3400 3600 50  0001 C CNN
F 1 "GND" V 3400 3650 50  0000 C CNN
F 2 "" H 3400 3850 50  0001 C CNN
F 3 "" H 3400 3850 50  0001 C CNN
	1    3400 3850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 695E5C40
P 2800 3850
F 0 "#PWR016" H 2800 3600 50  0001 C CNN
F 1 "GND" V 2800 3650 50  0000 C CNN
F 2 "" H 2800 3850 50  0001 C CNN
F 3 "" H 2800 3850 50  0001 C CNN
	1    2800 3850
	-1   0    0    -1  
$EndComp
$Comp
L 0_my_symbols:ESP32_DEV U2
U 1 1 695D175F
P 2400 3400
F 0 "U2" H 2300 3550 50  0000 L CNN
F 1 "ESP32_DEV" H 2500 3550 50  0000 L CNN
F 2 "0_my_footprints2:esp32_dev" H 2050 3500 50  0001 C CNN
F 3 "" H 2050 3500 50  0001 C CNN
	1    2400 3400
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4001 D3
U 1 1 6951D2E2
P 4450 4450
F 0 "D3" V 4404 4530 50  0001 L CNN
F 1 "1N5818" H 4300 4600 50  0000 L CNN
F 2 "0_my_footprints:myDiodeSchotsky" H 4450 4275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 4450 4450 50  0001 C CNN
	1    4450 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 6959F45E
P 4450 4750
F 0 "R5" V 4350 4700 50  0000 L CNN
F 1 "10K" V 4450 4750 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4380 4750 50  0001 C CNN
F 3 "~" H 4450 4750 50  0001 C CNN
	1    4450 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4300 5000 4450 5000
Wire Wire Line
	4450 4900 4450 5000
Connection ~ 4450 5000
Wire Wire Line
	4450 5000 4750 5000
$Comp
L power:+3V3 #PWR07
U 1 1 695A70B3
P 4450 4300
F 0 "#PWR07" H 4450 4150 50  0001 C CNN
F 1 "+3V3" V 4450 4500 50  0000 C CNN
F 2 "" H 4450 4300 50  0001 C CNN
F 3 "" H 4450 4300 50  0001 C CNN
	1    4450 4300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 5000 5200 5000
Wire Wire Line
	5200 5100 5200 5000
Connection ~ 5200 5000
Wire Wire Line
	5200 5000 5350 5000
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 6931ED47
P 1250 5500
F 0 "J8" H 1250 5150 50  0000 C CNN
F 1 "PUMP" H 1250 5250 50  0000 C CNN
F 2 "0_my_footprints:myPheonix2x3.81_right" H 1250 5500 50  0001 C CNN
F 3 "~" H 1250 5500 50  0001 C CNN
	1    1250 5500
	-1   0    0    1   
$EndComp
$EndSCHEMATC
