#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
{
}

bool ConstantBuffer::init(const D3D11Device& _device)
{
	// コンスタントバッファ作成
	D3D11_BUFFER_DESC constBufDesc{ 0 };
	constBufDesc.ByteWidth           = sizeof(ConstantBufferMatrix);
	constBufDesc.Usage               = D3D11_USAGE_DEFAULT;
	constBufDesc.BindFlags           = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc.CPUAccessFlags      = 0;
	constBufDesc.MiscFlags           = 0;
	constBufDesc.StructureByteStride = sizeof(float);

	auto hr = _device.Get()->CreateBuffer(&constBufDesc, nullptr, &constantBuffer);
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

ID3D11Buffer* ConstantBuffer::getConstantBuffer()
{
	return constantBuffer.Get();
}
