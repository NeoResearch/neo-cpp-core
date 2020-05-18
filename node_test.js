let lt = require('./build/librarytest');
var myteststr = lt.cwrap('myteststr', 'string', ['string', 'number']);

function testMain() {
    lt._mytest(5);
    var shello = 'hello';
    var str = myteststr(shello, shello.length);
    console.log(str);
}

// ----------- wait until loading ----------

setTimeout(function () {
    testMain()
}, 500);
