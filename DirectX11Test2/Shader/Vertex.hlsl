#include "ShaderHeader.h"

PS_INPUT vsMain(VS_INPUT _In) {
	PS_INPUT Out;

	Out.Pos = mul(_In.Pos, World);       // ���[���h�ϊ�
	Out.Pos = mul(Out.Pos, View);        // �r���[�ϊ�
	Out.Pos = mul(Out.Pos, Projection);  // �v���W�F�N�V�����ϊ�
	Out.Col = _In.Col;

	return Out;
}