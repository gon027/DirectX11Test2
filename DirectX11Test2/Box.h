#pragma once

#include "DirectXLib.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class Box {
public:
	Box(ID3D11Device* _device, ID3D11DeviceContext* _context);
	~Box() = default;

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