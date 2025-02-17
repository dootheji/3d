#pragma once
#include "syStd.h"
#include "syMatrix.h"
#include "syArcBall.h"
#include "syFrustum.h"
class syDebugCamera : public syFrustum
{
public:
	syDebugCamera();
	virtual ~syDebugCamera();

public:
	syArcBall      m_WorldArcBall;
	syArcBall      m_ViewArcBall;

public:
	D3DXVECTOR3		m_ModelCenter;
	D3DXMATRIX		m_mModelLastRot;    // Last arcball rotation matrix for model 
	D3DXMATRIX		m_mModelRot;            // Rotation matrix of model
	D3DXMATRIX		m_mCameraRotLast;

	//이동속도
	float			m_fSpeed;
	//뷰회전에 대한 쿼터니언
	D3DXQUATERNION	m_qRotation;
	// 각 축에 대한 변위값 w=반지름( 원점으로부터의 거리 )
	D3DXVECTOR3		m_vPosDelta;

	//뷰행렬 및 투영행렬
public:
	D3DXMATRIX		m_matWorld;
	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;
	//카메라 방향벡터 위치 / 타겟벡터
	D3DXVECTOR3		m_vLook;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3		m_vRight;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vTarget;
	D3DXVECTOR3		m_vDefaultEye;          // Default camera eye position
	D3DXVECTOR3		m_vDefaultLookAt;       // Default LookAt position

	int			  m_iMouseWhellDelta;
//	D3DXVECTOR4   m_vValue;	//yaw pitch roll값

	// 투영 행렬의 속성값수
	//--------------------------------------------------------------------------------------	
	float				m_fFOV;                 // Field of view
	float				m_fAspect;              // Aspect ratio
	float				m_fNearPlane;           // Near plane
	float				m_fFarPlane;            // Far plane
	// 추가 : 오일러 각 성분 	
	float				m_fCameraYawAngle;
	float				m_fCameraPitchAngle;
	float				m_fCameraRollAngle;
	// 추가 : 반지름( 초기 원점으로부터의 거리) 에 대한 변수 	
	float				m_fRadius;
	float				m_fDefaultRadius;       // Distance from the camera to model 
	float				m_fMinRadius;           // Min radius
	float				m_fMaxRadius;           // Max radius
	//float		  m_fFarPlane = 3000.0f;
	//float		  m_fNearPlane = 1.0f;
	//bool			isCameraMove = true;
	//카메라이동
	void Forward();
	void Backward();
public:
	//--------------------------------------------------------------------------------------
	// 타켓 위치로 부터 거리(반지름)을 지정한다.
	//--------------------------------------------------------------------------------------
	void						SetRadius(float fDefaultRadius = 5.0f, float fMinRadius = 1.0f, float fMaxRadius = FLT_MAX);
public:
	//--------------------------------------------------------------------------------------
	// 추가 : 뷰 방향벡터 저장 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			UpdateVector();
	//--------------------------------------------------------------------------------------
	//카메라 이동
	virtual void				MoveLook(float fValue);
	virtual void				MoveSide(float fValue);
	virtual void				MoveUp(float fValue);
	//--------------------------------------------------------------------------------------
	// 뷰 행렬 계산  
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetViewMatrix(D3DXVECTOR3 vPos,
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	//--------------------------------------------------------------------------------------
	// 투영 행렬 계산 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			SetProjMatrix(FLOAT fFOV,
		FLOAT fAspect,
		FLOAT fNearPlane,
		FLOAT fFarPlane);

	//--------------------------------------------------------------------------------------
	// 오일러 각에 따른 뷰 행렬 계산 
	//--------------------------------------------------------------------------------------
	virtual D3DXMATRIX			Update(D3DXVECTOR4 vDirValue);
	virtual bool				Frame();

	//--------------------------------------------------------------------------------------
	// 윈도우 사이즈가 변경을 반영한다. 
	//--------------------------------------------------------------------------------------
	virtual bool				Init();
	//--------------------------------------------------------------------------------------
	// 윈도우 메세지를 사용하여 카메라 제어 
	//--------------------------------------------------------------------------------------
	virtual LRESULT					MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// 모델 회전 중심위치를 지정한다.
	//--------------------------------------------------------------------------------------
	void						SetModelCenter(D3DXVECTOR3 vModelCenter);

	void						SetTargetPos(D3DXVECTOR3 vPos) { m_vTarget = vPos; };

public:
	//--------------------------------------------------------------------------------------
	// 멤버함수
	//--------------------------------------------------------------------------------------
	D3DXMATRIX*			GetWorldMatrix() { return &m_matWorld; };
	D3DXMATRIX*			GetViewMatrix() { return &m_matView; }
	D3DXMATRIX*			GetProjMatrix() { return &m_matProj; }

	D3DXVECTOR3*		GetEyePt() { return &m_vPosition; }
	D3DXVECTOR3*		GetLookAtPt() { return &m_vTarget; }
	float				GetNearClip() { return m_fNearPlane; }
	float				GetFarClip() { return m_fFarPlane; }

	float				GetYawAngle() { return m_fCameraYawAngle; }
	float				GetPitchAngle() { return m_fCameraPitchAngle; }
	float				GetRollAngle() { return m_fCameraRollAngle; }

	D3DXVECTOR3*		GetRightVector() { return &m_vRight; }
	D3DXVECTOR3*		GetLookVector() { return &m_vLook; }
	D3DXVECTOR3*		GetUpVector() { return &m_vUp; }

	float				GetRadius() { return m_fRadius; }
};


class syGameCamera : public syDebugCamera
{
public:
	syGameCamera();
	virtual ~syGameCamera();
public:
	float m_fOffsetPos;
	D3DXMATRIX    Update(D3DXVECTOR4 vPos);
	bool    Frame();
};