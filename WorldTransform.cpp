#include "WorldTransform.h"
#include "DXInitialize.h"
#include<cmath>





//WorldTransform::WorldTransform()
//{
//	matworld= XMMatrixIdentity();
//	scale = Vector3(1, 1, 1);
//	rotation = Vector3(0, 0, 0);
//	translation = Vector3(0, 0, 0);
//
//}
//
//void WorldTransform::Initialize()
//{
//	HRESULT result;
//	D3D12_HEAP_PROPERTIES cbHeapProp{};
//
//	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;			//GPUへの転送用
//
//	//リソース設定
//	D3D12_RESOURCE_DESC cbResourceDesc{};
//	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
//	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0Xff;	//256バイトアライメント
//	cbResourceDesc.Height = 1;
//	cbResourceDesc.DepthOrArraySize = 1;
//	cbResourceDesc.MipLevels = 1;
//	cbResourceDesc.SampleDesc.Count = 1;
//	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
//
//	result = DXInitialize::GetInstance()->Getdevice()->CreateCommittedResource(
//		&cbHeapProp,		//ヒープ設定
//		D3D12_HEAP_FLAG_NONE,
//		&cbResourceDesc,	//リソース設定
//		D3D12_RESOURCE_STATE_GENERIC_READ,
//		nullptr,
//		IID_PPV_ARGS(&constBuffTransform)
//	);
//	assert(SUCCEEDED(result));
//	result =constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);	//マッピング
//	assert(SUCCEEDED(result));
//}
//
//
//
//
//
//void WorldTransform::UpdateMatrix()
//{
//	matworld *= ChengeScr();
//	matworld *= ChengeRot();
//	matworld *= ChengePos();
//
//	if (parent != nullptr)
//	{
//		matworld *= parent->matworld;
//	}
//	constMapTransform->mat = matworld * DXInitialize::GetInstance()->matview * DXInitialize::GetInstance()->matProjection;
//}
//
//void WorldTransform::DrawOBJ(UINT numIndices)
//{
//	DXInitialize::GetInstance()->commandList->IASetVertexBuffers(0, 1, &DXInitialize::GetInstance()->vbView);
//	DXInitialize::GetInstance()->commandList->IASetIndexBuffer(&DXInitialize::GetInstance()->ibView);
//	DXInitialize::GetInstance()->commandList->SetGraphicsRootConstantBufferView(2, DXInitialize::GetInstance()->obj->constBuffTransform->GetGPUVirtualAddress());
//	DXInitialize::GetInstance()->commandList->DrawIndexedInstanced(numIndices, 1, 0, 0, 0);
//}
//
//XMMATRIX WorldTransform::ChengeRot()
//{
//	XMMATRIX matRot;
//	XMMATRIX matRotX, matRotY, matRotZ;
//
//	matRot =XMMatrixIdentity();
//	matRotX=XMMatrixIdentity();
//	matRotY=XMMatrixIdentity();
//	matRotZ=XMMatrixIdentity();
//
//	matRotX.r[1].m128_f32[1] = cosf(rotation.x);
//	matRotX.r[1].m128_f32[2] = sinf(rotation.x);
//	matRotX.r[2].m128_f32[1] = -sinf(rotation.x);
//	matRotX.r[2].m128_f32[2] = cosf(rotation.x);
//
//	matRotY.r[0].m128_f32[0] = cosf(rotation.y);
//	matRotY.r[0].m128_f32[2] = -sinf(rotation.y);
//	matRotY.r[2].m128_f32[0] = sinf(rotation.y);
//	matRotY.r[2].m128_f32[2] = cosf(rotation.y);
//
//	matRotZ.r[0].m128_f32[0] = cosf(rotation.z);
//	matRotZ.r[0].m128_f32[1] = sinf(rotation.z);
//	matRotZ.r[1].m128_f32[0] = -sinf(rotation.z);
//	matRotZ.r[1].m128_f32[1] = cosf(rotation.z);
//
//	matRot *= matRotZ;
//	matRot *= matRotX;
//	matRot *= matRotY;
//
//	return matRot;
//}
//
//XMMATRIX WorldTransform::ChengeScr()
//{
//	XMMATRIX matscale;
//	matscale= XMMatrixIdentity();
//
//	matscale.r[0].m128_f32[0] = scale.x;
//	matscale.r[1].m128_f32[1] = scale.y;
//	matscale.r[2].m128_f32[2] = scale.z;
//
//	return matscale;
//}
//
//XMMATRIX WorldTransform::ChengePos()
//{
//	XMMATRIX matTrans;
//	matTrans= XMMatrixIdentity();
//
//	matTrans.r[3].m128_f32[0] += translation.x;
//	matTrans.r[3].m128_f32[1] += translation.y;
//	matTrans.r[3].m128_f32[2] += translation.z;
//
//	return matTrans;
//}
//
//float ConvertRad(float dosuu)
//{
//	return dosuu * (PI_ / 180.0f);
//}
