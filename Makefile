all: master writer

master: master.cpp
	g++ -o master master.cpp -lm -lrt -lasound -ljack -lpthread -lportaudio

writer: writer.c
	gcc -o writer writer.c -lm

clean:
	rm master writer
