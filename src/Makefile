scf4: master writer
	alacritty --hold --command ./master --input-type double & ./writer
	# alacritty --hold --command ./master & ./writer

master: master.cpp
	g++ -o master master.cpp -lm -lrt -lasound -ljack -lpthread -lportaudio -largtable3

writer: writer.c
	gcc -o writer writer.c -lm

# mastertest: master
# 	./master
# test: master writer
# 	./master & ./writer
	
clean:
	rm master writer master.pipe
