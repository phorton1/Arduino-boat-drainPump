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
Text GLabel 4350 6200 2    50   Input ~ 0
PUMP
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
P 6500 1300
F 0 "R1" V 6600 1250 50  0000 L CNN
F 1 "1K" V 6500 1250 50  0000 L CNN
F 2 "0_my_footprints:myResistor" V 6430 1300 50  0001 C CNN
F 3 "~" H 6500 1300 50  0001 C CNN
	1    6500 1300
	0    1    -1   0   
$EndComp
Text GLabel 6850 1300 2    50   Input ~ 0
DRIVE_ROD
Text GLabel 6150 1300 0    50   Input ~ 0
S_DRIVE
$Comp
L Comparator:LM393 U1
U 3 1 692CE3A2
P 5450 6900
F 0 "U1" H 5408 6946 50  0000 L CNN
F 1 "LM393" H 5408 6855 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5450 6900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 5450 6900 50  0001 C CNN
	3    5450 6900
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR027
U 1 1 692DB0AB
P 5700 6600
F 0 "#PWR027" H 5700 6450 50  0001 C CNN
F 1 "+3V3" H 5715 6773 50  0000 C CNN
F 2 "" H 5700 6600 50  0001 C CNN
F 3 "" H 5700 6600 50  0001 C CNN
	1    5700 6600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 692DBCA7
P 5700 7200
F 0 "#PWR028" H 5700 6950 50  0001 C CNN
F 1 "GND" H 5705 7027 50  0000 C CNN
F 2 "" H 5700 7200 50  0001 C CNN
F 3 "" H 5700 7200 50  0001 C CNN
	1    5700 7200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 692F0D5E
P 6000 6900
F 0 "C6" H 6115 6946 50  0000 L CNN
F 1 "0.1uf" H 6115 6855 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 6038 6750 50  0001 C CNN
F 3 "~" H 6000 6900 50  0001 C CNN
	1    6000 6900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 692F13CC
P 6450 6900
F 0 "C7" H 6565 6946 50  0000 L CNN
F 1 "1uf" H 6565 6855 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 6488 6750 50  0001 C CNN
F 3 "~" H 6450 6900 50  0001 C CNN
	1    6450 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 7200 5700 7200
Wire Wire Line
	5700 7200 6000 7200
Wire Wire Line
	6000 7200 6000 7050
Connection ~ 5700 7200
Wire Wire Line
	6000 7050 6450 7050
Connection ~ 6000 7050
Wire Wire Line
	6450 6750 6000 6750
Wire Wire Line
	6000 6750 6000 6600
Wire Wire Line
	6000 6600 5700 6600
Connection ~ 6000 6750
Connection ~ 5700 6600
Wire Wire Line
	5700 6600 5350 6600
$Comp
L Device:R R14
U 1 1 693BBC61
P 6600 4900
F 0 "R14" V 6700 4850 50  0000 L CNN
F 1 "220K" V 6600 4900 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 6530 4900 50  0001 C CNN
F 3 "~" H 6600 4900 50  0001 C CNN
	1    6600 4900
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 693B8B66
P 6050 4100
F 0 "#PWR018" H 6050 3950 50  0001 C CNN
F 1 "+3V3" H 6065 4273 50  0000 C CNN
F 2 "" H 6050 4100 50  0001 C CNN
F 3 "" H 6050 4100 50  0001 C CNN
	1    6050 4100
	-1   0    0    -1  
$EndComp
Text GLabel 8350 4450 2    50   Input ~ 0
ROD_B
Text GLabel 7000 4650 2    50   Input ~ 0
THRESH_B
$Comp
L power:+3V3 #PWR020
U 1 1 6937DCAF
P 5700 4950
F 0 "#PWR020" H 5700 4800 50  0001 C CNN
F 1 "+3V3" H 5715 5123 50  0000 C CNN
F 2 "" H 5700 4950 50  0001 C CNN
F 3 "" H 5700 4950 50  0001 C CNN
	1    5700 4950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 692DCFD4
