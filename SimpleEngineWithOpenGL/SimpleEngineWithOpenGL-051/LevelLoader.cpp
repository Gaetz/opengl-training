#include "LevelLoader.h"
#include <fstream>
#include <vector>
#include "Log.h"
#include <sstream>
#include "Game.h"
#include "BallActor.h"
#include "FollowActor.h"
#include "TargetActor.h"
#include "AudioComponent.h"
#include "BallMoveComponent.h"
#include "TargetComponent.h"
#include "PointLightComponent.h"
#include "MirrorCameraComponent.h"
#include "SkeletalMeshComponent.h"
#include "FollowCameraComponent.h"
#include "BoxComponent.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

using std::vector;

const int levelVersion = 1;
std::unordered_map<string, ActorFunc> LevelLoader::actorFactoryMap
{
	{ "Actor", &Actor::Create<Actor> },
	{ "BallActor", &Actor::Create<BallActor> },
	{ "FollowActor", &Actor::Create<FollowActor> },
	{ "PlaneActor", &Actor::Create<PlaneActor> },
	{ "TargetActor", &Actor::Create<TargetActor> },
};

std::unordered_map<string, std::pair<int, ComponentFunc>> LevelLoader::componentFactoryMap
{
	{ "AudioComponent", { static_cast<int>(ComponentType::Audio), &Component::Create<AudioComponent>} },
	{ "BallMove", { static_cast<int>(ComponentType::BallMove), &Component::Create<BallMoveComponent> } },
	{ "BoxComponent", { static_cast<int>(ComponentType::Box), &Component::Create<BoxComponent> } },
	{ "CameraComponent", { static_cast<int>(ComponentType::Camera), &Component::Create<CameraComponent> } },
	{ "FollowCamera", { static_cast<int>(ComponentType::FollowCamera), &Component::Create<FollowCameraComponent> } },
	{ "MeshComponent", { static_cast<int>(ComponentType::Mesh), &Component::Create<MeshComponent> } },
	{ "MoveComponent", { static_cast<int>(ComponentType::Move), &Component::Create<MoveComponent> } },
	{ "SkeletalMeshComponent", { static_cast<int>(ComponentType::SkeletalMesh), &Component::Create<SkeletalMeshComponent> } },
	{ "SpriteComponent", { static_cast<int>(ComponentType::Sprite), &Component::Create<SpriteComponent> } },
	{ "MirrorCamera", { static_cast<int>(ComponentType::MirrorCamera), &Component::Create<MirrorCameraComponent> } },
	{ "PointLightComponent", { static_cast<int>(ComponentType::PointLight), &Component::Create<PointLightComponent> }},
	{ "TargetComponent",{ static_cast<int>(ComponentType::Target), &Component::Create<TargetComponent> } }
};

bool LevelLoader::loadLevel(const string& filename)
{
	rapidjson::Document doc;
	if (!loadJSON(filename, doc))
	{
		Log::error(LogCategory::Application, "Failed to load level " + filename);
	}

	int version = 0;
	if (!JsonHelper::getInt(doc, "version", version) ||	version != levelVersion)
	{
		Log::error(LogCategory::Application, "Incorrect level file version for " + filename);
		return false;
	}

	const rapidjson::Value& globals = doc["globalProperties"];
	if (globals.IsObject())
	{
		loadGlobalProperties(globals);
	}

	const rapidjson::Value& actors = doc["actors"];
	if (actors.IsArray())
	{
		loadActors(actors);
	}
}

bool LevelLoader::loadJSON(const string& filename, rapidjson::Document& outDoc)
{
	// Load the file from disk into an ifstream in binary mode,
	// loaded with stream buffer at the end (ate)
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::ostringstream loadError;
		loadError << "File " << filename << " not found.";
		Log::error(LogCategory::Application, loadError.str());
		return false;
	}

	// Get the current position in stream buffer, which is size of file
	std::ifstream::pos_type fileSize = file.tellg();
	// Seek back to start of file
	file.seekg(0, std::ios::beg);

	// Create a vector of size + 1 (for null terminator)
	vector<char> bytes(static_cast<size_t>(fileSize) + 1);
	// Read in bytes into vector
	file.read(bytes.data(), static_cast<size_t>(fileSize));

	// Load raw data into RapidJSON document
	outDoc.Parse(bytes.data());
	if (!outDoc.IsObject())
	{
		std::ostringstream loadError;
		loadError << "File " << filename << " is not valid JSON.";
		Log::error(LogCategory::Application, loadError.str());
		return false;
	}

	return true;
}

