var myaddon = require("./build/Release/matrix.node");

var mat1 = new myaddon.matrix(3, 3);
mat1.setVal(0, 0, 1);
mat1.setVal(0, 1, 2);
mat1.setVal(0, 2, -1);

mat1.setVal(1, 0, 3);
mat1.setVal(1, 1, 4);
mat1.setVal(1, 2, 5);

mat1.setVal(2, 0, 8);
mat1.setVal(2, 1, 6);
mat1.setVal(2, 2, 7);

console.log('\nOriginal matrix:');
var i;
for (i = 0; i < 3; i++) {console.log(mat1.getVal(0, i), mat1.getVal(1, i), mat1.getVal(2, i));}

console.log('\nInverse of original');
var mat2 = mat1.inverse();
for (i = 0; i < 3; i++) {console.log(mat2.getVal(0, i).toFixed(2), mat2.getVal(1, i).toFixed(2), mat2.getVal(2, i).toFixed(2));}

console.log('\nTranspose of original:');
var mat3 = mat1.transpose();
for (i = 0; i < 3; i++) {console.log(mat3.getVal(0, i), mat3.getVal(1, i), mat3.getVal(2, i));}

console.log('\nCofactor matrix of original matrix at position 0, 0:');
var mat4 = mat1.cofactorMatrix(0, 0);
for (i = 0; i < 2; i++) {console.log(mat4.getVal(0, i), mat4.getVal(1, i));}

console.log('\nAdded 10 to each entry in original matrix:');
var mat5 = mat1.addFloat(10);
for (i = 0; i < 3; i++) {console.log(mat5.getVal(0, i), mat5.getVal(1, i), mat5.getVal(2, i));}

console.log('\nMultiplied each entry in original matrix by two:');
var mat6 = mat1.multFloat(2);
for (i = 0; i < 3; i++) {console.log(mat6.getVal(0, i), mat6.getVal(1, i), mat6.getVal(2, i));}

console.log('\nDeterminant of the original matrix:');
var mat7 = mat1.getDet();
console.log(mat7);