#include "Basic.hlsli"

VSOutput main(float4 pos : POSITION, float2 uv : TEXCOORD)
{
	VSOutput output; //�s�N�Z���V�F�[�_�[n�ɓn���l
	//output.svpos = pos;
	output.svpos = mul(mat, pos);
	output.uv = uv;


	return output;
}