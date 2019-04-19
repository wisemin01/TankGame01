#pragma once
#include "CComponent.h"
#include "CFrame.h"

class CRenderer :
	public CComponent
{
public:
	UINT m_iRenderType = SCROLL;
	INT m_iRenderLayer = 0;
	INT m_iRenderFrame = 0;

	Vector3 m_vOffset = V3ZERO;
	Vector3 m_vCenter;

	CTexture* m_pTexture = nullptr;

	D3DCOLORVALUE m_ColorValue;

	CFrame m_Frame;
public:
	CRenderer();
	virtual ~CRenderer();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Destroy() override;

	int Width(int index = 0);
	int Height(int index = 0);

	void SetFrameLoop(bool value) { m_Frame.m_bIsLoop = value; }

	void SetFrame(int start, int end, DWORD delay);
	void SetFrameAsFixedDelay(int start, int end);

	int GetNowFrame() { return m_Frame.m_iCurrent; }

	UINT GetRenderType () { return m_iRenderType;  }
	INT  GetRenderLayer() { return m_iRenderLayer; }

	void SetRenderType(UINT render_type) { m_iRenderType = render_type; }
	void SetRenderLayer(INT render_layer) { m_iRenderLayer = render_layer; }

	LPINT GetRenderFramePtr() { return &m_iRenderFrame; }
	void SetRenderFrame(int frame) { m_iRenderFrame = frame; }

	bool CompareRenderType(UINT render_type) { return render_type == m_iRenderType; }
	bool CompareRenderLayer(INT render_layer) { return render_layer == m_iRenderLayer; }

	void SetColor(int a, int r, int g, int b);

	void SetAlpha(int a);
	void SetRed(int r);
	void SetGreen(int g);
	void SetBlue(int b);

	void SetTexture(ResourceID key, int count = -1);
	void SetTexture(CTexture* texture);

	D3DCOLORVALUE GetColor() { return m_ColorValue; }
	D3DCOLOR GetRealColor();

	void SetOffset(Vector3 offset) { m_vOffset = offset; }
	Vector3 GetOffset() { return m_vOffset; }

	int GetAlpha() { return m_ColorValue.a; }

	void operator()(CTexture* texture);
	void operator()(ResourceID rsid);
};

