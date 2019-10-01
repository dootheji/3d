#pragma once
#include "syPlaneObject.h"

struct SY_PLANE
{
	float fA, fB, fC, fD;
	bool CreatePlane(D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);
	bool CreatePlane(D3DXVECTOR3 vNormal,
		D3DXVECTOR3 v0);
	void Normalize();
};
class syFrustum
{
public:
	syFrustum();
	virtual ~syFrustum();
public:
	SY_PLANE			m_Plane[6];
	D3DXVECTOR3			m_vFrustum[8];
	syBoxObject			m_FrustumBoxObj;
	D3DXMATRIX			m_matWorld;
	D3DXMATRIX			m_matView;
	D3DXMATRIX			m_matProj;
	D3DXVECTOR3			m_NearCenter;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pPixelShader;
public:
	bool  Init();
	bool  PreRender(ID3D11DeviceContext* pContext, UINT iSize);
	bool  Render(ID3D11DeviceContext*    pContext);
	bool  PostRender(ID3D11DeviceContext*    pContext);
	bool  CreateFrustumObject(ID3D11Device* pd3dDevice);
	void  CreateFrustum(D3DXMATRIX& matView, D3DXMATRIX& matProj);
	void SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
};
