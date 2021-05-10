#include "Window.h"
#include "DirectX11.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Shader.h"
#include "Vertex.h"
#include "Camera3D.h"
#include "Rect.h"
#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	Window win{ hInstance, nCmdShow, "DirectX 11", 640, 480 };
	if(!win.init()) return -1;

	DirectXDevice dxDevice;
	if(!dxDevice.init(&win)) return -1;

	VertexShader vs;
	if(!vs.createShader(dxDevice.getDevice(), "Shader/Vertex.hlsl", "vsMain")) return -1;

	PixelShader ps;
	if(!ps.createShader(dxDevice.getDevice(), "Shader/Pixel.hlsl", "psMain")) return -1;

	InputLayout il;
	if(!il.createInputLayout(dxDevice.getDevice(), "Shader/Vertex.hlsl", "vsMain")) return -1;

	Camera3D camera;

	Rect rc(dxDevice.getDevicePtr(), dxDevice.getContext());;

	std::vector<Vertex> vertexs2 =
	{
		{ XMFLOAT3{ -0.25f, -0.7f, 3 },  XMFLOAT4{ 0, 0, 1, 1 } },
		{ XMFLOAT3{  0.80f, -0.8f, 3 },   XMFLOAT4{ 0, 0, 1, 1 } },
		{ XMFLOAT3{  0.80f, 0.8f,  3 },    XMFLOAT4{ 0, 0, 1, 1 } },
	};

	std::vector<UINT> idxs2 = { 0, 2, 1 };

	VertexBuffer vb2;
	vb2.init(dxDevice.getDevice(), vertexs2.data(), static_cast<UINT>(vertexs2.size()));

	IndexBuffer ib2;
	ib2.init(dxDevice.getDevice(), idxs2.data(), static_cast<UINT>(idxs2.size()));

	ConstantBuffer cb;
	cb.init(dxDevice.getDevice());

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
			frame += 0.01f;

			camera.update();
			camera.rotate(0.0f, 0.0f, frame);
			// camera.move(1.0f, 0.0f, 0.0f);

			dxDevice.setVertexShader(vs);
			dxDevice.setPixelShader(ps);
			dxDevice.setInputLayout(il);

			dxDevice.setContantBuffer(cb.getConstantBuffer(), camera.getMVPMatrix());

			rc.draw();

			// dxDevice.SetVertexBuffer(vb2.getVertexBuffer(), sizeof(Vertex));
			// dxDevice.SetIndexBuffer(ib2.getIndexBuffer());

			// ドローコール
			// dxDevice.DrawIndexed(static_cast<UINT>(idxs.size()));
		}
		dxDevice.DrawEnd();

		Sleep(1);

	}

	return 0;
}