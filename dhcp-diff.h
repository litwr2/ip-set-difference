#ifndef DHCP_DIFF_H
#define DHCP_DIFF_H

#include <cstdint>
#include <list>

using IPAddress = uint32_t; //IPv4
using Range = std::pair<IPAddress, IPAddress>; //IP-range, the border values  are included
using Pool = std::list<Range>; //IP-ranges, they can interset, their order is arbitrary

Pool find_diff(const Pool&, const Pool&);
#endif

