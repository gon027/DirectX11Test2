
struct VS_INPUT {
	float4 Pos : POSITION;
	float4 Col : TEXCOORD;
};

struct PS_INPUT {
	float4 Pos : SV_POSITION;
	float4 Col : TEXCOORD;
};

cbuffer ConstantBuffer : register(b0) {
	matrix World;
	matrix View;
	matrix Projection;
}

PS_INPUT vsMain(VS_INPUT IN) {
	PS_INPUT OUT = (PS_INPUT)0;

	OUT.Pos = mul(IN.Pos, World);        // ワールド変換
	OUT.Pos = mul(OUT.Pos, View);        // ビュー変換
	//OUT.Pos = mul(OUT.Pos, Projection);  // プロジェクション変換
	OUT.Col = IN.Col;

	return OUT;
}

float4 psMain(PS_INPUT input) : SV_TARGET{
	return input.Col;
}