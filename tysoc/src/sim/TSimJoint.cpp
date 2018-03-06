
#include <sim/TSimJoint.h>

using namespace std;

namespace tysoc
{

    TSimJoint::TSimJoint( btRigidBody* pParent, std::string sParent,
						  btRigidBody* pChild, std::string sChild,
                          glm::vec3 pPivot, glm::vec3 pAxis,
						  float pLimitLow, float pLimitHigh )
    {
		bBodyParent = pParent;
        sBodyParent = sParent;

        bBodyChild = pChild;
        sBodyChild = sChild;

        pivot = pPivot;
        axis  = pAxis;

		limitLow	= pLimitLow;
		limitHigh	= pLimitHigh;

        bJoint = NULL;
    }

    TSimJoint::~TSimJoint()
    {
        bBodyParent = NULL;
        bBodyChild = NULL;
        bJoint = NULL;
    }



}