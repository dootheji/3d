#include "sample.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "syStd.h"
#include "syTextureMgr.h"
sample::sample()
{
}


sample::~sample()
{
}




bool sample::Init()
{
	m_cbLight.g_cAmbientMaterial = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1);
	m_cbLight.g_cDiffuseMaterial = D3DXVECTOR4(0.9, 0.9, 0.9, 1);
	m_cbLight.g_cAmbientLightColor = D3DXVECTOR4(1, 1, 1, 1);
	m_cbLight.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
	

	m_pConstantBufferLight.Attach(DX::CreateConstantBuffer(
		m_pDevice, &m_cbLight, 1, sizeof(LIGHT_CONSTANT_BUFFER)));

	Import(L"../../data/text/final.SY");
	//getMaxObject();
	m_Ship.getMaxObject(m_ObjList, 0, m_TexList, 0);
	for (int i = 0; i < m_Ship.m_subObject.size(); i++)
	{
		if (!m_Ship.m_subObject[i].Create(m_pDevice, L"../../data/shader/shader.hlsl", nullptr))
		{
			return false;
		};
	}

	m_CameraBack.Init();
	m_CameraBack.CreateFrustumObject(m_pDevice);
	m_CameraBack.SetViewMatrix(D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_CameraBack.SetProjMatrix(D3DX_PI / 4, g_rtClient.right / g_rtClient.bottom, 1.0f, 1000.0f);
	m_pMainCamera = &m_CameraBack;

	return true;
}
bool sample::Frame()
{
	m_vLightVector.x = 1;// cosf(g_fGameTimer) / 2 + 0.5f;
	m_vLightVector.y = 1;// sinf(g_fGameTimer) / 2 + 0.5f;
	m_vLightVector.z = 1;// cosf(g_fGameTimer) * sinf(g_fGameTimer) / 2 + 0.5f;

	D3DXVec3Normalize(&m_vLightVector, &m_vLightVector);

	//m_vLightVector *= -1.0f;
	//for (int i = 0; i < m_ObjList.size(); i++)
	//{
	//	if (!m_ObjList[i].Frame());
	//	{
	//		return false;
	//	};
	//}
	return true;
}
bool sample::Render()
{
	m_cbLight.g_vLightDir.x = m_vLightVector.x;
	m_cbLight.g_vLightDir.y = m_vLightVector.y;
	m_cbLight.g_vLightDir.z = m_vLightVector.z;
	m_cbLight.g_vLightDir.w = 1;

	m_cbLight.g_vEyeDir.x = m_pMainCamera->GetLookVector()->x;
	m_cbLight.g_vEyeDir.y = m_pMainCamera->GetLookVector()->y;
	m_cbLight.g_vEyeDir.z = m_pMainCamera->GetLookVector()->z;
	m_cbLight.g_vEyeDir.w = 100;

	m_cbLight.g_vEyePos.x = m_pMainCamera->GetEyePt()->x;
	m_cbLight.g_vEyePos.y = m_pMainCamera->GetEyePt()->y;
	m_cbLight.g_vEyePos.z = m_pMainCamera->GetEyePt()->z;
	m_cbLight.g_vEyePos.w = 1;
	D3DXMATRIX matInvWorld;
	D3DXMatrixInverse(&matInvWorld, NULL, &m_pMainCamera->m_matWorld);
	D3DXMatrixTranspose(&matInvWorld, &matInvWorld);
	D3DXMatrixTranspose(&m_cbLight.g_matInvWorld, &matInvWorld);

	for (int i = 0; i < m_Ship.m_subObject.size(); i++)
	{
		m_Ship.m_subObject[i].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_Ship.m_subObject[i].Render(m_pImmediateContext);
		
	}
	//
	//for (int i = 0; i < m_ObjList.size(); i++)
	//{
	//	m_ObjList[i].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//	m_pImmediateContext->UpdateSubresource(m_pConstantBufferLight.Get(), 0, NULL, &m_cbLight, 0, 0);
	//	m_pImmediateContext->VSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());
	//	m_pImmediateContext->PSSetConstantBuffers(1, 1, m_pConstantBufferLight.GetAddressOf());

	//	m_ObjList[i].Render(m_pImmediateContext);
	//}
	return true;
}
bool sample::Release()
{
	/*for (auto obj : m_ObjList)
	{
		obj.Release();
	}*/
	return true;
}
bool sample::Import(wstring filename)
{
	char buffer[256];
	static TCHAR CheckFile[MAX_PATH];
	static TCHAR ExporterCheck[MAX_PATH];
	static TCHAR HeaderCheck[MAX_PATH];
	static TCHAR MaterialCheck[MAX_PATH];
	ZeroMemory(&buffer, sizeof(char) * 256);
	ZeroMemory(CheckFile, _countof(CheckFile));
	ZeroMemory(ExporterCheck, _countof(ExporterCheck));
	ZeroMemory(HeaderCheck, _countof(HeaderCheck));
	ZeroMemory(MaterialCheck, _countof(MaterialCheck));

	FILE* pStream = nullptr;
	_wfopen_s(&pStream, filename.c_str(), _T("rb"));


	_ftscanf_s(pStream, _T("%s"), CheckFile, _countof(CheckFile));
	//(필요) syexporter100인지 검증작업 필요 

	int objsize = 0;
	int texsize = 0;
	_ftscanf_s(pStream, _T("%s %d %d"), HeaderCheck, _countof(HeaderCheck), &objsize, &texsize);
	//HeaderCheck == #HEADER INFO" 검증
	m_ObjList.resize(objsize);
	m_TexList.resize(texsize);

	_ftscanf_s(pStream, _T("%s"), MaterialCheck, _countof(MaterialCheck));
	//MaterialCheck == #MATERIAL INFO" 검증


	for (int iMtl = 0; iMtl < m_TexList.size(); iMtl++)
	{
		static TCHAR texname[MAX_PATH];
		ZeroMemory(texname, _countof(texname));
		int subtexsize = 0;
		_ftscanf_s(pStream, _T("\n%s %d"),
			texname, _countof(texname),
			&subtexsize);
		m_TexList[iMtl].m_szName = texname;
		m_TexList[iMtl].m_SubTexture.resize(subtexsize);

		if (m_TexList[iMtl].m_SubTexture.size() > 0)
		{
			for (int iSubMtrl = 0; iSubMtrl < m_TexList[iMtl].m_SubTexture.size(); iSubMtrl++)
			{
				static TCHAR subtexname[MAX_PATH];
				ZeroMemory(subtexname, _countof(subtexname));
				int subtexsize = 0;

				_ftscanf_s(pStream, _T("\n%s %d"),
					subtexname, _countof(subtexname),
					&subtexsize
				);
				m_TexList[iMtl].m_SubTexture[iSubMtrl].m_szName = subtexname;
				m_TexList[iMtl].m_SubTexture[iSubMtrl].texList.resize(subtexsize);
						
				for (int iTex = 0; iTex < m_TexList[iMtl].m_SubTexture[iSubMtrl].texList.size(); iTex++)
				{
					int mapid = 0;
					static TCHAR texfilename[MAX_PATH];
					ZeroMemory(texfilename, _countof(texfilename));
					_ftscanf_s(pStream, _T("\n%d %s"),
						&mapid,
						texfilename, _countof(texfilename));
					m_TexList[iMtl].m_SubTexture[iSubMtrl].texList[iTex].iMapID = mapid;
					m_TexList[iMtl].m_SubTexture[iSubMtrl].texList[iTex].szName = texfilename;

				}
			}
		}
		else
		{
			static TCHAR subtexname[MAX_PATH];
			ZeroMemory(subtexname, _countof(subtexname));
			int subtexsize = 0;
			_ftscanf_s(pStream, _T("\n%s %d"),
				subtexname, _countof(subtexname),
				&subtexsize
			);
			//subtexsize == L"none" 체크 필요
			m_TexList[iMtl].texList.resize(subtexsize);
			for (int iTex = 0; iTex < m_TexList[iMtl].texList.size(); iTex++)
			{
				static TCHAR texlistname[MAX_PATH];
				ZeroMemory(texlistname, _countof(texlistname));
				int MapID = 0;

				_ftscanf_s(pStream, _T("\n%d %s"),
					&MapID,
					texlistname, _countof(texlistname));

				m_TexList[iMtl].texList[iTex].iMapID = MapID;
				m_TexList[iMtl].texList[iTex].szName = texlistname;

			}
		}
	}
	

	// mesh list
	static TCHAR meshname[MAX_PATH];
	ZeroMemory(meshname, _countof(meshname));
	_ftscanf_s(pStream, _T("\n%s"), meshname, _countof(meshname));
	//L"#OBJECT_INFO"일치하는지 검증 필요
	//검증

	for (int iObj = 0; iObj < m_ObjList.size(); iObj++)
	{
		static TCHAR sname[MAX_PATH];
		ZeroMemory(sname, _countof(sname));
		static TCHAR sparnetname[MAX_PATH];
		ZeroMemory(sparnetname, _countof(sparnetname));
		int buffersize = 0;
		int vertexsize = 0;
		_ftscanf_s(pStream, _T("\n%s %s %d %d %d"),
			sname, _countof(sname),
			sparnetname, _countof(sparnetname),
			&m_ObjList[iObj].iMtrlID,
			&m_ObjList[iObj].ibufferNum,		//5    subobj 수
			&m_ObjList[iObj].ivertexsize);		//4158 전체 vertex 수
		m_ObjList[iObj].m_szName = sname;
		m_ObjList[iObj].m_ParentzName = sparnetname;
		m_ObjList[iObj].vbList.resize(m_ObjList[iObj].ibufferNum);
		m_ObjList[iObj].ibList.resize(m_ObjList[iObj].ibufferNum);
		_ftscanf_s(pStream, _T("%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f\n\t%f %f %f %f"),
			&m_ObjList[iObj].m_matWorld._11,
			&m_ObjList[iObj].m_matWorld._12,
			&m_ObjList[iObj].m_matWorld._13,
			&m_ObjList[iObj].m_matWorld._14,

			&m_ObjList[iObj].m_matWorld._21,
			&m_ObjList[iObj].m_matWorld._22,
			&m_ObjList[iObj].m_matWorld._23,
			&m_ObjList[iObj].m_matWorld._24,

			&m_ObjList[iObj].m_matWorld._31,
			&m_ObjList[iObj].m_matWorld._32,
			&m_ObjList[iObj].m_matWorld._33,
			&m_ObjList[iObj].m_matWorld._34,

			&m_ObjList[iObj].m_matWorld._41,
			&m_ObjList[iObj].m_matWorld._42,
			&m_ObjList[iObj].m_matWorld._43,
			&m_ObjList[iObj].m_matWorld._44);



		for (int iSubTri = 0; iSubTri < m_ObjList[iObj].ibufferNum; iSubTri++)
		{
			vector<PNCT_VERTEX>& vList = m_ObjList[iObj].vbList[iSubTri];

			static TCHAR verListCheck[MAX_PATH];
			ZeroMemory(verListCheck, _countof(verListCheck));
			int verlistSize = 0;
			_ftscanf_s(pStream, _T("%s %d"),
				verListCheck, _countof(verListCheck),
				&verlistSize);
			vList.resize(verlistSize);
			//verListCheck == nVertexList랑 같은지 검증 필요
			for (int iVer = 0; iVer < vList.size(); iVer++)
			{
				_ftscanf_s(pStream, _T("%f %f %f"),
					&vList[iVer].p.x,
					&vList[iVer].p.y,
					&vList[iVer].p.z);
				_ftscanf_s(pStream, _T("%f %f %f"),
					&vList[iVer].n.x,
					&vList[iVer].n.y,
					&vList[iVer].n.z);
				_ftscanf_s(pStream, _T("%f %f %f %f"),
					&vList[iVer].c.x,
					&vList[iVer].c.y,
					&vList[iVer].c.z,
					&vList[iVer].c.w);
				_ftscanf_s(pStream, _T("%f %f"),
					&vList[iVer].t.x,
					&vList[iVer].t.y);
			}

			vector<DWORD>& iList =	m_ObjList[iObj].ibList[iSubTri];
			static TCHAR indexListCheck[MAX_PATH];
			ZeroMemory(indexListCheck, _countof(indexListCheck));
			int indexlistSize = 0;
			_ftscanf_s(pStream, _T("%s %d"),
				indexListCheck, _countof(indexListCheck),
				&indexlistSize);
			iList.resize(indexlistSize);
			//nIndexList
			for (int iIndex = 0; iIndex < iList.size(); iIndex += 3)
			{
				_ftscanf_s(pStream, _T("%d %d %d"),
					&iList[iIndex + 0],
					&iList[iIndex + 1],
					&iList[iIndex + 2]);
			}
		}
	}

	fclose(pStream);


	return true;


}

bool sample::getMaxObject()
{
	int shipsize = m_ObjList[0].ibufferNum;
	m_Ship.m_subObject.resize(shipsize);
	for (int shipNum = 0; shipNum < m_ObjList[0].ibufferNum; shipNum++)
	{
		m_Ship.m_subObject[shipNum].SetMatrix(&m_ObjList[0].m_matWorld, nullptr, nullptr);
	
		m_Ship.m_subObject[shipNum].m_VertexList = m_ObjList[0].vbList[shipNum];
		m_Ship.m_subObject[shipNum].m_IndexList = m_ObjList[0].ibList[shipNum];
		m_Ship.m_subObject[shipNum].m_resourceName = m_TexList[0].m_SubTexture[shipNum].texList[0].szName;
	}
	return true;
}

