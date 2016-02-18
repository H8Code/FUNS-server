# Building FUNS-server
`sudo apt install libssl-dev libtool autoconf`

## Building restbed
```git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cd restbed/build
cmake -DBUILD_SHARED=YES ..
make -j 5 install
cd -
```

## Building mongocxx
```git clone -b r1.3 https://github.com/mongodb/mongo-c-driver
cd mongo-c-driver
./autogen.sh
make ; sudo make install
```
