#include "GUA_OM.h"

namespace OMT
{
	Model::Model(){
		request_vertex_status();
		request_edge_status();
		request_face_status();
	}
	Model::~Model(){
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
}
void Tri_Mesh::Render_Solid() {
	FIter f_it;
	FVIter	fv_it;

	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_LIGHTING);
	glPolygonOffset(2.0, 2.0);

	glBegin(GL_TRIANGLES);
	glColor4f(0.81, 0.74, 0.33, 0.3);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		for (fv_it = fv_iter( f_it ); fv_it; ++fv_it){						
			glNormal3dv(normal(fv_it.handle()).data());
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();	
	
	glDisable(GL_POLYGON_OFFSET_FILL);
	glPopAttrib();
}
void Tri_Mesh::Render_SolidWireframe() {
	FIter f_it;
	FVIter	fv_it;

	///Triangles-----------------------------------------------------------------------------	
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);
	glPolygonOffset(2.0, 2.0);

	glBegin(GL_TRIANGLES);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
	if (property(isSelected, f_it.handle()) == true) {
		glColor4f(1.0, 0.0, 0.0, 1.0);
	}
	else {
		glColor4f(1.0, 0.96, 0.49, 1.0);
	}
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			//glNormal3dv(normal(fv_it.handle()));
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	//glDisable(GL_POLYGON_OFFSET_FILL); ///為何不用關???
	glPopAttrib();

	///Lines-----------------------------------------------------------------------------	
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glLineWidth(1.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	for (OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);///get halfedge

		OMT::Point curVertex = point(from_vertex_handle(_hedge));///get point
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

	glPopAttrib();
}
void Tri_Mesh::Render_Wireframe()
{
	//glPushAttrib(GL_LIGHTING_BIT);	
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);	
	for(OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(),1);

		OMT::Point curVertex  = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());			
	}
	glEnd();
}
void Tri_Mesh::Render_Point() {
	glPointSize(8.0);
	
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (OMT::VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		glVertex3dv(point(v_it).data());
	}
	glEnd();
}
bool ReadFile(std::string _fileName,Tri_Mesh *_mesh) { 
	bool isRead = false;																								
	OpenMesh::IO::Options opt;

	if (OpenMesh::IO::read_mesh(*_mesh, _fileName, opt)) {
		///read mesh from filename OK!																				  
		isRead = true;																								  
	}																												  
	if (isRead) {
		/// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them				  
		if (!opt.check(OpenMesh::IO::Options::VertexNormal) && _mesh->has_vertex_normals()) {
			_mesh->update_normals();																				  
		}																											  
	}																												  
	return isRead;																									  
}																													  
bool SaveFile(std::string _fileName, Tri_Mesh *_mesh) {																													  
	bool isSave = false;

	if (OpenMesh::IO::write_mesh(*_mesh, _fileName)) {
		isSave = true;																								  
	}																												  
	return isSave;																									  
}					

