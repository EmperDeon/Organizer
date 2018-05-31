## Dependant on
- Qt >= 5.5

## Common
```
git clone git@github.com:EmperDeon/Organizer.git
cd Organizer
git submodule init
git submodule update
```


### CMake
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
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
