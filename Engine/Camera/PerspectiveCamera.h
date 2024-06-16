#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "Camera.h"

#include <array>

class PerspectiveCamera : public Camera
{
public:

	struct Frustrum {
		float angle;
		float width;
		float height;
		float near;
		float far;
	};

public:
	PerspectiveCamera(const GLint width, const GLint heigth, 
		const glm::vec3& position,
		const Frustrum& frustrum = { 45.0f, 800.0f, 800.0f, 0.1f, -1.0f },
		const glm::vec3& lookAt = glm::vec3(0.0f, 2.0f, 0.0f),
		const glm::vec3& upVector = glm::vec3(0.0f, 1.0f, 0.0f)) {

		CameraFrustrum = frustrum;
		CameraFrustrum.width = width;
		CameraFrustrum.height = heigth;
		Camera::Position = position;
		LookAt = lookAt;
		UpVector = upVector;

		Camera::ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle), 
			CameraFrustrum.width / CameraFrustrum.height, CameraFrustrum.near, CameraFrustrum.far);
		Camera::ViewMatrix = glm::lookAt(Position, LookAt, UpVector);

		Camera::ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	~PerspectiveCamera() = default;
	PerspectiveCamera(const PerspectiveCamera& camera) : Camera(camera)
	{
		this->LookAt = camera.LookAt;
		this->UpVector = camera.UpVector;
		this->CameraFrustrum = camera.CameraFrustrum;
	}

	void SetLookAt(const glm::vec3& lookAt)
	{
		this->LookAt = lookAt; this->RecalculateMatrix();
	}
	glm::vec3 getLookAt() { return this->LookAt; }

	void SetUpVector(const glm::vec3& upVector)
	{
		this->UpVector = upVector; this->RecalculateMatrix();
	}
	glm::vec3 getUpVector() { return this->UpVector; }

	void SetFrustrum(const Frustrum& frustrum)
	{
		this->CameraFrustrum = frustrum; this->RecalculateMatrix();
	}

protected:
	/**
	*	@brief Recalculating both the projection and view matrix for the camera
	*	
	*/
	void RecalculateMatrix() {
		Camera::ProjectionMatrix = glm::perspective(glm::radians(CameraFrustrum.angle),
			CameraFrustrum.width / CameraFrustrum.height, CameraFrustrum.near, CameraFrustrum.far);

		Camera::ViewMatrix = glm::lookAt(Camera::Position, LookAt, UpVector);
		//Camera::Position + CameraFront
		Camera::ViewProjectionMatrix = Camera::ProjectionMatrix * Camera::ViewMatrix;
	}
protected:
	glm::vec3 LookAt;
	glm::vec3 UpVector;
	Frustrum CameraFrustrum;
};

#endif // PERSPECTIVECAMERA_H_
