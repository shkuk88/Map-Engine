#pragma once
#include "Renderer.h"
#include "Particle.h"

#pragma pack(push, 1)
struct ParticleData
{
	D3DXMATRIX matWorld;
	float numTexture;
	D3DXVECTOR4 color;
	//bool isEnable;
};
#pragma pack(pop)

class ParticleSystem : public Renderer
{
private:
	Particle* m_pParticle;
	forward_list<Particle*> m_particleList;
	stack<Particle*>		m_disabledParticle;

	ID3D11Buffer*		 m_pBuffers[2];				  // ���� + �ν��Ͻ�
	ID3D11Buffer*		 m_pInstanceBuffer = nullptr; // ������ ����� ����
	vector<ParticleData> m_dataList;				  // ���� ��� ������
	// ���� ���� ���ÿ�
	UINT Strides[2];				// ���� ũ��
	UINT Offsets[2];				// ���� ������

	bool m_isBillBoard = true;
	bool m_isRepeat    = true;
	bool m_isFollow    = false;
	///bool m_isBounding  = false;
	bool m_isScalarScale = true;
public:
	UINT  m_maxParticleCount;
	float m_spawnInterval;		// ���� ����
	// �ʱ� SRT
	D3DXVECTOR3 m_minInitPosition;
	D3DXVECTOR3 m_maxInitPosition;
	D3DXVECTOR3 m_minInitScale;
	D3DXVECTOR3 m_maxInitScale;
	D3DXVECTOR3 m_minInitRotation;
	D3DXVECTOR3 m_maxInitRotation;
	/// �����ֱ� ũ��, ����
	D3DXVECTOR3 m_minScalePerLife;
	D3DXVECTOR3 m_maxScalePerLife;
	//D3DXVECTOR4 m_minLifePerColor;
	//D3DXVECTOR4 m_maxLifePerColor;
	 
	float m_minLifeCycle;
	float m_maxLifeCycle;

	D3DXVECTOR3 m_minDirection;
	D3DXVECTOR3 m_maxDirection;
	// �̼�
	float m_minMaxMoveSpeed;
	float m_maxMaxMoveSpeed;
	float m_minAccMoveSpeed;
	float m_maxAccMoveSpeed;
	float m_minCurMoveSpeed;
	float m_maxCurMoveSpeed;
	// ȸ��
	D3DXQUATERNION m_minDirAngle;
	D3DXQUATERNION m_maxDirAngle;
	float m_minRotateSpeed;
	float m_maxRotateSpeed;

	D3DXVECTOR4 m_minColor;
	D3DXVECTOR4 m_maxColor;

	D3DXVECTOR3 m_dirGravity;
	float m_minGravityPower;
	float m_maxGravityPower;
private:
	HRESULT Create() noexcept override;
	// ���� ����
	HRESULT CreateInstanceBuffer() noexcept;
	void	UpdateInstanceBuffer(ID3D11DeviceContext* pDContext) noexcept;
	void	UpdateConstBuffer(ID3D11DeviceContext* pDContext) noexcept override;

	// �ν��Ͻ� �߰�, ����
	void AddInstance(Particle* pParticle)				noexcept;
	void RemoveInstance(Particle* pParticle)			noexcept;

	Component* cloneAddition()	noexcept override;
public:
	void SetParticle(Particle* pParticle, const bool& preParticleDelete = true)	noexcept;
	Particle* GetParticle()		noexcept;
	// ����
	void Clear()				noexcept;
	// ������, �ݺ�����
	bool isBillBoard()							noexcept;
	void isBillBoard(const bool& isBillBoard)	noexcept;
	bool isRepeat()								noexcept;
	void isRepeat(const bool& isRepeat)			noexcept;
	bool isFollow()								noexcept;
	void isFollow(const bool& isFollow)			noexcept;
	bool isScalarScale()						noexcept;
	void isScalarScale(const bool& isScalar)	noexcept;

	bool PostRender(ID3D11DeviceContext* pDContext)		noexcept override;
	bool Init()											noexcept override;
	bool Frame(const float& spf, const float& accTime)	noexcept override;
	bool Render(ID3D11DeviceContext* pDContext)			noexcept override;
	bool Release()										noexcept override;
	Component* clone() noexcept override;
private:
	//ParticleSystem() = default;
public:
	ParticleSystem(const wstring_view& myName, Particle* pParticle, const wstring_view& srcName = L"", const string_view& vertexShaderName = "VS_Particle", const string_view& pixelShaderName = "PS_SingleInstance");
	virtual ~ParticleSystem() = default;
};