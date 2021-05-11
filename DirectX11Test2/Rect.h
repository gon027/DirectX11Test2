#pragma once

#include "DirectXLib.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

struct Vector3 {
	float x;
	float y;
	float z;
};

class Rect {
public:
	Rect(ID3D11Device* _device, ID3D11DeviceContext* _context, const Vector3& _pos, float _size);
	~Rect() = default;

	void setPos(float _x, float _y, float _z);
	void setPos(const Vector3& _pos);

	void draw();

private:
	ID3D11Device* device;
	ID3D11DeviceContext* context;

	std::vector<Vertex> vertex;
	std::vector<UINT> index;
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;

	UINT vertexNum;
	UINT indexNum;

	Vector3 pos;
	float size;
};
