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

	//static std::map<DirectX::Model, wstring> m_models;

public:
	// コンストラクタ
	Obj3d();

	// モデルの読み込み
	void LoadModel(const wchar_t* fileName);

	void Update();

	void Draw();

	// setter
	// スケーリング用
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	// 回転角用
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation) { m_rotation = rotation; }
	// 平行移動用
	void SetTranslation(const DirectX::SimpleMath::Vector3& translation) { m_translation = translation; }
	// 親行列用
	void SetObjParent(Obj3d* pObjParent) { m_pObjParent = pObjParent; }
	// getter
	// スケーリング用
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	// 回転角用
	const DirectX::SimpleMath::Vector3& GetRotation() { return m_rotation; }
	// 平行移動用
	const DirectX::SimpleMath::Vector3& GetTranslation() { return m_translation; }
	// ワールド行列を取得
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }
	// 親行列用
	Obj3d* GetObjParent() { return m_pObjParent; }

private:
	// モデルのユニークポインタ
	std::unique_ptr<DirectX::Model> m_model;
	// スケーリング
	DirectX::SimpleMath::Vector3 m_scale;
	// 回転角
	DirectX::SimpleMath::Vector3 m_rotation;
	// 平行移動
	DirectX::SimpleMath::Vector3 m_translation;
	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;
	// 親となる３Ｄオブジェクトのクラスのポインタ
	Obj3d* m_pObjParent;
};

