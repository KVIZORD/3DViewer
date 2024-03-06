#include <gtest/gtest.h>

#include <vector>

#include "model/objreader.h"
#include "model/scene.h"
#include "model/transform_matrix_builder.h"

namespace s21 {

TEST(MoveObject, PositiveMoveX) {
  Scene scene;
  scene.SetVertices(
      {1.1, 11.0, 21.0, 34.1, 5.555, -54, 1000001.1, 0.924, 765.0});
  scene.TransformVertices(TransformMatrixBuilder::CreateMoveMatrix(2.1, 0, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], 1.1 + 2.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 34.1 + 2.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 1000001.1 + 2.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(MoveObject, NegativeMoveX) {
  Scene scene;
  scene.SetVertices(
      {-4.3, 11.0, 21.0, 28.7, 5.555, -54, 999995.7, 0.924, 765.0});
  scene.TransformVertices(TransformMatrixBuilder::CreateMoveMatrix(-3.3, 0, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -4.3 - 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 28.7 - 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999995.7 - 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(MoveObject, PositiveMoveY) {
  Scene scene;
  scene.SetVertices({-1.0, 16.7, 21.0, 32, 11.255, -54, 999999, 6.624, 765.0});
  scene.TransformVertices(TransformMatrixBuilder::CreateMoveMatrix(0, 5.7, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 16.7 + 5.7);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 11.255 + 5.7);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 6.624 + 5.7);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(MoveObject, NegativeMoveY) {
  Scene scene;
  scene.SetVertices({-1.0, 4.4, 21.0, 32, -1.045, -54, 999999, -5.676, 765.0});
  scene.TransformVertices(TransformMatrixBuilder::CreateMoveMatrix(0, -6.6, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 4.4 - 6.6);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], -1.045 - 6.6);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], -5.676 - 6.6);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(MoveObject, PositiveMoveZ) {
  Scene scene;
  scene.SetVertices(
      {-1.0, 11.0, 32.15, 32, 5.555, -42.85, 999999, 0.924, 776.15});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateMoveMatrix(0, 0, 11.15));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 32.15 + 11.15);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -42.85 + 11.15);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 776.15 + 11.15);
}

TEST(MoveObject, NegativeMoveZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 16.6, 32, 5.555, -58.4, 999999, 0.924, 760.6});
  scene.TransformVertices(TransformMatrixBuilder::CreateMoveMatrix(0, 0, -4.4));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 16.6 - 4.4);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -58.4 - 4.4);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 760.6 - 4.4);
}

TEST(MoveObject, MoveXYZ) {
  Scene scene;
  scene.SetVertices(
      {-6.2, 12.2, 26.6, 26.8, 6.755, -48.4, 999993.8, 2.124, 770.6});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateMoveMatrix(-5.2, 1.2, 5.6));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -6.2 - 5.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 12.2 + 1.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 26.6 + 5.6);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 26.8 - 5.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 6.755 + 1.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -48.4 + 5.6);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999993.8 - 5.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 2.124 + 1.2);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 770.6 + 5.6);
}

TEST(RotateObject, ClockwiseRotateX) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(1.15, 0, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], -14.6746809);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 18.6186396);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 51.55840051);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -16.98791812);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], -697.886972);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 313.336286);
}

TEST(RotateObject, CounterclockwiseRotateX) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(-1, 0, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 23.61421605);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 2.09016759);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], -42.43805387);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -33.85069584);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 644.224543);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 412.553745);
}

TEST(RotateObject, ClockwiseRotateY) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(0, 1.5, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], 20.87665752);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 2.48297622);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], -51.60113882);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -35.73964846);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 71500.214595);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], -997439.875149);
}

TEST(RotateObject, CounterclockwiseRotateY) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(0, -0.77, 0));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -15.33675068);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 14.37998882);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 60.56444431);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -16.49084852);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 717377.408242);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924000000);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 696683.744154);
}

TEST(RotateObject, ClockwiseRotateZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(0, 0, 0.5));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -6.15126349);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 9.17398264);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 25.41943311);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 20.21658837);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 877581.241318);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 479425.870064);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765);
}

TEST(RotateObject, CounterclockwiseRotateZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(0, 0, -1.7));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], 11.03715741);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], -0.42562515);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 1.3856726);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], -32.4490051);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], -128843.5);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], -991663.937839);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765);
}

TEST(RotateObject, RotateXYZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateRotationMatrix(0.245, 0.245, 0.245));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], 1.56407401);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 4.96189431);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 23.15023277);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 15.71212079);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 27.2122729);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54.62123661);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 941350.82629793);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 292210.13663822);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], -168731.86747298);
}

TEST(ScaleObject, IncScaleX) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(1.1, 1, 1));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0 * 1.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0 * 1.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999 * 1.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(ScaleObject, DecScaleX) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(0.4, 1, 1));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0 * 0.4);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0 * 0.4);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999 * 0.4);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(ScaleObject, IncScaleY) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(1, 1.9, 1));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0 * 1.9);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555 * 1.9);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924 * 1.9);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(ScaleObject, DecScaleY) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(1, 0.1, 1));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0 * 0.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555 * 0.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924 * 0.1);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0);
}

TEST(ScaleObject, IncScaleZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(TransformMatrixBuilder::CreateScaleMatrix(1, 1, 8.8));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0 * 8.8);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54 * 8.8);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0 * 8.8);
}

TEST(ScaleObject, DecScaleZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateScaleMatrix(1, 1, 0.35));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0 * 0.35);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54 * 0.35);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0 * 0.35);
}

TEST(ScaleObject, ScaleXYZ) {
  Scene scene;
  scene.SetVertices({-1.0, 11.0, 21.0, 32.0, 5.5550, -54, 999999, 0.924, 765});
  scene.TransformVertices(
      TransformMatrixBuilder::CreateScaleMatrix(3.3, 3.3, 3.3));
  ASSERT_FLOAT_EQ(scene.GetVertices()[0], -1.0 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[1], 11.0 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[2], 21.0 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[3], 32.0 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[4], 5.555 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[5], -54 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[6], 999999 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[7], 0.924 * 3.3);
  ASSERT_FLOAT_EQ(scene.GetVertices()[8], 765.0 * 3.3);
}

} // namespace s21
