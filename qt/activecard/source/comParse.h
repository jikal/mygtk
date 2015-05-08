#pragma once
#include "qextserialport.h"

class comParse
{
public:
	comParse(void);
	~comParse(void);

	bool getRFID(char *dstRFID,const char *port,int tiomeout = 10);

private:
	QextSerialPort *m_sSerialPort;

	int ReadData(unsigned char *buf,int timeout=1);
	int WriteData(unsigned char *buf, int len);
};
