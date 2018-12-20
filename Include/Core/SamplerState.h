#pragma once
#include "Input.h"

enum class ESamTextureS : char;
enum class ESamFilterS : char;

class SamplerState
{
private:
	ID3D11SamplerState*			m_pSamplerState;	// ���÷� ����
	D3D11_FILTER				m_curFilter;		// ���� ����
	D3D11_TEXTURE_ADDRESS_MODE	m_curTextureMode;	// ���� �ؽ�ó ��巹�� ���
public:
	void Frame(ID3D11DeviceContext* pDContext) noexcept;
	void Update(ID3D11DeviceContext* pDContext) noexcept;
	void SetSate(ID3D11DeviceContext* pDContext, const UINT& slotIndex, const ESamTextureS& textureEnum, const ESamFilterS& filterEnum, const UINT& maxAnisotropy = 16, const D3D11_COMPARISON_FUNC& compFunc = (D3D11_COMPARISON_FUNC)0) noexcept;

	SamplerState();
	virtual ~SamplerState() = default;
};