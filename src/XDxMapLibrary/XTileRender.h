#pragma once
#include "XQuadTreeIndex.h"


// XSpreatController���� Texture�� �����ϰ�
// XMultiTextureRender������ 4���� Alpha Blending�� �ؽ�ó�� ȥ���ؼ� Render
class XTileRender:public XQuadTreeIndex
{
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render(ID3D11DeviceContext* pContext) override;
	virtual bool Release() override;
public:
	XTileRender();
	virtual ~XTileRender();
};

