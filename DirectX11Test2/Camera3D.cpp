#include "Camera3D.h"

namespace helper {

	constexpr float PI = 3.141592f;

	const float toRadian(float _dig) {
		return _dig * PI / 180.00f;
	}
}

namespace {
	float time = 0.0f;
}

Camera3D::Camera3D()
	: world(XMMatrixIdentity())
	, view(XMMatrixIdentity())
	, projection(XMMatrixIdentity())
{
	// ビュー行列作成
	eye   = XMVectorSet(0.0f, 0.0f, -2.0f, 1.0f);
	focus = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	up    = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	view  = XMMatrixLookAtLH(eye, focus, up);

	// プロジェクション行列作成
	projection = XMMatrixPerspectiveFovLH(helper::toRadian(fov), aspect, nearZ, farZ);
}

void Camera3D::update()
{
	world = XMMatrixIdentity();
	time += 0.016f;

}

void Camera3D::move(float _x, float _y, float _z)
{
	XMMATRIX trans = XMMatrixTranslation(_x, _y, _z);
	world = trans * world;
}

void Camera3D::rotate(float _x, float _y, float _z)
{
	XMMATRIX rot = XMMatrixRotationZ(_z);
	rot = rot * XMMatrixRotationX(_x);
	rot = rot * XMMatrixRotationY(_y);
	world = rot * world;
}

XMMATRIX Camera3D::getWorldMatrix()
{
	return world;
}

XMMATRIX Camera3D::getTPWorldMatrix()
{
	return XMMatrixTranspose(world);
}

XMMATRIX Camera3D::getViewMatrix()
{
	return view;
}

XMMATRIX Camera3D::getTPViewMatrix()
{
	return XMMatrixTranspose(view);
}

XMMATRIX Camera3D::getProjectionMatrix()
{
	return projection;
}

XMMATRIX Camera3D::getTPProjectionMatrix()
{
	return  XMMatrixTranspose(projection);
}

