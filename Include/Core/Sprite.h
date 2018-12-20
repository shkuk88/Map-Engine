#pragma once
#include "Texture.h"

// ���ӵ� ��������Ʈ �� ������ �̹����� ���� ����
class Sprite
{
public:
	Texture*	m_pTexture;		// �ؽ�ó ������
	D3DXVECTOR4	m_textureUV;	// �ؽ�ó ������ǥ
	float		m_frame;		// �ش� ��������Ʈ ����(sec)
public:
	Sprite(Texture* pTexture, const float& frame, const D3DXVECTOR4& textureUV)
	{
		m_pTexture = pTexture;
		m_frame = frame;
		m_textureUV = textureUV;
	};
	Sprite(Texture* pTexture, const float& frame)
	{
		m_pTexture = pTexture;
		m_frame = frame;
		m_textureUV = { 0.0f, 0.0f, 1.0f, 1.0f };
	};
	virtual ~Sprite() = default;
};