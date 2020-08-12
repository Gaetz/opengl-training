#pragma once
#include <string>
#include <rapidjson/document.h>
#include "Quaternion.h"
#include <functional>
#include <unordered_map>

using std::string;
using ActorFunc = std::function<class Actor* (const rapidjson::Value&)>;
using ComponentFunc = std::function<class Component* (class Actor*, const rapidjson::Value&)>;

class LevelLoader
{
public:
	static bool loadLevel(const string& filename);
	static bool loadJSON(const string& filename, rapidjson::Document& outDoc);

protected:
	static void loadGlobalProperties(const rapidjson::Value& inObject);
	static void loadActors(const rapidjson::Value& inArray);
	static void loadComponents(class Actor* actor, const rapidjson::Value& inArray);

	static std::unordered_map<string, ActorFunc> actorFactoryMap;
	static std::unordered_map<string, std::pair<int, ComponentFunc>> componentFactoryMap;

};

class JsonHelper
{
public:
	static bool getInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt);
	static bool getFloat(const rapidjson::Value& inObject, const char* inProperty, float& outFloat);
	static bool getString(const rapidjson::Value& inObject, const char* inProperty, std::string& outStr);
	static bool getBool(const rapidjson::Value& inObject, const char* inProperty, bool& outBool);
	static bool getVector3(const rapidjson::Value& inObject, const char* inProperty, Vector3& outVector);
	static bool getQuaternion(const rapidjson::Value& inObject, const char* inProperty, Quaternion& outQuat);
};