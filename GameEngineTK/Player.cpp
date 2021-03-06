//--------------------------------------------------------------------------------------
// ファイル名: Player.cpp
// 作成者:
// 作成日:
// 説明:
//--------------------------------------------------------------------------------------

#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Player::~Player()
{
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void Player::Initialize()
{
	// 自機パーツのロード
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_TOWER].LoadModel(L"Resources/tower.cmo");
	m_Obj[PARTS_BASE].LoadModel(L"Resources/base.cmo");
	m_Obj[PARTS_ENGINE_R].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_ENGINE_L].LoadModel(L"Resources/engine.cmo");
	m_Obj[PARTS_FAN].LoadModel(L"Resources/fan.cmo");
	m_Obj[PARTS_SCORE].LoadModel(L"Resources/score.cmo");
	// 親子関係の構築（子供に親をセット）
	m_Obj[PARTS_BASE].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_SCORE].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_ENGINE_R].SetObjParent(
		&m_Obj[PARTS_TOWER]);
	m_Obj[PARTS_ENGINE_L].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	m_Obj[PARTS_FAN].SetObjParent(
		&m_Obj[PARTS_TOWER]);

	// 親からのオフセット（ローカルの座標ずれ）
	m_Obj[PARTS_TOWER].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_BASE].SetTranslation(
		Vector3(0, 0.7f, 0));

	m_Obj[PARTS_SCORE].SetTranslation(
		Vector3(0, 0.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));

	m_Obj[PARTS_ENGINE_R].SetTranslation(
		Vector3(0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_R].SetRotation(
		Vector3(0, XMConvertToRadians(45), 0));

	m_Obj[PARTS_ENGINE_L].SetTranslation(
		Vector3(-0.22f, 0.3f, 0.22f));
	m_Obj[PARTS_ENGINE_L].SetRotation(
		Vector3(0, XMConvertToRadians(-45), 0));

	m_Obj[PARTS_FAN].SetTranslation(
		Vector3(0, 0.3f, 1.0f));

	// 発射中ではない
	m_FireFlag = false;

	// 武器の当たり判定ノード設定
	{
		m_CollisionNodeBullet.Initialize();
		// 武器パーツにぶら下げる
		m_CollisionNodeBullet.SetParent(&m_Obj[PARTS_SCORE]);
		// 武器パーツからのオフセット
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		// 当たり判定の半径
		m_CollisionNodeBullet.SetLocalRadius(0.2f);
	}
	// 全身の当たり判定ノード設定
	{
		m_CollisionNodeBody.Initialize();
		// ベースパーツにぶら下げる
		m_CollisionNodeBody.SetParent(&m_Obj[0]);
		// ベースパーツからのオフセット
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.5f, 0));
		// 当たり判定の半径
		m_CollisionNodeBody.SetLocalRadius(0.5f);
	}

	m_isJump = false;
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void Player::Update()
{
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

	// スペースを押したらジャンプ
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		// ジャンプ開始
		StartJump();
	}

	// ジャンプ中なら
	if (m_isJump)
	{
		// 下方向に加速
		m_Velocity.y -= GRAVITY_ACC;
		if (m_Velocity.y <= -JUMP_SPEED_MAX)
		{
			m_Velocity.y = -JUMP_SPEED_MAX;
		}
	}

	Vector3 trans = this->GetTrans();
	trans += m_Velocity;
	this->SetTrans(trans);

	// 自機パーツのギミック
	//{
	//	// 自機の角度を変動
	//	Vector3 angle;

	//	angle = m_Obj[PARTS_SCORE].GetRotation();
	//	m_Obj[PARTS_SCORE].SetRotation(
	//		angle + Vector3(0.2f, 0.1f, 0));

	//	// サインの引数の角度がだんだん増える
	//	m_sinAngle += 0.1f;
	//	// ファンの角度がいったりきたりする(-1〜+1)
	//	float fan_angle = sinf(m_sinAngle) * 3.0f;
	//	/*m_Obj[PLAYER_PARTS_FAN].SetRotation(
	//	Vector3(0, 0, fan_angle));*/
	//	//m_Obj[PARTS_FAN].SetTranslation(
	//	//	Vector3(sinf(m_sinAngle), 0, cosf(m_sinAngle)*3.0f));
	//}


	// Aキーを押している間
	if (keystate.A)
	{
		// 自機の角度を変動
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle + 0.03f, 0));
	}

	// Dキーを押している間
	if (keystate.D)
	{
		// 自機の角度を変動
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(
			Vector3(0, angle - 0.03f, 0));
	}

	// Wキーを押している間
	if (keystate.W)
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 今の角度に合わせて移動ベクトルを回転
		// 回転行列
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	// Sキーを押している間
	if (keystate.S)
	{
		// 移動ベクトル
		Vector3 moveV(0, 0, +0.1f);
		// 回転行列
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動
		Vector3 pos = m_Obj[0].GetTranslation();
		pos += moveV;
		m_Obj[0].SetTranslation(pos);
	}

	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		if (m_FireFlag)
		{
			ResetBullet();
		}
		else
		{
			FireBullet();
		}
	}

	// 弾丸が進む処理
	if (m_FireFlag)
	{		
		// 自機の座標を移動
		Vector3 pos = m_Obj[PARTS_SCORE].GetTranslation();
		pos += m_BulletVel;
		m_Obj[PARTS_SCORE].SetTranslation(pos);
	}

	// 行列更新
	Calc();

	//FireBullet();
}

