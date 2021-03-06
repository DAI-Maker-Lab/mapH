EESchema Schematic File Version 4
LIBS:mapH-cache
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
L fona_808:FONA_808 U1
U 1 1 5B0286E9
P 3750 2550
F 0 "U1" H 3750 2500 60  0000 C CNN
F 1 "FONA_808" H 3750 2600 60  0000 C CNN
F 2 "DAI_Maker_Lab_footprints:FONA_808" H 3750 2550 60  0001 C CNN
F 3 "" H 3750 2550 60  0000 C CNN
	1    3750 2550
	0    1    1    0   
$EndComp
$Comp
L ArduProMiniTKB:ARDUPROMINI-6 uP1
U 1 1 5B028763
P 5750 3050
F 0 "uP1" H 5150 2100 60  0000 C CNN
F 1 "ARDUPROMINI-6" H 5150 2200 60  0000 C CNN
F 2 "DAI_Maker_Lab_footprints:Arduino_Pro_Mini-6" H 5750 3050 60  0001 C CNN
F 3 "" H 5750 3050 60  0000 C CNN
	1    5750 3050
	1    0    0    -1  
$EndComp
$Comp
L mapH-rescue:Conn_01x03 J1
U 1 1 5B0288BE
P 7000 4550
F 0 "J1" H 7000 4750 50  0000 C CNN
F 1 "DFRobot" H 7000 4350 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 7000 4550 50  0001 C CNN
F 3 "" H 7000 4550 50  0001 C CNN
	1    7000 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5B028ACF
P 6550 5250
F 0 "D3" H 6550 5350 50  0000 C CNN
F 1 "GREEN" H 6550 5150 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm_FlatTop" H 6550 5250 50  0001 C CNN
F 3 "" H 6550 5250 50  0001 C CNN
	1    6550 5250
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 5B028B9A
P 6550 4950
F 0 "D2" H 6550 5050 50  0000 C CNN
F 1 "RED" H 6550 4850 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm_FlatTop" H 6550 4950 50  0001 C CNN
F 3 "" H 6550 4950 50  0001 C CNN
	1    6550 4950
	-1   0    0    1   
$EndComp
Text GLabel 4250 3500 3    60   Input ~ 0
GND
Wire Wire Line
	4250 3500 4250 3350
Text GLabel 4450 3500 3    60   Input ~ 0
VCC
Wire Wire Line
	4450 3500 4450 3350
Wire Wire Line
	4050 3350 4050 5250
Wire Wire Line
	3950 3350 3950 5150
Wire Wire Line
	3850 3350 3850 5050
Text GLabel 4450 4550 0    60   Input ~ 0
INT0
Wire Wire Line
	4450 4550 4550 4550
Text GLabel 5050 2950 0    60   Input ~ 0
INT0
Text GLabel 5650 2950 2    60   Input ~ 0
GND
$Comp
L Device:R R1
U 1 1 5B02942F
P 6200 4950
F 0 "R1" V 6280 4950 50  0000 C CNN
F 1 "R" V 6200 4950 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6130 4950 50  0001 C CNN
F 3 "" H 6200 4950 50  0001 C CNN
	1    6200 4950
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5B0294A5
P 6200 5250
F 0 "R2" V 6280 5250 50  0000 C CNN
F 1 "R" V 6200 5250 50  0000 C CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6130 5250 50  0001 C CNN
F 3 "" H 6200 5250 50  0001 C CNN
	1    6200 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 5250 6050 5250
Wire Wire Line
	6350 5250 6400 5250
Wire Wire Line
	5750 5150 5950 5150
Wire Wire Line
	6350 4950 6400 4950
Text GLabel 6800 4950 2    60   Input ~ 0
GND
Wire Wire Line
	6800 4950 6700 4950
Text GLabel 6800 5250 2    60   Input ~ 0
GND
Wire Wire Line
	4050 5250 4550 5250
Wire Wire Line
	3950 5150 4550 5150
Wire Wire Line
	3850 5050 4550 5050
Wire Wire Line
	4550 4950 3650 4950
Wire Wire Line
	3650 4950 3650 3350
