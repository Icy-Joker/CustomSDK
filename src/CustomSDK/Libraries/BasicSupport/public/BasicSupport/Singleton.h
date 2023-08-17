#pragma once

#define SINGLETON_DECLARE(CLASS_NAME) \
private:\
	CLASS_NAME(){initialize();};\
	CLASS_NAME(const CLASS_NAME&);\
	CLASS_NAME& operator=(const CLASS_NAME&);\
	~CLASS_NAME(){finalize();};\
private:\
	friend class Singleton<CLASS_NAME>;

template<class ClassName>
class Singleton
{
public:
	static ClassName* instance()
	{
		static ClassName instance;
		return &instance;
	}
protected:
	Singleton()
	{
		//std::cout << "Singleton constructed" << std::endl;
	};
	virtual ~Singleton()
	{
		//std::cout << "Singleton destroyed" << std::endl;
	}
};