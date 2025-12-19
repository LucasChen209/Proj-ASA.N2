camioes: camioest.cpp
		g++ -std=c++11 -o camioes -Wall camioest.cpp -lm

clean:
		rm -f camioes

run:
		time ./camioes < testfile