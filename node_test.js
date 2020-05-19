let lt = require('./build/librarytest');
var myteststr = lt.cwrap('myteststr', 'string', ['string', 'number']);

function testMain() {
    lt._mytest(5);
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
    var str_cpp = lt.my_cpp_teststr("Hello World!");
    console.log(str_cpp);
}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
