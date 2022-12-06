#include "Camera.h"

Camera::Camera(const sf::Vector2f _Size, const sf::Vector3f _Pos)
{
	cameraSize = _Size;
	cameraSpeed = 0.5f;

	mouseSensitivity = 0.15;
	yaw = 0;
	pitch = 0;
	firstMouse = true;

	view = glm::mat4(1.f);

	cameraPos = glm::vec3(_Pos.x, _Pos.y, _Pos.z);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	updateView();
}

Camera::~Camera()
{

}

void Camera::enableDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void Camera::setViewDistance(const float _Near, const float _Far)
{
	viewDistance = sf::Vector2f(_Near, _Far);
}

void Camera::setCameraPosition(const sf::Vector3f _Position)
{
	cameraPos.x = _Position.x;
	cameraPos.y = _Position.y;
	cameraPos.z = _Position.z;
}

void Camera::move(const sf::Vector3f _Direction)
{
	cameraPos.x += _Direction.x;
	cameraPos.y += _Direction.y;
	cameraPos.z += _Direction.z;
}

void Camera::update(const double _DT)
{
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(glm::value_ptr(view));
}

void Camera::updateMouseMovement(sf::Window* window, const double _DT)
{
	float xpos = sf::Mouse::getPosition(*window).x;
	float ypos = sf::Mouse::getPosition(*window).y;

	if (firstMouse)
	{
		last.x = sf::Mouse::getPosition(*window).x;
		last.y = sf::Mouse::getPosition(*window).y;
		firstMouse = false;
	}

	float xoffset = xpos - last.x;
	float yoffset = last.y - ypos;
	last.x = xpos;
	last.y = ypos;

	float sensitivity = mouseSensitivity;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	updateDirection();
}

void Camera::updateMovement(const double _DT)
{
	float camSpeed = cameraSpeed * (_DT * 100);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		camSpeed *= 2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		camSpeed /= 2;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		glm::vec3 temp = camSpeed * cameraFront;
		//temp.y = 0;
		cameraPos += temp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		glm::vec3 temp = camSpeed * cameraFront;
		//temp.y = 0;
		cameraPos -= temp;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * camSpeed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		cameraPos.y += camSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		cameraPos.y -= camSpeed;
}

void Camera::setSize(const float _X, const float _Y)
{
	setSize(sf::Vector2f(_X, _Y));
}

void Camera::setSize(const sf::Vector2f _Size)
{
	cameraSize = _Size;
	updateView();
}

void Camera::setLastMouse(const sf::Vector2f _Last)
{
	last = _Last;
}

void Camera::updateDirection()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void Camera::updateView()
{
	glViewport(0.0f, 0.0f, cameraSize.x, cameraSize.y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = (float)cameraSize.x / (float)cameraSize.y;
	glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
}