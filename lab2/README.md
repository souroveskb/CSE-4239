### This is an implementation of Matrix operation using rpc on a client server architecture using rpcgen in ubuntu


## I faced some issues while running rpc generated code in my machine and these article helped me sovle the issue
<!-- [error compiling rpc.h](https://answers.launchpad.net/mg5amcnlo/+question/704526)   -->


We need to install these packages in our system
```bash
sudo apt-get install libntirpc-dev rpcgen
```
Check if the rpc folder only contains netdb.h
```bash
ls /usr/include/rpc
```
[for ubuntu 22.0++ change the makefile](https://stackoverflow.com/questions/75128485/undefined-reference-to-xdr-int)  

```js
CFLAGS += -g 
LDLIBS += -ltirpc
RPCGENFLAGS = 
```

Then copy the files from tirpc/rpc to rpc
```bash
sudo cp /usr/include/tirpc/rpc/* /usr/include/rpc/
sudo cp /usr/include/tirpc/netconfig.h /usr/include/
```
Then run rpcgen from start. this should solve the problem