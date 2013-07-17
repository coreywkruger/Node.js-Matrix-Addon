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
	tpl->PrototypeTemplate()->Set(String::NewSymbol("setValJ"), FunctionTemplate::New(setValJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getValJ"), FunctionTemplate::New(getValJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getDetJ"), FunctionTemplate::New(getDetJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("Det2x2J"), FunctionTemplate::New(Det2x2J)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("cofactorMJ"), FunctionTemplate::New(cofactorMJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("inverseJ"), FunctionTemplate::New(inverseJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("transposeJ"), FunctionTemplate::New(transposeJ)->GetFunction());	
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getHJ"), FunctionTemplate::New(getHJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("getWJ"), FunctionTemplate::New(getWJ)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("addMatrixJ"), FunctionTemplate::New(addMatrixJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("addFloatJ"), FunctionTemplate::New(addFloatJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("subMatrixJ"), FunctionTemplate::New(subMatrixJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("subFloatJ"), FunctionTemplate::New(subFloatJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("multMatrixJ"), FunctionTemplate::New(multMatrixJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("multFloatJ"), FunctionTemplate::New(multFloatJ)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("divFloatJ"), FunctionTemplate::New(divFloatJ)->GetFunction());
	
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

Handle<Value> matrix::setValJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	obj->setVal(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue());
	return scope.Close(Undefined());
}

Handle<Value> matrix::getValJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New( obj->getVal(args[0]->NumberValue(), args[1]->NumberValue()) ));
}

Handle<Value> matrix::getDetJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	float det = obj->getDet();
	return scope.Close(Number::New( det ));
}

Handle<Value> matrix::Det2x2J(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	float det = obj->Det2x2();
	return scope.Close(Number::New( det ));
}

Handle<Value> matrix::cofactorMJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> tempInst = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(tempInst);
	*inst = obj->cofactorM(args[0]->NumberValue(), args[1]->NumberValue());
	return scope.Close(tempInst);
}

Handle<Value> matrix::inverseJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> invInst = matrix::constructor->NewInstance();
	matrix* inv = ObjectWrap::Unwrap<matrix>(invInst);
	*inv = obj->inverse();
	return scope.Close(invInst);
}

Handle<Value> matrix::transposeJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> tranInst = matrix::constructor->NewInstance();
	matrix* tran = ObjectWrap::Unwrap<matrix>(tranInst);
	*tran = obj->transpose();
	return scope.Close(tranInst);
}

Handle<Value> matrix::getHJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New(obj->getH()));
}

Handle<Value> matrix::getWJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	return scope.Close(Number::New(obj->getW()));
}

Handle<Value> matrix::addMatrixJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->addMatrix(*input);
	return scope.Close(Instance);
}


Handle<Value> matrix::addFloatJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->addFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::subMatrixJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->subMatrix(*input);
	return scope.Close(Instance);
}

Handle<Value> matrix::subFloatJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->subFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::multMatrixJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	matrix* input = ObjectWrap::Unwrap<matrix>(args[0]->ToObject());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->multMatrix(*input);
	return scope.Close(Instance);
}

Handle<Value> matrix::multFloatJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->multFloat(args[0]->NumberValue());
	return scope.Close(Instance);
}

Handle<Value> matrix::divFloatJ(const Arguments& args) {
	HandleScope scope;
	matrix* obj = ObjectWrap::Unwrap<matrix>(args.This());
	Handle<Object> Instance = matrix::constructor->NewInstance();
	matrix* inst = ObjectWrap::Unwrap<matrix>(Instance);
	*inst = obj->divFloat(args[0]->NumberValue());
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
void matrix::setVal(int col, int row, float val) {
	mat[col][row] = val;
}

/////////////////////////////////////////////
//Returns the value of the entry specified.
float matrix::getVal(int col, int row) {
	return mat[col][row];
}

/////////////////////////////////////////////
//Returns the determinant of the matrix object as a float.
float matrix::getDet() {

	//This function moves along the top row of the matrix, and finds the cofactor matrix of each entry there.
	//These cofactor matrices are recursively condensed down, until a 2x2 matrix emerges. When the 2x2 matrix
	//is found, its determinant is returned.
	if (getH() == 2 && getW() == 2) {
		return Det2x2();
	} else if (getH() > 2 && getW() > 2 && getH() == getW()) {
		float value = 0;
		int i;
		for (i = 0; i < getW(); i++) {
			matrix temp = cofactorM(i, 0);
			value += pow(-1, i) * (temp.getDet()) * mat[i][0];
		}
		return value;
	} else if (getW() != getH()) {
		std::cerr << "Cannot get determinant of non-square matrix. Returned zero (0)." << std::endl;
		return 0;
	}
}

/////////////////////////////////////////////
//Returns the cofactor matrix of the entry specified, and returns it.
matrix matrix::cofactorM(int col, int row) {
	matrix newMat(getW() - 1, getH() - 1);
	int i, j;
	int k = 0;
	for (i = 0; i < getW(); i++) {
		if (i == col) {
			i++;
		}
		if (i >= getW()) {
			break;
		}
		int l = 0;
		for (j = 0; j < getH(); j++) {
			if (j == row) {
				j++;
			}
			if (j >= getH()) {
				break;
			}
			newMat.setVal(k, l, mat[i][j]);
			l++;
		}
		k++;

	}
	return newMat;
}

/////////////////////////////////////////////
//Returns a copy of the matrix in its inverse form.
matrix matrix::inverse() {
	matrix inversion(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			matrix temp = cofactorM(i, j);
			float num = ( (pow(-1, i + j)) * temp.getDet() ) / getDet();
			inversion.setVal(j, i, num);
		}
	}
	return inversion;
}

