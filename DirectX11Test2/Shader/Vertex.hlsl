#include "ShaderHeader.h"

PS_INPUT vsMain(VS_INPUT _In) {
	PS_INPUT Out;

	Out.Pos = mul(_In.Pos, World);       // ワールド変換
	Out.Pos = mul(Out.Pos, View);        // ビュー変換
	Out.Pos = mul(Out.Pos, Projection);  // プロジェクション変換
	Out.Col = _In.Col;

	return Out;
}