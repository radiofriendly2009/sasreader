#
# Makefile fuer "sasreader"
#

#
# Definitionen
#

###########################################################################################
# Compiler bestimmen : CXX
CXX = g++


# Includepfad bestimmen : INCLUDE
#INCLUDE = -I/usr/src/

# Compilerflags : CXXFFLAGS
#CXXFLAGS = $(INCLUDE) -c -D_CFRONT_3_0 -D_REENTRANT -g
CXXFLAGS = -D_REENTRANT -g
COMPILE = $(CXX) $(CXXFLAGS)
###########################################################################################


sasreader: main.o serielle.o CSasTelegram.o
	$(COMPILE) -o sasreader main.o serielle.o CSasTelegram.o
	mkdir -p ./Release
	mv sasreader ./Release/

clean: 
	rm *.o ./Release/sasreader
	echo Clean done

# Kompilieren
#serielle.o : serielle.cpp serielle.h
#	$(COMPILE) serielle.cpp

#main.o : main.cpp
#	$(COMPILE) main.cpp
