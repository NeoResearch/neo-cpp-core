const lt = require('./build/librarytest');

function mainTest()
{
    lt._mytest()
}

setTimeout(function() {
    mainTest()
    , 500
})
