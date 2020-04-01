ypcal: main.cpp
	$(CXX) -Wall -Werror -Wextra -I date/include --std=c++20 $^ -o $@
