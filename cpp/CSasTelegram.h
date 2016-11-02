/*
 * CSasTelegram.h
 *
 *  Created on: Jun 16, 2016
 *      Author: dachief
 */

#ifndef CSASTELEGRAM_H_
#define CSASTELEGRAM_H_

#include <string.h>
#include <sstream>

class CSasTelegram
{
	std::string m_strAusloeser;
	std::string m_strEinsatznummer;
	std::string m_strAnrufername;
	std::string m_strAnruferadresse;
	std::string m_strAnrufernummer;
	std::string m_strGemeldetvia;
	std::string m_strEinsatzort;
	std::string m_strZusatzinfo;
	std::string m_strEinsatztypShort;
	std::string m_strEinsatztyp;
	std::string m_strEinsatzuntertypShort;
	std::string m_strEinsatzuntertyp;
	std::string m_strAlarmstufe;
	std::string m_strDatum;
	std::string m_strUhrzeit;
	std::string m_strAlarmiert;
	std::string m_strSirenenadresse;

public:
	CSasTelegram()
	{

	}

	int TelegrammErzeuger( std::istringstream& iss);
	std::string TelegramProt();
	virtual ~CSasTelegram() {
		// TODO Auto-generated destructor stub
	}
};

#endif /* CSASTELEGRAM_H_ */
