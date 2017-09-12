#ifndef ServoSupport_h
#define ServoSupport_h
namespace ServoSupport {
	extern char CurID;
	extern          char Pins[9];
	extern unsigned char Angs[9];
	extern unsigned int  Cnts[9];
	extern unsigned int  UseCnt,MaxCnt;
	void Init();
	void SetAng(char id,char pin,unsigned char ang);
	void Stop();
	void Start();
	void Run();
}

#endif
