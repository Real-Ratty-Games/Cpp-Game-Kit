/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "pch.h"
#include "CppUnitTest.h"
#include "SystemTypes.hpp"
#include "FileSystem.hpp"
#include "Collider.hpp"
#include "Collision.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine::Core;
using namespace GameEngine::Math;

namespace GameEngineTest
{
	TEST_CLASS(MathTests)
	{
	public:
		TEST_METHOD(Vector2Test)
		{
			vec2 a(10.0f, 14.0f);
			vec2 b(2.5f, -2.0f);

			const vec2 addExp(12.5f, 12.0f);
			vec2 add = a + b;
			Assert::AreEqual(addExp.X, add.X);
			Assert::AreEqual(addExp.Y, add.Y);

			const vec2 subExp(7.5f, 16.0f);
			vec2 sub = a - b;
			Assert::AreEqual(subExp.X, sub.X);
			Assert::AreEqual(subExp.Y, sub.Y);

			const vec2 mulExp(25.0f, -28.0f);
			vec2 mul = a * b;
			Assert::AreEqual(mulExp.X, mul.X);
			Assert::AreEqual(mulExp.Y, mul.Y);

			const vec2 divExp(4.0f, -7.0f);
			vec2 div = a / b;
			Assert::AreEqual(divExp.X, div.X);
			Assert::AreEqual(divExp.Y, div.Y);
		}

		TEST_METHOD(Vector3Test)
		{
			vec3 a(10.0f, 14.0f, 2.0f);
			vec3 b(2.5f, -2.0f, 3.0f);

			const vec3 addExp(12.5f, 12.0f, 5.0f);
			vec3 add = a + b;
			Assert::AreEqual(addExp.X, add.X);
			Assert::AreEqual(addExp.Y, add.Y);
			Assert::AreEqual(addExp.Z, add.Z);

			const vec3 subExp(7.5f, 16.0f, -1.0f);
			vec3 sub = a - b;
			Assert::AreEqual(subExp.X, sub.X);
			Assert::AreEqual(subExp.Y, sub.Y);
			Assert::AreEqual(subExp.Z, sub.Z);

			const vec3 mulExp(25.0f, -28.0f, 6.0f);
			vec3 mul = a * b;
			Assert::AreEqual(mulExp.X, mul.X);
			Assert::AreEqual(mulExp.Y, mul.Y);
			Assert::AreEqual(mulExp.Z, mul.Z);

			const vec3 divExp(4.0f, -7.0f, 2.0f/3.0f);
			vec3 div = a / b;
			Assert::AreEqual(divExp.X, div.X);
			Assert::AreEqual(divExp.Y, div.Y);
			Assert::AreEqual(divExp.Z, div.Z);

			const vec3 crossExp(46.0f, -25.0f, -55.0f);
			vec3 cross = vec3::Cross(a, b);
			Assert::AreEqual(crossExp.X, cross.X);
			Assert::AreEqual(crossExp.Y, cross.Y);
			Assert::AreEqual(crossExp.Z, cross.Z);
		}

		TEST_METHOD(Vector4Test)
		{
			vec4 a(10.0f, 14.0f, 2.0f, -1.0f);
			vec4 b(2.5f, -2.0f, 3.0f, 4.0f);

			const vec4 addExp(12.5f, 12.0f, 5.0f, 3.0f);
			vec4 add = a + b;
			Assert::AreEqual(addExp.X, add.X);
			Assert::AreEqual(addExp.Y, add.Y);
			Assert::AreEqual(addExp.Z, add.Z);

			const vec4 subExp(7.5f, 16.0f, -1.0f, -5.0f);
			vec4 sub = a - b;
			Assert::AreEqual(subExp.X, sub.X);
			Assert::AreEqual(subExp.Y, sub.Y);
			Assert::AreEqual(subExp.Z, sub.Z);

			const vec4 mulExp(25.0f, -28.0f, 6.0f, -4.0f);
			vec4 mul = a * b;
			Assert::AreEqual(mulExp.X, mul.X);
			Assert::AreEqual(mulExp.Y, mul.Y);
			Assert::AreEqual(mulExp.Z, mul.Z);

			const vec4 divExp(4.0f, -7.0f, 2.0f / 3.0f, -0.25f);
			vec4 div = a / b;
			Assert::AreEqual(divExp.X, div.X);
			Assert::AreEqual(divExp.Y, div.Y);
			Assert::AreEqual(divExp.Z, div.Z);
		}

		TEST_METHOD(Matrix4Test)
		{
			mat4 a(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 4.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);

			mat4 b(3.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 4.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 3.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 2.0f);
			
			mat4 result(3.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 8.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 12.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 2.0f);

			mat4 cross = a * b;

			Assert::IsTrue(cross == result);
		}

		TEST_METHOD(CollisionTest)
		{
			const vec2				point(5.0f, 2.0f);
			const BoxCollider		box		= { vec2(4.0f, 1.0f), vec2(10.0f, 15.0f) };
			const BoxCollider		box2	= { vec2(10.0f, 20.0f), vec2(5.0f, 2.0f) };
			const CircleCollider	circle	= { vec2(3.0f, 2.0f), 2.5f };
			const CircleCollider	circle2 = { vec2(3.0f, 2.0f), 15.0f };

			Assert::IsTrue(Collision::Intersect(point,	box));
			Assert::IsTrue(Collision::Intersect(box,	box2));
			Assert::IsTrue(Collision::Intersect(point,	circle));
			Assert::IsTrue(Collision::Intersect(circle, circle2));
			Assert::IsTrue(Collision::Intersect(box,	circle));
			Assert::IsTrue(Collision::Intersect(box,	circle2));
		}
	};
}
