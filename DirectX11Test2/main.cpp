#include "Window.h"
#include "DirectX11.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "Vertex.h"
#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	Window win{ hInstance, nCmdShow, "DirectX 11", 640, 480 };
	if(!win.init()) return -1;

	DirectXDevice dxDevice;
	if(!dxDevice.init(&win)) return -1;

	VertexShader vs;
	if(!vs.createShader(dxDevice.getDevice(), "2DPipeLine.hlsl", "vsMain")) return -1;

	PixelShader ps;
	if(!ps.createShader(dxDevice.getDevice(), "2DPipeLine.hlsl", "psMain")) return -1;

	InputLayout il;
	if(!il.createInputLayout(dxDevice.getDevice(), "2DPipeLine.hlsl", "vsMain")) return -1;

	std::vector<Vertex> vertexs =
	{
		{XMFLOAT3{ -0.5f,-0.5f, 2.0f },  XMFLOAT4{ 0, 0, 1, 1 }},
		{XMFLOAT3{  0.5f,-0.5f, 2.0f },  XMFLOAT4{ 0, 1, 1, 1 }},
		{XMFLOAT3{  0.5f, 0.5f, 2.0f },  XMFLOAT4{ 0, 0, 1, 1 }},
		{XMFLOAT3{ -0.5f, 0.5f, 2.0f },  XMFLOAT4{ 0, 0, 1, 1 }},

		{XMFLOAT3{ -0.25f, -0.7f, 0 },  XMFLOAT4{ 0, 0, 1, 1 }},
		{XMFLOAT3{ 0.8f, -0.8f, 0 },  XMFLOAT4{ 0, 0, 1, 1 }},
		{XMFLOAT3{ 0.8f, 0.8f, 0 },  XMFLOAT4{ 0, 0, 1, 1 }},
	};

	std::vector<UINT> idxs = { 0, 3, 2, 0, 2, 1, 4, 6, 5 };

	VertexBuffer vb;
	vb.init(dxDevice.getDevice(), vertexs.data(), static_cast<UINT>(vertexs.size()));

	IndexBuffer ib;
	ib.init(dxDevice.getDevice(), idxs.data(), static_cast<UINT>(idxs.size()));

	ConstantBuffer cb;
	cb.init(dxDevice.getDevice());

	// 変換行列を作成

	float frame = 0.0f;

	MSG msg{ 0 };
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) return 0;

		dxDevice.DrawBegin();
		{
			
			// ワールド座標作成
			XMMATRIX world = XMMatrixIdentity();

			// ビュー行列作成
			XMVECTOR eye   = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
			XMVECTOR focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			XMVECTOR up    = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			XMMATRIX view  = XMMatrixLookAtLH(eye, focus, up);

			// プロジェクション行列作成
			float fov = XMConvertToRadians(45.0f);
			float aspect = 4.0f / 3.0f;
			float nearZ = 0.01f;
			float farZ = 1000.0f;
			XMMATRIX proj = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

			frame += 0.0001f;
			XMMATRIX rot = XMMatrixRotationZ(frame);
			world = XMMatrixMultiply(world, rot);

			ConstantBufferMatrix cbMat{ };
			cbMat.world = world;
			cbMat.view = view;
			cbMat.projection = proj;

			dxDevice.setVertexShader(vs);
			dxDevice.setPixelShader(ps);
			dxDevice.setInputLayout(il);
			dxDevice.SetVertexBuffer(vb.getVertexBuffer(), sizeof(Vertex));
			dxDevice.SetIndexBuffer(ib.getIndexBuffer());
			dxDevice.setContantBuffer(cb.getConstantBuffer(), cbMat);

			// ドローコール
			dxDevice.DrawIndexed(static_cast<UINT>(idxs.size()));
		}
		dxDevice.DrawEnd();

	}

	return 0;
}