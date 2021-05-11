all: master writer

master: master.cpp
	g++ -o master master.cpp -lm -lrt -lasound -ljack -lpthread -lportaudio

writer: writer.c
	gcc -o writer writer.c -lm

mastertest: master
	./master
test: master writer
	./master & ./writer
	
clean:
	rm master writer
