#pragma once

#include "DirectXLib.h"

template<class Vertex>
ID3D11Buffer* createVertexBuffer(const D3D11Device& _device, Vertex* VertexData, UINT VertexNum)
{
    //頂点バッファ作成
    D3D11_BUFFER_DESC hBufferDesc;
    ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
    hBufferDesc.ByteWidth      = sizeof(Vertex) * VertexNum;
    hBufferDesc.Usage          = D3D11_USAGE_DEFAULT;
    hBufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    hBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA hSubResourceData;
    ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
    hSubResourceData.pSysMem = VertexData;

    ID3D11Buffer* hpBuffer;
    auto hr = _device->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer);
    if (FAILED(hr)) {
        return nullptr;
    }

    return hpBuffer;
}

extern ID3D11Buffer* createIndexBuffer(const D3D11Device& _device, UINT* Index, UINT IndexNum)
{
    //インデックスバッファ作成
    D3D11_BUFFER_DESC hBufferDesc;
    ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
    hBufferDesc.ByteWidth = sizeof(UINT) * IndexNum;
    hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    hBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    hBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA hSubResourceData;
    ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
    hSubResourceData.pSysMem = Index;

    ID3D11Buffer* hpBuffer;
    auto hr = FAILED(_device->CreateBuffer(&hBufferDesc, &hSubResourceData, &hpBuffer));
    if (hr) {
        return nullptr;
    }

    return hpBuffer;
}