c:
	rm wheel

w:
	g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic -O3 -DNDEBUG main.cpp -o wheel
