/*
 * vasoInvernale
 * REQUIRES: FastLED 3.1.0
 *
 * Copyright (c) 2017 Matteo Marchesi
 *
 */


#include <FastLED.h>

// definisce il numero di led da comnadare nella striscia
#define NUM_LEDS 20

#define DATA_PIN 3

CRGB leds[NUM_LEDS];

//sequenze di lampeggio
int lampeggia_led_A[]={7,0,1,2,3,4,5,6};
//quante fasi ha ogni sequenza.
int lampeggia_sequenza_A = 2;

//quali colori devono lampeggiare
//primo   numero = colore
//secondo numero = saturazione
//terzo   numero = luminosità

int lampeggia_colori_A[6][3]={
  {0,120,125}, //pink
  {0,100,160},  //pink
  {0,120,225},  //pink
  {0,80,80},  //pink
  {0,70,125},  //pink
  {0,120,100}  //pink
  };
int lampeggia_conta_A = 0;

//sequenze di lampeggio
int lampeggia_led_B[]={6,7,8,9,10,11,12};
//quante fasi ha ogni sequenza.
int lampeggia_sequenza_B = 2;

//quali colori devono lampeggiare
//primo   numero = colore
//secondo numero = saturazione
//terzo   numero = luminosità

int lampeggia_colori_B[8][3]={
  {64,200,125}, //yellow
  {64,200,200},
  {64,200,100},
  {64,200,50},
  {64,200,70},
  {64,200,125},
  {64,200,150},
  {64,200,125}
  };
int lampeggia_conta_B = 0;


int lampa(int cycle, int maxN, int ledarray[], int seqarray[][3]);

//int giornonotte_ledGRP1[]= {7,0,1,2,3,4,5,6};
//int giornonotte_contaGRP1 = 0;
//int colorGRP1=0; //red

//int giornonotte_ledGRP2[]= {7,7,8,9,10,11,12,13};
//int giornonotte_contaGRP2 = 0;
//int colorGRP2=64; //yellow

int giornonotte_ledGRP3[]= {7,13,14,15,16,17,18,19};
int giornonotte_contaGRP3 = 0;
int colorGRP3=96; //green


int giornonotte(int cycle, int ledarray[]);

int bright = 255;
int fade = 32;

unsigned long previousGRP1 = 0;
const long intervalGRP1 = 150;

unsigned long previousGRP2 = 0;
const long intervalGRP2 = 500;

unsigned long previousGRP3 = 0;
const long intervalGRP3 = 80;


void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

}

void loop() {
  unsigned long current = millis();

  if (current - previousGRP1 >= intervalGRP1) {
    previousGRP1 = current;
    lampeggia_conta_A = lampa(lampeggia_conta_A, lampeggia_sequenza_A, lampeggia_led_A, lampeggia_colori_A);
  }

//  if (current - previousGRP1 >= intervalGRP1) {
//    previousGRP1 = current;
//    giornonotte_contaGRP1 = giornonotte(giornonotte_contaGRP1, giornonotte_ledGRP1,colorGRP1);
//  }

if (current - previousGRP2 >= intervalGRP2) {
  previousGRP2 = current;
  lampeggia_conta_B = lampa(lampeggia_conta_B, lampeggia_sequenza_B, lampeggia_led_B, lampeggia_colori_B);
}


//  if (current - previousGRP2 >= intervalGRP2) {
//    previousGRP2 = current;
//    giornonotte_contaGRP2 = giornonotte(giornonotte_contaGRP2, giornonotte_ledGRP2,colorGRP2);
//  }

  if (current - previousGRP3 >= intervalGRP3) {
    previousGRP3 = current;
    giornonotte_contaGRP3 = giornonotte(giornonotte_contaGRP3, giornonotte_ledGRP3,colorGRP3);
  }


}

int giornonotte(int cycle, int ledarray[],int C){
//  int C = 16; //color
  int B = sin8(cycle);      // bright
//  int S = sin8(cycle+128);  //saturation
  int S = 200;
  for (int i = 0; i < ledarray[0]; i++){
    leds[ledarray[i+1]] = CHSV(C,S,B);
  }
  FastLED.show();
  cycle ++;
  return cycle;
}

int lampa(int cycleLM, int maxN, int ledarray[], int seqarray[][3]){
  if (cycleLM>maxN-1) {
    cycleLM=0;
  }
  for (int i = 0; i<ledarray[0]; i++){
    leds[ledarray[i+1]]= CHSV(seqarray[cycleLM][0],seqarray[cycleLM][1],seqarray[cycleLM][2]);
  }

  FastLED.show();
  cycleLM++;
  return cycleLM;
}
