#include "Rect.h"

Rect::Rect(ID3D11Device* _device, ID3D11DeviceContext* _context, const Vector3& _pos, float _size)
	: device(_device)
	, context(_context)
	, vertex(4)
	, index(6)
	, vertexBuffer()
	, indexBuffer()
	, vertexNum(0)
	, indexNum(0)
	, pos(_pos)
	, size(_size)
{
	Vector3 v1{ pos.x - size, pos.y - size, pos.z };
	Vector3 v2{ pos.x + size, pos.y - size, pos.z };
	Vector3 v3{ pos.x + size, pos.y + size, pos.z };
	Vector3 v4{ pos.x - size, pos.y + size, pos.z };

	// í∏ì_Çê›íË

	XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

	vertex[0] = { XMFLOAT3{ v1.x, v1.y, v1.z }, color, XMFLOAT3{ -1.0f, -1.0f, 0.0f} };
	vertex[1] = { XMFLOAT3{ v2.x, v2.y, v2.z }, color, XMFLOAT3{  1.0f, -1.0f, 0.0f} };
	vertex[2] = { XMFLOAT3{ v3.x, v3.y, v3.z }, color, XMFLOAT3{  1.0f,  1.0f, 0.0f} };
	vertex[3] = { XMFLOAT3{ v4.x, v4.y, v4.z }, color, XMFLOAT3{ -1.0f,  1.0f, 0.0f} };

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
void Rect::setPos(float _x, float _y, float _z)
{
	setPos({ _x, _y, _z });
}

void Rect::setPos(const Vector3& _pos)
{
	pos = _pos;
}

void Rect::draw()
{
	Vector3 v1{ pos.x - size, pos.y - size, pos.z };
	Vector3 v2{ pos.x + size, pos.y - size, pos.z };
	Vector3 v3{ pos.x + size, pos.y + size, pos.z };
	Vector3 v4{ pos.x - size, pos.y + size, pos.z };

	// í∏ì_Çê›íË

	XMFLOAT4 color{ 0.0f, 1.0f, 0.0f, 1.0f };

	vertex[0] = { XMFLOAT3{ v1.x, v1.y, v1.z }, color, XMFLOAT3{ -1.0f, -1.0f, 0.0f} };
	vertex[1] = { XMFLOAT3{ v2.x, v2.y, v2.z }, color, XMFLOAT3{  1.0f, -1.0f, 0.0f} };
	vertex[2] = { XMFLOAT3{ v3.x, v3.y, v3.z }, color, XMFLOAT3{  1.0f,  1.0f, 0.0f} };
	vertex[3] = { XMFLOAT3{ v4.x, v4.y, v4.z }, color, XMFLOAT3{ -1.0f,  1.0f, 0.0f} };

	vertexBuffer.update(device);

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
