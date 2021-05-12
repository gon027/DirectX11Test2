#include "Window.h"
#include "DirectX11.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "DX11Render.h"
#include "Vertex.h"
#include "Camera3D.h"
#include "Rect.h"
#include "Box.h"
#include <vector>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	Window win{ hInstance, nCmdShow, "DirectX 11", 640, 480 };
	if(!win.init()) return -1;

	DirectXDevice dxDevice;
	if(!dxDevice.init(&win)) return -1;

	DX11Render render;
	if (!render.init(dxDevice.getDevicePtr(), dxDevice.getContext())) return -1;

	// 行列などのデータを渡す
	ConstantBuffer cb;
	cb.init(dxDevice.getDevice());

	Camera3D camera;

	Box boxc{ dxDevice.getDevicePtr(), dxDevice.getContext() };

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
				frame += 0.016f;

				camera.update();
				camera.move(0.0f, 0.0f, 5.0f);
				camera.rotate(frame, 0.0f, frame);
			}

			{
				render.update();

				ConstantBufferMatrix cbm{};
				cbm.world      = camera.getTPWorldMatrix();
				cbm.view       = camera.getTPViewMatrix();
				cbm.projection = camera.getTPProjectionMatrix();
				XMStoreFloat4(&cbm.light, XMVector3Normalize(XMVectorSet(0.0f, 5.0f, -3.0f, 0.0f)));
				float a[4] = { frame / 20.0f, frame, frame * 2, frame * 3 };
				cbm.Time[0] = frame / 20.0f;
				cbm.Time[1] = frame;
				cbm.Time[2] = frame * 2.0f;
				cbm.Time[3] = frame * 3.0f;
				dxDevice.setContantBuffer(cb.getConstantBuffer(), cbm);

			}

			// 図形の描画
			{
				boxc.draw();
			}
		}
		dxDevice.DrawEnd();

		Sleep(1);
	}

	return 0;
}