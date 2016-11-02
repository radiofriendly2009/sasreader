/*
 * CSasTelegram.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: dachief
 */

#include "CSasTelegram.h"




int CSasTelegram::TelegrammErzeuger(std::istringstream& iss)
{
char c=0;
	iss.get(c);
	if( std::getline( iss, m_strAusloeser ) 		&&
		std::getline( iss, m_strEinsatznummer) 		&&
		std::getline( iss, m_strAnrufername )		&&
		std::getline( iss, m_strAnruferadresse )	&&
		std::getline( iss, m_strAnrufernummer )		&&
		std::getline( iss, m_strGemeldetvia )		&&
		std::getline( iss, m_strEinsatzort)			&&
		std::getline( iss, m_strZusatzinfo)			&&
		std::getline(iss, m_strEinsatztypShort) 	&&
		std::getline(iss, m_strEinsatztyp) 			&&
		std::getline(iss, m_strEinsatzuntertypShort)&&
		std::getline(iss, m_strEinsatzuntertyp) 	&&
		std::getline(iss, m_strAlarmstufe) 			&&
		std::getline(iss, m_strDatum) 				&&
		std::getline(iss, m_strUhrzeit) 			&&
		std::getline(iss, m_strAlarmiert) 			&&
		std::getline(iss, m_strSirenenadresse) )
	{
		return 0;
	}
	else
	{
		return 1;
	}

}

std::string CSasTelegram::TelegramProt()
{
	std::ostringstream oss;
	oss << "Ausloeser: " 			<< m_strAusloeser				<< "\n"
		<< "Einsatznummer: "		<< m_strEinsatznummer			<< "\n"
		<< "Anrufername: "			<< m_strAnrufername				<< "\n"
		<< "Anruferadresse: "		<< m_strAnruferadresse			<< "\n"
		<< "Gemeldet via: "			<< m_strGemeldetvia				<< "\n"
		<< "Einsatzort: "			<< m_strEinsatzort				<< "\n"
		<< "Zusatzinfo: "			<< m_strZusatzinfo				<< "\n"
		<< "Einsatztyp kurz: "		<< m_strEinsatztypShort			<< "\n"
		<< "Einsatztyp: "			<< m_strEinsatztyp				<< "\n"
		<< "Einsatzuntertyp kurz: "	<< m_strEinsatzuntertypShort	<< "\n"
		<< "Einsatzuntertyp: "		<< m_strEinsatzuntertyp			<< "\n"
		<< "Alarmstufe: "			<< m_strAlarmstufe				<< "\n"\
		<< "Datum: "				<< m_strDatum					<< "\n"
		<< "Uhrzeit: "				<< m_strUhrzeit					<< "\n"
		<< "Alarmiert: "			<< m_strAlarmiert				<< "\n"
		<< "Sirenenadresse: "		<< m_strSirenenadresse			<< std::ends;

	return oss.str();
}

