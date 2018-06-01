## Dependant on
- Qt >= 5.5

## Common
```
sudo apt install qtbase5-dev libboost-regexp-dev libssl-dev
git clone git@github.com:EmperDeon/Organizer.git
cd Organizer
git submodule init
git submodule update
```


### CMake
```
mkdir build && cd build
cmake ..
make Organizer_unity
```


## QMake
```
cd vendor
mkdir build && mkdir libs && cd build

qmake ../simple_ossl.pro
make
mv libsimple_ossl.a ../libs

qmake ../cpp-markdown.pro
make
mv libmarkdown.a ../libs

cd ../../build
qmake ../Organizer.pro
make
```


### Tested with
- Ubuntu 16 (Qt 5.5.1)
- Ubuntu 18 (Qt 5.9.3)
- Qt 5.11 build from source
