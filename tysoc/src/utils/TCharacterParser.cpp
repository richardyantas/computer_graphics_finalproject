
#include <utils/TCharacterParser.h>


using namespace std;


namespace tysoc
{



    bool TCharacterParser::parseCharacter( TCharacterNode& tree, const string& charFileName )
    {

        string _fullCharFileName;
        _fullCharFileName += TYSOC_RESOURCES_PATH;
        _fullCharFileName += TYSOC_RESOURCES_CHARACTERS_SUB_PATH;
        _fullCharFileName += charFileName;

        ifstream _fStream;
		_fStream.open( _fullCharFileName.c_str(), std::ifstream::in );

		try
		{
			json _root;

			_fStream >> _root;

			_fStream.close();

			//cout << "json****" << endl;
			//cout << _root.dump( 4 ) << endl;
			//cout << "********" << endl;

			return _loadJson( tree, _root );
		}
		catch ( const std::exception& )
		{
			cout << "TCharacterParser::parseCharacter> failed to parse the character file: " << _fullCharFileName << endl;
		}

        return false;
    }

    bool TCharacterParser::_loadJson( TCharacterNode& tree, const json& root )
    {
        // parse joints - kinematic tree
        vector< TCharacterNodeData > _dataResources;

        if ( !_parseResources( _dataResources, root ) )
        {
            cout << "TCharacterParser::_loadSkeleton> error while parsing the skeleton resources" << endl;
            return false;
        }

        if ( !_buildTree( tree, _dataResources ) )
        {
            cout << "TCharacterParser::_loadSkeleton> error while parsing the skeleton tree" << endl;
            return false;
        }

        return true;
    }

    bool TCharacterParser::_parseResources( vector< TCharacterNodeData >& dataResources, const json& root )
    {
		cout << "foooo" << endl;
		cout << root.dump( 4 ) << endl;
		cout << "******" << endl;

        // Parse Joints
        if ( root.find( "Skeleton" ) != root.end() )
        {
			json _skeletonRoot = root["Skeleton"];
			if ( _skeletonRoot.find( "Joints" ) != _skeletonRoot.end() )
			{
				if ( !_parseJoints( dataResources, _skeletonRoot["Joints"] ) )
				{
					cout << "TCharacterParser::_parseResources> error while parsing 'Joints' node" << endl;
					return false;
				}
			}
			else
			{
				cout << "TCharacterParser::_parseResources> no 'Joints' node in json" << endl;
				return false;
			}
        }
        else
        {
			cout << "TCharacterParser::_parseResources> no 'Skeleton' node in json" << endl;
			return false;
        }

			//cout << "BodyDefs" << endl;
			//cout << root["BodyDefs"].dump( 4 ) << endl;
			//cout << "******" << endl;

			//cout << "DrawShapeDefs" << endl;
			//cout << root["DrawShapeDefs"].dump( 4 ) << endl;
			//cout << "******" << endl;

			//cout << "PDControllers" << endl;
			//cout << root["PDControllers"].dump( 4 ) << endl;
			//cout << "******" << endl;

        // Parse BodyDefs
        if ( root.find( "BodyDefs" ) != root.end() )
        {
			if ( !_parseShapes( dataResources, root["BodyDefs"] ) )
			{
				cout << "TCharacterParser::_parseResources> error while parsing 'BodyDefs' node" << endl;
				return false;
			}
        }
        else
        {
			cout << "TCharacterParser::_parseResources> no 'BodyDefs' node in json" << endl;
			return false;
        }

        // Parse DrawShapeDefs
        if ( root.find( "DrawShapeDefs" ) != root.end() )
        {
			auto _jsonShapesDefs = root["DrawShapeDefs"];
			if ( !_parseGraphics( dataResources, _jsonShapesDefs ) )
			{
				cout << "TCharacterParser::_parseResources> error while parsing 'DrawShapeDefs' node" << endl;
				return false;
			}
        }
        else
        {
			cout << "TCharacterParser::_parseResources> no 'DrawShapeDefs' node in json" << endl;
			return false;
        }

        // Parse PDControllers
        if ( root.find( "PDControllers" ) != root.end() )
        {
			if ( !_parsePDCdata( dataResources, root["PDControllers"] ) )
			{
				cout << "TCharacterParser::_parseResources> error while parsing 'PDControllers' node" << endl;
				return false;
			}
        }
        else
        {
			cout << "TCharacterParser::_parseResources> no 'PDControllers' node in json" << endl;
			return false;
        }

        return true;
    }

