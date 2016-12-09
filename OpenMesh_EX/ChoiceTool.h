#pragma once
#ifndef CHOICE_TOOL_H
#define CHOICE_TOOL_H

#include "Mesh/GUA_OM.h"
#include "MyForm.h"
using namespace OMT;

class ChoiceTool :public Model {
public:
	ChoiceTool();
	ChoiceTool(Tri_Mesh*);
	~ChoiceTool();


	void toMesh(Tri_Mesh*);
	//void toMapper(MapperTool*);
	Point getObjectPosition(int, int);
	VIter choicePoint(int, int);
	double seaDragon(Point trangleVertex1, Point trangleVertex2, Point trangleVertex3);
	void choiceFace(int, int);
	void choicePointRenderVertex(int, int);


	FHandle faceHandle;
	VHandle faceVertexHandle[3];
private:
	Tri_Mesh* choiceToolMesh;
	//MapperTool* mapper;
};
#endif /// !CHOICE_TOOL_H

