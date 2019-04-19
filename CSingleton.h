#pragma once

template <typename T>
class CSingleton
{
private:
	static T* instance;
public:
	static T* Instance()
	{
		if (!instance)
		{
			instance = new T;
		}
		return instance;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(instance);
	}
};

template <typename T>
T* CSingleton<T>::instance = nullptr;