### This is an implementation for a server-client Knock knock jokes in c++

## File structure
The folder contains server side code (server.cpp), client side code (client.cpp), test cases (testcases.cpp) and the jokes in a JSON file(jokes.json)

## Installation 
As I've used jsoncpp library we need to install the library in our unix/linux devices. To install it in ubuntu platform we need to run the following command.

```bash
make install
```

## Server Run
To run the server we'd need to run the following command in our terminal.

```bash
make runserver
```

## Client Run
To run the client instances we'd need to run the following command in our terminal

```bash
make runclient
```

## Test cases
Hardcoded test cases are implemented from the client side codebase. There are three instances for which test case can be run using the following command.

```bash
make test
```

## Cleaning up
To clean up after executing the code we can run the following command in our terminal.

```bash
make clean
```

The jokes are taken from mostly chatgpt.