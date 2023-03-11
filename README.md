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
sudo make install
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
              --deviceName "ttUSB0" \
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

Command line options:
|long command| short command| argument| description|
| --- | :---: | --- | --- |
|help|         h| no       | |
|start|        s| required | where to start reading (w/o offset)|
|length|       l| required | how many registers to read|
|deviceName|   n| required | e.g. `/dev/ttyUSB0` or shorter `ttyUSB0`|
|baud|         b| required | [bps]|
|parity|       p| required | `N`, `E` or `O`|
|data_bit|     d| required | number of bits of data, the allowed values are 5, 6, 7 and 8|
|stop_bit|     t| required | bits of stop, the allowed values are 1 and 2|
|slave_ad|     a| required | slave address|
|timeout_sec|  e| required | timeout to set in [sec]|
|timeout_usec| u| required | and the [μsec] part. At least 13000, better 20000 (20ms) or 40000|
|loops|        o| required | how many loops of reading. `0` = Inf|
|repTime|      r| required | time between loops [msec]|
|setTerm|      m| required | set termination register. False / 0 or off / 1 or on. Def = false|
|inPlace|      i| required | in inifinite loop mode print registers in place or scroll the screen. Def = false|
|recovery|     c| required | error recovery mode. Default = false|
|debug|        g| required | debug mode. Default = false|
