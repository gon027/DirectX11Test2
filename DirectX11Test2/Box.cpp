#include "Box.h"

namespace {
	constexpr int VERTEXCOUNT = 8;
	constexpr int INDEXCOUNT = 36;
}

Box::Box(ID3D11Device* _device, ID3D11DeviceContext* _context)
	: device(_device)
	, context(_context)
	, vertex(VERTEXCOUNT)
	, index(INDEXCOUNT)
	, vertexBuffer()
	, indexBuffer()
	, vertexNum(VERTEXCOUNT)
	, indexNum(INDEXCOUNT)
{
	{
		std::vector<Vertex> box =
		{
			{ XMFLOAT3{ -0.5f, -0.5f, -0.5f },  XMFLOAT4{ 0, 0, 0, 1 }, XMFLOAT3{ -1.0f, -1.0f, -1.0f } }, // 0
			{ XMFLOAT3{  0.5f, -0.5f, -0.5f },  XMFLOAT4{ 0, 0, 1, 1 }, XMFLOAT3{  1.0f, -1.0f, -1.0f } }, // 1
			{ XMFLOAT3{  0.5f,  0.5f, -0.5f },  XMFLOAT4{ 0, 1, 0, 1 }, XMFLOAT3{  1.0f,  1.0f, -1.0f } }, // 2 
			{ XMFLOAT3{ -0.5f,  0.5f, -0.5f },  XMFLOAT4{ 0, 1, 1, 1 }, XMFLOAT3{ -1.0f,  1.0f, -1.0f } }, // 3
			{ XMFLOAT3{  0.5f, -0.5f,  0.5f },  XMFLOAT4{ 1, 0, 0, 1 }, XMFLOAT3{  1.0f, -1.0f,  1.0f } }, // 4
			{ XMFLOAT3{  0.5f,  0.5f,  0.5f },  XMFLOAT4{ 1, 0, 1, 1 }, XMFLOAT3{  1.0f,  1.0f,  1.0f } }, // 5
			{ XMFLOAT3{ -0.5f, -0.5f,  0.5f },  XMFLOAT4{ 1, 1, 0, 1 }, XMFLOAT3{ -1.0f, -1.0f,  1.0f } }, // 6
			{ XMFLOAT3{ -0.5f,  0.5f,  0.5f },  XMFLOAT4{ 1, 1, 1, 1 }, XMFLOAT3{ -1.0f,  1.0f,  1.0f } }, // 7
		};

		vertex = std::move(box);
	}

	{
		std::vector<UINT> idxs = {
			0, 3, 2, 0, 2, 1,
			1, 2, 5, 1, 5, 4,
			3, 7, 5, 3, 5, 2,
			4, 5, 7, 4, 7, 6,
			6, 7, 3, 6, 3, 0,
			6, 0, 1, 6, 1, 4,
		};

		index = std::move(idxs);
	}

	vertexBuffer.init(device, vertex.data(), vertexNum);
	indexBuffer.init(device, index.data(), indexNum);
}

void Box::draw()
{
	UINT hOffsets{ 0 };
	ID3D11Buffer* ppVertexBuffer = vertexBuffer.getVertexBuffer();
	UINT strides = sizeof(Vertex);
	context->IASetVertexBuffers(
		0,
		1,
		&ppVertexBuffer,
		&strides,
		&hOffsets
	);

	context->IASetIndexBuffer(
		indexBuffer.getIndexBuffer(),
		DXGI_FORMAT_R32_UINT,
		0
	);

	context->DrawIndexed(indexNum, 0, 0);
}
