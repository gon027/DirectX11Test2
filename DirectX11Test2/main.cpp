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

	GeometryShader gs;
	if(!gs.createShader(dxDevice.getDevice(), "Shader/Geometry.hlsl", "gsMain")) return -1;

	InputLayout il;
	if(!il.createInputLayout(dxDevice.getDevice(), "Shader/Vertex.hlsl", "vsMain")) return -1;

	Camera3D camera;

	Rect rc(dxDevice.getDevicePtr(), dxDevice.getContext(), { 0.0f, 0.0f, 3.0f }, 0.5f);

	std::vector<Vertex> box =
	{
		{ XMFLOAT3{ -0.5f, -0.5f, -0.5f },  XMFLOAT4{ 0, 0, 0, 1 }, XMFLOAT3{ -1.0f, -1.0f, -1.0f } }, // 0
		{ XMFLOAT3{  0.5f, -0.5f, -0.5f },  XMFLOAT4{ 0, 0, 1, 1 }, XMFLOAT3{  1.0f, -1.0f, -1.0f } }, // 1
		{ XMFLOAT3{  0.5f,  0.5f, -0.5f },  XMFLOAT4{ 0, 1, 0, 1 }, XMFLOAT3{  1.0f,  1.0f, -1.0f } }, // 2 
		{ XMFLOAT3{ -0.5f,  0.5f, -0.5f },  XMFLOAT4{ 0, 1, 1, 1 }, XMFLOAT3{ -1.0f,  1.0f, -1.0f } }, // 3
		{ XMFLOAT3{  0.5f, -0.5f,  0.5f },  XMFLOAT4{ 1, 0, 0, 1 }, XMFLOAT3{  1.0f, -1.0f,  1.0f } }, // 4
		{ XMFLOAT3{  0.5f,  0.5f,  0.5f },  XMFLOAT4{ 1, 0, 1, 1 }, XMFLOAT3{  1.0f,  1.0f,  1.0f } }, // 5
		{ XMFLOAT3{ -0.5f, -0.5f,  0.5f },  XMFLOAT4{ 1, 1, 0, 1 }, XMFLOAT3{ -1.0f, -1.0f,  1.0f } }, // 6
		{ XMFLOAT3{ -0.5f,  0.5f,  0.5f },  XMFLOAT4{ 1, 1, 1, 1 }, XMFLOAT3{ -1.0f,  1.0f,  1.0f } }, // 7
	};

	std::vector<UINT> idxs2 = {
		0, 3, 2, 0, 2, 1,
		1, 2, 5, 1, 5, 4,
		3, 7, 5, 3, 5, 2,
		4, 5, 7, 4, 7, 6,
		6, 7, 3, 6, 3, 0,
		6, 0, 1, 6, 1, 4,
	};

	VertexBuffer vb2;
	vb2.init(dxDevice.getDevice(), box.data(), static_cast<UINT>(box.size()));

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
			// カメラの更新
			{
				frame += 0.01f;

				camera.update();
				camera.move(0.0f, 0.0f, 5.0f);
				//camera.rotate(frame, 0.0f, frame);
			}

			// シェーダのセット
			{
				dxDevice.setVertexShader(vs);
				dxDevice.getContext()->GSSetShader(gs.getShader().Get(), nullptr, 0);
				dxDevice.setPixelShader(ps);
				dxDevice.setInputLayout(il);
			}

			// 図形の描画
			{
				dxDevice.setContantBuffer(cb.getConstantBuffer(), camera.getMVPMatrix());

				dxDevice.SetVertexBuffer(vb2.getVertexBuffer(), sizeof(Vertex));
				dxDevice.SetIndexBuffer(ib2.getIndexBuffer());
				dxDevice.DrawIndexed(static_cast<UINT>(idxs2.size()));

				rc.setPos({ 0.0f, 0.0f, -3.0f });
				rc.draw();
			}
		}
		dxDevice.DrawEnd();

		Sleep(1);
	}

	return 0;
}