#pragma once
#include "syObject.h"

struct syMapDesc
{
	int iNumCols;
	int iNumRows;
	float fCellDistance;
	T_STR szmapTextureFile;
	T_STR szShaderFile;
	T_STR szCubeFile;
};
class syMap : public syModel
{
public:
	int m_iNumRows;
	int m_iNumCols;
	int m_iNumCellRows;
	int m_iNumCellCols;
	int m_iNumVertices;
	int m_iNumFace;
	float m_fCellDistance;
	int*					m_pNormalLookupTable;
	D3DXVECTOR3*			m_pFaceNormals;
	vector<PNCT_VERTEX> m_VertexList;
	D3DXMATRIX				m_matNormal;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pMapTex;
	vector<D3DXVECTOR3>   m_FaceNormals;
	vector<D3DXVECTOR3>		m_vTangentList;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_pTangentVB;

public:
	void	GenVertexNormal();
	void    InitFaceNormals();
	void	CalcFaceNormals();
	
	D3DXVECTOR3	ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);
	virtual float   GetHeightMap(UINT index)
	{
		return 0.0f;
	};
	virtual  D3DXVECTOR3  GetNormalMap(UINT index)
	{
		return D3DXVECTOR3(0, 1, 0);
	};
	virtual D3DXVECTOR4   GetColorMap(UINT index)
	{
		return D3DXVECTOR4(1, 1, 1, 1);
	};
public:
	void		GenNormalLookupTable();
	void		CalcPerVertexNormalsFastLookup();
	virtual bool    Load(ID3D11Device* pd3dDevice, syMapDesc& md);
	HRESULT CreateVertexData();
	HRESULT CreateVertexBuffer();
	HRESULT CreateIndexBuffer();
	HRESULT CreateIndexData();
	HRESULT SetInputLayout();
	bool UpdateBuffer();
public:
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v0,
		D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR2 uv0,
		D3DXVECTOR2 uv1, D3DXVECTOR2 uv2,
		D3DXVECTOR3 *vTangent, D3DXVECTOR3 *vBiNormal, D3DXVECTOR3 *vNormal);
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v1,
		D3DXVECTOR3 *v2,
		D3DXVECTOR3 *v3,
		float v1u, float v1v,
		float v2u, float v2v,
		float v3u, float v3v,
		D3DXVECTOR3 *vTangent,
		D3DXVECTOR3 *vBiNormal,
		D3DXVECTOR3 *vNormal);

public:
	
	virtual void PreRender(ID3D11DeviceContext* pContext, UINT iSize);
	bool	Render(ID3D11DeviceContext*	pContext);
public:
	syMap();
	virtual ~syMap();
};

class syHeightMap : public syMap
{
public :
	syHeightMap() {};
	virtual ~syHeightMap() {}
public:
	vector<float >  m_fHeightList;
public:
	virtual float   GetHeightMap(UINT index)
	{
		return m_fHeightList[index] / 5.0f;
	};
	virtual float GetHeightmap(int row, int col)
	{
		return m_VertexList[row * m_iNumRows + col].p.y;
	}
	float Lerp(float fStart, float fEnd, float fTangent)
	{
		return fStart - (fStart*fTangent) + (fEnd*fTangent);
	}
	virtual float GetHeight(float fPosX, float fPosZ)
	{
		// fPosX/fPosZ의 위치에 해당하는 높이맵셀을 찾는다.
		// m_iNumCols와m_iNumRows은 가로/세로의 실제 크기값임.
		float fCellX = (float)(m_iNumCellCols*m_fCellDistance / 2.0f + fPosX);
		float fCellZ = (float)(m_iNumCellRows*m_fCellDistance / 2.0f - fPosZ);

		// 셀의 크기로 나누어 0~1 단위의 값으로 바꾸어 높이맵 배열에 접근한다.
		fCellX /= (float)m_fCellDistance;
		fCellZ /= (float)m_fCellDistance;

		// fCellX, fCellZ 값보다 작거나 같은 최대 정수( 소수부분을 잘라낸다.)
		float fVertexCol = ::floorf(fCellX);
		float fVertexRow = ::floorf(fCellZ);

		// 높이맵 범위를 벗어나면 강제로 초기화 한다.
		if (fVertexCol < 0.0f)  fVertexCol = 0.0f;
		if (fVertexRow < 0.0f)  fVertexRow = 0.0f;
		if ((float)(m_iNumCols - 2) < fVertexCol)	fVertexCol = (float)(m_iNumCols - 2);
		if ((float)(m_iNumRows - 2) < fVertexRow)	fVertexRow = (float)(m_iNumRows - 2);

		// 계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다. 
		//  A   B
		//  *---*
		//  | / |
		//  *---*  
		//  C   D
		float A = GetHeightmap((int)fVertexRow, (int)fVertexCol);
		float B = GetHeightmap((int)fVertexRow, (int)fVertexCol + 1);
		float C = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol);
		float D = GetHeightmap((int)fVertexRow + 1, (int)fVertexCol + 1);

		// A정점의 위치에서 떨어진 값(변위값)을 계산한다. 0 ~ 1.0f
		float fDeltaX = fCellX - fVertexCol;
		float fDeltaZ = fCellZ - fVertexRow;
		// 보간작업를 위한 기준 페잇스를 찾는다. 
		float fHeight = 0.0f;
		// 윗페이스를 기준으로 보간한다.
		// fDeltaZ + fDeltaX < 1.0f
		if (fDeltaZ < (1.0f - fDeltaX))  //ABC
		{
			float uy = B - A; // A->B
			float vy = C - A; // A->C	
							  // 두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다.		
			fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
		}
		// 아래페이스를 기준으로 보간한다.
		else // DCB
		{
			float uy = C - D; // D->C
			float vy = B - D; // D->B
							  // 두 정점의 높이값의 차이를 비교하여 델타Z의 값에 따라 보간값을 찾는다.		
			fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
		}
		return fHeight;
	}
	/*virtual  Vector3  GetNormalMap(UINT index)
	{
		return Vector3(0,1,0);
	};
	virtual Vector4   GetColorMap(UINT index)
	{
		return Vector4(1, 1, 1,1);
	};*/
	bool CreateHeightMap(ID3D11Device* pd3dDevice,ID3D11DeviceContext*	pContext, const TCHAR* pMapFile);

};