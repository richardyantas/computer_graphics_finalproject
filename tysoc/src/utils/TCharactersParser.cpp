
#include <utils/TCharacterParser.h>


using namespace std;


namespace tysoc
{



    bool TCharacterParser::parseCharacter( TCharacterNode& tree, const string& charFileName )
    {

        ifstream _fStream( characterFile );
        Json::Reader _jReader;
        Json::Value _root;

        bool _succ = _jReader.parse( _fStream, _root );
        _fStream.close();

        if ( _succ )
        {
            if ( _root[ "Skeleton" ].isNull() )
            {
                cout << "TCharacterParser::parseCharacter> failed to parse the character file: " << charFileName << endl;
                return false;
            }
            else
            {
                return _loadSkeleton( tree, _root[ "Skeleton" ] );
            }
        }

        return false;
    }

    bool TCharacterParser::_loadSkeleton( TCharacterNode& tree, const Json::Value& root )
    {
        // parse joints - kinematic tree
        vector< TCharacterNodeData > _dataResources;

        if ( !_parseResources( _dataResources, root ) )
        {
            cout << "TCharacterParser::_loadSkeleton> error while parsing the skeleton resources" << endl;
            return false;
        }

        if ( !_buildTree() )
        {
            cout << "TCharacterParser::_loadSkeleton> error while parsing the skeleton tree" << endl;
            return false;
        }

        return true;
    }

    bool TCharacterParser::_parseResources( vector< TCharacterNodeData >& dataResources, const Json::Value& root )
    {
        // Parse Joints
        if ( root[ "Joints" ].isNull() )
        {
            cout << "TCharacterParser::_parseResources> no 'Joints' node in json" << endl;
            return false;
        }
        else
        {
            if ( !_parseJoints( dataResources, root[ "Joints" ] ) )
            {
                cout << "TCharacterParser::_parseResources> error while parsing 'Joints' node" << endl;
                return false;
            }
        }

        // Parse BodyDefs
        if ( root[ "BodyDefs" ].isNull() )
        {
            cout << "TCharacterParser::_parseResources> no 'BodyDefs' node in json" << endl;
            return false;
        }
        else
        {
            if ( !_parseShapes( dataResources, root[ "BodyDefs" ] ) )
            {
                cout << "TCharacterParser::_parseResources> error while parsing 'BodyDefs' node" << endl;
                return false;
            }
        }

        // Parse DrawShapeDefs
        if ( root[ "DrawShapeDefs" ].isNull() )
        {
            cout << "TCharacterParser::_parseResources> no 'DrawShapeDefs' node in json" << endl;
            return false;
        }
        else
        {
            if ( !_parseGraphics( dataResources, root[ "DrawShapeDefs" ] ) )
            {
                cout << "TCharacterParser::_parseResources> error while parsing 'DrawShapeDefs' node" << endl;
                return false;
            }
        }

        // Parse PDControllers
        if ( root[ "PDControllers" ].isNull() )
        {
            cout << "TCharacterParser::_parseResources> no 'PDControllers' node in json" << endl;
            return false;
        }
        else
        {
            if ( !_parsePDCdata( dataResources, root[ "PDControllers" ] ) )
            {
                cout << "TCharacterParser::_parseResources> error while parsing 'PDControllers' node" << endl;
                return false;
            }
        }

        return true;
    }

    bool TCharacterParser::_parseJoints( vector< TCharacterNodeData >& dataResources, const Json::Value& rootJoints )
    {
        int _numJoints = rootJoints.size();
        cout << "parsing " << _numJoints << " joints" << endl;

        for ( int q = 0; q < _numJoints; q++ )
        {
            // parse the joint
            string _jName   = rootJoints[ q ]["Name"].asString();

            int _jTypeId    = rootJoints[ q ]["Type"].asInt();
            int _jParentId  = rootJoints[ q ]["Parent"].asInt();

            float _jAttachX = rootJoints[ q ]["AttachX"].asFloat();
            float _jAttachY = rootJoints[ q ]["AttachY"].asFloat();
            float _jAttachZ = rootJoints[ q ]["AttachZ"].asFloat();

            float _jLinkStiffness = rootJoints[ q ]["LinkStiffness"].asFloat();
            float _jLimLow        = rootJoints[ q ]["LimLow"].asFloat();
            float _jLimHigh       = rootJoints[ q ]["LimHigh"].asFloat();

            TCharacterNodeData _nodeData;

            _nodeData.name  = _jName;
            _nodeData.resId = q;

            _nodeData.jointData.name            = _jName;
            _nodeData.jointData.pivot           = glm::vec3( _jAttachX, _jAttachY, _jAttachZ );
            _nodeData.jointData.axis            = glm::vec3( 0, 0, 1 );
            _nodeData.jointData.jointType       = _jTypeId;
            _nodeData.jointData.parentId        = _jParentId;
            _nodeData.jointData.linkStiffness   = _jLinkStiffness;
            _nodeData.jointData.loLimit         = _jLimLow;
            _nodeData.jointData.hiLimit         = _jLimHigh;


            dataResources.push_back( _nodeData );
        }

        return true;
    }

