# ip-set-difference
These programs calculate the difference between two IP sets, they may be helpful with DHCP configure.
There is also a test suite for thorough testing provided.

Use `make' to build the programs and `make test' for test them.

Input data has the format like:

192.168.2.1 - 192.168.128.255

10.1.1.5 - 10.1.2.128

192.168.1.2

10.1.2.100 - 10.1.2.255

10.127.2.200 - 10.255.2.255

10.1.1.1 - 10.255.255.255

(an additional line break is added to the end of each line to a proper view with github).

