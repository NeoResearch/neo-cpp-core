let lt = require('./build/librarytest');

function testMain()
{
    lt._mytest(5);
}

setTimeout(function() {
    testMain()
}, 500);

//testMain()
