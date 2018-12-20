#pragma once
#include <fstream>
#include <filesystem>
#include "CAnimation.h"
#include "InstanceRenderer.h"

// ~~ ios �ɼ� ~~
// app : ���� ���Ͽ� �߰�, ate : ���� ��ġ�� ���� ��, trunc : ���� ���� ����� ��
// binary : ���̳ʸ� ���, nocreate : ���� �ʰ� �ִ����� �Ǵ�
// cur, beg, end...

// ~~ ifstream ~~
// >> ����, open(url), close(), read(Type, byte)
// seekg(�̵���, ������ġ ios::cur, beg, end...), tellog() : ���� ��ġ ��ȯ
// getLine(ref, maxLength, findChar) -> string::getLine(ifstream, string)
// eof(), 

// ~~ ofstream ~~
// << ����, 
// seekg()


struct SceneDataAse 
{
	wstring FileName;		// ���� �̸�
	int FirstFrame	 = 0;	// ���� ������
	int LastFrame	 = 0;	// �� ������
	int FrameSpeed	 = 0;	// �ʴ� ������ ����
	int TickPerFrame = 0;	// 1������ ƽ ��
	//int MeshCount;		// �޽�������Ʈ ����
	//int MaxWeight;		// ���� �� ����ġ
	//int BindPose;			// ���ε� ���� ���ϸ��̼� ����
};

struct MaterialDataAse
{
	UINT	MaterialIndex;
	wstring MaterialName;
	wstring MaterialClassName;	// Ŭ���� Ÿ��(Standard, SubMaterial...)
	vector<MaterialDataAse> SubMaterials;
	Texture* pTexture = nullptr;
	//vector<Tex>;
	//UINT SubCount;
	//UINT TexMapCount;
	MaterialDataAse* pParent = nullptr;
};



class AseParser
{
protected:
	// �˻��� ������ �±�
	enum class EAseTag : char {
		Scene, MaterialList, GeomObject, HelperObject
	};
	enum class EScene : char {
		_MaterialList = 0,	
		FileName, FirstFrame, LastFrame, FrameSpeed, TickPerFrame,
	};
	enum class EMaterial : char {
		_Material = 0,	_GeomObject, _HelperObject,
		MatrialCount, MaterialName, MaterialClass, 
		NumSubMaterial, SubMaterial,
		MapDiffuse, BitMap, MapReflect
	};
	enum class EMaterial_Class : char {
		Standard, MultySubObject,
	};
	enum class EHelper : char {
		_GeomObject = 0, _HelperObject,
		NodeName, NodeParent, HelperClass, 
		NodeTM, BoundingMin, BoundingMax, Anim
	};
	enum class EGeom : char {
		_GeomObject = 0, _HelperObject,
		NodeName,	NodeParent,		MaterialRef,
		NodeTM,			Mesh,		Anim,	
	};
	enum class EGeom_Mesh : char {
		_MaterialRef = 0,	_NodeTM,			_Animation,		
		TimeValue,
		NumVertex,		VertexList,			Vertex,			// posision
		NumFaces,		FaceList,			Face,
		NumTexVertex,	TexVertexList,		TexVertex,		// texture
		NumTexFaces,	TexFaceList,		TexFace,
		NumColorVertex, ColorVertexList,	ColorVertex,	// color
		NumColorFace,	ColorFaceList,		ColorFace,
		Nomals,			FaceNormal,			VertexNormal,	// normal 
	};
	enum class EObject_NodeTM : char {
		_GeomObject = 0,_HelperObject,
		_MaterialRef,	_Mesh,		_Animation,
		NodeName, 
		TM_ROW0,		TM_ROW1,		TM_ROW2,		TM_ROW3,
		TM_POS,			TM_ROTAXIS, 
		TM_ROTANGLE,	TM_SCALE, 
		TM_SCALEAXIS,	TM_SCALEAXISANG,
	};
	enum class EObject_Animation {
		_GeomObject = 0, _HelperObject, _MaterialRef,
		NodeName,			
		PositionTrack,	 PositionSample,
		RotationTrack,	 RotationSample,
		ScaleTrack,		 ScaleSample,
	};
protected:
	filesystem::path m_filePath;					// ���� ���
	std::streampos m_fileSize;						// ���� ����Ʈ

	forward_list<wistringstream> m_LineBuffers;				// ��ü ���� �迭
	forward_list<wistringstream>::iterator m_curLineIter;	// ���� ����
	wstring m_subString;		// �ӽ� ��Ʈ��
	SceneDataAse m_SceneData;		// �� ������

	// �˻��� �±� ��
	static map<wstring, EAseTag>			m_AseTag;
	static map<wstring, EScene>				m_SceneTag;
	static map<wstring, EMaterial>			m_MaterialTag;
	static map<wstring, EMaterial_Class>	m_MaterialClass;
	static map<wstring, EHelper>			m_HelperTag;
	static map<wstring, EGeom>				m_GeomTag;
	static map<wstring, EGeom_Mesh>			m_GeomMesh;
	static map<wstring, EObject_NodeTM>		m_ObjectNodeTM;
	static map<wstring, EObject_Animation>	m_ObjectAnimation;

	vector<shared_ptr<MaterialDataAse> >	m_MaterialList;
	map<wstring, GameObject*>			m_ObjectList;
	map<wstring, InstanceRenderer*>		m_Instances;
private:
	// ���� �������� ��ü ����
	bool LoadFileData(GameObject** ppReturnObj) noexcept;
	// �� ������ ä��
	bool LoadScene(SceneDataAse* pScene) noexcept;
	bool LoadMaterialList() noexcept;
	bool LoadHelperObject() noexcept;
	bool LoadGeomObject()	noexcept;
	bool LoadGeomMesh(vector<Vertex_PNCT>* pVertexList, vector<WORD>* pIndexList, const D3DXMATRIX& matWorld)	noexcept;
	bool LoadObjectNodeTM(GameObject* pObject, CAnimation* pAnimation) noexcept;
	bool LoadObjectAnimation(vector<Anim>* pAnimations) noexcept;
	void SetVertexIndex(vector<Vertex_PNCT>* pTempVertex, vector<Vertex_PNCT>* pVertexList, vector<WORD>* pIndexList) noexcept;
	void Clear() noexcept;				// ���� �ʱ�ȭ
public:
	// ���� �ҷ����� ��ü ������ ��ȯ
	bool CreateFromFile(GameObject** ppReturnObj, const wstring_view& fileName, const wstring_view& directory = L"..\\..\\data\\model") noexcept;
public:
	AseParser() noexcept;
	virtual ~AseParser() = default;
};