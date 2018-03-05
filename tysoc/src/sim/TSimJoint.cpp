
#include <sim/TSimJoint.h>

using namespace std;

namespace tysoc
{

    TSimJoint::TSimJoint( btRigidBody* pParent, std::string sParent,
						  btRigidBody* pChild, std::string sChild )
    {
		bBodyParent = pParent;
        sBodyParent = sParent;

        bBodyChild = pChild;
        sBodyChild = sChild;

        bJoint = NULL;
    }

    TSimJoint::~TSimJoint()
    {
        bBodyParent = NULL;
        bBodyChild = NULL;
        bJoint = NULL;
    }



}