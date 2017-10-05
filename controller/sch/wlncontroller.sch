EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:relays
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
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
L ATMEGA16-P IC?
U 1 1 59D6C431
P 5750 3550
F 0 "IC?" H 4900 5430 40  0000 L BNN
F 1 "ATMEGA16-P" H 6200 1600 40  0000 L BNN
F 2 "DIL40" H 5750 3550 30  0000 C CIN
F 3 "" H 5750 3550 60  0000 C CNN
	1    5750 3550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 59D6C49F
P 5600 1400
F 0 "#PWR?" H 5600 1500 30  0001 C CNN
F 1 "VCC" H 5600 1500 30  0000 C CNN
F 2 "" H 5600 1400 60  0001 C CNN
F 3 "" H 5600 1400 60  0001 C CNN
	1    5600 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1550 5600 1400
Wire Wire Line
	5900 1550 5900 1500
Wire Wire Line
	5900 1500 5600 1500
Connection ~ 5600 1500
$Comp
L GND #PWR?
U 1 1 59D6C4C7
P 5700 5650
F 0 "#PWR?" H 5700 5650 30  0001 C CNN
F 1 "GND" H 5700 5580 30  0001 C CNN
F 2 "" H 5700 5650 60  0001 C CNN
F 3 "" H 5700 5650 60  0001 C CNN
	1    5700 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 5550 5700 5650
Wire Wire Line
	5800 5550 5800 5600
Wire Wire Line
	5800 5600 5700 5600
Connection ~ 5700 5600
Wire Wire Line
	6750 3650 6900 3650
Wire Wire Line
	6750 3750 6900 3750
Wire Wire Line
	6750 3850 6900 3850
Text Label 6900 3650 0    60   ~ 0
B1
Text Label 6900 3750 0    60   ~ 0
B2
Text Label 6900 3850 0    60   ~ 0
B3
Wire Wire Line
	6750 4550 6900 4550
Wire Wire Line
	6750 4650 6900 4650
Text Label 6900 4550 0    60   ~ 0
RX
Text Label 6900 4650 0    60   ~ 0
TX
$Comp
L CRYSTAL X?
U 1 1 59D6C619
P 4250 3050
F 0 "X?" H 4250 3200 60  0000 C CNN
F 1 "16M" H 4250 2900 60  0000 C CNN
F 2 "" H 4250 3050 60  0000 C CNN
F 3 "" H 4250 3050 60  0000 C CNN
	1    4250 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3050 4750 3050
Wire Wire Line
	4750 2650 3850 2650
Wire Wire Line
	3850 2650 3850 3150
Wire Wire Line
	3850 3050 3950 3050
$Comp
L C C?
U 1 1 59D6C6B1
P 3850 3350
F 0 "C?" H 3850 3450 40  0000 L CNN
F 1 "22p" H 3856 3265 40  0000 L CNN
F 2 "" H 3888 3200 30  0000 C CNN
F 3 "" H 3850 3350 60  0000 C CNN
	1    3850 3350
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 59D6C6DF
P 4650 3350
F 0 "C?" H 4650 3450 40  0000 L CNN
F 1 "22p" H 4656 3265 40  0000 L CNN
F 2 "" H 4688 3200 30  0000 C CNN
F 3 "" H 4650 3350 60  0000 C CNN
	1    4650 3350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 59D6C702
P 3850 3650
F 0 "#PWR?" H 3850 3650 30  0001 C CNN
F 1 "GND" H 3850 3580 30  0001 C CNN
F 2 "" H 3850 3650 60  0001 C CNN
F 3 "" H 3850 3650 60  0001 C CNN
	1    3850 3650
	1    0    0    -1  
$EndComp
Connection ~ 3850 3050
Wire Wire Line
	3850 3550 3850 3650
Wire Wire Line
	4650 3550 4650 3600
Wire Wire Line
	4650 3600 3850 3600
Connection ~ 3850 3600
Wire Wire Line
	4650 3150 4650 3050
Connection ~ 4650 3050
$EndSCHEMATC
