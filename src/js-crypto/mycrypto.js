mergeInto(
  LibraryManager.library, {
    mycrypto: function(vint) {
      //alert('mycrypto(value='+vint+')');
      console.log('mycrypto print: ' + vint);
      return vint+1;
    }
  }
);