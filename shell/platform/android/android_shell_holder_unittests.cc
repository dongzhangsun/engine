#include <memory>
#include "flutter/shell/platform/android/android_shell_holder.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace flutter {
namespace testing {
namespace {
class MockPlatformViewAndroidJNI : public PlatformViewAndroidJNI {
  MOCK_METHOD2(FlutterViewHandlePlatformMessage,
               void(std::unique_ptr<flutter::PlatformMessage> message,
                    int responseId));
  MOCK_METHOD2(FlutterViewHandlePlatformMessageResponse,
               void(int responseId, std::unique_ptr<fml::Mapping> data));
  MOCK_METHOD3(FlutterViewUpdateSemantics,
               void(std::vector<uint8_t> buffer,
                    std::vector<std::string> strings,
                    std::vector<std::vector<uint8_t>> string_attribute_args));
  MOCK_METHOD2(FlutterViewUpdateCustomAccessibilityActions,
               void(std::vector<uint8_t> actions_buffer,
                    std::vector<std::string> strings));
  MOCK_METHOD0(FlutterViewOnFirstFrame, void());
  MOCK_METHOD0(FlutterViewOnPreEngineRestart, void());
  MOCK_METHOD2(SurfaceTextureAttachToGLContext,
               void(JavaLocalRef surface_texture, int textureId));
  MOCK_METHOD1(SurfaceTextureUpdateTexImage,
               void(JavaLocalRef surface_texture));
  MOCK_METHOD2(SurfaceTextureGetTransformMatrix,
               void(JavaLocalRef surface_texture, SkMatrix& transform));
  MOCK_METHOD1(SurfaceTextureDetachFromGLContext,
               void(JavaLocalRef surface_texture));
  MOCK_METHOD8(FlutterViewOnDisplayPlatformView,
               void(int view_id,
                    int x,
                    int y,
                    int width,
                    int height,
                    int viewWidth,
                    int viewHeight,
                    MutatorsStack mutators_stack));
  MOCK_METHOD5(FlutterViewDisplayOverlaySurface,
               void(int surface_id, int x, int y, int width, int height));
  MOCK_METHOD0(FlutterViewBeginFrame, void());
  MOCK_METHOD0(FlutterViewEndFrame, void());
  MOCK_METHOD0(FlutterViewCreateOverlaySurface,
               std::unique_ptr<PlatformViewAndroidJNI::OverlayMetadata>());
  MOCK_METHOD0(FlutterViewDestroyOverlaySurfaces, void());
  MOCK_METHOD1(FlutterViewComputePlatformResolvedLocale,
               std::unique_ptr<std::vector<std::string>>(
                   std::vector<std::string> supported_locales_data));
  MOCK_METHOD0(GetDisplayRefreshRate, double());
  MOCK_METHOD1(RequestDartDeferredLibrary, bool(int loading_unit_id));
};
}  // namespace

TEST(AndroidShellHolder, Create) {
  Settings settings;
  settings.enable_software_rendering = false;
  auto jni = std::make_shared<MockPlatformViewAndroidJNI>();
  auto holder = std::make_unique<AndroidShellHolder>(
      settings, jni, /*is_background_view=*/false);
  EXPECT_NE(holder.get(), nullptr);
  EXPECT_TRUE(holder->IsValid());
  EXPECT_NE(holder->GetPlatformView().get(), nullptr);
  auto window =
      fml::MakeRefCounted<AndroidNativeWindow>(nullptr, /*is_offscreen=*/true);
  holder->GetPlatformView()->NotifyCreated(window);
}
}  // namespace testing
}  // namespace flutter
