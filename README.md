# File Controller

File controller can recursive register files and track their integrity.


## Build and Run

Install OpenSSL and run `make`.

Run program with `./bin/controller`


```bash
    make
    ./bin/controller --help
```



Integrity table is stored in `./control-list.txt`

## Using Nix

If you're using Nix, you can use nix-shell to build and run the program with:
```bash
nix-shell 
./bin/controller --help
```