void LevelLoader::saveLevel(const string& filename)
{
	// Create the document and root object
	rapidjson::Document doc;
	doc.SetObject();

	// Write the version
	JsonHelper::addInt(doc.GetAllocator(), doc, "version", levelVersion);

	// Globals
	rapidjson::Value globals(rapidjson::kObjectType);
	saveGlobalProperties(doc.GetAllocator(), globals);
	doc.AddMember("globalProperties", globals, doc.GetAllocator());

	// Actors
	rapidjson::Value actors(rapidjson::kArrayType);
	saveActors(doc.GetAllocator(), actors);
	doc.AddMember("actors", actors, doc.GetAllocator());

	// Save JSON to string buffer
	rapidjson::StringBuffer buffer;
	// Use PrettyWriter for pretty output (otherwise use Writer)
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	const char* output = buffer.GetString();

	// Write output to file
	std::ofstream outFile(filename);
	if (outFile.is_open())
	{
		outFile << output;
	}
}

void LevelLoader::loadGlobalProperties(const rapidjson::Value& inObject)
{
	Game& game = Game::instance();

	// Get ambient light
	Vector3 ambient;
	if (JsonHelper::getVector3(inObject, "ambientLight", ambient))
	{
		game.getRenderer().setAmbientLight(ambient);
	}

	// Get directional light
	const rapidjson::Value& dirObj = inObject["directionalLight"];
	if (dirObj.IsObject())
	{
		DirectionalLight& light = game.getRenderer().getDirectionalLight();

		// Set direction/color, if they exist
		JsonHelper::getVector3(dirObj, "direction", light.direction);
		JsonHelper::getVector3(dirObj, "color", light.diffuseColor);
	}
}

void LevelLoader::loadActors(const rapidjson::Value& inArray)
{
	// Loop through array of actors
	for (rapidjson::SizeType i = 0; i < inArray.Size(); i++)
	{
		const rapidjson::Value& actorObj = inArray[i];
		if (actorObj.IsObject())
		{
			// Get the type
			std::string type;
			if (JsonHelper::getString(actorObj, "type", type))
			{
				// Is this type in the map?
				auto iter = actorFactoryMap.find(type);
				if (iter != actorFactoryMap.end())
				{
					// Construct with function stored in map
					Actor* actor = iter->second(actorObj["properties"]);
					// Get the actor's components
					if (actorObj.HasMember("components"))
					{
						const rapidjson::Value& components = actorObj["components"];
						if (components.IsArray())
						{
							loadComponents(actor, components);
						}
					}
				}
				else
				{
					Log::error(LogCategory::Application, "Unknown actor type " + type);
				}
			}
		}
	}
}

void LevelLoader::loadComponents(Actor* actor, const rapidjson::Value& inArray)
{
	// Loop through array of components
	for (rapidjson::SizeType i = 0; i < inArray.Size(); i++)
	{
		const rapidjson::Value& compObj = inArray[i];
		if (compObj.IsObject())
		{
			// Get the type
			std::string type;
			if (JsonHelper::getString(compObj, "type", type))
			{
				auto iter = componentFactoryMap.find(type);
				if (iter != componentFactoryMap.end())
				{
					// Get the typeid of component
					ComponentType tid = static_cast<ComponentType>(iter->second.first);
					// Does the actor already have a component of this type?
					Component* comp = actor->getComponentOfType(tid);
					if (comp == nullptr)
					{
						// It's a new component, call function from map
						comp = iter->second.second(actor, compObj["properties"]);
					}
					else
					{
						// It already exists, just load properties
						comp->loadProperties(compObj["properties"]);
					}
				}
				else
				{
					Log::error(LogCategory::Application, "Unknown component type " + type);
				}
			}
		}
	}
}

void LevelLoader::saveGlobalProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject)
{
	// Ambient light
	JsonHelper::addVector3(alloc, inObject, "ambientLight",	Game::instance().getRenderer().getAmbientLight());

	// Directional light
	DirectionalLight& dirLight = Game::instance().getRenderer().getDirectionalLight();
	rapidjson::Value dirObj(rapidjson::kObjectType);
	JsonHelper::addVector3(alloc, dirObj, "direction", dirLight.direction);
	JsonHelper::addVector3(alloc, dirObj, "color", dirLight.diffuseColor);
	inObject.AddMember("directionalLight", dirObj, alloc);
}

