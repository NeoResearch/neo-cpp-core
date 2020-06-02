#!/bin/bash

# functions with EXPORT_NEO3API prefix (in Neo:: explicit namespace) will be automatically exported
# we expect these functions to be string -> string, so if signature is not this, export manually on .cpp file

echo "Listing EXPORT_NEO3API methods (remember to include Neo:: scope and auto-export only string->string methods)"
echo ""
(cd ../../src && grep -rh "EXPORT_NEO3API" . | grep "Neo::")

echo ""
BASEFILE=src/lib-neopt-core-js.cpp
OUTFILE=src/lib-neopt-core-js.autogen.cpp
#
BASEFILE_JS=src/index.js
OUTFILE_JS=src/index.autogen.js
#
echo "Adding these to '$OUTFILE' file"
echo "// AUTOMATICALLY GENERATED FILE - DO NOT EDIT THIS" > $OUTFILE
echo "// AUTOMATICALLY GENERATED FILE - DO NOT EDIT THIS" > $OUTFILE_JS
cat   $BASEFILE  >>  $OUTFILE
cat   $BASEFILE_JS  >>  $OUTFILE_JS
#
for func in `(cd ../../src && grep -rh "EXPORT_NEO3API" . | grep "Neo::" | cut -d '(' -f1 )`; do
    #
    func1=${func/Neo::/Neo3::}
    func2=${func1/EXPORT_NEO3API_}  # remove EXPORT_NEO3API_
    #
    func4=$(echo $func2 | sed "s/::/\_/g")
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
    echo "return $func(std::string(cs_in)).c_str();" >> $OUTFILE
    echo "}" >> $OUTFILE
    #
    # js part
    #
    echo "" >> $OUTFILE_JS
    echo "// this method was automatically imported" >> $OUTFILE_JS
    echo "export const $func4 =" >> $OUTFILE_JS
    echo "   mymodule.cwrap('$func4', 'string', ['string']);" >> $OUTFILE_JS
done