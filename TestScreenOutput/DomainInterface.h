#pragma once
#include "UserDefs.h"
#include "MyMath.h"
#include "FieldController.h"

class DomainInterface
{
private:
	Index_t tag = 0;
	Index_t width = 0;
	Index_t height = 0;

	Index_t iStart = 0;
	Index_t jStart = 0;
	Index_t nSize = 0;

	FieldController *field = nullptr;
	LUT_MotionVector motionVector;

public:
	DomainInterface() {};
	DomainInterface(Index_t _tag, Index_t _width, Index_t _height, Index_t _iStart, Index_t _jStart, Field *_field) {
		tag = _tag;
		width = _width;
		height = _height;
		iStart = _iStart;
		jStart = _jStart;
		nSize = width * height;
		field = new FieldController(_field);
	}

	~DomainInterface() {
		delete(field);
	};

	//Virtual Function
	virtual void apply(void) {};

	//Getters
	inline Index_t getTag() { return tag; }
	inline Index_t getSize() { return nSize; }
	inline Index_t getiStart() { return iStart; }
	inline Index_t getjStart() { return jStart; }
	//Setters


private:
	//move actions
	bool move(Index_t index, MoveDirs dir);
	bool move(Index_t index, MoveDirs dir, Index_t stepLength);
	bool move(Index2 ind, MoveDirs dir);


	//tools
	Index_t getDirIndex(Index_t index, Index2 motion);
	bool isOnEdge(Index_t index);
	bool isOnEdge(Index2 ind);
};

