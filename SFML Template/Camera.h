#pragma once
//OpenGL
#include <SFML/OpenGL.hpp>
#include <SFML/Window/Window.hpp>
//SFML
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

class Camera
{
public:
	Camera(const sf::Vector2f _Size = sf::Vector2f(), const sf::Vector3f _Cam_Position = sf::Vector3f());
	~Camera();

	void setClearDepth(const float _Depth);
	void enableDepth();

	float getYaw() const { return yaw; }
	float getPitch() const { return pitch; }
	float getMouseSensitivity() const { return mouseSensitivity; }
	glm::vec3 getCameraPosition() const { return cameraPos; }

	void setViewDistance(const float _Near, const float _Far);
	void setSize(const float _X, const float _Y);
	void setSize(const sf::Vector2f _Size);
	void setCameraSpeed(const float _Speed) { cameraSpeed = _Speed; }
	void setCameraPosition(const sf::Vector3f _Position);
	void setMouseSensitivity(const float _Sensitivity) { mouseSensitivity = _Sensitivity; }
	void setYaw(const float _Yaw) { yaw = _Yaw; updateDirection(); }
	void setPitch(const float _Pitch) { pitch = _Pitch; updateDirection(); }

	void move(const float _X, const float _Y, const float _Z) { move(sf::Vector3f(_X, _Y, _Z)); }
	void move(const sf::Vector3f _Direction);

	void updateView();
	void update(const double _DT);
	void updateMouseMovement(sf::Window* window, const double _DT);
	void updateMovement(const double _DT);

private:
	void updateDirection();

	sf::Vector2f cameraSize;
	//X > Near
	//Y > Far
	sf::Vector2f viewDistance;

	//Camera
	glm::mat4 view;
	
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float cameraSpeed;
	//

	//Mouse looking
	sf::Vector2f last;

	float mouseSensitivity;
	float yaw, pitch;
	bool firstMouse;
	//
};

