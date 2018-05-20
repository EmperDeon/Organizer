```
git clone git@github.com:EmperDeon/Organizer.git
cd Organizer
git submodule init
git submodule update
mkdir build && cd build
cmake ..
make Organizer_unity
```

### Errors
`cmake ..` couldn't find Qt5 - maybe use `hunter` ?
Test with default Qt5.5 in Ubuntu
