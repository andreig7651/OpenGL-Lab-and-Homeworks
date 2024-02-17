#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera_tema2.h"

namespace m1
{   
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

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
        void RenderScene(implemented::Camera_tema2* camera);
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, implemented::Camera_tema2* camera);
        void Tema2::RenderObstacle(glm::vec3* obj_pos , int *ind, glm::vec3* points, int *fill, 
            int *section, float *offset, Mesh* mesh, Shader* shader, implemented::Camera_tema2* camera);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        implemented::Camera_tema2* camera;
        glm::mat4 projectionMatrix;

        // TODO(student): If you need any other class variables, define them here.

        GLfloat fov;
        float orthoRight = 20.f, orthoUp = 20.f, orthoDown = -9.f, orthoLeft = -20.f;
        bool projectionType;
        bool renderCameraTarget;
        ViewportArea miniViewportArea;
        float translateX = 0, translateY = 0, translateZ = 0;

        float initialCamOX = 0, initialCamOY = 0, initialCamOZ = 0;
        float rotation_angle_OY = 0;
        glm::vec3 points[18];
        glm::vec3 red_points[18];
        glm::vec3 blue_points[18];
        glm::vec3 tree_red_points[18];
        glm::vec3 tree_blue_points[18];
        glm::vec3 car_red_points[18];
        glm::vec3 car_blue_points[18];
        float distRed = 0.3, distBlue = 0.3;
        int start = 0;
        int end = 0;
        int start_pos;
        int end_pos;
        int start1, start2;
        int copy_start1, copy_start2;
        int fill_percent1, steps, fill_percent2;
        int copy_fill_percent1, copy_fill_percent2;
        glm::vec3 obj_pos1, obj_pos2;
        glm::vec3 copy_obj_pos1, copy_obj_pos2;
        float offset1, offset2;
        float copy_offset1, copy_offset2;


    };
}   // namespace m1
