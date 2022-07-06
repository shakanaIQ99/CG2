#include "Object3D.h"
#include"DXInitialize.h"

Object3D::Object3D()
{
	matworld = XMMatrixIdentity();
	scale = { 1,1,1 };
	rotation = { 0,0,0 };
	translation = { 0,0,0 };

}

void Object3D::Initialize()
{
	HRESULT result;
	D3D12_HEAP_PROPERTIES cbHeapProp{};

	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;			//GPUへの転送用

	//リソース設定
	D3D12_RESOURCE_DESC cbResourceDesc{};
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataTransform) + 0xff) & ~0Xff;	//256バイトアライメント
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	result = DXInitialize::GetInstance()->Getdevice()->CreateCommittedResource(
		&cbHeapProp,		//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,	//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffTransform)
	);
	assert(SUCCEEDED(result));
	result = constBuffTransform->Map(0, nullptr, (void**)&constMapTransform);	//マッピング
	assert(SUCCEEDED(result));
	//単位行列を代入
	constMapTransform->mat = XMMatrixIdentity();

	constMapTransform->mat.r[0].m128_f32[0] = 2.0f / window_width;
	constMapTransform->mat.r[1].m128_f32[1] = -2.0f / window_height;

	constMapTransform->mat.r[3].m128_f32[0] = -1.0f;
	constMapTransform->mat.r[3].m128_f32[1] = 1.0f;
}

void Object3D::UpdateMatrix(XMMATRIX& matview, XMMATRIX& matProjection)
{
	XMMATRIX matScale, matRot, matTrans;
	matScale = XMMatrixScaling(scale.x, scale.y,scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation.z);
	matRot *= XMMatrixRotationX(rotation.x);
	matRot *= XMMatrixRotationY(rotation.y);
	matTrans = XMMatrixIdentity();
	matTrans = XMMatrixTranslation(translation.x, translation.y, translation.z);


	matworld = XMMatrixIdentity();
	matworld *= matScale;
	matworld *= matRot;
	matworld *= matTrans;
	if (parent != nullptr)
	{
		matworld *= parent->matworld;
	}

	constMapTransform->mat = matworld * matview * matProjection;
}

void Object3D::DrawOBJ(UINT numIndices)
{
	DXInitialize::GetInstance()->GetcommandList()->IASetVertexBuffers(0, 1, &DXInitialize::GetInstance()->vbView);
	DXInitialize::GetInstance()->GetcommandList()->IASetIndexBuffer(&DXInitialize::GetInstance()->ibView);
	DXInitialize::GetInstance()->GetcommandList()->SetGraphicsRootConstantBufferView(2, constBuffTransform->GetGPUVirtualAddress());
	DXInitialize::GetInstance()->GetcommandList()->DrawIndexedInstanced(numIndices, 1, 0, 0, 0);
}

Object3D* Object3D::GetInstance()
{
	static Object3D instance;
	return &instance;
}
