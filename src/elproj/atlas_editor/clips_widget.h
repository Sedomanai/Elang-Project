#pragma once
#include "clips_widget_ui.h"
#include "elgui/extension/view.h"

#include "elang/assets/camera.h"
#include "elang/common/random.h"
#include "elang/elements/button.h"
#include "elang/elements/basic.h"
#include "elang/elements/sprite.h"
#include "elang/elements/canvas.h"
#include "elang/elements/clipanim.h"

#include "tweeny/tween.h"

namespace el
{
	struct Clip;
	struct ShapeDebug2d;
	struct Camera;
	struct Texture;

	struct ClipframeHolder
	{
		Canvas<SpriteVertex> canvas;
		Button button;
		sizet index;

		ClipframeHolder(asset<Material> material, asset<Painter> painter, IButtonEvent* btnEvent);
		void reshape(asset<Clip> clip);
		void reorder(sizet index_);
	};

	struct ClipsWidget : public QWidget, public IButtonEvent
	{
		enum eState
		{
			None,
			Selecting,
			Moving,
			Deleting
		};

		Q_OBJECT
	public:
		ClipsWidget(QWidget* parent = Q_NULLPTR);

		void showEditor();
		void hideEditor();
		void animLoop();
		void recenterCamera();
		void loop();

		void createClip();
		void deleteClip();
		void addFrame();

		void updateOnAtlasLoad();
		void onKeyPress(QKeyEvent*);
		void onKeyRelease(QKeyEvent*);

		QElangView* view() { return ui.view; }
		QElangView* reel() { return ui.reel; }

		signal<> sig_Modified;
	private:
		void connectView();
		void connectReel();
		void safeCreateViewObjects();
		void safeCreateFrameObjects();
		void recreateList();
		void recreateReel();
		void reorderClipsAccordingToList();
		void updateAllCanvasButton();
		void connectList();
		void syncScroll();
		void updateCursor();
		vec2 screenToReel();

		// Inherited via IButtonEvent
		void onEnter(Entity self, Entity context) override {};
		void onHover(Entity self, Entity context) override;
		void onExit(Entity self, Entity context) override {};
		void postUpdate(Entity self, Entity context) override;
		void onMouseReelExit();

		bool mSuppressScroll;

		int mViewWidth, mViewHeight, mFramesWidth, mFramesHeight;
		int mMovingSide;

		rng crng;
		Ui::ClipsWidgetUI ui;

		ShapeDebug2d* mViewShapes;
		asset<Painter> mViewPainter;
		asset<Camera> mViewCam;
		tweeny::tween<vec3> mViewCamTween;
		Camera mViewCamTarget;

		asset<Texture> mTexture;
		ClipAnimation mClip;
		Sprite mClipSprite;
		Position mClipPosition;

		ShapeDebug2d* mReelShapes;
		QLabel* mLabel;
		
		asset<ClipframeHolder> mHovering, mHeld;
		eState mState;
		asset<Painter> mReelPainter;
		asset<Camera> mReelCam;
		tweeny::tween<vec3> mReelCamTween;
		Camera mReelCamTarget;

		bool mPaused, mSuppressSelect, mSuppressSpinbox;
		uint32 mFrame;

	};
}

