#pragma once

#include <d3d11.h>       // DirectX11��API
#include <d3dcompiler.h> // �V�F�[�_�̃R���p�C��
#include <DirectXMath.h> // �x�N�g��FLOAT3�Ȃ̎Z�p���C�u����
#include <wrl/client.h>  // DirectX�ł̃X�}�[�g�|�C���^

// DirectXAPI�֌W�̃����N
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using Microsoft::WRL::ComPtr;

using D3D11ConstantBuffer = ComPtr<ID3D11Buffer>;
using D3D11VertexBuffer   = ComPtr<ID3D11Buffer>;
using D3D11IndexBuffer    = ComPtr<ID3D11Buffer>;
using D3D11InputLayout    = ComPtr<ID3D11InputLayout>;
using D3D11VertexShader   = ComPtr<ID3D11VertexShader>;
using D3D11GeometryShader = ComPtr<ID3D11GeometryShader>;
using D3D11PixelShader    = ComPtr<ID3D11PixelShader>;
using ComputeShader       = ComPtr<ID3D11ComputeShader>;
using Texture2D           = ComPtr<ID3D11Texture2D>;
using ShaderTexture       = ComPtr<ID3D11ShaderResourceView>;
using ComputeOutputView   = ComPtr<ID3D11UnorderedAccessView>;

using D3D11Device           = ComPtr<ID3D11Device>;
using D3D11DeviceContext    = ComPtr<ID3D11DeviceContext>;
using DXGISwapChain         = ComPtr<IDXGISwapChain>;
using D3D11RenderTargetView = ComPtr<ID3D11RenderTargetView>;

using DXGFactroyPtr  = ComPtr<IDXGIFactory>;
using DXGIAdapterPtr = ComPtr<IDXGIAdapter>;
using DXGIOutputPtr  = ComPtr<IDXGIOutput>;