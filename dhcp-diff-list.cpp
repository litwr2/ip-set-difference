#include <utility>
#include "dhcp-diff.h"

//A function which calculates the difference between old and new pools of IP addresses
//it may be slow for large number of IP-address ranges
Pool find_diff(const Pool& old_pool0,const Pool& new_pool0)
{
	Pool old_pool(old_pool0), new_pool(new_pool0);
	old_pool.sort();
	new_pool.sort();
	for (Pool::iterator p = old_pool.begin(); p != old_pool.end(); p++) {
		Pool::iterator q;
		for (;;) {
			q = p;
			++q;
			if (q == old_pool.end()) break;
			if (p->second + 1 >= q->first) {
				if (q->second > p->second) p->second = q->second;
				old_pool.erase(q);
			}
			else break;
		}
	}
	for (Pool::iterator p = new_pool.begin(); p != new_pool.end(); p++) {
		Pool::iterator q;
		for (;;) {
			q = p;
			++q;
			if (q == new_pool.end()) break;
			if (p->second + 1 >= q->first) {
				if (q->second > p->second) p->second = q->second;
				new_pool.erase(q);
			}
			else break;
		}
	}
	for (Pool::iterator p = new_pool.begin(); p != new_pool.end();) {
		for (Pool::iterator q = old_pool.begin(); q != old_pool.end(); q++) {
			if (p->first <= q->first && p->second >= q->second) {
				old_pool.erase(q);
				goto L;
			}
			else if (p->first > q->first && p->second < q->second) {
				old_pool.insert(q, std::make_pair<IPAddress, IPAddress>((IPAddress)q->first, p->first - 1));
				q->first = p->second + 1;
				break;
			}
			else if (p->first > q->first && p->first <= q->second && p->second >= q->second)
				q->second = p->first - 1;
			else if (p->first <= q->first && p->second < q->second && p->second >= q->first) {
				q->first = p->second + 1;
				break;
			}
		}
		p++;
L:;
	}
	return old_pool;
}

