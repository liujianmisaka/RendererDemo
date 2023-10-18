#include "Misaka/World/Entity.hpp"

namespace RendererDemo {

template<typename T>
T& Entity::AddComponent(T& component) {
	return false;
}

template<typename T>
T& Entity::RemoveComponent(T& component) {
	return false;
}

template<typename T>
bool Entity::HasComponent(T& component) {
	return false;
}

}
