#!/bin/bash

# functions with EXPORT_NEO3API prefix (in Neo:: explicit namespace) will be automatically exported
# we expect these functions to be string -> string, so if signature is not this, export manually on .cpp file

echo "Listing EXPORT_NEO3API methods (remember to include Neo:: scope)"
echo ""
(cd ../../src && grep -rh "EXPORT_NEO3API" . | grep "Neo::")

echo ""
OUTFILE=lib-neopt-core-js.tmp.cpp
echo "Adding these to $OUTFILE file"
cp   src/lib-neopt-core-js.cpp   $OUTFILE
#
for func in `(cd ../../src && grep -rh "EXPORT_NEO3API" . | grep "Neo::" | cut -d '(' -f1 )`; do
    #
    func2=${func/EXPORT_NEO3API_}  # remove EXPORT_NEO3API_
    #echo $func2
    func3=${func2/Neo::/Neo3::}
    #echo $func3
    func4=$(echo $func3 | sed "s/::/\_/g")
    #echo $func4
    # ======================
    # writing to output file
    #
    echo "Exporting method '$func2' into C version '$func4'..."
    #
    echo "" >> $OUTFILE
    echo "// this method was automatically exported" >> $OUTFILE
    echo "EMSCRIPTEN_KEEPALIVE" >> $OUTFILE
    echo "extern \"C\" const char*" >> $OUTFILE
    echo "$func4(const char* cs_in) {" >> $OUTFILE
    echo "return $func2(std::string(cs_in)).c_str();" >> $OUTFILE
    echo "}" >> $OUTFILE
done