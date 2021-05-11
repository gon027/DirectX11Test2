cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
	//float4 Light;
}

struct VS_INPUT {
	float4 Pos    : POSITION;
	float4 Col    : TEXCOORD;
	float3 Nor    : NORMAL;
};

struct GS_INPUT {
	float4 Pos    : SV_POSITION;
	float4 Col    : TEXCOORD;
	float3 Nor    : NORMAL;
};

struct PS_INPUT {
	float4 Pos    : SV_POSITION;
	float4 Col    : TEXCOORD;
};