#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
	: vertexBuffer(nullptr)
{
}

bool VertexBuffer::init(const D3D11Device& _device, Vertex* VertexData, UINT VertexNum)
{
    //頂点バッファ作成
    //vertDesc{ 0 };
    vertDesc.ByteWidth           = sizeof(Vertex) * VertexNum;
    vertDesc.Usage               = D3D11_USAGE_DEFAULT;
    vertDesc.BindFlags           = D3D11_BIND_VERTEX_BUFFER;
    vertDesc.CPUAccessFlags      = 0;
    vertDesc.MiscFlags           = 0;
    vertDesc.StructureByteStride = 0;

    //vertData{ 0 };
    vertData.pSysMem          = VertexData;
    vertData.SysMemPitch      = 0;
    vertData.SysMemSlicePitch = 0;

    auto hr = _device->CreateBuffer(&vertDesc, &vertData, &vertexBuffer);
    if (FAILED(hr)) {
        return false;
    }

	return true;
}

bool VertexBuffer::update(const D3D11Device& _device)
{
    auto hr = _device->CreateBuffer(&vertDesc, &vertData, &vertexBuffer);
    if (FAILED(hr)) {
        return false;
    }
    return true;
}

ID3D11Buffer* VertexBuffer::getVertexBuffer()
{
	return vertexBuffer.Get();
}
