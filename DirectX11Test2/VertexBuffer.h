#pragma once

#include "DirectXLib.h"

template <class Vertex>
D3D11VertexBuffer createVertexBuffer(const D3D11Device _device, Vertex* vertexData, UINT VertexNum) {
	//頂点バッファ作成
	D3D11_BUFFER_DESC hBufferDesc{};
	ZeroMemory(&hBufferDesc, sizeof(hBufferDesc));
	hBufferDesc.ByteWidth = sizeof(Vertex) * VertexNum;
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA hSubResourceData;
	ZeroMemory(&hSubResourceData, sizeof(hSubResourceData));
	hSubResourceData.pSysMem = vertexData;

	D3D11VertexBuffer vertBuffer;
	auto hr = _device->CreateBuffer(&hBufferDesc, &hSubResourceData, &vertBuffer);
	if (FAILED(hr)) {
		return nullptr;
	}

	return vertBuffer;
}

extern D3D11IndexBuffer CreateIndexBuffer(const D3D11Device _device, UINT* Index, UINT IndexNum)
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

	D3D11IndexBuffer indexBuffer;
	auto hr = _device->CreateBuffer(&hBufferDesc, &hSubResourceData, &indexBuffer);
	if (FAILED(hr)) {
		return nullptr;
	}

	return indexBuffer;
}