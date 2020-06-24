#ifndef NF_SINGLETON_H
#define NF_SINGLETON_H

//The Singleton is from to boost/container/detail/Singleton.hpp
// T must be: no-throw default constructible and no-throw destructible
template <typename T>
struct Singleton
{
private:
    struct object_creator
    {
        // This constructor does nothing more than ensure that instance()
        //  is called before main() begins, thus creating the static
        //  T object before multithreading race issues can come up.
        object_creator() { Singleton<T>::Instance(); }
        inline void do_nothing() const { }
    };
    static object_creator create_object;

    Singleton();

public:
    typedef T object_type;

    // If, at any point (in user code), Singleton<T>::instance()
    //  is called, then the following function is instantiated.
    static object_type & Instance()
    {
        // This is the object that we return a reference to.
        // It is guaranteed to be created before main() begins because of
        //  the next line.
        static object_type obj;

        // The following line does nothing else than force the instantiation
        //  of Singleton<T>::create_object, whose constructor is
        //  called before main() begins.
        create_object.do_nothing();

        return obj;
    }
};

template <typename T>
typename Singleton<T>::object_creator Singleton<T>::create_object;

#endif