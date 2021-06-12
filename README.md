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
./ReadEncoder -s 1 -l 2 -n "ttyUSB0" -b 19200 -p 'E' -d 8 -t 1 -a 127
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
              --slave_ad 127
```

Command line options:\
{"help",       no_argument,       0,  'h' }\
{"start",      required_argument, 0,  's' }\
{"length",     required_argument, 0,  'l' }\
{"deviceName", required_argument, 0,  'n' }\
{"baud",       required_argument, 0,  'b' }\
{"parity",     required_argument, 0,  'p' }\
{"data_bit",   required_argument, 0,  'd' }\
{"stop_bit",   required_argument, 0,  't' }\
{"slave_ad",   required_argument, 0,  'a' }