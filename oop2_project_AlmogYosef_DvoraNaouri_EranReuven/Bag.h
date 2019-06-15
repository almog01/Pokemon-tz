#pragma once
#include "Screen.h"
class Bag :	public Screen
{
public:
	Bag();
	~Bag();

	// Inherited via Screen
	virtual void keyReleasedHandler(const Event & event) override;
};

