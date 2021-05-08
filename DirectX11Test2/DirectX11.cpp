#include "DirectX11.h"
#include "Window.h"

namespace helper {

	// 一番メモリ量が大きいアダプターを取得する
	DXGIAdapterPtr createDXGIAdapter() {

		DXGIAdapterPtr adapter{ nullptr };

		{
			DXGFactroyPtr factory{ nullptr };
			// グラフィックインターフェースファクトリ作成
			auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
			if (FAILED(hr)) return nullptr;

			int GPUNumber{ 0 };
			int GPUMaxMem{ 0 };

			// hr = factory->EnumAdapters(i, &add);

			// 一番強いGPUアダプタを検索
			DXGIAdapterPtr add{ nullptr };
			for (int i{ 0 }; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters(i, &add); ++i) {
				// DXGIAdapterPtr add{ nullptr };
				// hr = factory->EnumAdapters(i, &add);
				// if (FAILED(hr)) break;

				DXGI_ADAPTER_DESC adapterDesc{};
				hr = add->GetDesc(&adapterDesc);

				// ビデオカード名を取得
				{
					size_t stringLength{ 0 };
					char videoCardDescription[128];
					int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
					if (error != 0) break;
					std::string videoCard = "ビデオカード名 : " + std::string(videoCardDescription) + "\n";
					OutputDebugStringA(videoCard.c_str());
				}

				// ビデオカードメモリを取得
				{
					int videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
					std::string videoCardMemoryStr = "ビデオメモリー : " + std::to_string(videoCardMemory) + "\n";
					OutputDebugStringA(videoCardMemoryStr.c_str());

					// アウトプットに番号をつける
					DXGIOutputPtr adapterOutput{ nullptr };
					hr = add->EnumOutputs(0, &adapterOutput);
					if (FAILED(hr)) continue;

					// DXGI_FORMAT_R8G8B8A8_UNIORMの表示形式数を取得する
					unsigned int numModes{ 0 };
					hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
					if (FAILED(hr)) continue;

					if (videoCardMemory > GPUMaxMem) {
						GPUMaxMem = videoCardMemory;
						GPUNumber = i;
					}
				}
			}

			// グラフィックス　インターフェース　アダプターを作成
			hr = factory->EnumAdapters(GPUNumber, &adapter);
			if (FAILED(hr)) return nullptr;
		}

		return adapter;
	}
}

DirectXDevice::DirectXDevice()
	: device(nullptr)
	, deviceContext(nullptr)
	, swapChain(nullptr)
	, rtView(nullptr)
	, texture(nullptr)
	, viewport({ 0, 0, 0, 0, 0, 0 })
{
}

bool DirectXDevice::init(const Window* _window)
{
	// 最終的にこのアダプターに格納する
	DXGIAdapterPtr adapter{ helper::createDXGIAdapter() };
	if (!adapter) {
		return false;
	}

	// スワップチェイン設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _window->getWindowSize().width;
	sd.BufferDesc.Height = _window->getWindowSize().height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;  // 1 / 60 = 60fps
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _window->getWindowDevice().hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
	};

	// DirectX11デバイスとスワップチェイン作成
	UINT cdev_flags{ 0 };
	auto hr = D3D11CreateDeviceAndSwapChain(
		adapter.Get(),
		D3D_DRIVER_TYPE_UNKNOWN,
		NULL,
		cdev_flags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);

	if (FAILED(hr)) {
		return false;
	}

	// スワップチェインに用意されたバッファ（2Dテクスチャ）を取得
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&texture));
	if (FAILED(hr)) {
		return false;
	}

	// レンダーターゲットView作成
	hr = device->CreateRenderTargetView(
		texture.Get(),
		NULL,
		&rtView
	);

	// viewport設定
	viewport.Width = static_cast<FLOAT>(_window->getWindowSize().width);
	viewport.Height = static_cast<FLOAT>(_window->getWindowSize().height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	return true;
}

void DirectXDevice::setInputLayout(InputLayout& _inputLayout)
{
	deviceContext->IASetInputLayout(_inputLayout.getInputLayout().Get());
}

void DirectXDevice::setVertexShader(VertexShader& _vertexShader)
{
	deviceContext->VSSetShader(_vertexShader.getShader().Get(), nullptr, 0);
}

void DirectXDevice::setPixelShader(PixelShader& _pixelShader)
{
	deviceContext->PSSetShader(_pixelShader.getShader().Get(), nullptr, 0);
}

void DirectXDevice::SetVertexBuffer(ID3D11Buffer* _vertexBuffer, UINT _vertexSize)
{
	UINT hOffsets{ 0 };
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &_vertexSize, &hOffsets);
}

void DirectXDevice::SetIndexBuffer(ID3D11Buffer* _indexBuffer)
{
	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DirectXDevice::SetTexture2d(UINT _registerNo, ID3D11ShaderResourceView* _texture)
{
	deviceContext->PSSetShaderResources(_registerNo, 1, &_texture);
}

void DirectXDevice::DrawBegin()
{
	//ポリゴンの生成方法の指定
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 指定色で画面クリア
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; //red,green,blue,alpha
	deviceContext->ClearRenderTargetView(rtView.Get(), ClearColor);
	deviceContext->RSSetViewports(1, &viewport);

	//RenderTargetをバックバッファ
	ID3D11RenderTargetView* rtv[1] = { rtView.Get() };
	deviceContext->OMSetRenderTargets(1, rtv, nullptr);
}

void DirectXDevice::DrawEnd()
{
	swapChain->Present(0, 0);
}

void DirectXDevice::DrawIndexed(UINT _vertexNum)
{
	deviceContext->DrawIndexed(_vertexNum, 0, 0);
}

const D3D11Device& DirectXDevice::getDevice()
{
	return device;
}
