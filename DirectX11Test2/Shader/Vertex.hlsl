#include "ShaderHeader.h"

GS_INPUT vsMain(VS_INPUT _In) {
	float4x4 wvp = mul(mul(World, View), Projection);

	GS_INPUT Out = (GS_INPUT)0;
	Out.Pos = mul(_In.Pos, wvp);  // •ÏŠ·

	float3 normal = mul(_In.Nor, World).xyz;
	Out.Nor = normalize(_In.Nor);

	float col = saturate(dot(normal, (float3)Light));
	Out.Col = _In.Col * (1 - col) * abs(sin(Time.y));

	return Out;
}