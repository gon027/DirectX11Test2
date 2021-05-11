
cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

struct VS_INPUT {
	float4 vertex;
	float4 color;
};

struct PS_INPUT {
	float4 vertex;
	float4 color;
};

float4 ConvertWVP(float4 _vertex) {
	return mul(_vertex, mul(mul(World, View), Projection));
}

PS_INPUT vsMain(VS_INPUT _In) {
	PS_INPUT o = (PS_INPUT)0;
	o.vertex = ContertWVP(_In.vertes);
	o.color = _In.color;
	return o;
}

float4 psMain(PS_INPUT _In) {
	return _In.color;
}