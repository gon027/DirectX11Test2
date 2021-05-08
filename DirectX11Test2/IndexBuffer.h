#pragma once

#include "DirectXLib.h"

class IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer() = default;

    bool init(const D3D11Device& _device, UINT* _index, UINT _indexNum);

    ID3D11Buffer* getIndexBuffer();

private:
    D3D11IndexBuffer indexBuffer;
};
