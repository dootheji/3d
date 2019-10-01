#include "syPlaneObject.h"
#include "syTextureMgr.h"
//HRESULT syMaxObject::CreateVertexData()
//{
//	HRESULT hr = S_OK;
//	//m_VertexList = m_triList;
//	return hr;
//}
//HRESULT syMaxObject::CreateIndexData()
//{
//	HRESULT hr = S_OK;
//	return hr;
//}
//HRESULT syMaxObject::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
//{
//	HRESULT hr = S_OK;
//
//	
//	T_STR dir = L"../../data/bitmap/";
//	dir = dir + m_TexList[0].szName;
//
//	if (m_TexList[0].szName.length() == 0) return S_OK;
//	int iIndex = I_TextureMgr.Load(
//		m_pDevice,
//		dir);
//
//	m_dxObj.m_pSRV = I_TextureMgr.GetPtr(iIndex)->m_pSRV;
//
//	return hr;
//}
HRESULT syPlaneObject::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_VertexList.resize(4);
	m_VertexList[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_VertexList[0].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_VertexList[1].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[1].t = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[2].p = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	m_VertexList[2].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[2].t = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexList[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_VertexList[3].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[3].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[3].t = D3DXVECTOR2(0.0f, 1.0f);
	return hr;
}
HRESULT syPlaneObject::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(6);
	m_IndexList[0] = 1;
	m_IndexList[1] = 2;
	m_IndexList[2] = 0;
	m_IndexList[3] = 2;
	m_IndexList[4] = 3;
	m_IndexList[5] = 0;
	return hr;
}

HRESULT syDirectionLineObject::CreateVertexData()
{
	m_VertexList.resize(6);
	m_VertexList[0].p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[1].p = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
	m_VertexList[1].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[1].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[1].t = D3DXVECTOR2(1.0f, 0.0f);

	m_VertexList[2].p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[2].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[2].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[2].t = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[3].p = D3DXVECTOR3(0.0f, 1000.0f, 0.0f);
	m_VertexList[3].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[3].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);
	m_VertexList[3].t = D3DXVECTOR2(1.0f, 0.0f);


	m_VertexList[4].p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[4].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[4].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[4].t = D3DXVECTOR2(0.0f, 0.0f);

	m_VertexList[5].p = D3DXVECTOR3(0.0f, 0.0f, 1000.0f);
	m_VertexList[5].n = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexList[5].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	m_VertexList[5].t = D3DXVECTOR2(1.0f, 0.0f);
	return S_OK;
}

bool  syDirectionLineObject::PostRender(ID3D11DeviceContext* pContext)
{
	pContext->IASetPrimitiveTopology(
		D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	m_dxObj.PostRender(pContext,
		m_dxObj.m_iNumIndex);

	return true;
}

HRESULT syBoxObject::CreateVertexData()
{
	// »ó´Ü
	// 5    6
	// 1    2
	// ÇÏ´Ü
	// 4    7
	// 0    3  
	// ¾Õ¸é
	HRESULT hr = S_OK;
	
	m_VertexList.resize(24);
	m_VertexList[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	// µÞ¸é
	m_VertexList[4] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[6] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[7] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[8] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[9] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[10] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[11] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿ÞÂÊ
	m_VertexList[12] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[13] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[14] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[15] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// À­¸é
	m_VertexList[16] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[17] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[18] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[19] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¾Æ·§¸é
	m_VertexList[20] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[21] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[22] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[23] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	return hr;
}
HRESULT syBoxObject::CreateIndexData()
{
	HRESULT hr = S_OK;

	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

	return hr;
}

HRESULT syCircleObject::CreateVertexData()
{
	HRESULT hr = S_OK;

	float rad = DegreeToRandian(360/20);
	m_VertexList.resize(iNum+1);

	m_VertexList[0].p = D3DXVECTOR3(0, 0, -0.5f);
	m_VertexList[0].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = D3DXVECTOR2(1.0f, 0.0f);
	for (int i = 1; i < iNum+1; i++)
	{
		m_VertexList[i].p = D3DXVECTOR3(cos(rad*i), sin(rad*i), -0.5f);
		m_VertexList[i].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		m_VertexList[i].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
		m_VertexList[i].t = D3DXVECTOR2(cos(rad*i),  sin(rad*i));
	}
	

	return hr;
}
HRESULT syCircleObject::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(iNum*3);
	for (int i = 0; i < iNum * 3; )
	{
		static int j = 1;
		m_IndexList[i] = 0;
		m_IndexList[i+1] = j++;
		m_IndexList[i+2] = j;
		i = i + 3;
	}
	m_IndexList[iNum*3 - 3] = 0;
	m_IndexList[iNum*3 - 2] = iNum;
	m_IndexList[iNum*3 - 1] = 1;
	return hr;
}


HRESULT syTriangleObject::CreateVertexData()
{
	HRESULT hr = S_OK;

	m_VertexList.resize(3);

	m_VertexList[0].p = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_VertexList[0].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[0].t = D3DXVECTOR2(0.0f, 1.0f);

	m_VertexList[1].p = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexList[1].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[1].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[1].t = D3DXVECTOR2(0.5f, 0.0f);

	m_VertexList[2].p = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_VertexList[2].n = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_VertexList[2].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexList[2].t = D3DXVECTOR2(1.0f, 1.0f);
	return hr;
}
HRESULT syMaxObject::LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile)
{
	HRESULT hr = S_OK;
	T_STR dir = L"../../data/bitmap/";
	dir = dir + m_resourceName;

	if (m_resourceName.length() == 0) return S_OK;
	int iIndex = I_TextureMgr.Load(
		m_pDevice,
		dir);

	m_dxObj.m_pSRV = I_TextureMgr.GetPtr(iIndex)->m_pSRV;
	return hr;
}
void syMaxObject::getMaxObject(vector<syMaxMesh> m_ObjList, int ObjNum,
	vector<syMaxMtrl> m_TexList, int TexNum)
{
	int shipsize = m_ObjList[ObjNum].ibufferNum;
	m_subObject.resize(shipsize);
	for (int shipNum = 0; shipNum < m_ObjList[ObjNum].ibufferNum; shipNum++)
	{
		m_subObject[shipNum].SetMatrix(&m_ObjList[ObjNum].m_matWorld, nullptr, nullptr);

		m_subObject[shipNum].m_VertexList = m_ObjList[ObjNum].vbList[shipNum];
		m_subObject[shipNum].m_IndexList = m_ObjList[ObjNum].ibList[shipNum];
		m_subObject[shipNum].m_resourceName = m_TexList[TexNum].m_SubTexture[shipNum].texList[0].szName;
	}

}