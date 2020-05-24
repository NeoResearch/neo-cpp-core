## neo3-cpp-core



```
git submodule update --init --recursive
git submodule update --recursive
```

### Testing the prototype

This is still a prototype, but quite advanced on both C++ and JS!

- To test C++ implementation, just type `make` (and run `./build/app_main`).
- To test JS implementation, just type `make jstest` (it will build everything and run `node_test.js`)


## Dependencies

This project has very interesting dependencies. We need external:

- BigInteger library
- Cryptography library

### BigInteger

From C++ perspective, we use [csBigInteger-cpp](https://github.com/neoresearch/csBigInteger-cpp), that uses GNU MP (GMP) in background (or optionally, Mono BigInteger implementation).

From JS perspective, we use [csBigInteger.js](https://github.com/neoresearch/csBigInteger.js), that also uses [bn.js](https://github.com/indutny/bn.js) in background.

### Cryptography

From C++ perspective, we use [libcrypton](https://github.com/neoresearch/libcrypton), that uses OpenSSL in background (or optionally, Crypto++ implementation from Wei Dai).

From JS perspective, we use [crypto-js](https://github.com/brix/crypto-js) for SHA256, but we may also use [elliptic](https://github.com/indutny/elliptic) to double-check elliptic curves.
