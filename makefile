ypcal: main.cpp
	$(CXX) -Wall -Werror -Wextra -Wold-style-cast -pedantic -I date/include --std=c++20 $^ -o $@
