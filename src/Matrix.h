#ifndef MATRIX_H
#define MATRIX_H

#include <node.h>

class matrix: public node::ObjectWrap {
public:
	static v8::Persistent<v8::Function> constructor;
	static void Init(v8::Handle<v8::Object> exports);

	
private:
	
	//Interface functions below (exposed to javascript)
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> createNewMatrix(const v8::Arguments& args);
	static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
	static v8::Handle<v8::Value> setValJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> getValJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> getDetJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> Det2x2J(const v8::Arguments& args);
	static v8::Handle<v8::Value> cofactorMJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> inverseJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> transposeJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> getHJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> getWJ(const v8::Arguments& args);
	
	static v8::Handle<v8::Value> addMatrixJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> addFloatJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> subMatrixJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> subFloatJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> multMatrixJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> multFloatJ(const v8::Arguments& args);
	static v8::Handle<v8::Value> divFloatJ(const v8::Arguments& args);
	//static v8::Handle<v8::Value> copyMatrixJ(const v8::Arguments& args);
	
	//Original functions (un-exposed to Javascript)
	matrix(int, int);
	void setVal(int, int, float);
	float getVal(int, int);
	float getDet();
	float Det2x2();
	matrix cofactorM(int col, int row);
	matrix inverse();
	matrix transpose();
	int getH();
	int getW();
	//void printMatrix();
	void copyMatrix(matrix);
	matrix addMatrix(matrix addthis);
	matrix addFloat(float addthis);
	matrix subMatrix(matrix subthis);
	matrix subFloat(float subthis);
	matrix multMatrix(matrix multhis);
	matrix multFloat(float multhis);
	matrix divFloat(float divthis);

	int height;
	int width;
	float** mat;
};
#endif