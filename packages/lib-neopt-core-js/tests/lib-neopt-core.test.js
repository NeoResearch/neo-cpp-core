jest.setTimeout(30000);
describe('Compilation', () => {
  beforeAll(async () => {
    await page.goto('http://127.0.0.1:8080');
  });

  
  test('testConversionToVerification', async () => {
    await testCompilation();
  });

});

async function testCompilation(){
    await delay(100);
    const output = await page.evaluate(() => testConversionToVerification());
    expect(output).toBe("out='0c210230ef7722574ce16e2fce6cf36a05f64786d83f8282ce3db90067a32e6852cc000b418a6b1e75'");
}

function delay(time) {
   return new Promise(function(resolve) {
       setTimeout(resolve, time)
   });
}