    bool TCharacterParser::_parseShapes( vector< TCharacterNodeData >& dataResources, const Json::Value& rootShapes )
    {
        int _numBodies = rootShapes.size();
        cout << "parsing " << _numBodies << " bodies" << endl;

        for ( int q = 0; q < _numBodies; q++ )
        {
            string _bName   = rootShapes[ q ][ "Name" ].asString();
            string _bShape  = rootShapes[ q ][ "Shape" ].asString();

            float _bMass    = rootShapes[ q ][ "Mass" ].asFloat();

            float _bAttachX = rootShapes[ q ][ "AttachX" ].asFloat();
            float _bAttachY = rootShapes[ q ][ "AttachY" ].asFloat();
            float _bAttachZ = rootShapes[ q ][ "AttachZ" ].asFloat();
            float _bTheta   = rootShapes[ q ][ "Theta "].asFloat();

            float _bParam0 = rootShapes[ q ][ "Param0" ].asFloat();
            float _bParam1 = rootShapes[ q ][ "Param1" ].asFloat();
            float _bParam2 = rootShapes[ q ][ "Param2" ].asFloat();

            float _bColorR = rootShapes[ q ][ "ColorR" ].asFloat();
            float _bColorG = rootShapes[ q ][ "ColorG" ].asFloat();
            float _bColorB = rootShapes[ q ][ "ColorB" ].asFloat();

            if ( dataResources[ q ].name != _bName )
            {
                cout << "bodydef with name: " << _bName << " is not part of the parsed skeletal structure" << endl;
                return false;
            }

            TCharacterNodeData& _nodeData = dataResources[ q ];

            _nodeData.shapeData.name = _bName;
            _nodeData.shapeData.shape = _bShape;

            glm::mat4 _localTransform( 1.0f );
            _localTransform = glm::rotate( _bTheta, glm::vec3( 0, 0, 1 ) ) * _localTransform;
            _localTransform = glm::translate( _bAttachX, _bAttachY, _bAttachZ ) * _localTransform;
            
            _nodeData.shapeData.localTransform = _localTransform;

            _nodeData.shapeData.mass = _bMass;
            _nodeData.shapeData.param0 = _bParam0;
            _nodeData.shapeData.param1 = _bParam1;
            _nodeData.shapeData.param2 = _bParam2;

            _nodeData.shapeData.color = TVec3( _bColorR, _bColorG, _bColorB );
        }

        return true;
    }

    bool TCharacterParser::_parseGraphics( vector< TCharacterNodeData >& dataResources, const Json::Value& rootGraphics )
    {
        int _numGraphicsDef = rootGraphics.size();
        cout << "parsing " << _numGraphicsDef << " graphics def." << endl;

        for ( int q = 0; q < _numGraphicsDef; q++ )
        {
            string _gName   = rootShapes[ q ][ "Name" ].asString();
            string _gShape  = rootShapes[ q ][ "Shape" ].asString();

            float _gAttachX = rootShapes[ q ][ "AttachX" ].asFloat();
            float _gAttachY = rootShapes[ q ][ "AttachY" ].asFloat();
            float _gAttachZ = rootShapes[ q ][ "AttachZ" ].asFloat();
            float _gTheta   = rootShapes[ q ][ "Theta "].asFloat();

            float _gParam0 = rootShapes[ q ][ "Param0" ].asFloat();
            float _gParam1 = rootShapes[ q ][ "Param1" ].asFloat();
            float _gParam2 = rootShapes[ q ][ "Param2" ].asFloat();

            float _gColorR = rootShapes[ q ][ "ColorR" ].asFloat();
            float _gColorG = rootShapes[ q ][ "ColorG" ].asFloat();
            float _gColorB = rootShapes[ q ][ "ColorB" ].asFloat();

            if ( dataResources[ q ].name != _gName )
            {
                cout << "drawdef with name: " << _gName << " is not part of the parsed skeletal structure" << endl;
                return false;
            }

            TCharacterNodeData& _nodeData = dataResources[ q ];

            _nodeData.drawData.name = _gName;
            _nodeData.drawData.shape = _gShape;

            glm::mat4 _localTransform( 1.0f );
            _localTransform = glm::rotate( _gTheta, glm::vec3( 0, 0, 1 ) ) * _localTransform;
            _localTransform = glm::translate( _gAttachX, _gAttachY, _gAttachZ ) * _localTransform;
            
            _nodeData.drawData.localTransform = _localTransform;

            _nodeData.drawData.param0 = _gParam0;
            _nodeData.drawData.param1 = _gParam1;
            _nodeData.drawData.param2 = _gParam2;

            _nodeData.drawData.color = TVec3( _gColorR, _gColorG, _gColorB );            
        }

        return true;
    }

    bool TCharacterParser::_parsePDCdata( vector< TCharacterNodeData >& dataResources, const Json::Value& rootPDC )
    {
        return true;
    }

    bool TCharacterParser::_buildTree( TCharacterNode& tree, const vector< TCharacterNodeData >& dataResources )
    {
        int _rootIndx = -1;

        int _proccessed = 0;
        // Find root of the tree
        for ( int q = 0; q < dataResources.size(); q++ )
        {
            if ( dataResources[q].parentId == -1 )
            {
                tree.name = dataResources[q].name;
                tree.id = q;
                tree.parent = NULL;
                tree.data = dataResources[q];
                _rootIndx = q;
                _proccessed++;
                break;
            }
        }

        if ( _rootIndx == -1 )
        {
            cout << "TCharacterParser::_buildTree> is there are root node?" << endl;
            return false;
        }

        TCharacterNode* _root = &tree;

        _processNode( _root );

        return true;
    }

    void TCharacterParser::_processNode( TCharacterNode* node, const vector< TCharacterNodeData >& dataResources )
    {
        for ( int q = 0; q < dataResources.size(); q++ )
        {
            if ( dataResources[q].jointData.parentId == node->id )
            {
                TCharacterNode* _child = new TCharacterNode();
                _child->id = q;
                _child->name = dataResources[q].name;
                _child->parent = node;
                _child->data = dataResources[q];

                node->children.push_back( _child );
            }
        }

        for ( int q = 0; q < node->children.size(); q++ )
        {
            _processNode( node->children[q], dataResources );
        }
    }

}