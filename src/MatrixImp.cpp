#include <iostream>
#include <node.h>
#include "Matrix.h"
#include <math.h>

using namespace v8;

/////////////////////////////////////////////
//Constructor.
matrix::matrix(int w, int h) {
	height = h;
	width = w;
	int j;

	//Sets the height and width.
	mat = new float* [width];
	for (j = 0; j < width; j++) {
		mat[j] = new float[height];
	}
}

Persistent<Function> matrix::constructor;

void matrix::Init(Handle<Object> exports) {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("matrix"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	
	//tpl->PrototypeTemplate()->Set(String::NewSymbol("NewInstance"), FunctionTemplate::New(NewInstance)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("createNewMatrix"), FunctionTemplate::New(createNewMatrix)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("setVal"), FunctionTemplate::New(setVal)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getVal"), FunctionTemplate::New(getVal)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getDet"), FunctionTemplate::New(getDet)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("Det2x2"), FunctionTemplate::New(Det2x2)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("cofactorMatrix"), FunctionTemplate::New(cofactorMatrix)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("inverse"), FunctionTemplate::New(inverse)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("transpose"), FunctionTemplate::New(transpose)->GetFunction());	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getH"), FunctionTemplate::New(getH)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getW"), FunctionTemplate::New(getW)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("addMatrix"), FunctionTemplate::New(addMatrix)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("addFloat"), FunctionTemplate::New(addFloat)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("subMatrix"), FunctionTemplate::New(subMatrix)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("subFloat"), FunctionTemplate::New(subFloat)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("multMatrix"), FunctionTemplate::New(multMatrix)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("multFloat"), FunctionTemplate::New(multFloat)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("divFloat"), FunctionTemplate::New(divFloat)->GetFunction());
	
	//Persistent<Function> 
	matrix::constructor = Persistent<Function>::New(tpl->GetFunction());
	exports->Set(String::NewSymbol("matrix"), constructor);
}

Handle<Value> matrix::New(const Arguments& args) {
	HandleScope scope;
	
	args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
	
	matrix* obj = new matrix(args[0]->IsUndefined() ? 0 : args[0]->NumberValue(), 
							 args[1]->IsUndefined() ? 0 : args[1]->NumberValue());
	obj->Wrap(args.This());
	
	return args.This();
}

Handle<Value> matrix::createNewMatrix(const v8::Arguments& args) {
	HandleScope scope;
	
	Handle<Value> myObject = matrix::constructor->NewInstance();
	
	return scope.Close(myObject);
}
//
//Handle<Value> matrix::NewInstance(const Arguments& args) {
//	const unsigned argc = 1;
//	Handle<Value> argv[argc] = { args[0] };
//	Local<Object> instance = constructor->NewInstance(argc, argv);
//	return scope.Close(instance);
//}

Handle<Value> matrix::setVal(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	obj->_setVal(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue());
	return scope.Close(Undefined());
}

Handle<Value> matrix::getVal(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New( obj->_getVal(args[0]->NumberValue(), args[1]->NumberValue()) ));
}

Handle<Value> matrix::getDet(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	float det = obj->_getDet();
	return scope.Close(Number::New( det ));
}

Handle<Value> matrix::Det2x2(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	float det = obj->_Det2x2();
	return scope.Close(Number::New( det ));
}

Handle<Value> matrix::cofactorMatrix(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> tempInst = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(tempInst);
	*inst = obj->_cofactorMatrix(args[0]->NumberValue(), args[1]->NumberValue());
	return scope.Close(tempInst);
}

Handle<Value> matrix::inverse(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> invInst = matrix::constructor->NewInstance();
	matrix* inv = ObjectWrap::Unwrap<matrix>(invInst);
	*inv = obj->_inverse();
	return scope.Close(invInst);
}

Handle<Value> matrix::transpose(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> tranInst = matrix::constructor->NewInstance();
	matrix* tran = ObjectWrap::Unwrap<matrix>(tranInst);
	*tran = obj->_transpose();
	return scope.Close(tranInst);
}

