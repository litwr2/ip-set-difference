CXXFLAGS = -O3 -s -std=c++11
#CXXFLAGS = -g -std=c++11

results = dhcp-diff-list dhcp-diff-set gen-test-case

all: $(results)

dhcp-diff-list: dhcp-diff-list.o dhcp-diff-main.o
	c++ -o $@ $^

dhcp-diff-set: dhcp-diff-set.o dhcp-diff-main.o
	c++ -o $@ $^

dhcp-diff-main.o: dhcp-diff-main.cpp

dhcp-diff-list.o: dhcp-diff-list.cpp

dhcp-diff-set.o: dhcp-diff-set.cpp

gen-test-case: gen-test-case.cpp

test:
	./test-case.sh

clean:
	rm -f $(results) gen-test-case *.o
	rm -rf test[0-9]
