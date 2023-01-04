CC=g++
CFLAGS=-Wall -std=c++17
BINS=tarea prueba patrones
all: clean tarea 

tarea:
	$(CC) $(CFLAGS) -o tarea tarea.cpp
	
clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)
