#include "ShaderHeader.h"

[maxvertexcount(9)]
void gsMain(triangle GS_INPUT input[3], inout TriangleStream<PS_INPUT> output) {

	float4x4 wvp = mul(mul(World, View), Projection);
	
	[unroll] for (uint i = 0; i < 3; i++) {
		PS_INPUT o = (PS_INPUT)0;
		o.Pos = input[i].Pos;
		o.Col = input[i].Col;
		output.Append(o);
	}
	output.RestartStrip();
	
}
