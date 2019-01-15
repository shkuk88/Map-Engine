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
protected:
	filesystem::path m_filePath;							// ���� ���
	std::streampos	 m_fileSize;							// ���� ����Ʈ

	forward_list<istringstream> m_LineBuffers;				// ��ü ���� �迭
	forward_list<istringstream>::iterator m_curLineIter;	// ���� ����
	string m_subString;		// �ӽ� ��Ʈ��
	SceneData m_SceneData;		// �� ������

	// �˻��� �±� ��
	static map<string, EAseTag>			m_AseTag;

	vector<MaterialData>				m_MaterialList;
	map<string, GameObject*>			m_Objects;
	map<wstring, InstanceRenderer*>		m_Instances;
private:
	// ���� �������� ��ü ����
	bool LoadFileData(GameObject** ppReturnObj)			noexcept;
	// �� ������ ä��
	bool LoadScene(SceneData* pScene)					noexcept;
	bool LoadMaterialList(const int& parentCnt)			noexcept;
	bool LoadObject(const int& objCnt)					noexcept;
	// ���� �ʱ�ȭ
	void Clear()										noexcept;
	// Particle
	void LoadParticleSystem(GameObject** ppReturnObj)	noexcept;
public:
	// ���� �ҷ����� ��ü ������ ��ȯ
	bool CreateFromFile(GameObject** ppReturnObj, const wstring_view& fileName, const wstring_view& directory = L"..\\..\\data") noexcept;
public:
	MaxImporter() noexcept;
	virtual ~MaxImporter() = default;
};