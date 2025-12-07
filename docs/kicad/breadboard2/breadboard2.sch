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
Text GLabel 3550 5800 2    50   Input ~ 0
PUMP
$Comp
L Device:R R4
U 1 1 692C8E57
P 2750 4550
F 0 "R4" V 2850 4500 50  0000 L CNN
F 1 "1K" V 2750 4500 50  0000 L CNN
F 2 "0_my_footprints:myResistor" V 2680 4550 50  0001 C CNN
F 3 "~" H 2750 4550 50  0001 C CNN
	1    2750 4550
	0    1    -1   0   
$EndComp
Text GLabel 3100 4550 2    50   Input ~ 0
DRIVE_ROD
Text GLabel 2400 4550 0    50   Input ~ 0
S_DRIVE
Text GLabel 4600 3250 0    50   Input ~ 0
SENSOR_LOW
Text GLabel 5550 3250 2    50   Input ~ 0
ROD_LOW
$Comp
L power:GND #PWR06
U 1 1 694827AE
P 4750 4000
F 0 "#PWR06" H 4750 3750 50  0001 C CNN
F 1 "GND" H 4755 3827 50  0000 C CNN
F 2 "" H 4750 4000 50  0001 C CNN
F 3 "" H 4750 4000 50  0001 C CNN
	1    4750 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 694827BA
P 5100 3450
F 0 "C1" H 4850 3350 50  0000 L CNN
F 1 "2.2uf" H 4800 3450 50  0000 L CNN
F 2 "0_my_footprints:CP_my100uf" H 5138 3300 50  0001 C CNN
F 3 "~" H 5100 3450 50  0001 C CNN
	1    5100 3450
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 694827C0
P 4750 3450
F 0 "R3" H 4550 3450 50  0000 L CNN
F 1 "100K" V 4750 3450 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 4680 3450 50  0001 C CNN
F 3 "~" H 4750 3450 50  0001 C CNN
	1    4750 3450
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 694827CC
P 5250 3250
F 0 "R2" V 5350 3200 50  0000 L CNN
F 1 "1K" V 5250 3250 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5180 3250 50  0001 C CNN
F 3 "~" H 5250 3250 50  0001 C CNN
	1    5250 3250
	0    1    -1   0   
$EndComp
Wire Wire Line
	5100 3300 5100 3250
Connection ~ 5100 3250
Wire Wire Line
	5100 3600 5100 3900
Wire Wire Line
	4750 3600 4750 3900
Wire Wire Line
	4750 3200 4750 3250
Connection ~ 4750 3250
Wire Wire Line
	4750 3300 4750 3250
Connection ~ 4750 3900
Wire Wire Line
	4750 3900 4750 4000
Wire Wire Line
	5100 3900 4750 3900
Wire Wire Line
	5400 3250 5550 3250
Wire Wire Line
	2900 4550 3100 4550
Wire Wire Line
	2600 4550 2400 4550
$Comp
L power:GND #PWR05
U 1 1 695E5C40
P 2200 3850
F 0 "#PWR05" H 2200 3600 50  0001 C CNN
F 1 "GND" V 2200 3650 50  0000 C CNN
F 2 "" H 2200 3850 50  0001 C CNN
F 3 "" H 2200 3850 50  0001 C CNN
	1    2200 3850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 695EAB91
P 1750 2400
F 0 "#PWR02" H 1750 2150 50  0001 C CNN
F 1 "GND" V 1750 2200 50  0000 C CNN
F 2 "" H 1750 2400 50  0001 C CNN
F 3 "" H 1750 2400 50  0001 C CNN
	1    1750 2400
	1    0    0    1   
$EndComp
$Comp
L power:+3V3 #PWR04
U 1 1 695EF873
P 2100 3850
F 0 "#PWR04" H 2100 3700 50  0001 C CNN
F 1 "+3V3" V 2100 4050 50  0000 C CNN
F 2 "" H 2100 3850 50  0001 C CNN
F 3 "" H 2100 3850 50  0001 C CNN
	1    2100 3850
	1    0    0    1   
