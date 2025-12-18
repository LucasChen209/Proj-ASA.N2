camioes: camioes.cpp
		g++ -std=c++11 -o camioes -Wall camioes.cpp -lm

clean:
		rm -f camioes

run:
		time ./camioes < testfile