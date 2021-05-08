#pragma once

#include <string>
#include "DirectXLib.h"
#include "Shader.h"

class Window;

class DirectXDevice {
public:
	DirectXDevice();
	~DirectXDevice() = default;

	bool init(const Window* _window);

	void setInputLayout(InputLayout& _inputLayout);

	void setVertexShader(VertexShader& _vertexShader);

	void setPixelShader(PixelShader& _pixelShader);

	void SetVertexBuffer(D3D11VertexBuffer& _vertexBuffer, UINT _vertexSize);

	void SetIndexBuffer(D3D11IndexBuffer& _indexBuffer);
	
	void SetTexture2d(UINT _registerNo, ID3D11ShaderResourceView* _texture);
	
	void DrawBegin();
	
	void DrawEnd();
	
	void DrawIndexed(UINT VertexNum);

	const D3D11Device& getDevice();

private:
	D3D11Device           device;
	D3D11DeviceContext    deviceContext;
	DXGISwapChain         swapChain;
	D3D11RenderTargetView rtView;
	Texture2D             texture;
	D3D11_VIEWPORT        viewport;
};