    bool TCharacterParser::_parseJoints( vector< TCharacterNodeData >& dataResources, json rootJoints )
    {
        int _numJoints = rootJoints.size();
        cout << "parsing " << _numJoints << " joints" << endl;

        for ( int q = 0; q < _numJoints; q++ )
        {
            // parse the joint
            string _jName   = rootJoints[ q ]["Name"];

            int _jTypeId    = rootJoints[ q ]["Type"];
            int _jParentId  = rootJoints[ q ]["Parent"];

            float _jAttachX = rootJoints[ q ]["AttachX"];
            float _jAttachY = rootJoints[ q ]["AttachY"];
            float _jAttachZ = rootJoints[ q ]["AttachZ"];

            float _jLinkStiffness = rootJoints[ q ]["LinkStiffness"];
            float _jLimLow        = rootJoints[ q ]["LimLow"];
            float _jLimHigh       = rootJoints[ q ]["LimHigh"];

			if ( _jName == "right_hip" )
			{
				cout << "******" << endl;
				cout << rootJoints.dump( 4 ) << endl;
				cout << "******" << endl;
			}

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

    bool TCharacterParser::_parseShapes( vector< TCharacterNodeData >& dataResources, json rootShapes )
    {
        int _numBodies = rootShapes.size();
        cout << "parsing " << _numBodies << " bodies" << endl;

        for ( int q = 0; q < _numBodies; q++ )
        {
            string _bName   = rootShapes[ q ][ "Name" ];
            string _bShape  = rootShapes[ q ][ "Shape" ];

            float _bMass    = rootShapes[ q ][ "Mass" ];

            float _bAttachX = rootShapes[ q ][ "AttachX" ];
            float _bAttachY = rootShapes[ q ][ "AttachY" ];
            float _bAttachZ = rootShapes[ q ][ "AttachZ" ];
            float _bTheta   = rootShapes[ q ][ "Theta"];

			if ( _bName == "right_hip" )
			{
				cout << "******" << endl;
				cout << rootShapes.dump( 4 ) << endl;
				cout << "******" << endl;
			}

            float _bParam0 = rootShapes[ q ][ "Param0" ];
            float _bParam1 = rootShapes[ q ][ "Param1" ];
            float _bParam2 = rootShapes[ q ][ "Param2" ];

            float _bColorR = rootShapes[ q ][ "ColorR" ];
            float _bColorG = rootShapes[ q ][ "ColorG" ];
            float _bColorB = rootShapes[ q ][ "ColorB" ];

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
            _localTransform = glm::translate( glm::vec3( _bAttachX, _bAttachY, _bAttachZ ) ) * _localTransform;
            
            _nodeData.shapeData.localTransform = _localTransform;

            _nodeData.shapeData.mass = _bMass;
            _nodeData.shapeData.param0 = _bParam0;
            _nodeData.shapeData.param1 = _bParam1;
            _nodeData.shapeData.param2 = _bParam2;

            _nodeData.shapeData.color = TVec3( _bColorR, _bColorG, _bColorB );
        }

        return true;
    }

    bool TCharacterParser::_parseGraphics( vector< TCharacterNodeData >& dataResources, json rootGraphics )
    {
        int _numGraphicsDef = rootGraphics.size();
        cout << "parsing " << _numGraphicsDef << " graphics def." << endl;

        for ( int q = 0; q < _numGraphicsDef; q++ )
        {
            string _gName   = rootGraphics[ q ][ "Name" ];
            string _gShape  = rootGraphics[ q ][ "Shape" ];

            float _gAttachX = rootGraphics[ q ][ "AttachX" ];
            float _gAttachY = rootGraphics[ q ][ "AttachY" ];
            float _gAttachZ = rootGraphics[ q ][ "AttachZ" ];
            float _gTheta   = rootGraphics[ q ][ "Theta"];

			if ( _gName == "right_hip" )
			{
				cout << "******" << endl;
				cout << rootGraphics.dump( 4 ) << endl;
				cout << "******" << endl;
			}

            float _gParam0 = rootGraphics[ q ][ "Param0" ];
            float _gParam1 = rootGraphics[ q ][ "Param1" ];
            float _gParam2 = rootGraphics[ q ][ "Param2" ];

            float _gColorR = rootGraphics[ q ][ "ColorR" ];
            float _gColorG = rootGraphics[ q ][ "ColorG" ];
            float _gColorB = rootGraphics[ q ][ "ColorB" ];

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
            _localTransform = glm::translate( glm::vec3( _gAttachX, _gAttachY, _gAttachZ ) ) * _localTransform;
            
            _nodeData.drawData.localTransform = _localTransform;

            _nodeData.drawData.param0 = _gParam0;
            _nodeData.drawData.param1 = _gParam1;
            _nodeData.drawData.param2 = _gParam2;

            _nodeData.drawData.color = TVec3( _gColorR, _gColorG, _gColorB );            
        }

        return true;
    }

    bool TCharacterParser::_parsePDCdata( vector< TCharacterNodeData >& dataResources, json rootPDC )
    {
		int _numPDCdefs = rootPDC.size();
		cout << "parsing " << _numPDCdefs << " PDc def." << endl;

		for ( int q = 0; q < _numPDCdefs; q++ )
		{
			string _cName = rootPDC[q]["Name"];

			float _cKp			 = rootPDC[q]["Kp"];
			float _cKd			 = rootPDC[q]["Kd"];
			float _cTorqueLim	 = rootPDC[q]["TorqueLim"];
			float _cTargetTheta  = rootPDC[q]["TargetTheta"];
			int _cUseWorldCoord = rootPDC[q]["UseWorldCoord"];

			if ( dataResources[q].name != _cName )
			{
				cout << "PDcdef with name: " << _cName << " is not part of the parsed skeletal structure" << endl;
				return false;
			}

			TCharacterNodeData& _nodeData = dataResources[q];

			_nodeData.pdcData.name = _cName;

			_nodeData.pdcData.Kp = _cKp;
			_nodeData.pdcData.Kd = _cKd;
			_nodeData.pdcData.torqueLimit = _cTorqueLim;
			_nodeData.pdcData.targetAngle = _cTargetTheta;
			_nodeData.pdcData.useWorldCoordinates = _cUseWorldCoord;
		}

        return true;
    }

    bool TCharacterParser::_buildTree( TCharacterNode& tree, const vector< TCharacterNodeData >& dataResources )
    {
        int _rootIndx = -1;

        int _proccessed = 0;
        // Find root of the tree
        for ( int q = 0; q < dataResources.size(); q++ )
        {
            if ( dataResources[q].jointData.parentId == -1 )
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

        _processNode( _root, dataResources );

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