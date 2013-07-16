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
	matrix operator+(matrix addthis);
	matrix operator+(float addthis);
	matrix operator-(matrix subthis);
	matrix operator-(float subthis);
	matrix operator*(matrix multhis);
	matrix operator*(float multhis);

	int height;
	int width;
	float** mat;
};
#endif