P 7550 5200
F 0 "#PWR022" H 7550 4950 50  0001 C CNN
F 1 "GND" H 7555 5027 50  0000 C CNN
F 2 "" H 7550 5200 50  0001 C CNN
F 3 "" H 7550 5200 50  0001 C CNN
	1    7550 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 692D0AA3
P 5700 5400
F 0 "R15" H 5500 5400 50  0000 L CNN
F 1 "10k" V 5700 5400 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5630 5400 50  0001 C CNN
F 3 "~" H 5700 5400 50  0001 C CNN
	1    5700 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 692AE30E
P 7900 4650
F 0 "C5" H 7650 4550 50  0000 L CNN
F 1 "33nf" H 7600 4650 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 7938 4500 50  0001 C CNN
F 3 "~" H 7900 4650 50  0001 C CNN
	1    7900 4650
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 692AF36B
P 7550 4650
F 0 "R13" H 7350 4650 50  0000 L CNN
F 1 "100K" V 7550 4650 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7480 4650 50  0001 C CNN
F 3 "~" H 7550 4650 50  0001 C CNN
	1    7550 4650
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 693B66D7
P 7550 4250
F 0 "R9" H 7650 4250 50  0000 L CNN
F 1 "1M" V 7550 4250 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7480 4250 50  0001 C CNN
F 3 "~" H 7550 4250 50  0001 C CNN
	1    7550 4250
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 693D133A
P 8050 4450
F 0 "R11" V 8150 4400 50  0000 L CNN
F 1 "220" V 8050 4450 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7980 4450 50  0001 C CNN
F 3 "~" H 8050 4450 50  0001 C CNN
	1    8050 4450
	0    1    -1   0   
$EndComp
$Comp
L Comparator:LM393 U1
U 1 1 692A9A6C
P 6550 2450
F 0 "U1" H 6550 2450 50  0000 C CNN
F 1 "LM393" H 6700 2650 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6550 2450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 6550 2450 50  0001 C CNN
	1    6550 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7900 4450 7750 4450
Wire Wire Line
	7900 4500 7900 4450
Connection ~ 7900 4450
Wire Wire Line
	6900 4650 6950 4650
Wire Wire Line
	7900 4800 7900 5100
Wire Wire Line
	7550 4800 7550 5100
Wire Wire Line
	7550 4400 7550 4450
Connection ~ 7550 4450
Wire Wire Line
	7550 4450 6900 4450
Wire Wire Line
	7550 4500 7550 4450
Connection ~ 7550 5100
Wire Wire Line
	7550 5100 7550 5200
Wire Wire Line
	7900 5100 7550 5100
Wire Wire Line
	8200 4450 8350 4450
Wire Wire Line
	6950 4650 6950 4900
Connection ~ 6950 4650
Wire Wire Line
	6950 4650 7000 4650
Wire Wire Line
	6200 4550 6250 4550
Wire Wire Line
	6250 4550 6250 4900
Connection ~ 6250 4550
Wire Wire Line
	6250 4550 6300 4550
$Comp
L power:GND #PWR024
U 1 1 69456E7F
P 5700 5550
F 0 "#PWR024" H 5700 5300 50  0001 C CNN
F 1 "GND" H 5705 5377 50  0000 C CNN
F 2 "" H 5700 5550 50  0001 C CNN
F 3 "" H 5700 5550 50  0001 C CNN
	1    5700 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4900 6950 4900
Wire Wire Line
	6450 4900 6250 4900
Wire Wire Line
	5850 5100 6950 5100
Wire Wire Line
	6950 5100 6950 4900
Connection ~ 6950 4900
$Comp
L Comparator:LM393 U1
U 2 1 694692A8
P 6600 4550
F 0 "U1" H 6550 4550 50  0000 C CNN
F 1 "LM393" H 6700 4750 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6600 4550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 6600 4550 50  0001 C CNN
	2    6600 4550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 69482787
