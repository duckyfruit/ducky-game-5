#include "Mode.hpp"

#include "Scene.hpp"
#include "WalkMesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//animator
	struct Animation{
	std::vector<std::vector<Scene::Transform*>> frames; //a vector of vectors
	std::vector<std::vector<glm::vec3>> scales; //a vector of scales
	int fps = 12;
	int numframes;
	}duckrun, duckidle;
	int currframe = 0;
	float animtimer = 0.0f;
	glm::highp_quat *animrot;

	std::vector<Animation> animations;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	glm::highp_quat rotatecam;
	glm::highp_quat origcamrot;
	Scene::Transform *playertranslate;
	Scene::Transform *camrotate;
	Scene::Transform *camtranslate;
	//glm::vec3 playerpos;

	float rotateholdx;
	float rotateholdy;
	bool duckrotated = false;
	glm::highp_quat pastrotation;
	//float playerrotate;
	//float camrotate;


	//player info:
	struct Player {
		WalkPoint at;
		//transform is at player's feet and will be yawed by mouse left/right motion:
		Scene::Transform *transform = nullptr;
		//camera is at player's head and will be pitched by mouse up/down motion:
		Scene::Camera *camera = nullptr;
	} player;
};
