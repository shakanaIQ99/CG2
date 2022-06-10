cbuffer ConstBufferDataMaterial:register(b0)
{
	float4 color;
};

cbuffer ConstBufferDataTransform:register(b1)
{
	matrix mat;
};

//頂点シェーダーの出力構造体
// (頂点シェーダーからピクセルシェーダーへのやり取りに使用する)
struct VSOutput
{
	//システム用頂点座標
	float4 svpos : SV_POSITION;
	float3 normal : NORMAL;
	//uv値
	float2 uv :TEXCOORD;
};
