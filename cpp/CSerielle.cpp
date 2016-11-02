
#include "CSerielle.h"

//#using namespace std;


CSerielle::CSerielle(std::string strDevice, int nBaud, int nDatenBit, std::string strParity, int nStopBit, int nHWHandshake)
{
	m_hHandle = 0;
	m_strDevice = strDevice;
	m_nBaud = nBaud;
	m_nDatenBit = nDatenBit;
	m_strParity = strParity;
	m_nStopBit = nStopBit;
	m_nHardwareHandshake = nHWHandshake;
	m_cZeichenGelesen = 0;
	m_dwAnzahlGelesen = 0;
}

CSerielle::~CSerielle()
{
	CloseDevice();
}

int CSerielle::Configure(std::string strDevice, int nBaud, int nDatenBit, std::string strParity, int nStopBit, int nHWHandshake)
{
	if(!strDevice.length() || nBaud <= 0 || (nDatenBit <= 0 || nDatenBit > 8) || !strParity.length() ||
		(nStopBit <= 0  || nStopBit > 8) || strDevice.length() > 127)
	{
		return 0;
	}

	m_strDevice = strDevice;
	m_nBaud = nBaud;
	m_nDatenBit = nDatenBit;
	m_strParity = strParity;
	m_nStopBit = nStopBit;
	m_nHardwareHandshake = nHWHandshake;
	return 1;
}

int CSerielle::OpenDevice()
{

    struct termio term;

    m_hHandle = open(m_strDevice.c_str(), O_RDWR);

    if(m_hHandle < 0)
		return 0;

    errno = 0;

    if((ioctl(m_hHandle, TCGETA, &term)) != 0)  
		return 0;

    term.c_iflag &= ~IXON;		/* Xon, Xoff, Xany ausschalten */
    term.c_iflag &= ~IXOFF;
    term.c_iflag &= ~IXANY;
	term.c_iflag &= ~ISTRIP;	

    term.c_oflag &= ~OPOST;
    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;

    term.c_cflag |= HUPCL;		/* Wenn die serielle Leitung unterbrochen
								wird, soll die Verbindung ebenfalls
								unterbrochen werden */
    term.c_cflag |= CREAD;
    term.c_cflag |= CLOCAL;

    switch(m_strParity[0])			// Paritaet setzen
    {
	case 'E' :
		term.c_cflag &= ~PARODD;
		term.c_cflag |= PARENB;		// Paritaet aktivieren
		break;

   	case 'O' :
		term.c_cflag |= PARENB;
		term.c_cflag |= PARODD;
		break;

   	case 'N' :
		term.c_cflag &= ~PARODD;
		term.c_cflag &= ~PARENB;	// Paritaet deaktivieren 
		break;

	default:
		return 0;
    }
    
    switch(m_nStopBit)				// Stop Bit setzen
    {
	case 1 :
		term.c_cflag &= ~CSTOPB;
		break;

	case 2:
		term.c_cflag |= CSTOPB;
		break;

	default :
		return 0;
    }
    

    switch(m_nDatenBit)				// Daten Bit setzen
    {
	case 7 :
		term.c_cflag &= ~CS8;
		term.c_cflag |= CS7;
		break;

	case 8 :
		term.c_cflag &= ~CS7;
		term.c_cflag |= CS8;
		break;

	default:
		return 0;
    }


    switch(m_nBaud)					// Baudrate setzen
    {
	case 300 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B300;
		break;
			
	case 600 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B600;
		break;
			
	case 1200 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B1200;
		break;
		    
	case 2400 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B2400;
		break;

	case 4800 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B4800;
		break;

	case 9600 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B9600;
		break;

	case 19200 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B19200;
		break;

	case 38400 :
		term.c_cflag = (term.c_cflag & ~CBAUD) | B38400;
		break;

	default:
		return 0;
    }


    term.c_cc[VMIN] = 1;	// mindestens einzulesende Zeichen
    term.c_cc[VTIME] = 0;	// mindest Wartezeit, bis etwas ueber die Schnittstelle kommt

/*
	if (m_nHardwareHandshake)
	{
		term.c_line |= TIOCM_DTR;
		term.c_line |= TIOCM_RTS;
	}
	else
	{
		term.c_line &= ~TIOCM_DTR;
		term.c_line &= ~TIOCM_RTS;
	}
*/
    if((ioctl(m_hHandle, TCSETA, &term)) != 0)	// Parameter setzen
		return 0;

    if((ioctl(m_hHandle, TCFLSH, 0)) != 0)		// Puffer leeren
		return 0;

	return 1;


}

int CSerielle::CloseDevice(void)
{

    if(m_hHandle && close (m_hHandle))
		return 0;

	m_hHandle = 0;

    return 1;

}

int CSerielle::WriteDataString(std::string strTXDaten, int nAnzahlZeichen, int nTimeout)
{

	int nSchleifenZaehler;

	nTimeout = 0;							

    if((nSchleifenZaehler = write(m_hHandle, &strTXDaten[0], nAnzahlZeichen)) < 0)
	{

		return -1;
	}

	return(nSchleifenZaehler);

}

int CSerielle::WriteDataChar(unsigned char *pcDaten, int nAnzahlZeichen, int nTimeout)
{

	int nSchleifenZaehler;

	nTimeout = 0;							

    if((nSchleifenZaehler = write(m_hHandle, pcDaten, nAnzahlZeichen)) < 0)
		return -1;

	return(nSchleifenZaehler);

}


int CSerielle::ReadData(unsigned char *pcRXDaten, int nTimeout)
{
	DWORD dwErgebnis;


    struct termio term;
	//int nGelesen;

    if(nTimeout > 0)
	{
		if((ioctl(m_hHandle, TCGETA, &term)) < 0)
			return -1;

		term.c_cc[VMIN] = 0;					// Mindestens 1 Zeichen lesen
		term.c_cc[VTIME]= nTimeout / 100;
		
		term.c_lflag &= ~ECHO;
		term.c_lflag &= ~ICANON;

		if((ioctl(m_hHandle, TCSETA, &term)) < 0)
			return -1;
	}

    dwErgebnis = read(m_hHandle, pcRXDaten, 1);
	
	if(dwErgebnis < 0)
		return -1;

    return dwErgebnis;

}

int CSerielle::EmptyCache(void)
{

    if((ioctl(m_hHandle, TCFLSH, 0)) != 0)				// Puffer leeren
		return 0;
	return 1;

}

void CSerielle::GetLastErrorText(DWORD dwErr)
{
	char pcFehlerText[1024] = {0};

	if(dwErr) 
	{
		strncpy (pcFehlerText, strerror (dwErr),1023);
	}
}

std::string CSerielle::GetErrorText()
{
	return m_strFehlerText;
}
