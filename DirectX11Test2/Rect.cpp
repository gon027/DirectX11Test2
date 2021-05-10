#include "Rect.h"

Rect::Rect(ID3D11Device* _device, ID3D11DeviceContext* _context)
	: device(_device)
	, context(_context)
	, vertex(4)
	, index(6)
	, vertexBuffer()
	, indexBuffer()
	, vertexNum(0)
	, indexNum(0)
{

	// í∏ì_Çê›íË
	vertex[0] = { XMFLOAT3{ -0.5f,-0.5f, 0.0f }, XMFLOAT4{ 1, 0, 0, 1 } };
	vertex[1] = { XMFLOAT3{  0.5f,-0.5f, 0.0f }, XMFLOAT4{ 0, 1, 0, 1 } };
	vertex[2] = { XMFLOAT3{ 0.5f, 0.5f, 0.0f },  XMFLOAT4{ 0, 0, 1, 1 } };
	vertex[3] = { XMFLOAT3{ -0.5f, 0.5f, 0.0f }, XMFLOAT4{ 1, 1, 1, 1 } };

	vertexNum = static_cast<UINT>(vertex.size());

	// í∏ì_ÇÃê›íË
	index[0] = 0;
	index[1] = 3;
	index[2] = 2;
	index[3] = 0;
	index[4] = 2;
	index[5] = 1;

	indexNum = static_cast<UINT>(index.size());

	vertexBuffer.init(device, vertex.data(), vertexNum);
	indexBuffer.init(device,  index.data(),  indexNum);
}	

void Rect::draw()
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
