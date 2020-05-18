mergeInto(
  LibraryManager.library, {
    mycrypto: function(vint) {
      alert('mycrypto(value='+vint+')');
      return vint+1;
    },
  }
);