$EndComp
Text GLabel 3000 3850 3    50   Input ~ 0
PUMP
Text GLabel 2700 3850 3    50   Input ~ 0
S_DRIVE
Text GLabel 3100 2850 1    50   Input ~ 0
SENSOR_LOW
Text GLabel 2500 2750 1    50   Input ~ 0
SENSOR_HIGH
Text GLabel 2600 3850 3    50   Input ~ 0
WS2812B
Text GLabel 2400 5600 0    50   Input ~ 0
PUMP-
$Comp
L power:+12V #PWR08
U 1 1 61C07060
P 2950 5200
F 0 "#PWR08" H 2950 5050 50  0001 C CNN
F 1 "+12V" H 2965 5373 50  0000 C CNN
F 2 "" H 2950 5200 50  0001 C CNN
F 3 "" H 2950 5200 50  0001 C CNN
	1    2950 5200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 61C579E3
P 3250 5950
F 0 "R6" V 3150 5900 50  0001 L CNN
F 1 "10K" V 3250 5950 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3180 5950 50  0001 C CNN
F 3 "~" H 3250 5950 50  0001 C CNN
	1    3250 5950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 61C605D5
P 2950 6200
F 0 "#PWR011" H 2950 5950 50  0001 C CNN
F 1 "GND" H 2955 6027 50  0000 C CNN
F 2 "" H 2950 6200 50  0001 C CNN
F 3 "" H 2950 6200 50  0001 C CNN
	1    2950 6200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 61C62C8B
P 3400 5800
F 0 "R5" V 3300 5750 50  0001 L CNN
F 1 "220" V 3400 5800 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3330 5800 50  0001 C CNN
F 3 "~" H 3400 5800 50  0001 C CNN
	1    3400 5800
	0    1    -1   0   
$EndComp
$Comp
L Diode:1N4001 D1
U 1 1 61BE277E
P 2950 5450
F 0 "D1" V 2904 5530 50  0001 L CNN
F 1 "1N5818" V 2950 5550 50  0000 L CNN
F 2 "0_my_footprints:myDiodeSchotsky" H 2950 5275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 2950 5450 50  0001 C CNN
	1    2950 5450
	0    -1   1    0   
$EndComp
Wire Wire Line
	3250 6100 2950 6100
Wire Wire Line
	2950 6000 2950 6100
Connection ~ 3250 5800
$Comp
L Transistor_FET:IRLZ44N Q1
U 1 1 61C50415
P 3050 5800
F 0 "Q1" H 3254 5846 50  0001 L CNN
F 1 "IRF520N" H 3250 5800 50  0000 L CNN
F 2 "0_my_footprints:myThreeLegged" H 3300 5725 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irlz44n.pdf" H 3050 5800 50  0001 L CNN
	1    3050 5800
	-1   0    0    -1  
$EndComp
Text GLabel 2400 5300 0    50   Input ~ 0
PUMP+
Wire Wire Line
	2400 5600 2950 5600
Connection ~ 2950 5600
Wire Wire Line
	2400 5300 2950 5300
Wire Wire Line
	2950 5200 2950 5300
Connection ~ 2950 5300
Wire Wire Line
	2950 6100 2950 6200
Connection ~ 2950 6100
Wire Wire Line
	4600 3250 4750 3250
Wire Wire Line
	4750 3250 5100 3250
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 6939F4D2
P 4900 4800
F 0 "J1" H 4980 4842 50  0001 L CNN
F 1 "DRIVE_ROD" H 4980 4796 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 4800 50  0001 C CNN
F 3 "~" H 4900 4800 50  0001 C CNN
	1    4900 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 693A2866
P 4900 4900
F 0 "J2" H 4980 4942 50  0001 L CNN
F 1 "ROD_LOW" H 4980 4896 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 4900 50  0001 C CNN
F 3 "~" H 4900 4900 50  0001 C CNN
	1    4900 4900
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J4
U 1 1 693A77A2
P 4900 5200
F 0 "J4" H 4980 5242 50  0001 L CNN
F 1 "PUMP+" H 4980 5196 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5200 50  0001 C CNN
F 3 "~" H 4900 5200 50  0001 C CNN
	1    4900 5200
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J5
U 1 1 693A77A8
P 4900 5300
F 0 "J5" H 4980 5342 50  0001 L CNN
F 1 "PUMP-" H 4980 5296 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5300 50  0001 C CNN
F 3 "~" H 4900 5300 50  0001 C CNN
	1    4900 5300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J3
