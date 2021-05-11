#pragma once

#include <string>
#include "DirectXLib.h"

template <class Shader>
class BaseShader {
public:
	BaseShader()
		: shader(nullptr)
	{}

	virtual ~BaseShader() = default;

	virtual bool createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint) = 0;

	const Shader& getShader() {
		return shader;
	}

protected:
	Shader shader;
};

class VertexShader : public BaseShader<D3D11VertexShader> {
public:
	VertexShader();
	~VertexShader() = default;

	bool createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint) override;
};

class PixelShader : public BaseShader<D3D11PixelShader> {
public:
	PixelShader();
	~PixelShader() = default;

	bool createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint) override;
};

class GeometryShader : public BaseShader<D3D11GeometryShader> {
public:
	GeometryShader();
	~GeometryShader() = default;

	bool createShader(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint) override;
};

class InputLayout {
public:
	InputLayout();
	~InputLayout() = default;

	bool createInputLayout(const D3D11Device& _device, const std::string& _fileName, const std::string& _entryPoint);

	const D3D11InputLayout& getInputLayout();

private:
	D3D11InputLayout inputLayout;
};
