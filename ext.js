var myaddon = require("./build/Release/matrix.node");

var mat1 = new myaddon.matrix(3, 3);
mat1.setValJ(0, 0, 1);
mat1.setValJ(0, 1, 2);
mat1.setValJ(0, 2, -1);

mat1.setValJ(1, 0, 3);
mat1.setValJ(1, 1, 4);
mat1.setValJ(1, 2, 5);

mat1.setValJ(2, 0, 8);
mat1.setValJ(2, 1, 6);
mat1.setValJ(2, 2, 7);

console.log('\nOriginal matrix:');

var i;
for (i = 0; i < 3; i++) {console.log(mat1.getValJ(0, i), mat1.getValJ(1, i), mat1.getValJ(2, i));}

console.log('\nInverse of original');
var mat2 = mat1.inverseJ();
for (i = 0; i < 3; i++) {console.log(mat2.getValJ(0, i).toFixed(2), mat2.getValJ(1, i).toFixed(2), mat2.getValJ(2, i).toFixed(2));}

console.log('\nTranspose of original:');
var mat3 = mat1.transposeJ();
for (i = 0; i < 3; i++) {console.log(mat3.getValJ(0, i), mat3.getValJ(1, i), mat3.getValJ(2, i));}

console.log('\nCofactor matrix of original matrix at position 0, 0:');
var mat4 = mat1.cofactorMJ(0, 0);
for (i = 0; i < 2; i++) {console.log(mat4.getValJ(0, i), mat4.getValJ(1, i));}

console.log('\nAdded 10 to each entry in original matrix:');
var mat5 = mat1.addFloatJ(10);
for (i = 0; i < 3; i++) {console.log(mat5.getValJ(0, i), mat5.getValJ(1, i), mat5.getValJ(2, i));}

console.log('\nMultiplied each entry in original matrix by two:');
var mat6 = mat1.multFloatJ(2);
for (i = 0; i < 3; i++) {console.log(mat6.getValJ(0, i), mat6.getValJ(1, i), mat6.getValJ(2, i));}