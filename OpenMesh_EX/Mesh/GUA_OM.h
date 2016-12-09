#pragma once
#ifndef GUA_OM_H
#define GUA_OM_H

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

struct Face_InnerAngle {
	double Vertex_Angle[3];
};

class AllPairHarVal_class {
public:  
	std::vector<double> Har_val;
};


///OpenMesh Triangle mesh
namespace OMT {
	using namespace std;

	///�w�q�ϥΪ���ǫשM���ݩ�---------------------------------------------
	struct MyTraits : OpenMesh::DefaultTraits {
		/// let Point and Normal be a vector made from doubles
		typedef OpenMesh::Vec3d Point;
		typedef OpenMesh::Vec3d Normal;

		/// add normal property to vertices and faces
		VertexAttributes(OpenMesh::Attributes::Normal);
		FaceAttributes  (OpenMesh::Attributes::Normal);

		/// Already defined in OpenMesh::DefaultTraits
		/// HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
		
		/// Uncomment next line to disable attribute PrevHalfedge
		/// HalfedgeAttributes( OpenMesh::Attributes::None );
		///
		/// or
		///
		/// HalfedgeAttributes( 0 );
	
		VertexTraits{										///�ݧ���
		public:												///�ݧ���
			bool isSelected;								///�ݧ���
			float w;///Unknow								///�ݧ���
															///�ݧ���
			VertexT() :isSelected(false),w(0.0f) {			///�ݧ���
			}												///�ݧ���
		private:											///�ݧ���
		};													///�ݧ���
		FaceTraits{											///�ݧ���
		public:												///�ݧ���
			bool isSelected;								///�ݧ���
															///�ݧ���
			FaceT() :isSelected(false) {					///�ݧ���
			}												///�ݧ���
		private:											///�ݧ���
		};													///�ݧ���
	};

	///�w�q�`��type---------------------------------------------
	typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits>	    MyMesh	;
	typedef OpenMesh::Vec3d									Vector3d;	//Vec3D type
	typedef MyMesh::Scalar									Scalar	;	//Scalar type
	typedef MyMesh::Point									Point	;	//Point type
	typedef MyMesh::Normal									Normal	;	//Normal type
	typedef MyMesh::VertexHandle							VHandle	;	//VertexHandle type
	typedef MyMesh::HalfedgeHandle							HEHandle;	//HalfedgeHandle type
	typedef MyMesh::EdgeHandle							    EHandle ;	//edgeHandle type
	typedef MyMesh::FaceHandle								FHandle	;	//FaceHandle type

	///Vertex iterators & circulators---------------------------
	typedef MyMesh::VertexIter								VIter	;	//VertexIter type
	typedef MyMesh::VertexVertexIter						VVIter	;	//VertexVertexIter type
	typedef MyMesh::VertexEdgeIter							VEIter	;	//VertexEdgeIter type
	typedef MyMesh::VertexFaceIter							VFIter	;	//VertexFaceIter type
	typedef MyMesh::EdgeIter								EIter	;	//EdgeIterT	type
	typedef MyMesh::FaceIter								FIter	;	//FaceIter type
	typedef MyMesh::FaceVertexIter							FVIter	;	//FaceVertexIter type
	typedef MyMesh::FaceEdgeIter							FEIter	;	//FaceEdgeIter type
	typedef MyMesh::FaceFaceIter							FFIter	;	//FaceFaceIter type
	typedef MyMesh::VertexOHalfedgeIter						VOHEIter;	//VertexOutHalfEdge type
	typedef MyMesh::ConstVertexVertexIter					CVVIter	;	//ConstVertexVertexIter type

	///�w�q�B�~��Ƶ��c-----------------------------------------
	using namespace OpenMesh;

	///�w�q���O---------------------------------------------
	class Model:public MyMesh {
	public:
		Model();
		~Model();
	};
}


class Tri_Mesh:public OMT::Model {
public:
	Tri_Mesh() {
		//add_property(isSelected);
		//for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		//	property(isSelected, f_it.handle()) = false;
		//}
		//remove_property(isSelectedAgain);
		//for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		//	property(isSelectedAgain, f_it.handle()) = false;
		//}
	}
	//penMesh::FPropHandleT<bool> isSelected;
	//penMesh::FPropHandleT<bool> isSelectedAgain;
	
	///Edit Flag---------------------------------------------
    bool                                       Delete_Flag;
	
	int                                        Constrain_num;
	int                                        Boundary_num ;
	int                                        PatchType;
	OMT::VHandle                               start_vh,end_vh;
	OMT::VHandle                               ExtremeVh[2];

	std::vector<OMT::VHandle>                  Pluspt      ;
	std::vector<OMT::VHandle>                  Minuspt     ;
	std::vector<OMT::VHandle>                  Extrme_Pt   ;

	void Render_Solid();
	void Render_SolidWireframe();
	void Render_Wireframe();
	void Render_Point();
	

	double seaDragon(Point trangleVertex1, Point trangleVertex2, Point trangleVertex3);
	double distance(Point point1, Point point2);
	void choiceFace(GLdouble objX, GLdouble objY, GLdouble objZ);
	void choicePoint(GLdouble objX, GLdouble objY, GLdouble objZ);
	void choicePointRenderPoint();
	void choicePointRenderFace();
	void choiceFaceRenderVertex();
	void choiceFaceRenderFace();
	void continuousChoiceFace();
	void addVertex();
	void addFace();

	OMT::FHandle faceHandle;
	OMT::VHandle faceVertexHandle[3];
	OMT::VHandle pointHandle;
	std::vector<OMT::VHandle> closePointHandle;
	std::vector<OMT::FHandle> closeFaceHandle;
private:
};

bool ReadFile(std::string _fileName, Tri_Mesh *_mesh); ///Ū��mesh���
bool SaveFile(std::string _fileName, Tri_Mesh *_mesh); ///�x�smesh���
///��l��view port�]�w�禡---------------------------------------------

#endif