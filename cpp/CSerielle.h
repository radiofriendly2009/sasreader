// serielle.h
#ifndef __SERIELLE_H__
#define __SERIELLE_H__


#include <errno.h>
#include <termio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>

//using namespace std;

// Definitionen
#ifndef WIN32
	#define HANDLE int
	#define DWORD unsigned int
	#define TRUE	1
	#define FALSE	0
#endif

class CSerielle
{
	
private:

	HANDLE	m_hHandle;
	char	m_cZeichenGelesen;
	DWORD	m_dwAnzahlGelesen;

	int		m_nBaud;
	int		m_nDatenBit;
	int		m_nStopBit;
	std::string	m_strDevice;
	std::string	m_strParity;
	int		m_nHardwareHandshake;

	std::string	m_strFehlerText;

	void	GetLastErrorText(DWORD dwErr);

public:	
	CSerielle() : m_hHandle (0), m_cZeichenGelesen(0), m_dwAnzahlGelesen(0),
				  m_nBaud(0), m_nDatenBit(0), m_nStopBit(0), m_nHardwareHandshake(0){};

	CSerielle(std::string strDevice, int nBaud, int nDatenBit, std::string strParity, int nStopBit, int nHWHandshake = TRUE);
	virtual ~CSerielle();


	int	Configure(std::string strDevice, int nBaud, int nDatenBit, std::string strParity, int nStopBit, int nHWHandshake = TRUE);
	HANDLE Handle(void) { return m_hHandle; };
	std::string DeviceName(void) { return m_strDevice; };
	int	OpenDevice(void);
	int	CloseDevice(void);
	int	WriteDataString(std::string strTXDaten, int nAnzahlZeichen, int nTimeout);
	int WriteDataChar(unsigned char *pcDaten, int nAnzahlZeichen, int nTimeout);
	int	ReadData(unsigned char *pcRXDaten, int nTimeout);
	int	EmptyCache(void);

	std::string	GetErrorText();
};





#endif // __CESERIELLE_H__
