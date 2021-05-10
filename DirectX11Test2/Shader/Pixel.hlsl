#include "ShaderHeader.h"

float4 psMain(PS_INPUT _In) : SV_TARGET {
	return _In.Col;
}