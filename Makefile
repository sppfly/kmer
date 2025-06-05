main: main.cpp
	g++ main.cpp -o main -Werror -Wall -std=c++20

clean:
	rm -rf main