LZ0DLS
======

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
Power :	10 mW ( 10dBm )
Coordinates:	23 15' 26"E; 42 41' 11" N
	

Beacon Hardware

    The Core:
        Silicon Labs Si570 CAC000141DG DCO. Decode chip's part number
        Seeduino (v2.12) - Atmel MCU ATmega168 based board 
    Time refference: cheap GPS receiver module by Rockwell (thanks to eBay :-) ) + external antenna
    Power Amplifier - (planned) 2SC1970(driver) + IRF510 (final stage)
    The design of the amplifier is borrowed from: HF SDR Transceiver-AVALA-01 by YU1LM
    similar solutions:
        Mighty Mike TX by by N1HFX
        The NB6M Miniboots
        Двудиапазонен CW/SSB трансивър 
    Antenna - I dont know yet!? 


The beacon firmware is coded in C, using Arduino 0022 IDE (source code will be posted later)

Why DLS ? The suffix of the callsign stands for "Dobrata Lamya Spaska". Translated directly to English it means "The good dragon Spaska" :-))
Female dragon Spaska is a mythical hero of Bulgarian fairy tales and also involved in many jokes of recent times. She is good at heart and LZ0DLS just whispers her name instead of roaring and scaring people. :-)

Step-By-Step:
2 Nov 2011 A request was sent to the Communications Regulation Commission (CRC) for a license for LZ0DLS.

3 Nov 2011 The first WSPR message was transmitted (5 mW power), received at the other side of my desk and successfully decoded. Transmissions normally begin at one second after an even UTC minute (i.e. hh:00:01, hh:02:01). During the first tests, start and stop timing was performed by hand :-). Data symbols, sync symbols and resultant channel symbols were calculated by WSPRcode.exe

4 Nov 2011 A frequency adjustment procedure was performed. Thomas MARTIN (DF7TV) does an excellent job of describing the correct setup procedure for the Si570 in his notes on his Si570/PICAXE experiments. However, in my experience, there was no need to measure Fstart. I simply measured the output frequency of the Si570 using an FT897D after warm-up. The signal was aproximably 1kHz higher than expected. I then recaulatued the the register 7 to 12 values to reduce the frequency to the desired value. The step between channel frequencies (tone separation) was 1.4648 Hz (0x673). Calculations were performed using Silicon Labs Programmable Oscillator Software.

5 Nov 2011 LZ0DLS learned Morse code and can now send CW ID (as required by the regulations for amateur radio services in Bulgaria)

6 Nov 2011 LZ0DLS now capable of utilizing GPS satellites to synchronize its clock via the GPS Module Rockwell

11 Nov 2011 The national regulatory agency (The Communications Regulation Commission or CRC) issued a license to LZ0DLS.

12 Nov 2011 First "on-air" tests were performed
Pout = 10 mW (yes, only 10 mW or less)
Antenna - dipole for 40m band
First logged spots at WSPRnet:
(callsign used during tests - LZ1NY)

 2011-11-12 19:56   LZ1NY   10.140204  -23  0  KN12pq	0.01  PA3DPN   JO21ot  1693  313 
 2011-11-12 19:56   LZ1NY   10.140244  -15  0  KN12pq	0.01  ON7KO    JO21ce  1722  310 
 

15 Nov 2011 5 Watts PA (2SC1970 + IRF510) is ready to be tuned and tested. Does it work? I don't know yet....

19-20 Nov 2011 Too busy to work with LZ0DLS this weekend due to a LZ DX Contest :-)
....... etc.....etc.....etc

19 Jan 2012 Two months later... the PA is still not ready ... so LZ0DLS began at 10mW.
"weak signal" means - weak signal :-)
for some months LZ0DLS was off line due to hardware crash caused by statics :-( The most expensive part Si570 chip was damaged! 