double Tri_Mesh::seaDragon(Point trangleVertex1, Point trangleVertex2, Point trangleVertex3) {						  
																													  
	double triSide[3];																								  
	double s, triArea;																								  
																													  
	triSide[0] = (trangleVertex1 - trangleVertex2).length();														  
	triSide[1] = (trangleVertex2 - trangleVertex3).length();														  
	triSide[2] = (trangleVertex3 - trangleVertex1).length();														  
																													  
	s = (triSide[0] + triSide[1] + triSide[2]) / 2;																	  
	triArea = sqrt(s*(s - triSide[0])*(s - triSide[1])*(s - triSide[2]));			  
																					  
	return triArea;
	/*
	#include<iostream>
	#include<math.h>
	#include<cstdlib>

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
double Tri_Mesh::distance(Point point1, Point point2) {
	double pointDistance;
	pointDistance = (point1 - point2).length();
	return pointDistance;
}
void Tri_Mesh::choiceFace(GLdouble objX, GLdouble objY, GLdouble objZ) {
	double triArea[4];
	double mostSuitableTriangle;
	double minimumValue = 99;

	OMT::Point objPosition;
	objPosition.data()[0] = objX;
	objPosition.data()[1] = objY;
	objPosition.data()[2] = objZ;

	for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		std::vector<OMT::Point> fv_it_point;
		for (OMT::FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			fv_it_point.push_back(point(fv_it.handle()));///handle()裡面存有該Point內含相關的值、位子阿、點的座標阿、等等
			//glNormal3dv(normal(fv_it.handle()));
			//glVertex3dv(point(fv_it.handle()).data());
		}
		triArea[0] = seaDragon(fv_it_point.at(0), fv_it_point.at(1), fv_it_point.at(2));
		triArea[1] = seaDragon(objPosition, fv_it_point.at(0), fv_it_point.at(1));
		triArea[2] = seaDragon(objPosition, fv_it_point.at(1), fv_it_point.at(2));
		triArea[3] = seaDragon(objPosition, fv_it_point.at(2), fv_it_point.at(0));

		mostSuitableTriangle = ((triArea[1] + triArea[2] + triArea[3]) - triArea[0]);
		if (mostSuitableTriangle < minimumValue) {
			minimumValue = mostSuitableTriangle;
			faceHandle = f_it.handle();		///選面、面的handla
			FVIter fv_it = fv_iter(f_it);	///選面、周圍點的handel
			faceVertexHandle[0] = ++fv_it;	///選面、周圍點的handle
			faceVertexHandle[1] = ++fv_it;	///選面、周圍點的handle 
			faceVertexHandle[2] = ++fv_it;	///選面、周圍點的handle
		}
	}
	//property(isSelected, faceHandle) = true;

}
void Tri_Mesh::choicePoint(GLdouble objX, GLdouble objY, GLdouble objZ) {
	double mostSuitablePoint;
	double minimunValue = 99;
	OMT::Point objPosition;
	objPosition.data()[0] = objX;
	objPosition.data()[1] = objY;
	objPosition.data()[2] = objZ;

	for (OMT::VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		std::vector<OMT::Point>v_it_point;
		v_it_point.push_back(point(v_it.handle()));
		mostSuitablePoint = distance(v_it_point.at(0), objPosition);
		if (mostSuitablePoint < minimunValue) {
			minimunValue = mostSuitablePoint;
			pointHandle = v_it.handle();	///選點，點的handle
		}
	}

	for (OMT::VVIter vv_it = vv_iter(pointHandle); vv_it; ++vv_it) {
		closePointHandle.push_back(vv_it.handle());
	}
	for (OMT::VFIter vf_it = vf_iter(pointHandle); vf_it; ++vf_it) {
		closeFaceHandle.push_back(vf_it.handle());
	}
}
void Tri_Mesh::choicePointRenderFace() {
	FIter f_it;
	FVIter fv_it;
	EIter e_it;
	VIter v_it, v_it2;
	VVIter vv_it;
	VFIter vf_it;
	///face
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);

	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
		if (is_valid_handle(pointHandle)) {
			for (vf_it = vf_iter(pointHandle); vf_it; ++vf_it) {
				for (fv_it = fv_iter(vf_it); fv_it; ++fv_it) {
					glColor4f(0.0, 1.0, 0.0, 1.0);///選點、亮周圍面	
					glVertex3dv(point(fv_it.handle()).data());
				}
			}
		}
		else {
			glColor4f(1.0, 0.96, 0.49, 1.0);
		}
	glEnd();
	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		glColor4f(1.0, 0.96, 0.49, 1.0);
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			///render Face
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	///Edge
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		glColor3f(0.0, 0.0, 0.0);
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);
		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

	///Point
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4f(1.0, 0.0, 0.0, 1.0);///選點、亮點																											
	glVertex3dv(point(pointHandle).data());
	glEnd();
}
void Tri_Mesh::choicePointRenderPoint() {
	FIter f_it;
	FVIter fv_it;
	EIter e_it;
	VIter v_it, v_it2;
	VVIter vv_it;

	///face
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);

	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
			glColor4f(1.0, 0.96, 0.49, 1.0);
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			///render Face
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	///Edge
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		glColor3f(0.0, 0.0, 0.0);
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);
		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

	///Point
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4f(1.0, 0.0, 0.0, 1.0);///選點、亮點																											
	glVertex3dv(point(pointHandle).data());
	if (is_valid_handle(pointHandle)) {
		for (vv_it = vv_iter(pointHandle); vv_it; ++vv_it) {
			glColor4f(0.0, 1.0, 0.0, 1.0);///選點、亮周圍點	
			glVertex3dv(point(vv_it).data());
		}
	}
	glEnd();
}
void Tri_Mesh::choiceFaceRenderVertex() {
	FIter f_it;
	FVIter fv_it;
	EIter e_it;
	VIter v_it, v_it2;
	VVIter vv_it;

	///face
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);

	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		//if (f_it.handle() == faceHandle&&property(isSelected,f_it.handle())==true) {
		if (property(isSelected, f_it.handle()) == true) {
			///choice Face render Face
			glColor4f(1.0, 0.0, 0.0, 1.0);
		}
		//else if(property(isSelectedAgain, f_it.handle()) = true){
		//	property(isSelected, f_it.handle()) = false;
		//	glColor4f(1.0, 0.96, 0.49, 1.0);
		//}
		else {
			glColor4f(1.0, 0.96, 0.49, 1.0);
		}
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			///render Face
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
		
	glEnd();

	///Edge
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		glColor3f(0.0, 0.0, 0.0);
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);
		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

	///Point
	glPointSize(8.0);
	glBegin(GL_POINTS);
	for (v_it2 = vertices_begin(); v_it2 != vertices_end(); ++v_it2) {
		if (v_it2.handle() == faceVertexHandle[0] || v_it2.handle() == faceVertexHandle[1] || v_it2.handle() == faceVertexHandle[2]) {
		//if (property(isSelected, v_it2.handle()) == true) {
			///choice face render vertexPoint
			glColor4f(0.0, 1.0, 0.0, 1.0);
		}
		else {
			glColor4f(0.0, 0.0, 0.0, 1.0);
		}
		///render point
		glVertex3dv(point(v_it2).data());
	}
	glEnd();
	glPopAttrib();
}
void Tri_Mesh::choiceFaceRenderFace() {
	FIter f_it;
	FVIter fv_it;
	EIter e_it;
	VIter v_it, v_it2;
	VVIter vv_it;
	VFIter vf_it;

	FFIter ff_it;
	///face
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);

	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	if (is_valid_handle(faceHandle)) {
		for (ff_it = ff_iter(faceHandle); ff_it; ++ff_it) {
			for (fv_it = fv_iter(vf_it); fv_it; ++fv_it) {
				glColor4f(0.0, 1.0, 0.0, 1.0);///選點、亮周圍面	
				glVertex3dv(point(fv_it.handle()).data());
			}
		}
	}
	else {
		glColor4f(1.0, 0.96, 0.49, 1.0);
	}
	glEnd();
	///Face
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		glColor4f(1.0, 0.96, 0.49, 1.0);
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it) {
			///render Face
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	///Edge
	glLineWidth(1.0);
	glBegin(GL_LINES);
	for (e_it = edges_begin(); e_it != edges_end(); ++e_it) {
		glColor3f(0.0, 0.0, 0.0);
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);
		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

	///Point
	glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4f(1.0, 0.0, 0.0, 1.0);///選點、亮點																											
	glVertex3dv(point(pointHandle).data());
	glEnd();
}

void Tri_Mesh::continuousChoiceFace() {
	
}
void Tri_Mesh::addVertex() {
	VHandle *VHandleVec = new VHandle();

	for (VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it) {
		//if(property(selectVertex,v_it))
	}
}
void Tri_Mesh::addFace() {
	FHandle *FHandleFace = new FHandle();
	for (FIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		
	}
}