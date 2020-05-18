let lt = require('./build/librarytest');
var myteststr = lt.cwrap('myteststr','string', ['string']);

function testMain() {
    lt._mytest(5);
    var str = myteststr('hello');
    console.log(str);
}

setTimeout(function () {
    testMain()
}, 500);

//testMain()
