#!/bin/bash

(cd ../../src && grep -rh "NEO3API" . | grep "Neo::")