Wire Wire Line
	4550 4850 3450 4850
Wire Wire Line
	3450 4850 3450 3350
Text GLabel 6700 4550 0    60   Input ~ 0
VCC
Wire Wire Line
	6700 4550 6800 4550
Text GLabel 6700 4350 1    60   Input ~ 0
GND
Wire Wire Line
	6700 4350 6700 4450
Wire Wire Line
	6700 4450 6800 4450
Wire Wire Line
	5850 4650 6800 4650
$Comp
L mapH-rescue:Conn_01x02 J2
U 1 1 5B034B38
P 6700 3250
F 0 "J2" H 6700 3350 50  0000 C CNN
F 1 "JST" H 6700 3050 50  0000 C CNN
F 2 "DAI_Maker_Lab_footprints:JST-PH-2" H 6700 3250 50  0001 C CNN
F 3 "" H 6700 3250 50  0001 C CNN
	1    6700 3250
	0    1    1    0   
$EndComp
Text GLabel 6650 2550 1    60   Input ~ 0
BAT+
Text GLabel 6500 2950 0    60   Input ~ 0
GND
Wire Wire Line
	6500 2950 6600 2950
Wire Wire Line
	6600 2950 6600 3050
Text GLabel 4350 3850 3    60   Input ~ 0
BAT+
Wire Wire Line
	4350 3850 4350 3350
Text GLabel 6000 4400 2    60   Input ~ 0
GND
Wire Wire Line
	5900 4250 5900 4400
Wire Wire Line
	5900 4400 6000 4400
Text GLabel 4400 4350 0    60   Input ~ 0
GND
Wire Wire Line
	4400 4350 4450 4350
Wire Wire Line
	4450 4350 4450 4450
Wire Wire Line
	6700 3000 6700 3050
Wire Wire Line
	6800 5250 6700 5250
Wire Wire Line
	5900 4250 5750 4250
Wire Wire Line
	4450 4450 4550 4450
$Comp
L SPDT:SPDT S1
U 1 1 5B0382D5
P 6700 2800
F 0 "S1" H 6700 2915 40  0000 C CNN
F 1 "Power" H 6700 2690 40  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03_Pitch2.54mm" H 6700 2800 60  0001 C CNN
F 3 "" H 6700 2800 60  0000 C CNN
	1    6700 2800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 2550 6650 2650
$Comp
L switch-tact:DTS-3 S2
U 1 1 5B038FF7
P 5350 2950
F 0 "S2" V 5065 2875 50  0000 L BNN
F 1 "DTS-3" V 5165 3075 50  0000 L BNN
F 2 "Buttons_Switches_THT:SW_PUSH-12mm" H 5350 3100 50  0001 C CNN
F 3 "" H 5350 2950 60  0001 C CNN
	1    5350 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 2950 5150 2950
Wire Wire Line
	5550 2950 5650 2950
Wire Wire Line
	5750 4150 5850 4150
Text GLabel 6250 4150 2    60   Input ~ 0
BAT+
$Comp
L Device:D D1
U 1 1 5B039E0F
P 6000 4150
F 0 "D1" H 6000 4250 50  0000 C CNN
F 1 "D" H 6000 4050 50  0000 C CNN
F 2 "Diodes_THT:D_DO-41_SOD81_P7.62mm_Horizontal" H 6000 4150 50  0001 C CNN
F 3 "" H 6000 4150 50  0001 C CNN
	1    6000 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4150 6250 4150
Wire Wire Line
	5850 4850 5850 4650
Wire Wire Line
	5950 5150 5950 4950
Wire Wire Line
	5950 4950 6050 4950
Text GLabel 6000 4550 2    60   Input ~ 0
VCC
Wire Wire Line
	5750 4450 5900 4450
Wire Wire Line
	5900 4450 5900 4550
Wire Wire Line
	5900 4550 6000 4550
Text GLabel 4150 3850 3    60   Input ~ 0
VCC
Wire Wire Line
	4150 3850 4150 3350
Wire Wire Line
	5850 4850 5750 4850
$EndSCHEMATC
