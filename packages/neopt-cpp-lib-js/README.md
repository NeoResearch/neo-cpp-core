# neopt-cpp-lib  (in JS)

This subproject of `neo3-cpp-core` intends to provide a library available for javascript users (and other subprojects such as `neopt-sdk-js`).

## Rationale

The idea behind the library construction process is the following:

- construct a `js+wasm` version of cpp core via `emscripten` (v1.39.4 in docker)
- bundling it into a single library (including its js dependencies `crypto-js` and `csbiginteger`)

### Build Process

To build it, just type `npm run start` (temporary `js+wasm` will be put on `build/` and final lib on `dist/`).

## How to use it

...


## License

All provided binaries can be used freely.
These are NOT tested after bundling, so you MUST test them in your own project!

**MIT License**

*NeoResearch 2020*
