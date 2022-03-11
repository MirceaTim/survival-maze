#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_camera.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
        void CreateCube(const char* name, glm::vec3 color);

        struct Projectile
        {
            Projectile() : time_elapsed(0), forward(glm::vec3(0, 0, 0)), projectilePosition(glm::vec3(0, 0, 0)), disabled(0) {}
            Projectile(float time_elapsed, glm::vec3 forward, glm::vec3 projectilePosition, int disabled):
                time_elapsed(time_elapsed), forward(forward), projectilePosition(projectilePosition), disabled(disabled) {}
            float time_elapsed;
            glm::vec3 forward, projectilePosition;
            int disabled;
        };

        struct Enemy
        {
            Enemy() : x(0), y(0), xpos(0), ypos(0), numberHits(0), disabled(0), dir(1) {}
            Enemy(int x, int y, float xpos, float ypos, int numberHits, int disabled, int dir) :
                x(x), y(y), xpos(xpos), ypos(ypos), numberHits(numberHits), disabled(disabled), dir(dir) {}
            int x, y;
            float xpos, ypos;
            int numberHits, disabled, dir;
        };
    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Camera* camera;
        glm::mat4 projectionMatrix;
        bool thirdPerson;
        float FoV;
        float zNear;
        float zFar;
        bool persp;
        float left, right, bottom, top, angleX, angleY, projectile_time, xenemy, yenemy, injuryTimer, health, timeLeft;
        int timer;
        int m[15][15], xstart, ystart;
        glm::vec3 cameraPosition, bulletPosition;
        std::vector<Projectile> projectiles;
        std::vector<Enemy> enemies;
    };
}
