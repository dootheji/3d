#pragma once
#include "syMatrix.h"
#include "syModel.h"
struct TriList {
	int iMapID;
	T_STR szName;
};
struct syTexMap		//
{
	int   iMapID;
	T_STR  szName;
};
class syMaxMtrl
{
public:
	syMaxMtrl() {};
	virtual ~syMaxMtrl() {};
public:
	T_STR		m_szName; //Material#4248
	std::vector<syTexMap>  texList;
	std::vector< syMaxMtrl> m_SubTexture;
};

class syMaxMesh
{
public:
	syMaxMesh() {};
	virtual ~syMaxMesh() {};
public:
	D3DXMATRIX	m_matWorld;
	T_STR		m_szName;
	T_STR		m_ParentzName;
	int			ibufferNum;
	int			ivertexsize;
	vector<vector<PNCT_VERTEX>> vbList;
	vector<vector<DWORD>> ibList;
	int     iMtrlID;
};

class syMaxObject : public syModel
{
public:
	syMaxObject() {};
	virtual ~syMaxObject() {};
public:
	void		getMaxObject(vector<syMaxMesh> m_ObjList, int ObjNum, vector<syMaxMtrl> m_TexList, int TexNum);
	T_STR		m_resourceName;
	vector <syMaxObject> m_subObject;
	virtual HRESULT LoadTextures(ID3D11Device* pd3dDevice, const TCHAR* pLoadTextureFile) override;
};

class syPlaneObject : public syModel
{
public:
	syPlaneObject() {};
	virtual ~syPlaneObject() {};

public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
};


class syDirectionLineObject : public syModel
{
public:
	syDirectionLineObject() {};
	virtual ~syDirectionLineObject() {};

public:
	virtual HRESULT CreateVertexData() override;
	virtual bool  PostRender(ID3D11DeviceContext* pContext);
};

class syBoxObject : public syModel
{
public:
	syBoxObject() {};
	virtual ~syBoxObject() {};

public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
};
class syCircleObject : public syModel
{
public:
	syCircleObject(int num) { iNum = num; };
	syCircleObject() { iNum = 20; };
	virtual ~syCircleObject() {};

public:
	int iNum = 20;
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
};
class syTriangleObject : public syModel
{
public:
	syTriangleObject() {};
	virtual ~syTriangleObject() {};

public:
	virtual HRESULT CreateVertexData() override;

};