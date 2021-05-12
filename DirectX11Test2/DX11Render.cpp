#include "DX11Render.h"

DX11Render::DX11Render()
	: device(nullptr)
	, context(nullptr)
	, vertexShader()
	, geometryShader()
	, pixelShader()
{
}

bool DX11Render::init(ID3D11Device* _device, ID3D11DeviceContext* _context)
{
	{
		device = _device;
		context = _context;
	}

	if (!vertexShader.createShader(_device, "Shader/Vertex.hlsl", "vsMain")) return false;

	if (!geometryShader.createShader(_device, "Shader/Geometry.hlsl", "gsMain")) return false;

	if (!pixelShader.createShader(_device, "Shader/Pixel.hlsl", "psMain")) return false;

	if (!inputLayout.createInputLayout(_device, "Shader/Vertex.hlsl", "vsMain")) return false;

	return true;
}

void DX11Render::update()
{
	// シェーダをセット
	{
		context->VSSetShader(vertexShader.getShader().Get(), nullptr, 0);
		context->GSSetShader(geometryShader.getShader().Get(), nullptr, 0);
		context->PSSetShader(pixelShader.getShader().Get(), nullptr, 0);
	}

	// インプットレイアウトをセット
	{
		context->IASetInputLayout(inputLayout.getInputLayout().Get());
	}
}
