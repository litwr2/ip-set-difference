#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <cstdlib>
#include <arpa/inet.h>
using namespace std;

using IPAddress = uint32_t;
using Range = std::pair<IPAddress, IPAddress>;
using Pool = std::list<Range>;

uint32_t conv_ip(const char* s) {
	return htonl(inet_addr(s));  //LSB architectures only!!!
}

int main() {
	set<uint32_t> ipset_n, ipset_o;
	unsigned k, l, t;
        srand(time(0)%777);
	uint32_t start_ip = conv_ip("192.168.0.0");
        ofstream fo1("1"), fo2("2");
	for (int i = 0; i < 500; i++) {
		k = start_ip + (rand()&65535);
		l = rand()%50 + 20;
		for (int i = 0; i < l && k + i < start_ip + 65536; i++)
			ipset_o.insert(k + (t = i));
		{
			in_addr a1 = {htonl(k)}, a2 = {htonl(k + t)};
			fo1 << inet_ntoa(a1);
        	        if (t) fo1 << " - " << inet_ntoa(a2);
			fo1 << endl;
		}
		k = start_ip + (rand()&65535);
		l = rand()%50 + 20;
		for (int i = 0; i < l && k + i < start_ip + 65536; i++)
			ipset_n.insert(k + (t = i));
		{
			in_addr a1 = {htonl(k)}, a2 = {htonl(k + t)};
			fo2 << inet_ntoa(a1);
        	        if (t) fo2 << " - " << inet_ntoa(a2);
			fo2 << endl;
		}
	}
	start_ip = conv_ip("10.0.0.0");
	for (int i = 0; i < 500; i++) {
		k = start_ip + (rand()&((1 << 24) - 1));
		l = rand()%5000 + 2000;
		for (int i = 0; i < l && k + i < start_ip + (1 << 24); i++)
			ipset_o.insert(k + (t = i));
		{
			in_addr a1 = {htonl(k)}, a2 = {htonl(k + t)};
			fo1 << inet_ntoa(a1);
        	        if (t) fo1 << " - " << inet_ntoa(a2);
			fo1 << endl;
		}
		k = start_ip + (rand()&((1 << 24) - 1));
		l = rand()%5000 + 2000;
		for (int i = 0; i < l && k + i < start_ip + (1 << 24); i++)
			ipset_n.insert(k + (t = i));
		{
			in_addr a1 = {htonl(k)}, a2 = {htonl(k + t)};
			fo2 << inet_ntoa(a1);
        	        if (t) fo2 << " - " << inet_ntoa(a2);
			fo2 << endl;
		}
	}
        fo1.close();
        fo2.close();
        fo1.open("3");
        for (auto p = ipset_n.begin(); p != ipset_n.end(); p++)
		ipset_o.erase(*p);
	for (auto p = ipset_o.begin(); p != ipset_o.end(); p++) {
		uint32_t a = *p;
		while (p != ipset_o.end()) {
			std::set<uint32_t>::const_iterator q = p;
			if (*p + 1 == *++q) p++; else break;
		}
		in_addr a1 = {htonl(a)}, a2 = {htonl(*p)};
		fo1 << inet_ntoa(a1);
                if (a != *p) fo1 << " - " << inet_ntoa(a2);
		fo1 << endl;
		if (p == ipset_o.end()) break;
	}
        fo1.close();
	return 0;
}

