# Building FUNS-server
`sudo apt install git libssl-dev libtool autoconf cmake libmhash-dev gcc g++ pkg-config`

## Building restbed
```bash
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake -DBUILD_SHARED=YES ..
make -j 5 install
cd -
```

## Building mongocxx
```bash
git clone -b r1.3 https://github.com/mongodb/mongo-c-driver
cd mongo-c-driver
./autogen.sh
make ; sudo make install
cd -

git clone -b master https://github.com/mongodb/mongo-cxx-driver
cd mongo-cxx-driver/build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
make -j 5 ; sudo make install
cd -
```

## Building sources
```bash
git clone --recursive https://github.com/H8Code/FUNS-server.git
mkdir build
cd build
cmake ../FUNS-server
make -j 5
```