U 1 1 693A86F9
P 4900 5100
F 0 "J3" H 4980 5142 50  0001 L CNN
F 1 "12V" H 4980 5096 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5100 50  0001 C CNN
F 3 "~" H 4900 5100 50  0001 C CNN
	1    4900 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J7
U 1 1 693AA555
P 4900 5650
F 0 "J7" H 4980 5692 50  0001 L CNN
F 1 "WS28128B" H 4980 5646 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5650 50  0001 C CNN
F 3 "~" H 4900 5650 50  0001 C CNN
	1    4900 5650
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J8
U 1 1 693AA55B
P 4900 5750
F 0 "J8" H 4980 5792 50  0001 L CNN
F 1 "5V" H 4980 5746 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5750 50  0001 C CNN
F 3 "~" H 4900 5750 50  0001 C CNN
	1    4900 5750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J6
U 1 1 693AA561
P 4900 5550
F 0 "J6" H 4980 5592 50  0001 L CNN
F 1 "GND" H 4980 5546 50  0000 L CNN
F 2 "0_my_footprints:myPinHeader_1x01" H 4900 5550 50  0001 C CNN
F 3 "~" H 4900 5550 50  0001 C CNN
	1    4900 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 693AAF7E
P 1650 2400
F 0 "#PWR01" H 1650 2250 50  0001 C CNN
F 1 "+5V" V 1650 2600 50  0000 C CNN
F 2 "" H 1650 2400 50  0001 C CNN
F 3 "" H 1650 2400 50  0001 C CNN
	1    1650 2400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 693AFEB1
P 4700 5750
F 0 "#PWR010" H 4700 5600 50  0001 C CNN
F 1 "+5V" V 4700 5950 50  0000 C CNN
F 2 "" H 4700 5750 50  0001 C CNN
F 3 "" H 4700 5750 50  0001 C CNN
	1    4700 5750
	0    -1   -1   0   
$EndComp
Text GLabel 4700 5650 0    50   Input ~ 0
WS2812B
Text GLabel 4700 4800 0    50   Input ~ 0
DRIVE_ROD
Text GLabel 4700 4900 0    50   Input ~ 0
ROD_LOW
$Comp
L power:+12V #PWR07
U 1 1 693B98D3
P 4700 5100
F 0 "#PWR07" H 4700 4950 50  0001 C CNN
F 1 "+12V" V 4700 5350 50  0000 C CNN
F 2 "" H 4700 5100 50  0001 C CNN
F 3 "" H 4700 5100 50  0001 C CNN
	1    4700 5100
	0    -1   1    0   
$EndComp
Text GLabel 4700 5300 0    50   Input ~ 0
PUMP-
Text GLabel 4700 5200 0    50   Input ~ 0
PUMP+
$Comp
L power:GND #PWR09
U 1 1 693BE1B4
P 4700 5550
F 0 "#PWR09" H 4700 5300 50  0001 C CNN
F 1 "GND" V 4700 5350 50  0000 C CNN
F 2 "" H 4700 5550 50  0001 C CNN
F 3 "" H 4700 5550 50  0001 C CNN
	1    4700 5550
	0    1    -1   0   
$EndComp
$Comp
L Driver_FET:IR2104 U?
U 1 1 693EBEA1
P 1300 5650
F 0 "U?" H 1300 6331 50  0000 C CNN
F 1 "IR2104" H 1300 6240 50  0000 C CNN
F 2 "" H 1300 5650 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/ir2104.pdf?fileId=5546d462533600a4015355c7c1c31671" H 1300 5650 50  0001 C CNN
	1    1300 5650
	1    0    0    -1  
$EndComp
$Comp
L 0_my_symbols:ESP32_DEV U?
U 1 1 693F0C5E
P 1950 3400
F 0 "U?" H 3078 3496 50  0000 L CNN
F 1 "ESP32_DEV" H 3078 3405 50  0000 L CNN
F 2 "" H 1600 3500 50  0001 C CNN
F 3 "" H 1600 3500 50  0001 C CNN
	1    1950 3400
	1    0    0    -1  
$EndComp
$EndSCHEMATC
