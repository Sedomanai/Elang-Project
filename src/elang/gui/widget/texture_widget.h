/*****************************************************************//**
 * @file   texture_widget.h
 * @brief  Custom OpenGL view which displays a texture
 *	       Pan view with scrollbars, mouse middle click, and right click
 *		   Zoom in and out using middle mouse wheel
 * 
 * @author Sedomanai
 * @date   September 2022
 *********************************************************************/

#pragma once
#include "texture_widget_ui.h"

#include "../extension/view.h"

#include "../../assets/camera.h"
#include "../../elements/basic.h"
#include "../../elements/sprite.h"
#include "../../registry/asset.h"
#include <tweeny/tween.h>

namespace el
{
	struct Material;
	struct Painter;
	class QElangTextureWidget : public QWidget
	{
		Q_OBJECT

	public:
		QElangTextureWidget(QWidget* parent = Q_NULLPTR, bool internalLoop = false);
		virtual ~QElangTextureWidget() { release(); }

		// Call this in a custom loop if the parameter internalLoop was false when constructed
		// Used for tweening, panning, etc.
		virtual void loop();

		// Update texture using a material that holds the texture. 
		// If you reimport or modify either the texture or the material, you must call this method again
		void updateMaterial(asset<Material>, const vec2& startPosition = vec2(-65332.0f, 65332.0f), float startScale = 1.0f);

		// why was this exposed?... pending
		//QElangViewSignaled* view();

		vec2 camPosition();
		float camScale();

	protected:
		Ui::QElangTextureWidgetUI ui;

		Qt::CursorShape mMoveCursor;
		aabb mCamBounds;
		vec2 mMoveDelta;
		vec2 mMoveCenter;
		vec2 mScrollStep;
		float mResolution;

		Box mMainCamBox, mTextureBox;
		asset<Material> mMaterial;
		asset<Painter> mPainter;
		asset<Camera> mMainCam;
		tweeny::tween<vec3> mMainCamTween;
		Camera mMainCamTarget;

		Sprite mSprite;
		Position mSpritePosition;

		bool mSuppressScroll;
		bool mMovingScreen;

		void safeCreateObjects();
		void connectMouseInput();
		void snapCamera();
		void syncCameraTarget(); // fixed
		void syncScrollBars(); // fixed
		void syncScrollBarPositionToCam();
		virtual void release();
	};

}





