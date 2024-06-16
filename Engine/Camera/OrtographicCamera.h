#ifndef ORTHOGRAPHICCAMERA_H_
#define ORTHOGRAPHICCAMERA_H_

#include "Camera.h"

#include <glm/fwd.hpp>

#include <array>

class OrthographicCamera : public Camera
{
public:

	struct Frustrum {
		float left;
		float right;
		float bottom;
		float top;
		float near;
		float far;
	};

public:
	OrthographicCamera(const Frustrum& frustrum = { -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f },
		const glm::vec3& position = glm::vec3(0.0f), float rotation = 0.0f) {
		this->Rotation = rotation;
		this->Position = position;
		this->CameraFrustrum = frustrum;

		Camera::ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right,
			CameraFrustrum.bottom, CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;

	}
	~OrthographicCamera() = default;

	OrthographicCamera(const OrthographicCamera& camera) : Camera(camera)
	{
		this->Rotation = camera.Rotation;
		this->CameraFrustrum = camera.CameraFrustrum;
	}

	void SetRotation(float rotation)
	{
		this->Rotation = rotation; this->RecalculateMatrix();
	}

	void SetFrustrum(const Frustrum& frustrum)
	{
		this->CameraFrustrum = frustrum; this->RecalculateMatrix();
	}

protected:
	/**
	*	@brief Recalculating both the projection and view matrix for the camera
	*/
	void RecalculateMatrix() {
		Camera::ProjectionMatrix = glm::ortho(CameraFrustrum.left, CameraFrustrum.right,
			CameraFrustrum.bottom, CameraFrustrum.top, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;
	}

protected:
	float Rotation; // in degrees around the Z axis
	Frustrum CameraFrustrum;
};

#endif // ORTHOGRAPHICCAMERA_H_
