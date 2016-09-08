C++ Notes
=========

# Effective C++

The following are some notes that I've took on the items discussed in
the book.

## Item 4 - Make sure that objects are initialized before use

Object members are initialized before executing the body of the
constructor through initialization lists

Object members are initialized in the same order they're declared in the
class, and not in the order given by the initialization list

Good practice: use the same order when declaring members and in the
initialization list

Use initialization lists instead of assigning values in the constructor
body, as this avoids double initialization (the default constructor will
also be called in the initialization list)

## Item 5 - Functions that C++ silently writes and calls

Compilers can implicitly declare the default constructor, copy
constructor, copy assignment operator, and destructor if these are
necessary and the programmer didn't declare them

The copy assignment operator won't be defined if the class contains
references or consts members.

## Item 7 - Declare virtual destructors in polymorphic base classes

Deleting a derived class object through a pointer to it's base class
that doesn't have a virtual destructor results in undefined behaviour as
derived class-specific resources won't be freed

Don't declare virtual destructors for non-polymorphic classes (or for
classes that will never become base classes). It's a bad idea because
objects that have virtual methods occupy more space for the vptr.

## Item 13 - Resource Acquisition Is Initialization (RAII)

Simply put, resources should be acquired and then turned over to
resource-managing objects. There are two ways of doing this:
  * Acquire resource, initialize resource-managing object with it
  * Acquire resource, assign to resource-managing object

Resource-managing objects use their destructors to release the
resources, which is safer because these are called automatically when
the object is destroyed.

Resource leaks are prevented through use of RAII objects that
**acquire** resources in *constructors* and **release** them in their
*destructors*.

Examples in the standard library of resource-managing objects:
  * `std::shared_ptr<T>`- reference counting, intuitive copy behaviour
  * `std::auto_ptr<T>`  - set to null when copied

## Item 17 - Store `new`ed objects in smart pointers in standalone statements

C++ doesn't guarantee a particular order when evaluating function call
parameters. This can lead to leaked resources, for example:

```
function(std::shared_ptr<MyClass>(new MyClass), exception_thrower());
```

The function arguments can be evaluated (a.k.a. valid C++) in this order:

  - `new MyClass`
  - `exception_thrower()`
  - `shared_ptr<MyClass>()`

If the `exception_thrower()` call throws an exception, the smart pointer
class is never created, thus leaking the newly created `MyClass` object.

## Item 27 - Minimize casting

Use C++-style casting instead of C-style:
  * `const_cast<T>`  - for getting rid of constness of objects
  * `dynamic_cast<T>` - for safe downcasting (from a base class to a
    specific type in the inheritance hierarchy), returns null for
    failure
  * `reinterpret_cast<T>` - low-level casts, e.g. pointer to int
  * `static_cast<T>` - implicit conversions and upcasting (from a
    derived class to a base class)

Avoid casting in general try to design it out, especially `dynamic_casts` in
performance-sensitive code. Hide casting in library functions, so
clients don't have to write it.

## Item 28 - Avoid returning "handles" to object internals

Avoid returning references, pointers, or iterators to object internals
(a.k.a. fields and methods of a class instance). This helps overall
encapsulation, const member functions will act const.

```
#include <memory>

class Component {
    public:
        int value;
};

class SystemData {
    public:
        Component base;
        Component helper;
};

class System {
    public:
        Component& get_base() const { return data->base; }
        Component& get_helper() const { return data->helper; }

    private:
        std::shared_ptr<SystemData> data;
};

int main(void)
{
    System system;

    system.get_base().value = 1;

    return 0;
}
```

In this example, although the getter methods for the System class are
const, these return references to objects that are part of the
SystemData class - thus making it possible to alter the internals of the
System class.

One solution might be to make the reference return type const, but that
won't solve the issue of dangling references if the System object is
deallocated (e.g. when running out of scope).
