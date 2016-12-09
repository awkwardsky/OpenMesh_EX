#include"ChoiceTool.h"

ChoiceTool::ChoiceTool() {
}
ChoiceTool::ChoiceTool(Tri_Mesh* mesh) {
}
ChoiceTool::~ChoiceTool() {
}

void ChoiceTool::toMesh(Tri_Mesh* mesh) {
	this->choiceToolMesh = mesh;
}
//void ChoiceTool::toMapper(MapperTool* target) {
//	this->mapper = target;
//}
Point ChoiceTool::getObjectPosition(int mouseX, int mouseY) {
	glReadPixels(mouseX, mouseY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &pixels);
	gluUnProject(mouseX, mouseY, pixels, xf, projMatrix, viewport, &objX, &objY, &objZ);
	std::cout << "obj(x, y, z): (" << objX << ", " << objY << ", " << objZ << ")" << std::endl;

	///mesh->choiceFace(objX, objY, objZ);///選面
	///mesh->choicePoint(objX, objY, objZ);///選點
	return Point(objX, objY, objZ);
}
VIter ChoiceTool::choicePoint(int mouseX, int mouseY) {
	Point objPosition = getObjectPosition(mouseX,mouseY);
	VIter currentV;///Unknow
	float currentL;///Unknow
	bool first = true;///Unknow
	double mostSuitablePoint;
	double minimunValue = 99;///這不用特地放全域變數應該不會有錯
	double b = 123;

	for (VIter v_it = choiceToolMesh->vertices_begin(); v_it != choiceToolMesh->vertices_end(); ++v_it) {
		vector<Point> point_v_it;
		point_v_it.push_back(point(v_it.handle()));///這邊的point是吃、class本身繼承Model的point

		mostSuitablePoint = (objPosition - point_v_it.at(0)).length();
		if (mostSuitablePoint < minimunValue) {///pointOnMesh.at(0)、因為雖然pointOnMesh是vector、但只會用到第一個		///待弄懂
			if (first) {																							///待弄懂
				first = false;																						///待弄懂
				currentV = v_it;																					///待弄懂
			}																										///待弄懂
			if (!first && mostSuitablePoint < currentL) {															///待弄懂
				currentL = mostSuitablePoint;																		///待弄懂
				currentV = v_it;																					///待弄懂
			}																										///待弄懂
		}																											///待弄懂
	}
	if (!first) {
		choiceToolMesh->data(currentV).isSelected = !choiceToolMesh->data(currentV).isSelected;						///待弄懂
		return currentV;																							///待弄懂
	}																												///待弄懂
	else																											///待弄懂
		return choiceToolMesh->vertices_end();																		///待弄懂
}
double ChoiceTool::seaDragon(Point trangleVertex1, Point trangleVertex2, Point trangleVertex3) {
	double triSide[3];
	double s, triArea;

	triSide[0] = (trangleVertex1 - trangleVertex2).length();
	triSide[1] = (trangleVertex2 - trangleVertex3).length();
	triSide[2] = (trangleVertex3 - trangleVertex1).length();

	s = (triSide[0] + triSide[1] + triSide[2]) / 2;
	triArea = sqrt(s*(s - triSide[0])*(s - triSide[1])*(s - triSide[2]));

	return triArea;
	/*
	a、b、c:三邊長
	a、b、c=	[(x2-x1)^2+(y2-y1)^2+(z2-z1)^2]^(1/2)
	s = ( a + b + c) / 2;
	cout << "三角形面積：" << sqrt(s*(s - a)*(s - b)*(s - c)) << endl;
	---------------------------------------------------------------------

	NOTE:   fv_it_point.at(0)// call first point

	triSide[0] = (fv_it_point.at(0) - fv_it_point.at(1)).length();
	triSide[1] = (fv_it_point.at(1) - fv_it_point.at(2)).length();
	triSide[2] = (fv_it_point.at(2) - fv_it_point.at(0)).length();
	*/
}
void ChoiceTool::choiceFace(int mouseX, int mouseY) {
	Point objPosition = getObjectPosition(mouseX, mouseY);
	double triArea[4];
	double mostSuitableTriangle;
	double minimunValue = 99;

	for (FIter f_it = choiceToolMesh->faces_begin(); f_it != choiceToolMesh->faces_end(); ++f_it) {
		vector<Point> point_fv_it;
		for (FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			point_fv_it.push_back(point(fv_it.handle()));
		}
		triArea[0] = seaDragon(point_fv_it.at(0), point_fv_it.at(1), point_fv_it.at(2));
		triArea[1] = seaDragon(objPosition, point_fv_it.at(0), point_fv_it.at(1));
		triArea[2] = seaDragon(objPosition, point_fv_it.at(1), point_fv_it.at(2));
		triArea[3] = seaDragon(objPosition, point_fv_it.at(2), point_fv_it.at(0));

		mostSuitableTriangle = ((triArea[1] + triArea[2] + triArea[3]) - triArea[0]);
		if (mostSuitableTriangle < minimunValue) {
			minimunValue = mostSuitableTriangle;///應該是用不到這個、姑且還是留著比較好懂

			faceHandle = f_it.handle();		///選面、面的handla
			FVIter fv_it = fv_iter(f_it);	///選面、周圍點的handel
			faceVertexHandle[0] = ++fv_it;	///選面、周圍點的handle
			faceVertexHandle[1] = ++fv_it;	///選面、周圍點的handle 
			faceVertexHandle[2] = ++fv_it;	///選面、周圍點的handle

			choiceToolMesh->data(f_it).isSelected = !choiceToolMesh->data(f_it).isSelected;

			if (choiceToolMesh->data(f_it).isSelected) {
				cout << "Add Face" << endl;
				//this->mapper->AddFace(point_fv_it.at(0), point_fv_it.at(1), point_fv_it.at(2));
			}
			else {
				cout << "Delete Face" << endl;
				//this->mapper->DeleteFace(point_fv_it.at(0), point_fv_it.at(1), point_fv_it.at(2));
			}
		}
	}
}
void ChoiceTool::choicePointRenderVertex(int mouseX, int mouseY) {
	VIter hitPoint = choicePoint(mouseX, mouseY);

	if (hitPoint != choiceToolMesh->vertices_end()) {
		for (VFIter vf_it = choiceToolMesh->vf_begin(hitPoint); vf_it != choiceToolMesh->vf_end(hitPoint); ++vf_it) {
			choiceToolMesh->data(vf_it).isSelected = choiceToolMesh->data(hitPoint).isSelected;

			vector<Point> point_fv_it;
			for (FVIter fv_it = fv_iter(vf_it); fv_it; ++fv_it) {
				point_fv_it.push_back(point(fv_it.handle()));
			}
			if (choiceToolMesh->data(vf_it).isSelected) {
				cout << "Add Face" << endl;
				//this->mapper->AddFace(point_fv_it.at(0), point_fv_it.at(1), point_fv_it.at(2));
			}
			else {
				cout << "Delete Face" << endl;
				//this->mapper->DeleteFace(point_fv_it.at(0), point_fv_it.at(1), point_fv_it.at(2));
			}
		}
	}
}