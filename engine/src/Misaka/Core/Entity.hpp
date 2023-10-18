#pragma once

#include <string>
namespace RendererDemo {

class Entity {
public:
	template<typename T>
	T& AddComponent(T& component);

	template<typename T>
	T& RemoveComponent(T& component);

	template<typename T>
	bool HasComponent(T& component);

    virtual const std::string GetClassName() { return m_ClassName; }

private:
	std::string m_ClassName = "Entity";
};

}
