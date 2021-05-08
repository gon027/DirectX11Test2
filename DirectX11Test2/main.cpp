#include "Window.h"
#include "DirectX11.h"
#include "DirectX11Buffer.h"
#include "Shader.h"

#include <vector>

struct Vertex {
	XMFLOAT3 pos;
	XMFLOAT4 col;
};

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
		{XMFLOAT3{ -0.5f,-0.5f, 0 },  XMFLOAT4{ 1, 0, 0, 1 }},
		{XMFLOAT3{  0.5f,-0.5f, 0 },  XMFLOAT4{ 0, 1, 0, 1 }},
		{XMFLOAT3{  0.5f, 0.5f, 0 },  XMFLOAT4{ 0, 0, 1, 1 }},
		{XMFLOAT3{ -0.5f, 0.5f, 0 },  XMFLOAT4{ 0, 0, 0, 1 }}
	};

	auto vb = createVertexBuffer(dxDevice.getDevice(), vertexs.data(), static_cast<UINT>(vertexs.size()));
	if (!vb) return -1;
	D3D11VertexBuffer dvb{ nullptr };
	dvb.Attach(vb);
	if (!dvb.Get()) return -1;

	std::vector<UINT> idxs = { 0, 3, 2, 0, 2, 1 };
	auto aa = createIndexBuffer(dxDevice.getDevice(), idxs.data(), static_cast<UINT>(idxs.size()));
	if (!aa) return -1;
	D3D11IndexBuffer ib; 
	ib.Attach(aa);

	MSG msg{ 0 };
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) return 0;

		dxDevice.DrawBegin();

		{
			dxDevice.setVertexShader(vs);
			dxDevice.setPixelShader(ps);
			dxDevice.setInputLayout(il);
			dxDevice.SetVertexBuffer(dvb, sizeof(Vertex));
			dxDevice.SetIndexBuffer(ib);

			// ドローコール
			dxDevice.DrawIndexed(static_cast<UINT>(idxs.size()));
		}

		dxDevice.DrawEnd();

	}

	return 0;
}