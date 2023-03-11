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
./ReadEncoder -s 1 -l 2 -n "ttyUSB0" -b 19200 -p 'E' -d 8 -t 1 -a 127 -e 0 -u 40000 -o 1 -r 0 -i 1 -c 1 -g 1
```
or the same in a longer version:
```
./ReadEncoder --start 1 \
              --length 2 \
              --deviceName "ttyUSB0" \
              --baud 19200 \
              --parity 'E' \
              --data_bit 8 \
              --stop_bit 1 \
              --slave_ad 127 \
              --timeout_sec  0 \
              --timeout_usec 40000 \
              --loops 1 \
              --repTime 0 \
              --setTerm false \
              --inPlace false \
              --recovery true \
              --debug true
```

Command line options:\
help         no_argument,         'h'\
start        required_argument,   's'     where to start reading (w/o offset)\
length       required_argument,   'l'     how many registers to read\
deviceName   required_argument,   'n'     e.g. "/dev/ttyUSB0" or shorter "ttyUSB0"\
baud         required_argument,   'b'     [bps]\
parity       required_argument,   'p'     'N', 'E' or 'O'\
data_bit     required_argument,   'd'     number of bits of data, the allowed values are 5, 6, 7 and 8\
stop_bit     required_argument,   't'     bits of stop, the allowed values are 1 and 2\
slave_ad     required_argument,   'a'     slave address\
timeout_sec  required_argument,   'e'     timeout to set in [sec]\
timeout_usec required_argument,   'u'     and the [μsec] part. At least 1300 better 20000 (20ms) or 40000\
loops        required_argument,   'o'     how many loops of reading. 0 = Inf\
repTime      required_argument,   'r'     time between loops [msec]\
setTerm      required_argument,   'm'     set termination register. False / 0 or off / 1 or on. Def = false\
inPlace      required_argument,   'i'     in inifinite loop mode print registers in place or scroll the screen. Def = false.\
recovery     required_argument,   'c'     error recovery mode. Default = false\
debug        required_argument,   'g'     debug mode. Default = false