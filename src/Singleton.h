#ifndef SINGLETON_PROPERTY_H
#define SINGLETON_PROPERTY_H
#include <memory>
// used like a property for other classes.
template<class C>
class Singleton{
	public:
		Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		static std::shared_ptr<C> get_instance(){
			static std::shared_ptr<C> s{new C};
			return s;
		}
	private:
};

#endif
