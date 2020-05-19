mergeInto(
  LibraryManager.library, {
    mycrypto: function(vint) {
      //alert('mycrypto(value='+vint+')');
      console.log('mycrypto print: ' + vint);
      return vint+1;
    },
    bignum_add: function(ptr_str1, ptr_str2) {
      vstr1 = Module.UTF8ToString(ptr_str1);
      vstr2 = Module.UTF8ToString(ptr_str2);
      console.log("js bignum_add: "+vstr1+" "+vstr2);
      
      Module['mytestf'] = function(){
        console.log("oi");
      };
      //console.log(BN);
      var b1 = new BN(vstr1);
      var b2 = new BN(vstr2);
      var b3 = b1.add(b2);
      return b3.toString(10); // string
    }
  }
);