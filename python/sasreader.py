#!/usr/bin/python

import serial, time, io, os
from datetime import datetime

ser = serial.Serial()
ser.port = "/dev/ttyUSB0"
ser.baudrate = 19200
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.timeout = 1  #timeout for block read
ser.xonxoff = False 
ser.rtscts = False  
ser.dsrdtr = False       


try: 
    ser.open()
except Exception, e:
    print "error open serial port: " + str(e)
    exit()

if ser.isOpen():
		
    outfileext=".txt"
    outfilepath="./alertlog/"
    if not os.path.exists(outfilepath):
    	os.mkdir(outfilepath)    

    try:
        ser.flushInput() 

	sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser, 1),encoding='ascii', newline='\n')

        while ser.isOpen():
		#data = sio.readline()
		data = sio.read(1024)
		if data:
			data = data[:-1]	# remove 0x7F from end of string
			print("read data: " + data)
			#time.sleep(0.5)  #give the serial port sometime to receive the data
			outfile = outfilepath + datetime.utcnow().isoformat() + outfileext
			with open(outfile, 'a') as f:
				f.write(datetime.utcnow().isoformat() + '\n' + data + '\n' )
				f.flush()
				
    except Exception, e1:
        ser.close()
        print "error communicating...: " + str(e1)

else:
    print "cannot open serial port "
