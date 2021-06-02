# ReadEncoder for SRT
Reading encoder module for [SRT: The Small Radio Telescope](https://www.haystack.mit.edu/haystack-public-outreach/srt-the-small-radio-telescope-for-education/).


## Software prerequisites
* git (for installation)
* cmake (for installation)
* Doxygen (for documentation, optional)
* WCSLIB
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
```
./ReadEncoder
```
Command line options:
* h for help
* c for connection attempt