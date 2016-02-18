# Building FUNS-server

`sudo apt install libssl-dev`

## Building restbed
`
git clone --recursive https://github.com/corvusoft/restbed.git
mkdir restbed/build
cmake -DBUILD_SHARED=YES ..
make -j 5 install
`