P 6000 2200
F 0 "R3" H 5800 2250 50  0000 L CNN
F 1 "10k" V 6000 2200 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5930 2200 50  0001 C CNN
F 3 "~" H 6000 2200 50  0001 C CNN
	1    6000 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 6948278D
P 5650 3000
F 0 "RV1" H 5550 3000 50  0000 R CNN
F 1 "200K" V 5650 3100 50  0000 R CNN
F 2 "0_my_footprints:myTrimPot" H 5650 3000 50  0001 C CNN
F 3 "~" H 5650 3000 50  0001 C CNN
	1    5650 3000
	1    0    0    -1  
$EndComp
Text GLabel 5400 2450 0    50   Input ~ 0
SENSOR_A
$Comp
L Device:R R7
U 1 1 69482794
P 6550 2800
F 0 "R7" V 6650 2750 50  0000 L CNN
F 1 "220K" V 6550 2800 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 6480 2800 50  0001 C CNN
F 3 "~" H 6550 2800 50  0001 C CNN
	1    6550 2800
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR06
U 1 1 6948279A
P 6000 2000
F 0 "#PWR06" H 6000 1850 50  0001 C CNN
F 1 "+3V3" H 6015 2173 50  0000 C CNN
F 2 "" H 6000 2000 50  0001 C CNN
F 3 "" H 6000 2000 50  0001 C CNN
	1    6000 2000
	-1   0    0    -1  
$EndComp
Text GLabel 8300 2350 2    50   Input ~ 0
ROD_A
Text GLabel 6950 2550 2    50   Input ~ 0
THRESH_A
$Comp
L Device:R R5
U 1 1 694827A2
P 5700 2450
F 0 "R5" V 5800 2400 50  0000 L CNN
F 1 "100" V 5700 2450 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5630 2450 50  0001 C CNN
F 3 "~" H 5700 2450 50  0001 C CNN
	1    5700 2450
	0    1    -1   0   
$EndComp
$Comp
L power:+3V3 #PWR011
U 1 1 694827A8
P 5650 2850
F 0 "#PWR011" H 5650 2700 50  0001 C CNN
F 1 "+3V3" H 5665 3023 50  0000 C CNN
F 2 "" H 5650 2850 50  0001 C CNN
F 3 "" H 5650 2850 50  0001 C CNN
	1    5650 2850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 694827AE
P 7500 3100
F 0 "#PWR014" H 7500 2850 50  0001 C CNN
F 1 "GND" H 7505 2927 50  0000 C CNN
F 2 "" H 7500 3100 50  0001 C CNN
F 3 "" H 7500 3100 50  0001 C CNN
	1    7500 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 694827B4
P 5650 3300
F 0 "R8" H 5450 3300 50  0000 L CNN
F 1 "10k" V 5650 3300 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5580 3300 50  0001 C CNN
F 3 "~" H 5650 3300 50  0001 C CNN
	1    5650 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 694827BA
P 7850 2550
F 0 "C2" H 7600 2450 50  0000 L CNN
F 1 "33nf" H 7550 2550 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 7888 2400 50  0001 C CNN
F 3 "~" H 7850 2550 50  0001 C CNN
	1    7850 2550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 694827C0
P 7500 2550
F 0 "R6" H 7300 2550 50  0000 L CNN
F 1 "100K" V 7500 2550 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7430 2550 50  0001 C CNN
F 3 "~" H 7500 2550 50  0001 C CNN
	1    7500 2550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 694827C6
P 7500 2150
F 0 "R2" H 7600 2150 50  0000 L CNN
F 1 "1M" V 7500 2150 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7430 2150 50  0001 C CNN
F 3 "~" H 7500 2150 50  0001 C CNN
	1    7500 2150
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 694827CC
P 8000 2350
F 0 "R4" V 8100 2300 50  0000 L CNN
F 1 "220" V 8000 2350 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 7930 2350 50  0001 C CNN
F 3 "~" H 8000 2350 50  0001 C CNN
	1    8000 2350
	0    1    -1   0   
$EndComp
Wire Wire Line
	7850 2350 7700 2350
Wire Wire Line
	7850 2400 7850 2350
