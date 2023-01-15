# comand - COMpress and ANalyze Data

## Contents

- [Overview](#overview)

- [Getting started](#getting-started)

- [License](#license)

---

## Overview

`comand` uses IPC through shared memory and Huffman coding to compress and decompress data. No third-party libraries are used, only pure C.

This project is composed of two programs: `encoder` and `decoder`. `encoder` reads the data, compress it and shares it using a shared memory segment. `decoder` will decompress the compressed data, sending it back to the first program - which will print the received stats.

Since it was an one-week challenge, `comand` is a relatively small program:

```shell

.
├── Makefile
├── include
│   └── comand.h
├── lib
│   ├── comand_ipc
│   │   ├── c_ipc.c
│   │   ├── c_ipc.h
│   │   └── Makefile
│   └── huffman
│       ├── huffman_ds.c
│       ├── huffman_ds.h
│       └── Makefile
└── src
    ├── decoder
    │   ├── decoder.c
    │   ├── decoder.h
    │   ├── decompress.c
    │   └── Makefile
    └── encoder
        ├── compress.c
        ├── encoder.c
        ├── encoder.h
        ├── input.c
        └── Makefile

```

---

## Getting started

After cloning this repository, run:

```shell
make
```

You can now run `encoder`:

```shell
./src/encoder/encoder "text to be " "compressed " "!!!!!"

# Alternatively, run it with '--file' option, to compress
# the contents of a given file
./src/encoder/encoder --file file_to_have_its_contents_compressed
```


After compressing the data, it will send it to `decoder` and start to wait for feedback, so you can run `decoder`:

```shell
./src/decoder/decoder
```

`encoder` will print received stats such as the decompressed data and its total bytes, total of compressd bytes and time used to decompress.

---

## License

`comand` is licensed under the terms of the 'license link'.
