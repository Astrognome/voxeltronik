/*
 * Describes a render task, drawable + camera + target
 */

#pragma once

namespace vtk {

//forward declaration
class Drawable;
class Camera;
class RenderTarget;

class RenderTask {
public:
	RenderTask(Drawable& drawable, Camera& camera, RenderTarget& renderTarget);

	void draw();

	Drawable& getDrawable();
	Camera& getCamera();
	RenderTarget& getRenderTarget();
		
protected:
	Drawable& mDrawable;
	Camera& mCamera;
	RenderTarget& mRenderTarget;
};

}
