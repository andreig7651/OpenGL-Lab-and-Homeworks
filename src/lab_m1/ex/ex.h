#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Ex/ex_camera.h"


namespace m1
{
    class Ex : public gfxc::SimpleScene
    {
    public:
        Ex();
        ~Ex();

        bool isOrtho = false;

        void Init() override;
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
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
        void RenderScene();

    protected:
        glm::vec3 points[35];
        glm::vec3 pointsRed[35];
        glm::vec3 pointsBlue[35];
        float distRed = 0.1, distBlue = 0.7;
        glm::vec3 UP = glm::vec3(0, 1, 0);
        implement::Camera* camera;
        float rotation_angle_OY = 0;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        float initialCamOX = 0, initialCamOY = 0, initialCamOZ = 0;
        // TODO(student): If you need any other class variables, define them here.
        float translateX = 0, translateY = 0, translateZ = 0;
        GLfloat fov;
        float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;
        bool projectionType;
        glm::mat4 modelMatrix = glm::mat4(1);
        ViewportArea miniViewportArea;
    };
}   // namespace m1





