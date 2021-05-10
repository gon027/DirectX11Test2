struct VS_INPUT {
	float4 Pos : POSITION;
	float4 Col : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

struct PS_INPUT {
	float4 Pos : SV_POSITION;
	float4 Col : TEXCOORD;
};