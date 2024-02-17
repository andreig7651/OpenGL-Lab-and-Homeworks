#pragma once

#include "components/simple_scene.h"
#define NUM_COLOURS		(4)
#define NUM_OBJECTS		(3)
#define SPEED_FACTOR	(2.f)
#define RANGE			(.02f)


namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
     public:
        Lab1();
        ~Lab1();

        void Init() override;

     private:
        GLuint colourCase = 0, objectCase = 0;
        GLfloat clearRed, clearGreen, clearBlue;

        std::string objName;
        glm::vec3 objScale;

        GLfloat posX = -1.f, posY = 0.5f, posZ = 0.f;
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void changeClearColour();

        // TODO(student): Class variables go here

    };
}   // namespace m1