Handle<Value> matrix::getH(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New(obj->_getH()));
}

Handle<Value> matrix::getW(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New(obj->_getW()));
}

Handle<Value> matrix::addMatrix(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_addMatrix(*input);
	return scope.Close(Instance);
}


Handle<Value> matrix::addFloat(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_addFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::subMatrix(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_subMatrix(*input);
	return scope.Close(Instance);
}

Handle<Value> matrix::subFloat(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_subFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::multMatrix(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_multMatrix(*input);
	return scope.Close(Instance);
}

Handle<Value> matrix::multFloat(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_multFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::divFloat(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->_divFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

//Handle<Value> matrix::copyMatrixJ(const Arguments& args) {
//	HandleScope scope;
//	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
//	obj->copyMatrix(args[0]);
//	
//}

/////////////////////////////////////////////
//Sets the value of the entry specified.
void matrix::_setVal(int col, int row, float val) {
	mat[col][row] = val;
}

/////////////////////////////////////////////
//Returns the value of the entry specified.
float matrix::_getVal(int col, int row) {
	if (col > _getW()) {
		std::cerr << 'Column index out of range.' << std::endl;
	} else if (row > _getH()) {
		std::cerr << 'Row index out of range.' << std::endl;
	} else {
		return mat[col][row];
	}
}

/////////////////////////////////////////////
//Returns the determinant of the matrix object as a float.
float matrix::_getDet() {

	//This function moves along the top row of the matrix, and finds the cofactor matrix of each entry there.
	//These cofactor matrices are recursively condensed down, until a 2x2 matrix emerges. When the 2x2 matrix
	//is found, its determinant is returned.
	if (_getH() == 2 && _getW() == 2) {
		return _Det2x2();
	} else if (_getH() > 2 && _getW() > 2 && _getH() == _getW()) {
		float value = 0;
		int i;
		for (i = 0; i < _getW(); i++) {
			matrix temp = _cofactorMatrix(i, 0);
			value += pow(-1, i) * (temp._getDet()) * mat[i][0];
		}
		return value;
	} else if (_getW() != _getH()) {
		std::cerr << "Cannot get determinant of non-square matrix. Returned zero (0)." << std::endl;
		return 0;
	}
}

/////////////////////////////////////////////
//Returns the cofactor matrix of the entry specified, and returns it.
matrix matrix::_cofactorMatrix(int col, int row) {
	matrix newMat(_getW() - 1, _getH() - 1);
	int i, j;
	int k = 0;
	for (i = 0; i < _getW(); i++) {
		if (i == col) {
			i++;
		}
		if (i >= _getW()) {
			break;
		}
		int l = 0;
		for (j = 0; j < _getH(); j++) {
			if (j == row) {
				j++;
			}
			if (j >= _getH()) {
				break;
			}
			newMat._setVal(k, l, mat[i][j]);
			l++;
		}
		k++;

	}
	return newMat;
}

/////////////////////////////////////////////
//Returns a copy of the matrix in its inverse form.
matrix matrix::_inverse() {
	matrix inversion(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			matrix temp = _cofactorMatrix(i, j);
			float num = ( (pow(-1, i + j)) * temp._getDet() ) / _getDet();
			inversion._setVal(j, i, num);
		}
	}
	return inversion;
}

/////////////////////////////////////////////
//Returns a copy of the matrix in transpose form.
matrix matrix::_transpose() {
	matrix transM(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			transM._setVal(i, j, mat[j][i]);
		}
	}
	return transM;
}

/////////////////////////////////////////////
//Returns the determinant of a 2x2 matrix (if provided).
float matrix::_Det2x2() {
		return (mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1]);
}

/////////////////////////////////////////////
//Return height of the matrix.
int matrix::_getH() {
	return height;
}

/////////////////////////////////////////////
//Return width of the matrix.
int matrix::_getW() {
	return width;
}

void matrix::_copyMatrix(matrix copyMe) {
	int i, j;
	for (i = 0; i < copyMe._getW(); i++) {
		for (j = 0; j < copyMe._getH(); j++) {
			mat[i][j] = copyMe._getVal(i, j);
		}
	}
}

/////////////////////////////////////////////
//For printing the matrix, line-by-line.
//void matrix::printMatrix() {
//	cout << "---------------" << endl;
//	int i;
//	for (i = 0; i < _getH(); i++) {
//		int j;
//		for (j = 0; j < _getW(); j++) {
//			cout << _getVal(j, i) << " | ";
//		}
//		cout << endl;
//	}
//}

/////////////////////////////////////////////
//For adding one matrix object to another matrix object.
matrix matrix::_addMatrix(matrix addthis) {
	matrix newMat(_getW(), _getH());
	if (_getW() == addthis._getW() && _getH() == addthis._getH()) {
		int i, j;
		for (i = 0; i < _getW(); i++) {
			for (j = 0; j < _getH(); j++) {
				newMat._setVal(i, j, mat[i][j] + addthis._getVal(i, j));
			}
		}
		return newMat;
	} else {
		std::cerr << "Matrices not eligible for addition: not of equal dimension. Returned NULL matrix." << std::endl;
	}
}

/////////////////////////////////////////////
//For adding a float to all entries in the matrix object.
matrix matrix::_addFloat(float addthis) {
	matrix newMat(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			newMat._setVal(i, j, mat[i][j] + addthis);
		}
	}
	return newMat;
}


