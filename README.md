# ReadEncoder for SRT
Reading encoder module for [SRT: The Small Radio Telescope](https://www.haystack.mit.edu/haystack-public-outreach/srt-the-small-radio-telescope-for-education/).


## Software prerequisites
* git (for installation)
* cmake (for installation)
* Doxygen (for documentation, optional)
* [modbus library](https://github.com/stephane/libmodbus)
* [SRT software](https://www.haystack.mit.edu/haystack-public-outreach/srt-the-small-radio-telescope-for-education/)

## Installation:
Example installation commands:
```
mkdir build/
cd build/
cmake -DCMAKE_INSTALL_PREFIX="/opt/ReadEncoder/" -DCMAKE_BUILD_TYPE="Release" -DBUILD_DOC=OFF ../
make
make install
```

## Run:
E.g.:
```
./ReadEncoder -s 1 -l 2 -n "ttyUSB0" -b 19200 -p 'E' -d 8 -t 1 -a 127 -e 1 -u 0 -o 1 -r 0 -c 1 -g 1
```
or the same in longer version:
```
./ReadEncoder --start 1 \
              --length 2 \
              --deviceName "ttyUSB0" \
              --baud 19200 \
              --parity 'E' \
              --data_bit 8 \
              --stop_bit 1 \
              --slave_ad 127 \
              --timeout_sec  1 \
              --timeout_usec 0 \
              --loops 1 \
              --repTime 0 \
              --recovery true \
              --debug true
```

Command line options:\
{"help",         no_argument,       0,  'h' },
{"start",        required_argument, 0,  's' },  // where to start reading (w/o offset)\
{"length",       required_argument, 0,  'l' },  // how many registers to read\
{"deviceName",   required_argument, 0,  'n' },  // e.g. "/dev/ttyUSB0" or shorter "ttyUSB0"\
{"baud",         required_argument, 0,  'b' },  // [bps]\
{"parity",       required_argument, 0,  'p' },  // 'N', 'E' or 'O'\
{"data_bit",     required_argument, 0,  'd' },  // number of bits of data, the allowed values are 5, 6, 7 and 8\
{"stop_bit",     required_argument, 0,  't' },  // bits of stop, the allowed values are 1 and 2\
{"slave_ad",     required_argument, 0,  'a' },  // slave address\
{"timeout_sec",  required_argument, 0,  'e' },  // timeout to set in [sec]\
{"timeout_usec", required_argument, 0,  'u' },  // and the [μsec] part. At least 13000, better 20000 (20ms)\
{"loops",        required_argument, 0,  'o' },  // how many loops of reading
{"repTime",      required_argument, 0,  'r' },  // time between loops [msec]\
{"recovery",     required_argument, 0,  'c' },  // error recovery mode. Default = false\
{"debug",        required_argument, 0,  'g' },  // debug mode. Default = false