Connection ~ 7850 2350
Wire Wire Line
	6850 2550 6900 2550
Wire Wire Line
	7850 2700 7850 3000
Wire Wire Line
	7500 2700 7500 3000
Wire Wire Line
	7500 2300 7500 2350
Connection ~ 7500 2350
Wire Wire Line
	7500 2350 6850 2350
Wire Wire Line
	7500 2400 7500 2350
Connection ~ 7500 3000
Wire Wire Line
	7500 3000 7500 3100
Wire Wire Line
	7850 3000 7500 3000
Wire Wire Line
	8150 2350 8300 2350
Wire Wire Line
	6900 2550 6900 2800
Connection ~ 6900 2550
Wire Wire Line
	6900 2550 6950 2550
Wire Wire Line
	6200 2450 6200 2800
Wire Wire Line
	6200 2450 6250 2450
$Comp
L power:GND #PWR015
U 1 1 694827EE
P 5650 3450
F 0 "#PWR015" H 5650 3200 50  0001 C CNN
F 1 "GND" H 5655 3277 50  0000 C CNN
F 2 "" H 5650 3450 50  0001 C CNN
F 3 "" H 5650 3450 50  0001 C CNN
	1    5650 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2800 6900 2800
Wire Wire Line
	6400 2800 6200 2800
Wire Wire Line
	5800 3000 6900 3000
Wire Wire Line
	6900 3000 6900 2800
Connection ~ 6900 2800
Wire Wire Line
	6650 1300 6850 1300
Wire Wire Line
	6350 1300 6150 1300
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 694D6097
P 9950 1350
F 0 "J2" H 10250 1450 50  0000 C CNN
F 1 "SENSOR_ASSY" H 10300 1350 50  0000 C CNN
F 2 "0_my_footprints:myJSTx03" H 9950 1350 50  0001 C CNN
F 3 "~" H 9950 1350 50  0001 C CNN
	1    9950 1350
	1    0    0    -1  
$EndComp
Text GLabel 9750 1350 0    50   Input ~ 0
DRIVE_ROD
Text GLabel 9750 1250 0    50   Input ~ 0
ROD_A
Text GLabel 9750 1450 0    50   Input ~ 0
ROD_B
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 69591300
P 1550 5200
F 0 "J7" H 1900 5100 50  0000 C CNN
F 1 "WS2812_B" H 1900 5200 50  0000 C CNN
F 2 "0_my_footprints:myJSTx03" H 1550 5200 50  0001 C CNN
F 3 "~" H 1550 5200 50  0001 C CNN
	1    1550 5200
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 695A36E8
P 9950 1950
F 0 "J5" H 10200 1850 50  0000 C CNN
F 1 "TEST_A" H 10200 1950 50  0000 C CNN
F 2 "0_my_footprints:myPinSocket_1x02" H 9950 1950 50  0001 C CNN
F 3 "~" H 9950 1950 50  0001 C CNN
	1    9950 1950
	1    0    0    1   
$EndComp
Wire Wire Line
	7700 2350 7700 2100
Wire Wire Line
	7700 2100 7850 2100
Connection ~ 7700 2350
Wire Wire Line
	7700 2350 7500 2350
Wire Wire Line
	7750 4450 7750 4200
Wire Wire Line
	7750 4200 7950 4200
Connection ~ 7750 4450
Wire Wire Line
	7750 4450 7550 4450
Text GLabel 7850 2100 2    50   Input ~ 0
INPUT_A
Text GLabel 9750 1850 0    50   Input ~ 0
INPUT_A
Text GLabel 9750 1950 0    50   Input ~ 0
THRESH_A
Text GLabel 7950 4200 2    50   Input ~ 0
INPUT_B
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 695B4928
P 9950 2450
F 0 "J6" H 10200 2350 50  0000 C CNN
F 1 "TEST_B" H 10200 2450 50  0000 C CNN
F 2 "0_my_footprints:myPinSocket_1x02" H 9950 2450 50  0001 C CNN
F 3 "~" H 9950 2450 50  0001 C CNN
	1    9950 2450
	1    0    0    1   
