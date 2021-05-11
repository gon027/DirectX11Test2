#include "ShaderHeader.h"

GS_INPUT vsMain(VS_INPUT _In) {
	GS_INPUT Out = (GS_INPUT)0;

	float4x4 wvp = mul(mul(World, View), Projection);

	/*
	Out.Pos = mul(_In.Pos, World);       // ���[���h�ϊ�
	Out.Pos = mul(Out.Pos, View);        // �r���[�ϊ�
	Out.Pos = mul(Out.Pos, Projection);  // �v���W�F�N�V�����ϊ�
	*/

	Out.Pos = mul(_In.Pos, wvp);  // �v���W�F�N�V�����ϊ�
	Out.Col = _In.Col;

	return Out;
}