
#pragma once

#include "TCommon.h"


namespace tysoc
{

    struct TSimJoint
    {
		enum
		{
			JOINT_TYPE_REVOLUTE
		};

        btRigidBody* bBodyParent;
        std::string sBodyParent;

        btRigidBody* bBodyChild;
        std::string sBodyChild;

        btHingeConstraint* bJoint;

        glm::vec3 pivot;
        glm::vec3 axis;

		float limitLow;
		float limitHigh;

        TSimJoint( btRigidBody* pParent, std::string sParent,
                   btRigidBody* pChild, std::string sChild,
                   glm::vec3 pPivot, glm::vec3 pAxis,
				   float pLimitLow, float pLimitHigh );

        ~TSimJoint();
    };



}