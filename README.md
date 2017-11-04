# ip-set-difference
These programs calculate the difference between two IP sets, they may be helpful with DHCP configure.
There is also a test suite for thorough testing provided.

Use **make** to build the programs and **make test** for testing them.

Input data has the format like:
```
192.168.2.1 - 192.168.128.255
10.1.1.5 - 10.1.2.128
192.168.1.2
10.1.2.100 - 10.1.2.255
10.127.2.200 - 10.255.2.255
10.1.1.1 - 10.255.255.255
```

See also a file **ip-data.txt** for the example of the data format.