void LevelLoader::saveActors(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inArray)
{
	const auto& actors = Game::instance().getActors();
	for (const Actor* actor : actors)
	{
		// Make a JSON object
		rapidjson::Value obj(rapidjson::kObjectType);
		// Add type
		JsonHelper::addString(alloc, obj, "type", Actor::typeNames[static_cast<int>(actor->getType())]);

		// Make object for properties
		rapidjson::Value props(rapidjson::kObjectType);
		// Save properties
		actor->saveProperties(alloc, props);
		// Add the properties member
		obj.AddMember("properties", props, alloc);

		// Save components
		rapidjson::Value components(rapidjson::kArrayType);
		saveComponents(alloc, actor, components);
		obj.AddMember("components", components, alloc);

		// Add actor to inArray
		inArray.PushBack(obj, alloc);
	}
}

void LevelLoader::saveComponents(rapidjson::Document::AllocatorType& alloc, const Actor* actor, rapidjson::Value& inArray)
{
	const auto& components = actor->getComponents();
	for (const Component* comp : components)
	{
		// Make a JSON object
		rapidjson::Value obj(rapidjson::kObjectType);
		// Add type
		JsonHelper::addString(alloc, obj, "type", Component::typeNames[static_cast<int>(comp->getType())]);

		// Make an object for properties
		rapidjson::Value props(rapidjson::kObjectType);
		// Save rest of properties
		comp->saveProperties(alloc, props);
		// Add the member
		obj.AddMember("properties", props, alloc);

		// Add component to array
		inArray.PushBack(obj, alloc);
	}
}

bool JsonHelper::getInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt)
{
	// Check if this property exists
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	// Get the value type, and check it's an integer
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	// We have the property
	outInt = property.GetInt();
	return true;
}

bool JsonHelper::getFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsDouble())
	{
		return false;
	}

	outFloat = property.GetDouble();
	return true;
}

bool JsonHelper::getString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	outStr = property.GetString();
	return true;
}

bool JsonHelper::getBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	outBool = property.GetBool();
	return true;
}

bool JsonHelper::getVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;
	if (!property.IsArray() || property.Size() != 3)
	{
		return false;
	}

	for (rapidjson::SizeType i = 0; i < 3; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outVector.x = property[0].GetDouble();
	outVector.y = property[1].GetDouble();
	outVector.z = property[2].GetDouble();

	return true;
}

bool JsonHelper::getQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat)
{
	auto itr = inObject.FindMember(inProperty);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	auto& property = itr->value;

	for (rapidjson::SizeType i = 0; i < 4; i++)
	{
		if (!property[i].IsDouble())
		{
			return false;
		}
	}

	outQuat.x = property[0].GetDouble();
	outQuat.y = property[1].GetDouble();
	outQuat.z = property[2].GetDouble();
	outQuat.w = property[3].GetDouble();

	return true;
}

void JsonHelper::addInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, int value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::addFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, float value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::addString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const std::string& value)
{
	rapidjson::Value v;
	v.SetString(value.c_str(), static_cast<rapidjson::SizeType>(value.length()),
		alloc);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::addBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, bool value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::addVector3(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Vector3& value)
{
	// Create an array
	rapidjson::Value v(rapidjson::kArrayType);
	// Push back elements
	v.PushBack(rapidjson::Value(value.x).Move(), alloc);
	v.PushBack(rapidjson::Value(value.y).Move(), alloc);
	v.PushBack(rapidjson::Value(value.z).Move(), alloc);

	// Add array to inObject
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}

void JsonHelper::addQuaternion(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, const Quaternion& value)
{
	// Create an array
	rapidjson::Value v(rapidjson::kArrayType);
	// Push back elements
	v.PushBack(rapidjson::Value(value.x).Move(), alloc);
	v.PushBack(rapidjson::Value(value.y).Move(), alloc);
	v.PushBack(rapidjson::Value(value.z).Move(), alloc);
	v.PushBack(rapidjson::Value(value.w).Move(), alloc);

	// Add array to inObject
	inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}