$EndComp
Text GLabel 9750 2350 0    50   Input ~ 0
INPUT_B
Text GLabel 9750 2450 0    50   Input ~ 0
THRESH_B
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 6931ED47
P 1550 6400
F 0 "J8" H 1550 6050 50  0000 C CNN
F 1 "PUMP" H 1550 6150 50  0000 C CNN
F 2 "0_my_footprints:myPheonix2x3.81_right" H 1550 6400 50  0001 C CNN
F 3 "~" H 1550 6400 50  0001 C CNN
	1    1550 6400
	-1   0    0    1   
$EndComp
Text GLabel 1750 6300 2    50   Input ~ 0
PUMP+
Text GLabel 1750 6400 2    50   Input ~ 0
PUMP-
Text GLabel 2200 5300 2    50   Input ~ 0
WS2812B
$Comp
L power:GND #PWR023
U 1 1 695C7DB1
P 1750 5200
F 0 "#PWR023" H 1750 4950 50  0001 C CNN
F 1 "GND" V 1750 5000 50  0000 C CNN
F 2 "" H 1750 5200 50  0001 C CNN
F 3 "" H 1750 5200 50  0001 C CNN
	1    1750 5200
	0    -1   1    0   
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
Text GLabel 2700 3850 3    50   Input ~ 0
PUMP
Text GLabel 2400 3850 3    50   Input ~ 0
S_DRIVE
Text GLabel 2900 2850 1    50   Input ~ 0
SENSOR_A
Text GLabel 2700 2850 1    50   Input ~ 0
SENSOR_B
Text GLabel 2300 3850 3    50   Input ~ 0
WS2812B
Text GLabel 3200 6000 0    50   Input ~ 0
PUMP-
$Comp
L power:+12V #PWR025
U 1 1 61C07060
P 3750 5600
F 0 "#PWR025" H 3750 5450 50  0001 C CNN
F 1 "+12V" H 3765 5773 50  0000 C CNN
F 2 "" H 3750 5600 50  0001 C CNN
F 3 "" H 3750 5600 50  0001 C CNN
	1    3750 5600
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R17
U 1 1 61C579E3
P 4050 6350
F 0 "R17" V 3950 6300 50  0001 L CNN
F 1 "10K" V 4050 6350 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3980 6350 50  0001 C CNN
F 3 "~" H 4050 6350 50  0001 C CNN
	1    4050 6350
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 61C605D5
P 3750 6600
F 0 "#PWR026" H 3750 6350 50  0001 C CNN
F 1 "GND" H 3755 6427 50  0000 C CNN
F 2 "" H 3750 6600 50  0001 C CNN
F 3 "" H 3750 6600 50  0001 C CNN
	1    3750 6600
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 61C62C8B
P 4200 6200
F 0 "R16" V 4100 6150 50  0001 L CNN
F 1 "220" V 4200 6200 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4130 6200 50  0001 C CNN
F 3 "~" H 4200 6200 50  0001 C CNN
	1    4200 6200
	0    1    -1   0   
$EndComp
$Comp
L Diode:1N4001 D2
U 1 1 61BE277E
P 3750 5850
F 0 "D2" V 3704 5930 50  0001 L CNN
F 1 "1N5818" V 3750 5950 50  0000 L CNN
F 2 "0_my_footprints:myDiodeSchotsky" H 3750 5675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3750 5850 50  0001 C CNN
	1    3750 5850
	0    -1   1    0   
$EndComp
Wire Wire Line
	4050 6500 3750 6500
Wire Wire Line
	3750 6400 3750 6500
Connection ~ 4050 6200
$Comp
L Transistor_FET:IRLZ44N Q1
U 1 1 61C50415
P 3850 6200
F 0 "Q1" H 4054 6246 50  0001 L CNN
F 1 "IRF520N" H 4050 6200 50  0000 L CNN
F 2 "0_my_footprints:myThreeLegged" H 4100 6125 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irlz44n.pdf" H 3850 6200 50  0001 L CNN
	1    3850 6200
	-1   0    0    -1  
