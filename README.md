# DragonTCP

### What is DragonTCP?

DragonTCP is a simple C++ TCP communication library licensed under the GNU 
GPLv3 license. It is a cross-platform library and can be installed on any 
ystem due to the use of the cmake build system and the boost asio library. 

### What makes DragonTCP different from other TCP communication libraries?

We often have to send data over the network with different purposes to another 
computer. It can be challenging to determine on the other side what's the 
purpose of a specific data. To tackle this, many programs use multiple sockets 
on different ports and send all data with a specific purpose on a specific 
port. However, this is very inefficient since we will begin using more and 
more ports as we have to send more and more data with many different purposes. 
For this reason, all data sent with DragonTCP on a socket must have and id and 
a message, meaning the id will specify the purpose of the data and message 
will be the main data being sent. This can make TCP network communication 
possible with data with many different purposes on the same socket. 

## Getting started

### Installation - Linux/Unix/Cygwin

First, make sure cmake, a make utility (e.g. GNU make, BSD make), boost libraries, and git is installed.

If you're using Cygwin, omit ```sudo``` in commands that  use it.

Enter these commands in the terminal:

```
git clone https://github.com/gaborszita/DragonTCP
cd DragonTCP
mkdir build
cd build
cmake ../ -G "Unix Makefiles"
sudo make install
```

### Examples

The examples are located in the examples folder. After you installed 
DragonTCP, you can build and run these examples.

First, make sure you're in the base DragonTCP folder where you cloned the git 
repository.

Enter these commands in the terminal:
```
cd examples
mkdir build
cd build
cmake ../ -G "Unix Makefiles"
make
```

Now, you should have two executables: Server and Client. First run Server in 
one command window and **after** that run Client in *another* command window. 
They should connect to each other and give you a prompt 
Enter command: . 

There are three commands available: read, send, and disconnect. 

- ```read``` prints out the data received
- ```send``` sends data and asks you the id and message of the data
- ```disconnect``` disconnects from the socket

### Writing your own program

When you write you're own program that uses DragonTCP include the 
DragonTCP/DragonTCP.hpp header file. This includes all the classes 
that you need to use DragonTCP. When linking your program link the DragonTCP 
and pthread libraries. 

For example, here's how to link the mainclient.cpp file using the GNU C++ 
compiler:

```g++ -std=c++11 -o mainclient mainclient.cpp -lDragonTCP -lpthread```

### Documentation

Detailed documentation is at [https://gaborszita.github.io/DragonTCP/](https://gaborszita.github.io/DragonTCP/).

## Troubleshooting

- Check if your firewall is blocking network connections from your executables
- Check if the port you're using isn't already in use

### Uninstallation

If you'd like to uninstall DragonTCP, go to the directory where you built it 
(if you followed this tutorial, it is build), and enter this command:

```sudo xargs rm < install_manifest.txt```
