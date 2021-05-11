#include "Shader.h"
#include <locale.h>
#include <vector>

namespace flags {

#if defined(_DEBUG)
	// �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
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
	// ���_�V�F�[�_���R���p�C��
	ComPtr<ID3DBlob> blob{ nullptr };
	ComPtr<ID3DBlob> errorBlob{ nullptr };

	auto path = helper::convertWString(_fileName);

	// ���_�V�F�[�_
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
		// �V�F�[�_�̃G���[���e��\��
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

	// �s�N�Z���V�F�[�_
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
		// �V�F�[�_�̃G���[���e��\��
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

	// �W�I���g���V�F�[�_
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
		// �V�F�[�_�̃G���[���e��\��
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

	// �G���[�`�F�b�N.
	if (FAILED(hr))
	{
		// �G���[���b�Z�[�W���o��.
		if (errorBlob != NULL)
		{
			MessageBox(NULL, (char*)errorBlob->GetBufferPointer(), "Vertex Shader is Compile Error. \n", MB_OK);
		}
		return false;
	}

	// Vertex�ɂ�������͐ݒ�
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
