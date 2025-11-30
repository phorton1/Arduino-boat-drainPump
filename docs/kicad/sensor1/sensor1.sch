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
L Comparator:LM393 U1
U 1 1 692A9A6C
P 5700 4850
F 0 "U1" H 5700 4850 50  0000 C CNN
F 1 "LM393" H 5900 5100 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 5700 4850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 5700 4850 50  0001 C CNN
	1    5700 4850
	1    0    0    1   
$EndComp
Text GLabel 1850 4700 0    50   Input ~ 0
RodB
$Comp
L Device:C C1
U 1 1 692AE30E
P 2450 4950
F 0 "C1" H 2565 4996 50  0000 L CNN
F 1 "33nf" H 2565 4905 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 2488 4800 50  0001 C CNN
F 3 "~" H 2450 4950 50  0001 C CNN
	1    2450 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 692AEF42
P 2700 5300
F 0 "#PWR0101" H 2700 5050 50  0001 C CNN
F 1 "GND" H 2705 5127 50  0000 C CNN
F 2 "" H 2700 5300 50  0001 C CNN
F 3 "" H 2700 5300 50  0001 C CNN
	1    2700 5300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0102
U 1 1 692B4F14
P 5700 2300
F 0 "#PWR0102" H 5700 2150 50  0001 C CNN
F 1 "+3V3" H 5715 2473 50  0000 C CNN
F 2 "" H 5700 2300 50  0001 C CNN
F 3 "" H 5700 2300 50  0001 C CNN
	1    5700 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 692C4DC0
P 5700 2650
F 0 "R1" H 5550 2700 50  0000 L CNN
F 1 "10k" V 5700 2650 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5630 2650 50  0001 C CNN
F 3 "~" H 5700 2650 50  0001 C CNN
	1    5700 2650
	1    0    0    -1  
$EndComp
Text GLabel 5900 2950 2    50   Input ~ 0
ESP32_DIGITAL_INPUT
$Comp
L Device:R R6
U 1 1 692C8E57
P 5350 3600
F 0 "R6" V 5450 3550 50  0000 L CNN
F 1 "1K" V 5350 3550 50  0000 L CNN
F 2 "0_my_footprints:myResistor" V 5280 3600 50  0001 C CNN
F 3 "~" H 5350 3600 50  0001 C CNN
	1    5350 3600
	0    -1   -1   0   
$EndComp
Text GLabel 5000 3600 0    50   Input ~ 0
RodA
Text GLabel 5800 3600 2    50   Input ~ 0
ESP32_GPIO_AC_DRIVE
Wire Wire Line
	5200 3600 5000 3600
$Comp
L Comparator:LM393 U1
U 3 1 692CE3A2
P 1700 2600
F 0 "U1" H 1658 2646 50  0000 L CNN
F 1 "LM393" H 1658 2555 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 1700 2600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm393.pdf" H 1700 2600 50  0001 C CNN
	3    1700 2600
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR0103
U 1 1 692DB0AB
P 1950 2300
F 0 "#PWR0103" H 1950 2150 50  0001 C CNN
F 1 "+3V3" H 1965 2473 50  0000 C CNN
F 2 "" H 1950 2300 50  0001 C CNN
F 3 "" H 1950 2300 50  0001 C CNN
	1    1950 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 692DBCA7
P 1950 2900
F 0 "#PWR0104" H 1950 2650 50  0001 C CNN
F 1 "GND" H 1955 2727 50  0000 C CNN
F 2 "" H 1950 2900 50  0001 C CNN
F 3 "" H 1950 2900 50  0001 C CNN
	1    1950 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 692F0D5E
P 2250 2600
F 0 "C2" H 2365 2646 50  0000 L CNN
F 1 "0.1uf" H 2365 2555 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 2288 2450 50  0001 C CNN
F 3 "~" H 2250 2600 50  0001 C CNN
	1    2250 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 692F13CC
P 2700 2600
F 0 "C3" H 2815 2646 50  0000 L CNN
F 1 "1uf" H 2815 2555 50  0000 L CNN
F 2 "0_my_footprints:myCapCeramicSmall" H 2738 2450 50  0001 C CNN
F 3 "~" H 2700 2600 50  0001 C CNN
	1    2700 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2900 1950 2900
Wire Wire Line
	1950 2900 2250 2900
Wire Wire Line
	2250 2900 2250 2750
Connection ~ 1950 2900
Wire Wire Line
	2250 2750 2700 2750
Connection ~ 2250 2750
Wire Wire Line
	2700 2450 2250 2450
Wire Wire Line
	2250 2450 2250 2300
Wire Wire Line
	2250 2300 1950 2300
Connection ~ 2250 2450
Connection ~ 1950 2300
Wire Wire Line
	1950 2300 1600 2300
$Comp
L Device:R R7
U 1 1 692D0AA3
P 3550 2650
F 0 "R7" H 3350 2650 50  0000 L CNN
F 1 "10k" V 3550 2650 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 3480 2650 50  0001 C CNN
F 3 "~" H 3550 2650 50  0001 C CNN
	1    3550 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 692DCFD4
P 3550 3000
F 0 "#PWR0105" H 3550 2750 50  0001 C CNN
F 1 "GND" H 3555 2827 50  0000 C CNN
F 2 "" H 3550 3000 50  0001 C CNN
F 3 "" H 3550 3000 50  0001 C CNN
	1    3550 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3600 5800 3600
