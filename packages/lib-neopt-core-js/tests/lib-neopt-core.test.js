jest.setTimeout(30000);
describe('Compilation', () => {
  beforeAll(async () => {
    await page.goto('http://127.0.0.1:8080');
  });


  test('testConversionToVerification', async () => {
    await testCompilation();
  });

  // testing with function defined elsewhere... more verbose...
  test('test_Neo3_Wallets_wHelper_ToAddress', async () => {
    await test_Neo3_Wallets_wHelper_ToAddress();
  });

  // inline testing... simpler!
  test('test_Neo3_Wallets_wHelper_ToScriptHash', async () => {
    await async function () {
      await delay(100);
      const output = await page.evaluate(
        () => Neo3CppLib.Neo3_Wallets_wHelper_ToScriptHash("NSh6STZ6K4jUVDNZHwYSLc4ViuEm9Q1JtU")
      );
      expect(output).toBe("0x0eec9e10f6491c39f3e8dbc8af7186282487594a");
    }
  });



});

async function testCompilation() {
  await delay(100);
  const output = await page.evaluate(() => testConversionToVerification());
  expect(output).toBe("out='0c210230ef7722574ce16e2fce6cf36a05f64786d83f8282ce3db90067a32e6852cc000b418a6b1e75'");
}



async function test_Neo3_Wallets_wHelper_ToAddress() {
  await delay(100);
  const output = await page.evaluate(
    () => Neo3CppLib.Neo3_Wallets_wHelper_ToAddress("0x0eec9e10f6491c39f3e8dbc8af7186282487594a")
  );
  expect(output).toBe("NSh6STZ6K4jUVDNZHwYSLc4ViuEm9Q1JtU");
}



function delay(time) {
  return new Promise(function (resolve) {
    setTimeout(resolve, time)
  });
}