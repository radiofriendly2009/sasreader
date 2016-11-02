#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <sstream>

#include "CSasTelegram.h"
#include "CSerielle.h"

#ifndef DAEMON_NAME
#define DAEMON_NAME "sasreader"
#endif

#ifndef MAX_SIZE
#define MAX_SIZE 1024	//max telegram length should be 969
#endif


int LeseVonSerieller (int iTimeout,CSerielle& ser )
{
	unsigned char cDaten[MAX_SIZE] = {0};
	int iRet = 0;
	int	i = 0;

	do 
	{
		iRet = ser.ReadData (&cDaten[i], iTimeout);
		if (iRet<0) {	// Fehler beim lesen
		syslog(LOG_NOTICE, "Fehler beim lesen von V24:");
			return -1;
		} 
		else if (!iRet) 
		{
			if (i>0) 
			{
			// Timeout erhalten aber Daten sind gekommen
				std::string strHex;
				syslog(LOG_NOTICE, "Gelesen (2)");
	//			return 1;
			} 	
			else
			{

		syslog(LOG_NOTICE, "timeout ohne daten    V24:");
				return 0;
			}
		} 
		else
		{
			i++;	// zeichenzähler erhöhen
		}

		
	} 
	while (iRet > 0 && i< MAX_SIZE);

	syslog( LOG_NOTICE, "voll gelesen");
	
	syslog( LOG_NOTICE, "%s", (char*) cDaten);
	

	std::istringstream iss ((char*) cDaten );


	CSasTelegram aTg;

	aTg.TelegrammErzeuger(iss);

	syslog( LOG_NOTICE, aTg.TelegramProt().c_str() );
	return 1;
}
#define _DEBUG
int main (int argc, char **argv)
{
        
        /* Our process ID and Session ID */
        pid_t pid, sid;
        
        /* Open any logs here */        
	//Set our Logging Mask and open the Log
    setlogmask(LOG_UPTO(LOG_INFO));
    openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);
    //openlog(DAEMON_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1 );
    syslog(LOG_NOTICE, "Entering Daemon");


#ifndef _DEBUG
// Fork off the parent process 
        pid = fork();
        if (pid < 0) 
	{
                exit(EXIT_FAILURE);
        }
        // If we got a good PID, then
        // we can exit the parent process. 
        if (pid > 0) 
	{
                exit(EXIT_SUCCESS);
        }

        // Change the file mode mask 
        umask(0);
                
        // Create a new SID for the child process
        sid = setsid();
        if (sid < 0) 
	{
                // Log the failure 
		syslog(LOG_INFO, "no sid");
                exit(EXIT_FAILURE);
        }

        
        // Change the current working directory 
        if ((chdir("/")) < 0) 	
	{
                // Log the failure 
		syslog(LOG_INFO, "chdir failed");
                exit(EXIT_FAILURE);
        }
        
        // Close out the standard file descriptors
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
#endif

	CSerielle aser;
	aser.Configure( "/dev/ttyUSB0", 19200, 8, "N", 1 );
	int nCountdown = 3;
	int nIntervalsec = 5;
	while( !aser.OpenDevice() )
	{ 
               aser.CloseDevice ();
		if ( nCountdown <= 0 )
		{ 	
			
			syslog(LOG_INFO, "failed to open serial port");
                       return 1;
		} 
		else 
		{ 
                       nCountdown --;
                       sleep( nIntervalsec );
		}
	}

// The Big Loop 
        while (1) 
	{
		//syslog(LOG_INFO, "in Mainloop");
       		
		LeseVonSerieller( 1000, aser );
		//sleep(30); 
        }
	aser.CloseDevice();
	//Close the log
    	closelog ();
  
	exit(EXIT_SUCCESS);

/* stuff for reading cmdline args
   int bflag = 0;
   int sflag = 0;
   int index;
   int c;

   opterr = 0;

   while ((c = getopt (argc, argv, "bs")) != -1)
     switch (c)
       {
       case 'b':
         bflag = 1;
         break;
       case 's':
         sflag = 1;
         break;
       case '?':
         if (isprint (optopt))
           fprintf (stderr, "Unknown option `-%c'.\n", optopt);
         else
           fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
         return 1;
       default:
         abort ();
       }

   printf ("bflag = %d, sflag = %d\n", bflag, sflag);

   for (index = optind; index < argc; index++)
     printf ("Non-option argument %s\n", argv[index]);
  
*/
 return 0;
}
