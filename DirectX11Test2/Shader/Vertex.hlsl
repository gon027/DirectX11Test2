#include "ShaderHeader.h"

GS_INPUT vsMain(VS_INPUT _In) {
	float4x4 wvp = mul(mul(World, View), Projection);

	GS_INPUT Out = (GS_INPUT)0;
	Out.Pos = mul(_In.Pos, wvp);  // •ÏŠ·

	float3 normal = mul(_In.Nor, World).xyz;
	Out.Nor = normalize(normal);

	//float col = saturate(dot(normal, (float3)Light));
	//col = col * 0.5f, + 0.5f;
	//Out.Col = float4(col, col, col, 1.0f);
	
	Out.Col = _In.Col;

	return Out;
}