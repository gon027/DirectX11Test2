#pragma once

#include "DirectXLib.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class Rect {
public:
	Rect(ID3D11Device* _device, ID3D11DeviceContext* _context);
	~Rect() = default;

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
};