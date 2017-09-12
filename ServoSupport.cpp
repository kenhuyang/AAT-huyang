#include "ServoSupport.h"
#include "Arduino.h"

char ServoSupport::CurID;  //Current ID
char ServoSupport::Pins[9]; //Pin's
unsigned char ServoSupport::Angs[9]; //angle's
unsigned int  ServoSupport::Cnts[9]; //TCNT's
unsigned int  ServoSupport::UseCnt,ServoSupport::MaxCnt;

void ServoSupport::Init() {	
	Stop();
	TCCR1A = 
		(0<<WGM10) | (0<<WGM11) | //Normal Mode
		(0<<COM1A1) |
		(0<<COM1A0) |
		(0<<COM1B1) |
		(0<<COM1B0);  
	TCCR1B =
		(0<<CS10) | (1<<CS11) | (0<<CS12) | //8
		(0<<WGM13)| (0<<WGM12); //Normal Mode
	TCCR1C = 0;

	for(int i=0;i<9;i++) Pins[i]=-1;
	MaxCnt=40000; //20ms*2000;
}
void ServoSupport::SetAng(char id,char pin,unsigned char ang) { 
	float val=ang;
//	val=val/180+1; //1-2ms
	val=val/90+0.5; //0.5-2.5ms
	Cnts[id]=(int)(val*2000);  //F_CPU/8*0.001=2000
	Angs[id]=ang;
	Pins[id]=pin;
}
void ServoSupport::Stop() {	
	TIMSK1 = 0;
}
void ServoSupport::Start() {
	for(int i=0;i<9;i++) if( Pins[i]>=0 ) pinMode(Pins[i],OUTPUT);
	CurID=0;
	Run();
	TIMSK1 |= (1<<TOIE1);
}
void ServoSupport::Run() {
	char pin;
	if( CurID==0 ) UseCnt=0; //
	else if( CurID>0 ) {
		if( Pins[CurID]>=0 ) digitalWrite(Pins[CurID],LOW); //
	}
	while( ++CurID<=8 && Pins[CurID]<0 ) ; //
	if( CurID>8 ) { //
		TCNT1=65536-MaxCnt+UseCnt;
		CurID=0;
	}
	else {
		TCNT1=65536-Cnts[CurID];
		digitalWrite(Pins[CurID],HIGH);
		UseCnt+=Cnts[CurID];
	}
}

ISR(TIMER1_OVF_vect) {
	ServoSupport::Run();
}

