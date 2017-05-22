#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ関数の実体
// カメラ
Camera* Obj3d::m_pCamera;
// 汎用ステート
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
// デバイス
Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;
// コンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;
// エフェクトファクトリ
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;


void Obj3d::InitializeStatic(Camera * pCamera, Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_pCamera = pCamera;
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;

	// ステートの設定
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// エフェクトファクトリ生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// テクスチャの読み込みフォルダを指定
	m_factory->SetDirectory(L"Resources");
}

Obj3d::Obj3d()
{
	// 変数の初期化
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
}
