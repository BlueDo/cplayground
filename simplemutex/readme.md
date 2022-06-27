# simplemutex
A proof of concept of Mutexes in C.  
Creates a few threads, each with sub jobs. Each subjob cannot be worked on at the same time, so the threads line up for each subjob. 

## Running
```
make build
./demo.out
make clean
```