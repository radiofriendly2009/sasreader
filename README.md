# sasreader

work in progress - daChief 11/2016

project to connect a raspberry pi or any other linux machine
to the "euro-sas siren controller"
can be used by voluntary fire departments in county
of salzburg/austria (or others which use euro-sas) as addition or replacement
for the sms interface of feuerwehreinsatz.info

folder bash:
scripts for testing, creating and deleting virtual pseudo ttys
init script for cpp daemon

folder cpp:
linux daemon written in c/cpp which reads data from serial interface 
connected to euro-sas

folder python:
python script which reads data from serial interface connected to euro-sas