/////////////////////////////////////////////
//For subtracting one matrix from another.
matrix matrix::_subMatrix(matrix addthis) {
	matrix newMat(_getW(), _getH());
	if (_getW() == addthis._getW() && _getH() == addthis._getH()) {
		int i, j;
		for (i = 0; i < _getW(); i++) {
			for (j = 0; j < _getH(); j++) {
				newMat._setVal(i, j, mat[i][j] - addthis._getVal(i, j));
			}
		}
		return newMat;
	} else {
		std::cerr << "Matrices not eligible for subtraction: not of equal dimension. Returned NULL matrix." << std::endl;
		return newMat;
	}
}

/////////////////////////////////////////////
//For multiplying all entries in the matrix object by a single float.
matrix matrix::_multFloat(float multhis) {
	matrix newMat(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			newMat._setVal(i, j, mat[i][j]*multhis);
		}
	}
	return newMat;
}

/////////////////////////////////////////////
//For subtracting a float from each entry in the matrix object.
matrix matrix::_subFloat(float addthis) {
	matrix newMat(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			newMat._setVal(i, j, mat[i][j] - addthis);
		}
	}
	return newMat;
}



/////////////////////////////////////////////
//For multiplying two matrix objects.
matrix matrix::_multMatrix(matrix multhis) {
	matrix newMat(_getH(), multhis._getW());
	if (_getH() == multhis._getW()) {
		int i, j;
		for (i = 0; i < newMat._getW(); i++) {
			for (j = 0; j < newMat._getH(); j++) {
				float val = 0;
				int k;
				for (k = 0; k < _getW(); k++) {
					val += mat[k][j]*multhis._getVal(i, k);
				}
				newMat._setVal(i, j, val);
			}
		}
		return newMat;
	} else {
		std::cerr << "Matrices not eligible for multiplication: not of correct dimension. Returned NULL matrix." << std::endl;
		return newMat;
	}
}

/////////////////////////////////////////////
//For dividing all entries in the matrix object by a single float.
matrix matrix::_divFloat(float multhis) {
	matrix newMat(_getW(), _getH());
	int i, j;
	for (i = 0; i < _getW(); i++) {
		for (j = 0; j < _getH(); j++) {
			newMat._setVal(i, j, mat[i][j] / multhis);
		}
	}
	return newMat;
}