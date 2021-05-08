#pragma once

#include "DirectXLib.h"
#include "Vertex.h"

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer() = default;

    bool init(const D3D11Device& _device, Vertex* VertexData, UINT VertexNum);

    ID3D11Buffer* getVertexBuffer();

private:
    D3D11VertexBuffer vertexBuffer;
};