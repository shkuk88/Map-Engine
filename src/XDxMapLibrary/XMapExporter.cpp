#include "XMapExporter.h"



void XMapExporter::ExportStandard(int iCellCnt, float fDistance)
{
	m_iCellConut = iCellCnt;
	m_fDistance = fDistance;
}

bool XMapExporter::ExportVertexData(vector<PNCT_Vertex>* pVertexList, vector<DWORD>* pIndexList)
{
	m_VertexList.resize(pVertexList->size());
	for (int iLoop = 0; iLoop < pVertexList->size(); iLoop++)
	{
		m_VertexList[iLoop].p = (*pVertexList)[iLoop].p;
		m_VertexList[iLoop].n = (*pVertexList)[iLoop].n;
		m_VertexList[iLoop].c = (*pVertexList)[iLoop].c;
		m_VertexList[iLoop].t = (*pVertexList)[iLoop].t;
	}

	m_IndexList.resize(pIndexList->size());
	for (int iLoop = 0; iLoop < pIndexList->size(); iLoop++)
	{
		m_IndexList[iLoop] = (*pIndexList)[iLoop];
	}
	return true;
}

bool XMapExporter::ExportSpreatTexture(ID3D11DeviceContext* pContext,ID3D11Texture2D * pSpreatTexture)
{
	if (!pSpreatTexture)	return false;
	m_szSpreatTexture = { _T("../Data/Map/Texture/SpreatTexture.bmp") };
	D3DX11SaveTextureToFile(pContext, pSpreatTexture, D3DX11_IFF_BMP, m_szSpreatTexture.c_str());
	return true;
}

bool XMapExporter::ExportAlphaTexture(TCHAR * szAlphaTexture, int iColor)
{
	m_szAlphaTexture[iColor] = szAlphaTexture;
	return true;
}

bool XMapExporter::Export()
{
	if (!FileOpen(_T("../Data/Map/Save/Map.txt"), _T("wt")))	return false;
	// standard
	_ftprintf(m_fp, _T("%d\n"), m_iCellConut);
	_ftprintf(m_fp, _T("%f\n"), m_fDistance);
	// spreat texture
	_ftprintf(m_fp, _T("%s\n"), m_szSpreatTexture.c_str());
	// alpha texture
	for (int iLoop = 0; iLoop < m_szAlphaTexture.size(); iLoop++)
	{
		_ftprintf(m_fp, _T("%s\n"), m_szAlphaTexture[iLoop].c_str());
	}

	// vector list
	_ftprintf(m_fp, _T("%d\n"), m_VertexList.size());
	for (int iLoop = 0; iLoop < m_VertexList.size(); iLoop++)
	{
		_ftprintf(m_fp, _T("%f %f %f %f %f %f %f %f %f %f %f %f\n"), m_VertexList[iLoop].p.x, m_VertexList[iLoop].p.y, m_VertexList[iLoop].p.z,
			m_VertexList[iLoop].n.x, m_VertexList[iLoop].n.y, m_VertexList[iLoop].n.z,
			m_VertexList[iLoop].c.x, m_VertexList[iLoop].c.y, m_VertexList[iLoop].c.z, m_VertexList[iLoop].c.w,
			m_VertexList[iLoop].t.x, m_VertexList[iLoop].t.y);
	}
	// index list
	_ftprintf(m_fp, _T("%d\n"), m_IndexList.size());
	for (int iLoop = 0; iLoop < m_IndexList.size(); iLoop++)
	{
		_ftprintf(m_fp, _T("%d\n"), m_IndexList[iLoop]);
	}
	if (!FileClose())	return false;
	return true;
}

XMapExporter::XMapExporter()
{

}


XMapExporter::~XMapExporter()
{
}