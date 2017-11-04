#include <set>
#include <utility>
#include "dhcp-diff.h"

//A function which calculates the difference between old and new pools of IP addresses
//it may be slow for large number of IP-addresses
Pool find_diff(const Pool& old_pool, const Pool& new_pool)
{
	Pool result;
	std::set<IPAddress> result_set;
	for (Pool::const_iterator p = old_pool.begin(); p != old_pool.end(); p++)
		for (IPAddress k = p->first; k <= p->second; k++) 
			result_set.insert(k);
	for (Pool::const_iterator p = new_pool.begin(); p != new_pool.end(); p++)
		for (IPAddress k = p->first; k <= p->second; k++)
			result_set.erase(k);
	for (std::set<IPAddress>::const_iterator p = result_set.begin(); p != result_set.end(); p++) {
		IPAddress a = *p;
		while (p != result_set.end()) {
			std::set<IPAddress>::const_iterator q = p;
			if (*p + 1 == *++q) p++; else break;
		}
		result.push_back(std::make_pair<IPAddress, IPAddress>((IPAddress)a, (IPAddress)*p));
		if (p == result_set.end()) break;
	}
	return result;
}

