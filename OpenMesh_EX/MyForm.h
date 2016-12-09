#pragma once
#ifndef MY_FORM_H
#define MY_FORM_H

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include "ChoiceTool.h"

//using namespace std;

//ChoiceTool choiceTool;
Tri_Mesh *mesh;
Tri_Mesh *newMesh = new Tri_Mesh();
ChoiceTool choiceTool;
xform xf;
GLCamera camera;
float fov = 0.7f;
GLfloat pixels;
GLint viewport[4];
GLdouble projMatrix[16];
GLdouble objX, objY, objZ;


static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;

namespace OpenMesh_EX {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// MyForm summary
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			///
			///TODO:  �b���[�J�غc�禡�{���X
			///
		}
	protected:
		/// �M������ϥΤ����귽�C
		~MyForm(){
			if (components){
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::ToolStripMenuItem^  vertexToolStripMenuItem;

	protected:

	private:
		/// �]�p�u��һݪ��ܼơC
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		void InitializeComponent(void) {
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->vertexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(613, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem, this->vertexToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// vertexToolStripMenuItem
			// 
			this->vertexToolStripMenuItem->Name = L"vertexToolStripMenuItem";
			this->vertexToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->vertexToolStripMenuItem->Text = L"vertex";
			this->vertexToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::vertexToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 24);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(613, 430);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 454);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		glEnable(GL_COLOR_MATERIAL);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		point center;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.setupGL(xf * center, 1.0);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xf);
		if (mesh != NULL) {
			//mesh->choicePointRenderFace();	//O
			//mesh->choicePointRenderPoint();	//O
			mesh->choiceFaceRenderVertex();	//O
			//mesh->Render_SolidWireframe();
			//mesh->choiceFaceRenderFace();		//X
		}
		glPopMatrix();
	}
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		glGetIntegerv(GL_VIEWPORT, viewport);

		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle) {
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State, xf * center, 1.0, xf);
		}
	
		if(e->Button == System::Windows::Forms::MouseButtons::Right){
			glReadPixels(e->X, hkoglPanelControl1->Height - e->Y, 1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&pixels);
			gluUnProject(e->X, hkoglPanelControl1->Height - e->Y, pixels, xf, projMatrix, viewport, &objX, &objY, &objZ);
			hkoglPanelControl1->Invalidate();
			std::cout << "obj(x, y, z): (" << objX << ", " << objY << ", " << objZ << ")" << std::endl;

			//isSelected();
		
			mesh->choiceFace(objX, objY, objZ);///�ﭱ
			mesh->choicePoint(objX, objY, objZ);///���I
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			choiceTool.getObjectPosition(e->X, hkoglPanelControl1->Height - e->Y);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State, xf * center, 1.0, xf);
			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State, xf * center, 1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Delta < 0) {
			point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State, xf * center, 1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
		else {
			point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State, xf * center, 1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openModelDialog->Filter = "Model(*.obj)|*obj";
		openModelDialog->Multiselect = false;
		openModelDialog->ShowDialog();
	}
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		if (mesh != NULL)
			delete mesh;

		mesh = new Tri_Mesh;

		if (ReadFile(filename, mesh))
			std::cout << filename << std::endl;

		hkoglPanelControl1->Invalidate();
	}
	private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		saveModelDialog->Filter = "Model(*.obj)|*obj";
		saveModelDialog->ShowDialog();
	}
	private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(saveModelDialog->FileName, filename);

		if (SaveFile(filename, mesh))
			std::cout << filename << std::endl;
	}

	private: System::Void vertexToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
#endif // !MY_FORM_H