$Comp
L Device:R R?
U 1 1 692E8EEF
P 5350 2950
F 0 "R?" V 5450 2900 50  0000 L CNN
F 1 "100" V 5350 2950 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5280 2950 50  0001 C CNN
F 3 "~" H 5350 2950 50  0001 C CNN
	1    5350 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 2800 5700 2950
$Comp
L Device:R_POT RV1
U 1 1 692FA5C9
P 3550 2200
F 0 "RV1" H 3481 2246 50  0000 R CNN
F 1 "200K" V 3550 2300 50  0000 R CNN
F 2 "0_my_footprints:myTrimPot" H 3550 2200 50  0001 C CNN
F 3 "~" H 3550 2200 50  0001 C CNN
	1    3550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 2350 3550 2500
$Comp
L power:+3V3 #PWR?
U 1 1 693297AB
P 3550 1950
F 0 "#PWR?" H 3550 1800 50  0001 C CNN
F 1 "+3V3" H 3565 2123 50  0000 C CNN
F 2 "" H 3550 1950 50  0001 C CNN
F 3 "" H 3550 1950 50  0001 C CNN
	1    3550 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1950 3550 2050
Text GLabel 4100 2200 2    50   Input ~ 0
THRESH
Text GLabel 5100 4750 0    50   Input ~ 0
THRESH
Text GLabel 6200 4850 2    50   Input ~ 0
SIGNAL
Wire Wire Line
	5500 2950 5700 2950
Connection ~ 5700 2950
Wire Wire Line
	5700 2950 5900 2950
Text GLabel 4900 2950 0    50   Input ~ 0
SIGNAL
Wire Wire Line
	4900 2950 5200 2950
Wire Wire Line
	5700 2300 5700 2500
Text GLabel 5100 4950 0    50   Input ~ 0
INPUT
Wire Wire Line
	2450 5100 2450 5200
Wire Wire Line
	2450 5200 2700 5200
Wire Wire Line
	2950 5200 2950 5100
Wire Wire Line
	2450 4800 2450 4700
Wire Wire Line
	2450 4700 2950 4700
Wire Wire Line
	2950 4700 2950 4800
Wire Wire Line
	2700 5300 2700 5200
Connection ~ 2700 5200
Wire Wire Line
	2700 5200 2950 5200
Text GLabel 3200 4700 2    50   Input ~ 0
INPUT
Wire Wire Line
	2950 4700 3200 4700
Connection ~ 2950 4700
Wire Wire Line
	3700 2200 4100 2200
Wire Wire Line
	3550 2800 3550 3000
$Comp
L Device:R R4
U 1 1 692AF36B
P 2950 4950
F 0 "R4" H 3050 4950 50  0000 L CNN
F 1 "100K" V 2950 4950 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 2880 4950 50  0001 C CNN
F 3 "~" H 2950 4950 50  0001 C CNN
	1    2950 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 693B66D7
P 2950 4450
F 0 "R?" H 3050 4450 50  0000 L CNN
F 1 "1M" V 2950 4450 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 2880 4450 50  0001 C CNN
F 3 "~" H 2950 4450 50  0001 C CNN
	1    2950 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 4600 2950 4700
$Comp
L power:+3V3 #PWR?
U 1 1 693B8B66
P 2950 4300
F 0 "#PWR?" H 2950 4150 50  0001 C CNN
F 1 "+3V3" H 2965 4473 50  0000 C CNN
F 2 "" H 2950 4300 50  0001 C CNN
F 3 "" H 2950 4300 50  0001 C CNN
	1    2950 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 693BBC61
P 5700 4450
F 0 "R?" V 5800 4400 50  0000 L CNN
F 1 "220K" V 5700 4450 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 5630 4450 50  0001 C CNN
F 3 "~" H 5700 4450 50  0001 C CNN
	1    5700 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6000 4850 6050 4850
Wire Wire Line
	5100 4750 5300 4750
Wire Wire Line
	5100 4950 5400 4950
Wire Wire Line
	5300 4750 5300 4450
Wire Wire Line
	5300 4450 5550 4450
Connection ~ 5300 4750
Wire Wire Line
	5300 4750 5400 4750
Wire Wire Line
	5850 4450 6050 4450
Wire Wire Line
	6050 4450 6050 4850
Connection ~ 6050 4850
Wire Wire Line
	6050 4850 6200 4850
$Comp
L Device:R R?
U 1 1 693D133A
P 2150 4700
F 0 "R?" V 2250 4650 50  0000 L CNN
F 1 "220" V 2150 4700 50  0000 C CNN
F 2 "0_my_footprints:myResistor" V 2080 4700 50  0001 C CNN
F 3 "~" H 2150 4700 50  0001 C CNN
	1    2150 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2450 4700 2300 4700
Connection ~ 2450 4700
Wire Wire Line
	2000 4700 1850 4700
Text Notes 2750 1600 0    50   ~ 0
Note: a 68K/75K fixed resistor here gives a threshold\nvoltage of approx 0.42/0.39V which matches the measured\nworking threshold with tap water.
Text Notes 1300 3950 0    50   ~ 0
Note: I measured 0.03V dry and 0.96V wet with MM at INPUT\nwith 2Khz square wave through 1K resistor to RodA from ESP32
Text Notes 4900 5600 0    50   ~ 0
Note: Hysterisis resistor or 220K provides about \n60-120mv band to keep decisions clean
Text Notes 1500 5950 0    50   ~ 0
Note: 220 ohm lead in resistor from input near to connector\ndamps high frequency edge bleed from drive line and works\nwith 33nf to create a gentle RC
$EndSCHEMATC