/////////////////////////////////////////////
//Returns a copy of the matrix in transpose form.
matrix matrix::transpose() {
	matrix transM(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			transM.setVal(i, j, mat[j][i]);
		}
	}
	return transM;
}

/////////////////////////////////////////////
//Returns the determinant of a 2x2 matrix (if provided).
float matrix::Det2x2() {
		return (mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1]);
}

/////////////////////////////////////////////
//Return height of the matrix.
int matrix::getH() {
	return height;
}

/////////////////////////////////////////////
//Return width of the matrix.
int matrix::getW() {
	return width;
}

void matrix::copyMatrix(matrix copyMe) {
	int i, j;
	for (i = 0; i < copyMe.getW(); i++) {
		for (j = 0; j < copyMe.getH(); j++) {
			mat[i][j] = copyMe.getVal(i, j);
		}
	}
}

/////////////////////////////////////////////
//For printing the matrix, line-by-line.
//void matrix::printMatrix() {
//	cout << "---------------" << endl;
//	int i;
//	for (i = 0; i < getH(); i++) {
//		int j;
//		for (j = 0; j < getW(); j++) {
//			cout << getVal(j, i) << " | ";
//		}
//		cout << endl;
//	}
//}

/////////////////////////////////////////////
//For adding one matrix object to another matrix object.
matrix matrix::addMatrix(matrix addthis) {
	matrix newMat(getW(), getH());
	if (getW() == addthis.getW() && getH() == addthis.getH()) {
		int i, j;
		for (i = 0; i < getW(); i++) {
			for (j = 0; j < getH(); j++) {
				newMat.setVal(i, j, mat[i][j] + addthis.getVal(i, j));
			}
		}
		return newMat;
	} else {
		std::cerr << "Matrices not eligible for addition: not of equal dimension. Returned NULL matrix." << std::endl;
	}
}

/////////////////////////////////////////////
//For adding a float to all entries in the matrix object.
matrix matrix::addFloat(float addthis) {
	matrix newMat(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			newMat.setVal(i, j, mat[i][j] + addthis);
		}
	}
	return newMat;
}


/////////////////////////////////////////////
//For subtracting one matrix from another.
matrix matrix::subMatrix(matrix addthis) {
	matrix newMat(getW(), getH());
	if (getW() == addthis.getW() && getH() == addthis.getH()) {
		int i, j;
		for (i = 0; i < getW(); i++) {
			for (j = 0; j < getH(); j++) {
				newMat.setVal(i, j, mat[i][j] - addthis.getVal(i, j));
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
matrix matrix::multFloat(float multhis) {
	matrix newMat(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			newMat.setVal(i, j, mat[i][j]*multhis);
		}
	}
	return newMat;
}

/////////////////////////////////////////////
//For subtracting a float from each entry in the matrix object.
matrix matrix::subFloat(float addthis) {
	matrix newMat(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			newMat.setVal(i, j, mat[i][j] - addthis);
		}
	}
	return newMat;
}



/////////////////////////////////////////////
//For multiplying two matrix objects.
matrix matrix::multMatrix(matrix multhis) {
	matrix newMat(getH(), multhis.getW());
	if (getH() == multhis.getW()) {
		int i, j;
		for (i = 0; i < newMat.getW(); i++) {
			for (j = 0; j < newMat.getH(); j++) {
				float val = 0;
				int k;
				for (k = 0; k < getW(); k++) {
					val += mat[k][j]*multhis.getVal(i, k);
				}
				newMat.setVal(i, j, val);
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
matrix matrix::divFloat(float multhis) {
	matrix newMat(getW(), getH());
	int i, j;
	for (i = 0; i < getW(); i++) {
		for (j = 0; j < getH(); j++) {
			newMat.setVal(i, j, mat[i][j] / multhis);
		}
	}
	return newMat;
}