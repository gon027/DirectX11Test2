#include "ShaderHeader.h"

GS_INPUT vsMain(VS_INPUT _In) {
	GS_INPUT Out = (GS_INPUT)0;

	float4x4 wvp = mul(mul(World, View), Projection);

	/*
	Out.Pos = mul(_In.Pos, World);       // ワールド変換
	Out.Pos = mul(Out.Pos, View);        // ビュー変換
	Out.Pos = mul(Out.Pos, Projection);  // プロジェクション変換
	*/

	Out.Pos = mul(_In.Pos, wvp);  // プロジェクション変換
	Out.Col = _In.Col;

	return Out;
}