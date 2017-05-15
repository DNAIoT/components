# DNA Components
DNA framework components.

## compile example tests
- make sure you are you have gcc installed on your system,
- go to the project directory and issue:

gcc -Wall test.c framework/configuration.c framework/request.c framework/response.c framework/tcpclient.c framework/udpclient.c framework/serviceagent.c -o test

- execute tests by running:

./test y y y
(Note: type n for each y you don't wish to run, ommiting y's will result in discarding test)


## building server
- to build TCP server, run:

gcc -Wall tcpserver.c -o tcpserver
- to build UDP server, run:

gcc -Wall udpserver.c -o udpserver
## running server
- TCP:

./tcpserver
- UDP:

./udpserver
