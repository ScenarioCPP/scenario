#-------------------------------------------------
#
# Project created by QtCreator 2018-11-21T08:35:39
#
#  Added AssetsManager, moved initialization to World
#
#-------------------------------------------------

TEMPLATE = lib
TARGET = box2d

DEFINES += BOX2DSHAREDLIB_LIBRARY
CONFIG+=sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11
INCLUDEPATH += "$$PWD/Box2D"
INCLUDEPATH += "$$PWD/Box2D/Box2D"
#INCLUDEPATH += "$$PWD/Box2D/Box2D/Common"
#INCLUDEPATH += "$$PWD/Box2D/Box2D/Dynamics"

SOURCES += \
            $$PWD/Box2D/Box2D/Dynamics/b2Body.cpp \
            $$PWD/Box2D/Box2D/Dynamics/b2World.cpp \
            $$PWD/Box2D/Box2D/Dynamics/b2Fixture.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp \
            $$PWD/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
            $$PWD/Box2D/Box2D/Dynamics/b2Island.cpp \
            $$PWD/Box2D/Box2D/Dynamics/b2ContactManager.cpp \
            $$PWD/Box2D/Box2D/Rope/b2Rope.cpp \
            $$PWD/Box2D/Box2D/Common/b2Draw.cpp \
            $$PWD/Box2D/Box2D/Common/b2BlockAllocator.cpp \
            $$PWD/Box2D/Box2D/Common/b2Settings.cpp \
            $$PWD/Box2D/Box2D/Common/b2Timer.cpp \
            $$PWD/Box2D/Box2D/Common/b2StackAllocator.cpp \
            $$PWD/Box2D/Box2D/Common/b2Math.cpp \ 
            $$PWD/Box2D/Box2D/Collision/b2Distance.cpp \
            $$PWD/Box2D/Box2D/Collision/b2CollideCircle.cpp \
            $$PWD/Box2D/Box2D/Collision/b2CollidePolygon.cpp \
            $$PWD/Box2D/Box2D/Collision/b2DynamicTree.cpp \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp \
            $$PWD/Box2D/Box2D/Collision/b2TimeOfImpact.cpp \
            $$PWD/Box2D/Box2D/Collision/b2BroadPhase.cpp \
            $$PWD/Box2D/Box2D/Collision/b2CollideEdge.cpp \
            $$PWD/Box2D/Box2D/Collision/b2Collision.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/XForm.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/ShapeDef.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Manifold.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Joint.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/BodyDef.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/JointDef.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/AABB.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/ShapeType.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/ManifoldPoint.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Vector.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/AssemblyInfo.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Body.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Contact.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Shape.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Matrix.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Delegates.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/World.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/RevoluteJoint.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/MassData.cpp \
#            $$PWD/Box2D/Contributions/Platforms/Box2D.Net/VariousImplementations.cpp \
#            $$PWD/Box2D/Contributions/Tests/Biped.cpp \
#            $$PWD/Box2D/Contributions/Tests/BipedDef.cpp \
#            $$PWD/Box2D/Contributions/Utilities/ConvexDecomposition/b2Triangle.cpp \
#            $$PWD/Box2D/Contributions/Utilities/ConvexDecomposition/b2Polygon.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2Controller.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2GravityController.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2ConstantForceController.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2TensorDampingController.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2BuoyancyController.cpp \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2ConstantAccelController.cpp

HEADERS += \
            $$PWD/Box2D/Box2D/Dynamics/b2World.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2Contact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2Joint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h \
            $$PWD/Box2D/Box2D/Dynamics/b2Body.h \
            $$PWD/Box2D/Box2D/Dynamics/b2Fixture.h \
            $$PWD/Box2D/Box2D/Dynamics/b2TimeStep.h \
            $$PWD/Box2D/Box2D/Dynamics/b2WorldCallbacks.h \
            $$PWD/Box2D/Box2D/Dynamics/b2ContactManager.h \
            $$PWD/Box2D/Box2D/Dynamics/b2Island.h \
            $$PWD/Box2D/Box2D/Box2D.h \
            $$PWD/Box2D/Box2D/Rope/b2Rope.h \
            $$PWD/Box2D/Box2D/Common/b2StackAllocator.h \
            $$PWD/Box2D/Box2D/Common/b2GrowableStack.h \
            $$PWD/Box2D/Box2D/Common/b2BlockAllocator.h \
            $$PWD/Box2D/Box2D/Common/b2Timer.h \
            $$PWD/Box2D/Box2D/Common/b2Math.h \
            $$PWD/Box2D/Box2D/Common/b2Draw.h \
            $$PWD/Box2D/Box2D/Common/b2Settings.h \
            $$PWD/Box2D/Box2D/Collision/b2Collision.h \
            $$PWD/Box2D/Box2D/Collision/b2DynamicTree.h \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2Shape.h \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2ChainShape.h \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2EdgeShape.h \
            $$PWD/Box2D/Box2D/Collision/Shapes/b2CircleShape.h \
            $$PWD/Box2D/Box2D/Collision/b2TimeOfImpact.h \
            $$PWD/Box2D/Box2D/Collision/b2BroadPhase.h \
            $$PWD/Box2D/Box2D/Collision/b2Distance.h \
# win32 { $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Stdafx.h \ $$PWD/Box2D/Contributions/Platforms/Box2D.Net/Shape.h \  }
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/Box2DAppDelegate.h \
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/Delegates.h \
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/TestEntriesViewController.h \
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/Box2DView.h \
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/GLES-Render.h \
#            $$PWD/Box2D/Contributions/Platforms/iPhone/Classes/iPhoneTest.h \
#            $$PWD/Box2D/Contributions/Tests/BipedTest.h \
#            $$PWD/Box2D/Contributions/Tests/ElasticBody.h \
#            $$PWD/Box2D/Contributions/Tests/PyramidStaticEdges.h \
#            $$PWD/Box2D/Contributions/Tests/Car.h \
#            $$PWD/Box2D/Contributions/Tests/BreakableBody.h \
#            $$PWD/Box2D/Contributions/Tests/StaticEdges.h \
#            $$PWD/Box2D/Contributions/Tests/ContactCallbackTest.h \
#            $$PWD/Box2D/Contributions/Tests/BipedDef.h \
#            $$PWD/Box2D/Contributions/Tests/Biped.h \
#            $$PWD/Box2D/Contributions/Tests/DynamicEdges.h \
#            $$PWD/Box2D/Contributions/Utilities/ConvexDecomposition/b2Triangle.h \
#            $$PWD/Box2D/Contributions/Utilities/ConvexDecomposition/b2Polygon.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2Controller.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2GravityController.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2BuoyancyController.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2TensorDampingController.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2ConstantForceController.h \
#            $$PWD/Box2D/Contributions/Enhancements/Controllers/b2ConstantAccelController.h \
#            $$PWD/Box2D/Contributions/Enhancements/FixedPoint/jtypes.h \
#            $$PWD/Box2D/Contributions/Enhancements/FixedPoint/Fixed.h

