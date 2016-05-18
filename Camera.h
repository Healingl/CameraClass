#ifndef CAMERA_H
#define CAMERA_H


#include <vector>


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum Camera_Movement {
	NONE,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float windowWIDTH = 1080.0f, windowHEIGHT = 720.0f;
const float minDetect = 20.0f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	
	glm::vec3 Position;
	glm::vec3 TargetPosition;
	glm::vec3 WorldUp;
	GLfloat Zoom;
	GLint Direction;

	// Constructor with vectors
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, glm::vec3 targetPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
	{
		
		this->Position = glm::vec3(posX, posY, posZ);
		this->TargetPosition = targetPosition;
		this->WorldUp = up;
		this->Zoom = ZOOM;
	}
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat tagX, GLfloat tagY, GLfloat tagZ, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
	{

	
		this->Position = glm::vec3(posX, posY, posZ);
		this->TargetPosition = glm::vec3(tagX, tagY, tagZ);
		this->WorldUp = up;
		this->Zoom = ZOOM;
	}
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		
		return glm::lookAt(this->Position, this->TargetPosition, this->WorldUp);

	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void AutoTransView(float now_mouseX, float now_mouseY)
	{
		float cameraSpeed = 0.1f;
		if (now_mouseX >= windowWIDTH - minDetect && now_mouseX <= windowWIDTH)
		{
			
			this->Direction = RIGHT;
		}
		if (now_mouseX <= minDetect )
		{
			this->Direction = LEFT;
		}
		if (now_mouseY >= windowHEIGHT - minDetect)
		{
			this->Direction = FORWARD;
		}
		if (now_mouseY <= minDetect)
		{
			this->Direction = BACKWARD;
		}
		if (now_mouseX > minDetect && now_mouseX <windowWIDTH - minDetect&& now_mouseY>minDetect && now_mouseY < windowHEIGHT - minDetect){
		
			this->Direction = NONE;
		}
		
		switch (Direction)
		{
		case RIGHT:
			Position += glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
			TargetPosition += glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
			break;
		case LEFT:
			Position -= glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
			TargetPosition -= glm::normalize(glm::cross(TargetPosition - Position, WorldUp))* cameraSpeed;
			break;
		case FORWARD:
			Position -= glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp))* cameraSpeed;
			TargetPosition -= glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp)) * cameraSpeed;
			break;
		case BACKWARD:
			Position += glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp))* cameraSpeed;
			TargetPosition += glm::normalize(glm::cross(glm::normalize(glm::cross(TargetPosition - Position, WorldUp)), WorldUp)) * cameraSpeed;
			break;
		default:
			break;
		}


	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void RotateView(GLfloat xoffset, GLfloat yoffset)
	{
		glm::vec3 positionSaved;	
		positionSaved = Position;
		Position = glm::vec3(glm::rotate(glm::mat4(), -((GLint)xoffset)* 10.0f / windowWIDTH, WorldUp) * glm::vec4(positionSaved, 1.0f));

	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset)
	{
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
		
	}


};
#endif