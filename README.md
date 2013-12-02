LZ0DLS
======

http://wspr.lz1ny.net

LZ0DLS WSPR Beacon
73

WSPR - The network
The Weak Signal Propagation Reporter Network is a group of amateur radio operators using K1JT's MEPT_JT digital mode to probe radio frequency propagation conditions using very low power (QRP/QRPp) transmissions. The data collected are available to the public.
The WSPRnet web site provides a simple user interface for querying the database, a mapping facility, and many other features.

WSPR 2.0 - The program
WSPR (pronounced "whisper") stands for "Weak Signal Propagation Reporter".
The WSPR software is designed by Joe Taylor ( K1JT ) for probing potential radio propagation paths using low-power beacon-like transmissions. WSPR signals convey a callsign, Maidenhead grid locator, and power level using a compressed data format with strong forward error correction and narrow-band 4-FSK modulation. The protocol is effective at signal-to-noise ratios as low as -28 dB in a 2500 Hz bandwidth. Receiving stations with internet access may automatically upload reception reports to a central database - WSPRnet.

WSPR The protocol
Specifications of the WSPR Protocol
Standard message	callsign + 4-digit locator + transmitted power level [dBm]
Standard message components after lossless compression	28 bits for callsign, 15 for locator, 7 for power level, 50 bits total
Forward error correction (FEC)	convolutional code with constraint length K=32, rate r=1/2
Keying rate	1.4648 baud
Number of binary channel symbols	162
Modulation	continuous phase 4-FSK, tone separation 1.4648 Hz
Occupied bandwidth	about 6Hz
Synchronization	162-bit pseudo-random sync vector
Data structure	each channel symbol conveys one sync bit (LSB) and one data bit (MSB)
Duration of transmission	110.6 s
Minimum S/N for reception	around -28 dB on the WSJT scale (2500 Hz reference bandwidth).
	
LZ0DLS - The beacon
Specifications of the LZ0DLS

WSPR message	LZ0DLS KN12 10


Source-encoded message (50 bits, hex): 94 7B 7B 86 EB 92 80

Data symbols:
      1 1 0 0 1 0 0 0 0 0 0 0 1 0 0 0 1 0 1 1 0 0 0 1 1 1 0 1 1 1
      0 1 1 0 1 1 1 1 1 0 1 1 1 1 1 0 0 0 1 1 0 0 1 0 0 1 0 1 1 1
      1 1 1 0 0 0 0 0 1 1 0 1 0 1 1 1 0 1 0 0 1 0 0 1 0 1 0 0 0 0
      1 1 1 1 1 1 1 0 1 0 0 0 0 0 1 0 1 0 0 0 0 1 1 1 0 0 0 0 0 1
      1 1 1 1 1 0 0 0 1 0 0 1 1 1 0 1 1 0 1 0 0 1 0 1 1 0 0 0 0 0
      1 0 0 1 1 0 0 1 1 1 0 0
      
Sync symbols:
      1 1 0 0 0 0 0 0 1 0 0 0 1 1 1 0 0 0 1 0 0 1 0 1 1 1 1 0 0 0
      0 0 0 0 1 0 0 1 0 1 0 0 0 0 0 0 1 0 1 1 0 0 1 1 0 1 0 0 0 1
      1 0 1 0 0 0 0 1 1 0 1 0 1 0 1 0 1 0 0 1 0 0 1 0 1 1 0 0 0 1
      1 0 1 0 1 0 0 0 1 0 0 0 0 0 1 0 0 1 0 0 1 1 1 0 1 1 0 0 1 1
      0 1 0 0 0 1 1 1 0 0 0 0 0 1 0 1 0 0 1 1 0 0 0 0 0 0 0 1 1 0
      1 0 1 1 0 0 0 1 1 0 0 0
      
Channel symbols:
      3 3 0 0 2 0 0 0 1 0 0 0 3 1 1 0 2 0 3 2 0 1 0 3 3 3 1 2 2 2
      0 2 2 0 3 2 2 3 2 1 2 2 2 2 2 0 1 0 3 3 0 0 3 1 0 3 0 2 2 3
      3 2 3 0 0 0 0 1 3 2 1 2 1 2 3 2 1 2 0 1 2 0 1 2 1 3 0 0 0 1
      3 2 3 2 3 2 2 0 3 0 0 0 0 0 3 0 2 1 0 0 1 3 3 2 1 1 0 0 1 3
      2 3 2 2 2 1 1 1 2 0 0 2 2 3 0 3 2 0 3 1 0 2 0 2 2 0 0 1 1 0
      3 0 1 3 2 0 0 3 3 2 0 0
      

CW ID	LZ0DLS WSPR BEACON KN12PQ 600 ASL
Operating Frequency :	10.140 250 MHz
Power supply :	200mA @ 12V
Power :	200 mW ( 23dBm )
Coordinates:	23 15' 26"E; 42 41' 11" N
	

Beacon Hardware

    The Core:
        Silicon Labs Si570 CAC000141DG DCO. Decode chip's part number
        Seeduino (v2.12) - Atmel MCU ATmega168 based board 
    Time refference: cheap GPS receiver module by Rockwell (thanks to eBay :-) ) + external antenna

    


The beacon firmware is coded in C, using Arduino IDE 

Why DLS ? The suffix of the callsign stands for "Dobrata Lamya Spaska". Translated directly to English it means "The good dragon Spaska" :-))
Female dragon Spaska is a mythical hero of Bulgarian fairy tales and also involved in many jokes of recent times. She is good at heart and LZ0DLS just whispers her name instead of roaring and scaring people. :-)

First logged spots at WSPRnet:
(callsign used during tests - LZ1NY)

 2011-11-12 19:56   LZ1NY   10.140204  -23  0  KN12pq	0.01  PA3DPN   JO21ot  1693  313 
 2011-11-12 19:56   LZ1NY   10.140244  -15  0  KN12pq	0.01  ON7KO    JO21ce  1722  310 
 

73! Victor / LZ1NY 
