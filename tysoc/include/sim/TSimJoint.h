
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

        TSimJoint( btRigidBody* pParent, std::string sParent,
                   btRigidBody* pChild, std::string sChild );

        ~TSimJoint();
    };



}