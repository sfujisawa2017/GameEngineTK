/// <summary>
/// ３Ｄオブジェクトのクラス
/// </summary>
#pragma once

#include <memory>
#include <windows.h>
#include <wrl/client.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
	// 静的メンバ
public:
	// 静的メンバの初期化
	static void InitializeStatic(Camera* pCamera,
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);

private:
	// カメラ
	static Camera* m_pCamera;
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	// コンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	// 汎用ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	// コンストラクタ
	Obj3d();

	// モデルの読み込み
	void LoadModel(const wchar_t* fileName);

	// setter
	// スケーリング用

	// 回転角用

	// 平行移動用

	// getter
	// スケーリング用

	// 回転角用

	// 平行移動用

	// ワールド行列を取得

private:
	// モデルのユニークポインタ
	
	// スケーリング

	// 回転角

	// 平行移動

	// ワールド行列

	// 親となる３Ｄオブジェクトのクラスのポインタ
	Obj3d* m_pObjParent;
};