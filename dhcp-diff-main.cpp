#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <arpa/inet.h>
#include "dhcp-diff.h"

uint32_t conv_ip(const char* s) {
	return htonl(inet_addr(s));  //LSB architectures only!!!
}

int main(int argc, char *argv[]) {
	Pool old_pool, new_pool, diff_pool;
	if (argc != 3) {
		std::cerr << "USAGE: dhcp-diff OLD-IP NEW-IP\n";
		return 3;
	}
	std::ifstream fi(argv[1]);
	if (!fi) {
		std::cerr << "no file with old ip addresses\n";
		return 1;
	}
	std::string s1, s2, st;
	while (!fi.eof()) {
		std::getline(fi, st);
		if (st.length() < 7) break;
		std::istringstream is(st);
		if (st.find("-") == std::string::npos) {
			is >> s1;
			old_pool.push_front(std::make_pair<IPAddress, IPAddress>(conv_ip(s1.c_str()), conv_ip(s1.c_str())));
		}
		else {
			is >> s1 >> st >> s2;
			old_pool.push_front(std::make_pair<IPAddress, IPAddress>(conv_ip(s1.c_str()), conv_ip(s2.c_str())));
		}
	}	
	fi.close();
	fi.open(argv[2]);
	if (!fi) {
		std::cerr << "no file with new ip addresses\n";
		return 2;
	}
	while (!fi.eof()) {
		std::getline(fi, st);
		if (st.length() < 7) break;
		std::istringstream is(st);
		if (st.find("-") == std::string::npos) {
			is >> s1;
			new_pool.push_front(std::make_pair<IPAddress, IPAddress>(conv_ip(s1.c_str()), conv_ip(s1.c_str())));
		}
		else {
			is >> s1 >> st >> s2;
			new_pool.push_front(std::make_pair<IPAddress, IPAddress>(conv_ip(s1.c_str()), conv_ip(s2.c_str())));
		}
	}	
	fi.close();
	diff_pool = find_diff(old_pool, new_pool);
	for (Pool::const_iterator p = diff_pool.begin(); p != diff_pool.end(); p++) {
                in_addr a1 = {htonl(p->first)}, a2 = {htonl(p->second)};
		if (p->first == p->second)
			std::cout << inet_ntoa(a1) << std::endl;
                else {
			std::cout << inet_ntoa(a1);
			std::cout << " - " << inet_ntoa(a2) << std::endl;
		}
	}
	return 0;
}

