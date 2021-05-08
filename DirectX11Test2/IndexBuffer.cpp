#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
	: indexBuffer(nullptr)
{
}

bool IndexBuffer::init(const D3D11Device& _device, UINT* _index, UINT _indexNum)
{
    //インデックスバッファ作成
    D3D11_BUFFER_DESC indexDesc{ 0 };
    indexDesc.ByteWidth           = sizeof(UINT) * _indexNum;
    indexDesc.Usage               = D3D11_USAGE_DEFAULT;
    indexDesc.BindFlags           = D3D11_BIND_INDEX_BUFFER;
    indexDesc.CPUAccessFlags      = 0;
    indexDesc.MiscFlags           = 0;
    indexDesc.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA indexData{ 0 };
    indexData.pSysMem          = _index;
    indexData.SysMemPitch      = 0;
    indexData.SysMemSlicePitch = 0;

    auto hr = _device->CreateBuffer(&indexDesc, &indexData, &indexBuffer);
    if (FAILED(hr)) {
        return false;
    }

	return true;
}

ID3D11Buffer* IndexBuffer::getIndexBuffer()
{
	return indexBuffer.Get();
}
