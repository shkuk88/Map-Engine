#pragma once
#include <filesystem>
#include <fstream>
#include "GameObject.h"
#include "CAnimation.h"
#include "InstanceRenderer.h"


enum class EClassType : char {
	Geom = 0, Biped,
	Bone, Dummy,
};

struct SceneData
{
	int TotalFrame = 0;		// �� ������ ��
	float SPF = 0.0f;		// ������ ����
	int MeshCount;			// �޽�������Ʈ ����
	int MaxWeight;			// ���� �� ����ġ
	bool BindPose;			// ���ε� ���� ���ϸ��̼� ����
}; 

struct MaterialData
{
	UINT	MaterialIndex;
	//wstring MaterialName;
	//wstring MaterialClassName;	// Ŭ���� Ÿ��(Standard, SubMaterial...)
	vector<MaterialData> SubMaterials;
	Texture* pTexture = nullptr;
	//vector<Tex>;
	//UINT SubCount;
	//UINT TexMapCount;
	MaterialData* pParent = nullptr;
};



class MaxImporter
{
protected:
	// �˻��� ������ �±�
	enum class EAseTag : char {
		Scene, MaterialList, Mesh
	};
	/*enum class EScene : char {
		_MaterialList = 0,
		FileName, FirstFrame, LastFrame, FrameSpeed, TickPerFrame,
	};*/
	//enum class EMaterial : char {
	//	_Material = 0, _GeomObject, _HelperObject,
	//	MatrialCount, MaterialName, MaterialClass,
	//	NumSubMaterial, SubMaterial,
	//	MapDiffuse, BitMap, MapReflect
	//};
	//enum class EMaterial_Class : char {
	//	Standard, MultySubObject,
	//};
	//enum class EHelper : char {
	//	_GeomObject = 0, _HelperObject,
	//	NodeName, NodeParent, HelperClass,
	//	NodeTM, BoundingMin, BoundingMax, Anim
	//};
	//enum class EGeom : char {
	//	_GeomObject = 0, _HelperObject,
	//	NodeName, NodeParent, MaterialRef,
	//	NodeTM, Mesh, Anim,
	//};
	//enum class EGeom_Mesh : char {
	//	_MaterialRef = 0, _NodeTM, _Animation,
	//	TimeValue,
	//	NumVertex, VertexList, Vertex,			// posision
	//	NumFaces, FaceList, Face,
	//	NumTexVertex, TexVertexList, TexVertex,		// texture
	//	NumTexFaces, TexFaceList, TexFace,
	//	NumColorVertex, ColorVertexList, ColorVertex,	// color
	//	NumColorFace, ColorFaceList, ColorFace,
	//	Nomals, FaceNormal, VertexNormal,	// normal 
	//};
	/*enum class EObject_NodeTM : char {
		_GeomObject = 0, _HelperObject,
		_MaterialRef, _Mesh, _Animation,
		NodeName,
		TM_ROW0, TM_ROW1, TM_ROW2, TM_ROW3,
		TM_POS, TM_ROTAXIS,
		TM_ROTANGLE, TM_SCALE,
		TM_SCALEAXIS, TM_SCALEAXISANG,
	};
	enum class EObject_Animation {
		_GeomObject = 0, _HelperObject, _MaterialRef,
		NodeName,
		PositionTrack, PositionSample,
		RotationTrack, RotationSample,
		ScaleTrack, ScaleSample,
	};*/
protected:
	filesystem::path m_filePath;					// ���� ���
	std::streampos m_fileSize;						// ���� ����Ʈ

	forward_list<wistringstream> m_LineBuffers;				// ��ü ���� �迭
	forward_list<wistringstream>::iterator m_curLineIter;	// ���� ����
	wstring m_subString;		// �ӽ� ��Ʈ��
	SceneData m_SceneData;		// �� ������

	// �˻��� �±� ��
	static map<wstring, EAseTag>			m_AseTag;
	//static map<wstring, EScene>				m_SceneTag;
	//static map<wstring, EMaterial>			m_MaterialTag;
	//static map<wstring, EMaterial_Class>	m_MaterialClass;
	//static map<wstring, EHelper>			m_HelperTag;
	//static map<wstring, EGeom>				m_GeomTag;
	//static map<wstring, EGeom_Mesh>			m_GeomMesh;
	//static map<wstring, EObject_NodeTM>		m_ObjectNodeTM;
	//static map<wstring, EObject_Animation>	m_ObjectAnimation;

	vector<MaterialData>	m_MaterialList;
	map<wstring, GameObject*>			m_Objects;
	map<wstring, InstanceRenderer*>		m_Instances;
private:
	// ���� �������� ��ü ����
	bool LoadFileData(GameObject** ppReturnObj) noexcept;
	// �� ������ ä��
	bool LoadScene(SceneData* pScene) noexcept;
	bool LoadMaterialList(const int& parentCnt) noexcept;
	bool LoadObject(const int& objCnt) noexcept;
	//bool LoadGeomMesh(vector<Vertex_PNCT>* pVertexList, vector<WORD>* pIndexList, const D3DXMATRIX& matWorld)	noexcept;
	//bool LoadObjectNodeTM(GameObject* pObject, CAnimation* pAnimation) noexcept;
	//bool LoadObjectAnimation(vector<Anim>* pAnimations) noexcept;
	//void SetVertexIndex(vector<Vertex_PNCT>* pTempVertex, vector<Vertex_PNCT>* pVertexList, vector<WORD>* pIndexList) noexcept;
	void Clear() noexcept;				// ���� �ʱ�ȭ
public:
	// ���� �ҷ����� ��ü ������ ��ȯ
	bool CreateFromFile(GameObject** ppReturnObj, const wstring_view& fileName, const wstring_view& directory = L"..\\..\\data\\model") noexcept;
public:
	MaxImporter() noexcept;
	virtual ~MaxImporter() = default;
};