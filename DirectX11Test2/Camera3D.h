#pragma once

#include "DirectXLib.h"

class Camera3D {
public:
	Camera3D();
	~Camera3D() = default;

	void update();

	void move(float _x, float _y, float _z);
	void rotate(float _x, float _y, float _z);

	XMMATRIX getWorldMatrix();
	XMMATRIX getTPWorldMatrix();

	XMMATRIX getViewMatrix();
	XMMATRIX getTPViewMatrix();

	XMMATRIX getProjectionMatrix();
	XMMATRIX getTPProjectionMatrix();

private:
	// �s��
	XMMATRIX world;      // ���[���h�s��
	XMMATRIX view;       // �r���[�s��
	XMMATRIX projection; // �v���W�F�N�V�����s��

	// �x�N�g��
	XMVECTOR eye;
	XMVECTOR up;
	XMVECTOR focus;

	const float fov    = 45.0f;
	const float aspect = 4.0f / 3.0f;
	const float nearZ  = 0.01f;
	const float farZ   = 100.00f;
};