$EndComp
Text GLabel 3200 5700 0    50   Input ~ 0
PUMP+
Wire Wire Line
	3200 6000 3750 6000
Connection ~ 3750 6000
Wire Wire Line
	3200 5700 3750 5700
Wire Wire Line
	3750 5600 3750 5700
Connection ~ 3750 5700
Wire Wire Line
	3750 6500 3750 6600
Connection ~ 3750 6500
Wire Wire Line
	5400 2450 5550 2450
Wire Wire Line
	5850 2450 6000 2450
Connection ~ 6200 2450
Wire Wire Line
	6000 2050 6000 2000
Wire Wire Line
	6000 2350 6000 2450
Connection ~ 6000 2450
Wire Wire Line
	6000 2450 6200 2450
$Comp
L Device:R R10
U 1 1 69674543
P 6050 4300
F 0 "R10" H 5750 4350 50  0000 L CNN
F 1 "10k" V 6050 4300 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5980 4300 50  0001 C CNN
F 3 "~" H 6050 4300 50  0001 C CNN
	1    6050 4300
	1    0    0    -1  
$EndComp
Text GLabel 5450 4550 0    50   Input ~ 0
SENSOR_B
$Comp
L Device:R R12
U 1 1 6967454A
P 5750 4550
F 0 "R12" V 5850 4500 50  0000 L CNN
F 1 "100" V 5750 4550 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5680 4550 50  0001 C CNN
F 3 "~" H 5750 4550 50  0001 C CNN
	1    5750 4550
	0    1    -1   0   
$EndComp
Wire Wire Line
	5450 4550 5600 4550
Wire Wire Line
	5900 4550 6050 4550
Wire Wire Line
	6050 4150 6050 4100
Wire Wire Line
	6050 4450 6050 4550
Connection ~ 6050 4550
Wire Wire Line
	6050 4550 6250 4550
$Comp
L power:+3V3 #PWR07
U 1 1 6968D5E2
P 7500 2000
F 0 "#PWR07" H 7500 1850 50  0001 C CNN
F 1 "+3V3" H 7515 2173 50  0000 C CNN
F 2 "" H 7500 2000 50  0001 C CNN
F 3 "" H 7500 2000 50  0001 C CNN
	1    7500 2000
	-1   0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR019
U 1 1 69699D92
P 7550 4100
F 0 "#PWR019" H 7550 3950 50  0001 C CNN
F 1 "+3V3" H 7565 4273 50  0000 C CNN
F 2 "" H 7550 4100 50  0001 C CNN
F 3 "" H 7550 4100 50  0001 C CNN
	1    7550 4100
	-1   0    0    -1  
$EndComp
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
L Device:R_POT RV2
U 1 1 692FA5C9
P 5700 5100
F 0 "RV2" H 5600 5100 50  0000 R CNN
F 1 "200K" V 5700 5200 50  0000 R CNN
F 2 "0_my_footprints:myTrimPot" H 5700 5100 50  0001 C CNN
F 3 "~" H 5700 5100 50  0001 C CNN
	1    5700 5100
	1    0    0    1   
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 6943AF93
P 1750 5100
F 0 "#PWR0101" H 1750 4950 50  0001 C CNN
F 1 "+5V" V 1750 5300 50  0000 C CNN
F 2 "" H 1750 5100 50  0001 C CNN
F 3 "" H 1750 5100 50  0001 C CNN
	1    1750 5100
	0    1    1    0   
$EndComp
$Comp
L Device:R R18
U 1 1 69443C96
P 1900 5300
F 0 "R18" V 1800 5250 50  0000 L CNN
F 1 "330" V 1900 5300 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 1830 5300 50  0001 C CNN
F 3 "~" H 1900 5300 50  0001 C CNN
	1    1900 5300
	0    1    -1   0   
$EndComp
Wire Wire Line
	2200 5300 2050 5300
$EndSCHEMATC