//-----------------------------------------------------------------------------
// 行列更新
//-----------------------------------------------------------------------------
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}

	// 当たり判定ノード更新
	m_CollisionNodeBullet.Update();
	// 当たり判定ノード更新
	m_CollisionNodeBody.Update();
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}

	m_CollisionNodeBullet.Draw();
	m_CollisionNodeBody.Draw();
}

void Player::FireBullet()
{
	if (m_FireFlag) return;

	// ワールド行列を取得
	Matrix worldm = m_Obj[PARTS_SCORE].GetWorld();

	Vector3 scale;	// ワールドスケーリング
	Quaternion rotation;	// ワールド回転
	Vector3 translation;	// ワールド座標

	// ワールド行列から各要素を取り出す
	worldm.Decompose(scale, rotation, translation);

	// 親子関係を解除してパーツを独立させる
	m_Obj[PARTS_SCORE].SetObjParent(nullptr);
	m_Obj[PARTS_SCORE].SetScale(scale);
	m_Obj[PARTS_SCORE].SetRotationQ(rotation);
	m_Obj[PARTS_SCORE].SetTranslation(translation);

	// 弾の速度を設定
	m_BulletVel = Vector3(0, 0, -0.1f);
	// 弾の向きに合わせて進行方向を回転
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	m_Obj[PARTS_SCORE].SetObjParent(
		&m_Obj[PARTS_BASE]);

	m_Obj[PARTS_SCORE].SetTranslation(
		Vector3(0, 0.0f, 0));
	m_Obj[PARTS_SCORE].SetScale(
		Vector3(2, 2, 2));
	m_Obj[PARTS_SCORE].SetRotation(Vector3(0, 0, 0));

	m_FireFlag = false;

}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// タンクパーツの座標を返す
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3& Player::GetRot()
{
	// タンクパーツの座標を返す
	return m_Obj[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_Obj[0].GetWorld();
}

/// <summary>
/// ジャンプ開始
/// </summary>
void Player::StartJump()
{
	if (!m_isJump)
	{
		// 上方向の初速を設定
		m_Velocity.y = JUMP_SPEED_FIRST;
		m_isJump = true;
	}
}

/// <summary>
/// 落下開始
/// </summary>
void Player::StartFall()
{
	if (!m_isJump)
	{
		// 上方向の初速を設定
		m_Velocity.y = 0.0f;
		m_isJump = true;
	}
}

/// <summary>
/// ジャンプ終了
/// </summary>
void Player::StopJump()
{
	m_isJump = false;
	m_Velocity = Vector3::Zero;
}