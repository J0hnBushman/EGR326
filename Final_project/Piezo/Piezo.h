#ifndef __PIEZO_H__
#define __PIEZO_H__

#include "stm32f4xx.h"
// System Clock is set to 16 MHz
#define SYSTEM_CLOCK_HZ 16000000

// Prescaler to set the timer frequency
#define TIMER_PRESCALER (16) - 1  // Timer frequency to 1 MHz

// Define musical notes frequencies (in Hz) for reference
#define NOTE_B0    31
#define NOTE_C1    33
#define NOTE_CS1   35
#define NOTE_D1    37
#define NOTE_DS1   39
#define NOTE_E1    41
#define NOTE_F1    44
#define NOTE_FS1   46
#define NOTE_G1    49
#define NOTE_GS1   52
#define NOTE_A1    55
#define NOTE_AS1   58
#define NOTE_B1    62
#define NOTE_C2    65
#define NOTE_CS2   69
#define NOTE_D2    73
#define NOTE_DS2   78
#define NOTE_E2    82
#define NOTE_F2    87
#define NOTE_FS2   93
#define NOTE_G2    98
#define NOTE_GS2   104
#define NOTE_A2    110
#define NOTE_AS2   117
#define NOTE_B2    123
#define NOTE_C3    130
#define NOTE_CS3   138
#define NOTE_D3    146
#define NOTE_DS3   155
#define NOTE_E3    164
#define NOTE_F3    174
#define NOTE_FS3   185
#define NOTE_G3    196
#define NOTE_GS3   208
#define NOTE_A3    220
#define NOTE_AS3   233
#define NOTE_B3    246
#define NOTE_C4    261
#define NOTE_CS4   277
#define NOTE_D4    293
#define NOTE_DS4   311
#define NOTE_E4    329
#define NOTE_F4    349
#define NOTE_FS4   370
#define NOTE_G4    392
#define NOTE_GS4   415
#define NOTE_A4    440
#define NOTE_AS4   466
#define NOTE_B4    493
#define NOTE_C5    523
#define NOTE_CS5   554
#define NOTE_D5    587
#define NOTE_DS5   622
#define NOTE_E5    659
#define NOTE_F5    698
#define NOTE_FS5   740
#define NOTE_G5    784
#define NOTE_GS5   831
#define NOTE_A5    880
#define NOTE_AS5   932
#define NOTE_B5    987
#define NOTE_C6    1047
#define NOTE_CS6   1109
#define NOTE_D6    1175
#define NOTE_DS6   1245
#define NOTE_E6    1319
#define NOTE_F6    1397
#define NOTE_FS6   1480
#define NOTE_G6    1568
#define NOTE_GS6   1661
#define NOTE_A6    1760
#define NOTE_AS6   1865
#define NOTE_B6    1975
#define NOTE_C7    2093
#define NOTE_CS7   2217
#define NOTE_D7    2349
#define NOTE_DS7   2489
#define NOTE_E7    2637
#define NOTE_F7    2794
#define NOTE_FS7   2960
#define NOTE_G7    3136
#define NOTE_GS7   3322
#define NOTE_A7    3520
#define NOTE_AS7   3729
#define NOTE_B7    3951
#define NOTE_C8    4186
#define NOTE_CS8   4435
#define NOTE_D8    4699
#define NOTE_DS8   4978

#define TONE1_0		 0
#define TONE1_1		 1
#define TONE1_2		 2
#define TONE1_3		 3
#define TONE1_END	 4

#define TONE2_0		 5
#define TONE2_1		 6
#define TONE2_2		 7
#define TONE2_3		 8
#define TONE2_END	 9

#define TONE3_0		 10
#define TONE3_1		 11
#define TONE3_2		 12
#define TONE3_3		 13
#define TONE3_END	 14

#define TONE4_0		 15
#define TONE4_1		 16
#define TONE4_2		 17
#define TONE4_3		 18
#define TONE4_END	 19

extern unsigned long long milliseconds;
extern int tone_state;

// Initialize the buzzer by configuring the GPIO and Timer
void Buzzer_Init(void);

// Generate a tone on the buzzer for a specific duration (in milliseconds)
void Play_Tone_1(void);
void Play_Tone_2(void);
void Play_Tone_3(void);
void Play_Tone_4(void);

// Stop the tone (Disable Timer)
void Buzzer_Stop(void);

void Timer7_Init(void);

void TIM7_IRQHandler(void);





#endif