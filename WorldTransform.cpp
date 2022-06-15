#include "WorldTransform.h"
#include "DXInitialize.h"
#include<cmath>



float ConvertRad(float dosuu);

WorldTransform::WorldTransform()
{
	matworld.IdentityMatrix4();
	scale = Vector3(1, 1, 1);
	rotation = Vector3(0, 0, 0);
	translation = Vector3(0, 0, 0);

}

void WorldTransform::Initialize()
{
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void WorldTransform::CreateConstBuffer()
{
	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;			//GPUへの転送用
	//リソース設定
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0Xff;	//256バイトアライメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	HRESULT result;
	
	result = DXInitialize::GetInstance()->Getdevice()->CreateCommittedResource(
		&cbHeapProp,		//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform)
	);
	assert(SUCCEEDED(result));
}

void WorldTransform::Map()
{
	HRESULT result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);	//マッピング
	assert(SUCCEEDED(result));
}

void WorldTransform::UpdateMatrix()
{
	matworld *= ChengeScr();
	matworld *= ChengeRot();
	matworld *= ChengePos();

	constMapTransform->mat = matworld;
}

Matrix4 WorldTransform::ChengeRot()
{
	Matrix4 matRot;
	Matrix4 matRotX, matRotY, matRotZ;

	matRot.IdentityMatrix4();
	matRotX.IdentityMatrix4();
	matRotY.IdentityMatrix4();
	matRotZ.IdentityMatrix4();

	matRotX.m[1][1] = cosf(rotation.x);
	matRotX.m[1][2] = sinf(rotation.x);
	matRotX.m[2][1] = -sinf(rotation.x);
	matRotX.m[2][2] = cosf(rotation.x);

	matRotY.m[0][0] = cosf(rotation.y);
	matRotY.m[0][2] = -sinf(rotation.y);
	matRotY.m[2][0] = sinf(rotation.y);
	matRotY.m[2][2] = cosf(rotation.y);

	matRotZ.m[0][0] = cosf(rotation.z);
	matRotZ.m[0][1] = sinf(rotation.z);
	matRotZ.m[1][0] = -sinf(rotation.z);
	matRotZ.m[1][1] = cosf(rotation.z);

	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	return matRot;
}

Matrix4 WorldTransform::ChengeScr()
{
	Matrix4 matscale;
	matscale.IdentityMatrix4();

	matscale.m[0][0] = scale.x;
	matscale.m[1][1] = scale.y;
	matscale.m[2][2] = scale.z;

	return matscale;
}

Matrix4 WorldTransform::ChengePos()
{
	Matrix4 matTrans;
	matTrans.IdentityMatrix4();

	matTrans.m[3][0] += translation.x;
	matTrans.m[3][1] += translation.y;
	matTrans.m[3][2] += translation.z;

	return matTrans;
}

float ConvertRad(float dosuu)
{
	return dosuu * (PI_ / 180.0f);
}
