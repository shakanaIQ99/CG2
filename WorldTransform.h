//#pragma once
//#include "Matrix4.h"
//#include "Vector3.h"
//#include <d3d12.h>
//#include <cassert>
//
//const float PI_ = 3.14592654f;
//
//struct ConstBufferDataTransform
//{
//	Matrix4 mat;
//};
//
//
//class WorldTransform
//{
//public:
//	WorldTransform();
//
//	ID3D12Resource* constBuffTransform = nullptr;
//	ConstBufferDataTransform* constMapTransform = nullptr;
//	Matrix4 matworld;
//
//	Vector3 scale;
//	Vector3 rotation;
//	Vector3 translation;
//
//	void Initialize();
//
//	void CreateConstBuffer();
//
//	void Map();
//
//	void UpdateMatrix();
//
//	Matrix4 ChengeRot();
//
//	Matrix4 ChengeScr();
//
//	Matrix4 ChengePos();
//
//private:
//	//ヒープ設定
//	D3D12_HEAP_PROPERTIES cbHeapProp{};
//	//リソース設定
//	D3D12_RESOURCE_DESC cbResourceDesc{};
//
//};
//
