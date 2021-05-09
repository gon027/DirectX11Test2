#pragma once

#include "DirectXLib.h"

class ConstantBuffer {
public:
	ConstantBuffer();
	~ConstantBuffer() = default;

	bool init(const D3D11Device& _device);

	ID3D11Buffer* getConstantBuffer();

private:
	D3D11ConstantBuffer constantBuffer;
};