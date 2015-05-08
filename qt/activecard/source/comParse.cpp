#include "comParse.h"
#include <QMessageBox>
#include <time.h>
#ifdef _WIN32
#define CARDPORT "COM9"
#else
#define CARDPORT "/dev/ttyS1"
#endif
//cmd
static unsigned char SetBaud[]={0x02,0x00,0x02,0x23,0x00,0x21};
static unsigned char SetAddr[]={0x02,0x00,0x02,0x24,0x00,0x26};
static unsigned char ReadAddr[]={0x02,0x00,0x01,0x25,0x24};
static unsigned char ResetCard[]={0x02,0x00,0x01,0x2d,0x2c};
static unsigned char bip[]={0x02,0x00,0x02,0x2c,0x08,0x26};
static unsigned char RequestCard[]={0x02,0x00,0x02,0x31,0x52,0x61};
static unsigned char AntiColl[]={0x02,0x00,0x02,0x32,0x93,0xa3};
static unsigned char ActiveOk[]={0x02,0x00,0x01,0x00,0x01};
static unsigned char AddrZero[]={0x02,0x00,0x02,0x00,0x00,0x02};
static unsigned char NoCard[]={0x02,0x00,0x01,0x01,0x00};

static void MySleep(long nTime)
//	延时nTime毫秒，毫秒是千分之一秒
{
#if defined(_WIN32 )||defined(_WIN64)
	//	windows 代码
	Sleep(nTime);
#else

	//	unix/linux代码
	timespec localTimeSpec;
	timespec localLeftSpec;
	localTimeSpec.tv_sec=nTime/1000;
	localTimeSpec.tv_nsec=(nTime%1000)*1000000;
	nanosleep(&localTimeSpec,&localLeftSpec);
#endif
}

comParse::comParse(void)
{
	m_sSerialPort = NULL;
}

comParse::~comParse(void)
{
	if (m_sSerialPort != NULL)
	{
		if (m_sSerialPort->isOpen())
		{
			m_sSerialPort->close();
		}
	}
}

bool comParse::getRFID(char *dstRFID,const char *port,int tiomeout)
{
	unsigned char uBuf[32];
	char buf[256];
	PortSettings set;
	bool ret = false;
	int nRead = 0;
	if (dstRFID == NULL)
	{
		return false;
	}

	set.BaudRate = BAUD9600;
	set.DataBits = DATA_8;
	//set.FlowControl = FLOW_OFF;
	set.Parity = PAR_NONE;
	set.StopBits = STOP_1;
	set.Timeout_Sec = 2;
	set.Timeout_Millisec = 0;

	if (m_sSerialPort != NULL)
	{
		if (m_sSerialPort->isOpen())
		{
			m_sSerialPort->close();
		}
	}
	m_sSerialPort = new QextSerialPort(port,set);
	ret = m_sSerialPort->open(QIODevice::ReadWrite);

	if (!ret)
	{
		return false;
	}


	int time0,time1;
	time0 = time((time_t *) NULL);

	//WriteData(SetBaud,sizeof(SetBaud));
	//nRead = ReadData(uBuf);
	//sprintf(buf,"%02x %02x %02x %02x %02x %02x ",uBuf[0],uBuf[1],uBuf[2],uBuf[3],uBuf[4],uBuf[5]);
	//WriteData(SetAddr,sizeof(SetAddr));
	//nRead = ReadData(uBuf);
	//sprintf(buf,"%02x %02x %02x %02x %02x %02x ",uBuf[0],uBuf[1],uBuf[2],uBuf[3],uBuf[4],uBuf[5]);
	printf("start write\n");

	WriteData(bip,sizeof(bip));
	nRead = ReadData(uBuf,1);
	sprintf(buf,"%02x %02x %02x %02x %02x %02x \n",uBuf[0],uBuf[1],uBuf[2],uBuf[3],uBuf[4],uBuf[5]);
        printf(buf);

		

	while(true)
	{
		WriteData(RequestCard,sizeof(RequestCard));
		nRead = ReadData(uBuf,1);
		sprintf(buf,"%02x %02x %02x %02x %02x %02x \n",uBuf[0],uBuf[1],uBuf[2],uBuf[3],uBuf[4],uBuf[5]);
                printf(buf);
		if(WriteData(AntiColl,sizeof(AntiColl)) == sizeof(AntiColl))
		{
			if (ReadData(uBuf,1) == 9)
			{
				sprintf(buf,"%02x %02x %02x %02x %02x %02x %02x %02x %02x\n",uBuf[0],uBuf[1],uBuf[2],uBuf[3],uBuf[4],uBuf[5],uBuf[6],uBuf[7],uBuf[8]);
                                printf(buf);
				//QMessageBox::information(NULL,"Information",buf);
				printf(buf);
				sprintf(dstRFID,"%x:%x:%x:%x",uBuf[4],uBuf[5],uBuf[6],uBuf[7]);
				WriteData(bip,sizeof(bip));
				nRead = ReadData(uBuf,1);
				break;
			}
		}
		time1 = time((time_t *) NULL);
		difftime(time1,time0);
		if (difftime(time1,time0) > tiomeout)
		{
			printf("time out\n");
			return false;
		}
	}
	return  true;
}


int comParse::ReadData(unsigned char *buf,int timeout)
{
	int count = 0;

	if (NULL == buf || m_sSerialPort == NULL)
	{
		return 0;
	}


	if (!m_sSerialPort->isReadable())
	{
		return 0;
	}

	int len = 0;
	int remainLen = 0;
	while(1)
	{
#ifdef _WIN32
		len = m_sSerialPort->bytesAvailable();
		len = m_sSerialPort->readData((char*)buf, len);
#else
		len = m_sSerialPort->readData((char*)buf, 256);
#endif
printf("count=%d,len=%d\n",count,len);
		if (len <= 0)
		{
#ifdef _WIN32
			if (count >= timeout*20)
			{
				break;
			}
			MySleep(50);
#else
			if (count >= timeout*2)
			{
				break;
			}
			MySleep(50);
#endif		
			count ++ ; 
		}
		else
		{
			break;
		}
	}


	return len < 0 ? 0 : len;
}

int comParse::WriteData(unsigned char *buf, int len)
{
	if (NULL == buf || len == 0 || m_sSerialPort == NULL)
	{
		return 0;
	}

	if (!m_sSerialPort->isOpen())
	{
		return 0;
	}

	if(m_sSerialPort != NULL)
	{
		int n = m_sSerialPort->writeData((char *)buf, len);	
		return n;
	}
	return 0;
}
