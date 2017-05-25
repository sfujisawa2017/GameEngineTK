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
	m_scale = Vector3(1, 1, 1);

	m_pObjParent = nullptr;
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(
		m_d3dDevice.Get(),
		fileName,
		*m_factory
	);
}

void Obj3d::Update()
{
	// 行列を計算
	// スケーリング行列
	Matrix scalemat = Matrix::CreateScale(m_scale);
	// 回転行列
	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotation.z);
	Matrix rotmatX = Matrix::CreateRotationX(m_rotation.x);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotation.y);
	Matrix rotmat = rotmatZ * rotmatX * rotmatY;
	// 平行移動行列
	Matrix transmat = Matrix::CreateTranslation(m_translation);
	// ワールド行列を合成
	m_world = scalemat * rotmat * transmat;
	// 親の行列をかける
	if (m_pObjParent)
	{
		m_world *= m_pObjParent->GetWorld();
	}
}

void Obj3d::Draw()
{
	// モデルを描画
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(),
			*m_states,
			m_world,
			m_pCamera->GetView(),
			m_pCamera->GetProj());
	}
}
