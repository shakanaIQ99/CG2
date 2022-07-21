#pragma once
#include<DirectXMath.h>
using namespace DirectX;
#include "Vector3.h"
#include <d3d12.h>
#include <cassert>

#include<wrl.h>

using namespace Microsoft::WRL;

const float PI_ = 3.14592654f;

struct ConstBufferDataTransform
{
	XMMATRIX mat;
};

struct Object3D
{
	Object3D();


	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform;

	XMMATRIX matworld;

	Vector3 scale;
	Vector3 rotation;
	Vector3 translation;

	void Initialize();

	void UpdateMatrix(XMMATRIX& matview,XMMATRIX&matProjection);

	void DrawOBJ(UINT numIndices);

	Object3D* parent = nullptr;

	static Object3D* GetInstance();
};