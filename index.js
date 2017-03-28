const MtpLite = require('./build/Release/MtpLite');

console.log(MtpLite.DelFile(482))

/*
const findLpConfigID = (contents) => {
  return Object.keys(contents).find(key => {
    if (contents[key]['OBJECT_ORIGINAL_FILE_NAME'] === 'Version.59.20170301T2258-GMT.txt') return key;
    return false;
  });
}

let contents = MtpLite.List()[0];
let lpConfigID = findLpConfigID(contents);

console.log(`~~~~> lpConfigID before MTPDelFile ${lpConfigID}`);

let delFileResults = MtpLite.DelFile(lpConfigID);

console.log(`~~~~> DelFile Results:`);
console.log(delFileResults);

let newContents = MtpLite.List()[0];
let newLpConfigID = findLpConfigID(newContents);

if (newLpConfigID) {
  console.log(`~~~~> FAILURE: lpConfig.db3 still exists immediately recreated after the MTP-DelFile operation.`)
  console.log(`~~~~> lpConfigID after MTP-DelFile operation ${newLpConfigID}`);
} else {
  console.log(`~~~> SUCCESS: lpConfig.db3 was not immediately recreated after a MTP-DelFile operation.`)
}
*/
module.exports = MtpLite;
