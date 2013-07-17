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
	static v8::Handle<v8::Value> setVal(const v8::Arguments& args);
	static v8::Handle<v8::Value> getVal(const v8::Arguments& args);
	static v8::Handle<v8::Value> getDet(const v8::Arguments& args);
	static v8::Handle<v8::Value> Det2x2(const v8::Arguments& args);
	static v8::Handle<v8::Value> cofactorMatrix(const v8::Arguments& args);
	static v8::Handle<v8::Value> inverse(const v8::Arguments& args);
	static v8::Handle<v8::Value> transpose(const v8::Arguments& args);
	static v8::Handle<v8::Value> getH(const v8::Arguments& args);
	static v8::Handle<v8::Value> getW(const v8::Arguments& args);
	
	static v8::Handle<v8::Value> addMatrix(const v8::Arguments& args);
	static v8::Handle<v8::Value> addFloat(const v8::Arguments& args);
	static v8::Handle<v8::Value> subMatrix(const v8::Arguments& args);
	static v8::Handle<v8::Value> subFloat(const v8::Arguments& args);
	static v8::Handle<v8::Value> multMatrix(const v8::Arguments& args);
	static v8::Handle<v8::Value> multFloat(const v8::Arguments& args);
	static v8::Handle<v8::Value> divFloat(const v8::Arguments& args);
	//static v8::Handle<v8::Value> copyMatrixJ(const v8::Arguments& args);
	
	//Original functions (un-exposed to Javascript)
	matrix(int, int);
	void _setVal(int, int, float);
	float _getVal(int, int);
	float _getDet();
	float _Det2x2();
	matrix _cofactorMatrix(int col, int row);
	matrix _inverse();
	matrix _transpose();
	int _getH();
	int _getW();
	//void printMatrix();
	void _copyMatrix(matrix);
	matrix _addMatrix(matrix addthis);
	matrix _addFloat(float addthis);
	matrix _subMatrix(matrix subthis);
	matrix _subFloat(float subthis);
	matrix _multMatrix(matrix multhis);
	matrix _multFloat(float multhis);
	matrix _divFloat(float divthis);

	int height;
	int width;
	float** mat;
};
#endif