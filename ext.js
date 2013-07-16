var myaddon = require("./build/Release/matrix.node");

var myMatrix = new myaddon.matrix(3, 3);
myMatrix.setValJ(0, 0, 1);
myMatrix.setValJ(0, 1, 2);
myMatrix.setValJ(0, 2, -1);

myMatrix.setValJ(1, 0, 3);
myMatrix.setValJ(1, 1, 4);
myMatrix.setValJ(1, 2, 5);

myMatrix.setValJ(2, 0, 8);
myMatrix.setValJ(2, 1, 6);
myMatrix.setValJ(2, 2, 7);

console.log('Original matrix:');
console.log(myMatrix.getValJ(0, 0), myMatrix.getValJ(1, 0), myMatrix.getValJ(2, 0));
console.log(myMatrix.getValJ(0, 1), myMatrix.getValJ(1, 1), myMatrix.getValJ(2, 1));
console.log(myMatrix.getValJ(0, 2), myMatrix.getValJ(1, 2), myMatrix.getValJ(2, 2));
console.log('\nInverse of original');

var myInv = myMatrix.inverseJ();
console.log(myInv.getValJ(0, 0), myInv.getValJ(1, 0), myInv.getValJ(2, 0));
console.log(myInv.getValJ(0, 1), myInv.getValJ(1, 1), myInv.getValJ(2, 1));
console.log(myInv.getValJ(0, 2), myInv.getValJ(1, 2), myInv.getValJ(2, 2));
console.log('\nTranspose of original:');

var myM1 = myMatrix.transposeJ();
console.log(myM1.getValJ(0, 0), myM1.getValJ(1, 0), myM1.getValJ(2, 0));
console.log(myM1.getValJ(0, 1), myM1.getValJ(1, 1), myM1.getValJ(2, 1));
console.log(myM1.getValJ(0, 2), myM1.getValJ(1, 2), myM1.getValJ(2, 2));
console.log('\nCofactor matrix of original matrix at position 0, 0:');

var myM2 = myMatrix.cofactorMJ(0, 0);
console.log(myM2.getValJ(0, 0), myM2.getValJ(1, 0));
console.log(myM2.getValJ(0, 1), myM2.getValJ(1, 1));

