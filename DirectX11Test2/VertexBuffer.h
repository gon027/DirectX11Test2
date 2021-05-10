#pragma once

#include "DirectXLib.h"
#include "Vertex.h"

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer() = default;

    bool init(const D3D11Device& _device, Vertex* VertexData, UINT VertexNum);

    bool update(const D3D11Device& _device);

    ID3D11Buffer* getVertexBuffer();

private:
    D3D11VertexBuffer vertexBuffer;

    D3D11_BUFFER_DESC vertDesc{ 0 };
    D3D11_SUBRESOURCE_DATA vertData{ 0 };
};