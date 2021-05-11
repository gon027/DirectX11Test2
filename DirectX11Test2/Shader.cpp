#include "Shader.h"
#include <locale.h>
#include <vector>

namespace flags {

#if defined(_DEBUG)
	// グラフィックデバッグツールによるシェーダーのデバッグを有効にする
	constexpr UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	constexpr UINT compileFlags = 0;
#endif

}

namespace helper {

	std::wstring convertWString(const std::string& _str) {
		wchar_t ws[64];
		size_t ret;
		setlocale(LC_CTYPE, "jpn");
		mbstowcs_s(&ret, ws, 64, _str.c_str(), _TRUNCATE);

		return ws;
	}

}

VertexShader::VertexShader()
	: BaseShader()
{

}

bool VertexShader::createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint)
{
	// 頂点シェーダをコンパイル
	ComPtr<ID3DBlob> blob{ nullptr };
	ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto path = helper::convertWString(_fileName);

	// 頂点シェーダ
	auto hr = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_entryPoint.c_str(),
		"vs_5_0",
		flags::compileFlags,
		0,
		&blob,
		&errorBlob
	);

	if (FAILED(hr)) {
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)errorBlob->GetBufferPointer(), "Vertex Shader is Compile Error. \n", MB_OK);
		return false;
	}

	hr = _device->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);

	if (FAILED(hr)) {
		return false;
	}

	return true;
}

PixelShader::PixelShader()
	: BaseShader()
{

}

bool PixelShader::createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint)
{
	ComPtr<ID3DBlob> blob{ nullptr };
	ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto path = helper::convertWString(_fileName);

	// ピクセルシェーダ
	auto hr = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_entryPoint.c_str(),
		"ps_5_0",
		flags::compileFlags,
		0,
		&blob,
		&errorBlob
	);

	if (FAILED(hr)) {
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)errorBlob->GetBufferPointer(), "Pixel Shader is Compile Error. \n", MB_OK);
		return false;
	}

	hr = _device->CreatePixelShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);

	return true;
}


GeometryShader::GeometryShader()
	: BaseShader()
{
}

bool GeometryShader::createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint)
{
	ComPtr<ID3DBlob> blob{ nullptr };
	ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto path = helper::convertWString(_fileName);

	// ジオメトリシェーダ
	auto hr = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_entryPoint.c_str(),
		"gs_5_0",
		flags::compileFlags,
		0,
		&blob,
		&errorBlob
	);

	if (FAILED(hr)) {
		// シェーダのエラー内容を表示
		MessageBox(NULL, (char*)errorBlob->GetBufferPointer(), "Geometry Shader is Compile Error. \n", MB_OK);
		return false;
	}

	hr = _device->CreateGeometryShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&shader
	);

	return true;
}


InputLayout::InputLayout()
	: inputLayout(nullptr)
{

}

bool InputLayout::createInputLayout(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint) {
	ComPtr<ID3DBlob> blob{ nullptr };
	ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto path = helper::convertWString(_fileName);

	auto hr = D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		_entryPoint.c_str(),
		"vs_5_0",
		flags::compileFlags,
		0,
		&blob,
		&errorBlob
	);

	// エラーチェック.
	if (FAILED(hr))
	{
		// エラーメッセージを出力.
		if (errorBlob != NULL)
		{
			MessageBox(NULL, (char*)errorBlob->GetBufferPointer(), "Vertex Shader is Compile Error. \n", MB_OK);
		}
		return false;
	}

	// Vertexにおける入力設定
	const std::vector<D3D11_INPUT_ELEMENT_DESC> elem = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                             0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = _device->CreateInputLayout(
		elem.data(),
		static_cast<UINT>(elem.size()),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);

	return true;
}

const D3D11InputLayout& InputLayout::getInputLayout() {
	return inputLayout;
}
