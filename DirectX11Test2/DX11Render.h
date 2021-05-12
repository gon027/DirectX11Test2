#pragma once

#include "DirectXLib.h"
#include "Shader.h"

class DX11Render {
public:
	DX11Render();
	~DX11Render() = default;

	bool init(ID3D11Device* _device, ID3D11DeviceContext* _context);

	void update();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;

	VertexShader vertexShader;
	GeometryShader geometryShader;
	PixelShader pixelShader;
	InputLayout inputLayout;
};