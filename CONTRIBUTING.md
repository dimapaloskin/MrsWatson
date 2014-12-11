Contributing to MrsWatson
=========================

Submitting a Patch
------------------

So perhaps you've found a bug in MrsWatson, or maybe even added a new
feature which you would like to see merged into the codebase. Great!
Patches are happily accepted into the project, provided they meet the
following conditions:

* The [test suite][1] still passes with 100% success rate
  - Also, you get big bonus points for adding new tests, both in the case
    of bugfixes or new features.
  - The test suite is also run through [valgrind][5] and must not leak any
    resources or overwrite memory boundaries. As valgrind only runs well on
    Linux, you may ask for valgrind verification in your pull request if
    you do not have access to a Linux machine/VM.
* The code is properly formatted, and meets the project's style and
  readability conventions.
* In the case of a new feature, it provides something which is useful to
  the broader community.

Regarding the last point, niche features which are only likely to be used by
yourself should not be submitted to the codebase. Since the code is
open-source, you are free to maintain a fork with whatever crazy features
you like and pull from upstream.

Lastly, it should be noted that patches are *only* accepted via GitHub on
the [project's official homepage][4]. Patches sent as diffs over email,
with carrier pigeons, etc., will be asked to resubmit as pull requests over
GitHub. This is because GitHub offers code review and public visibility of
the merge process.


Coding Style Conventions
------------------------

MrsWatson is indented in [K&R style][2], with the addition of the 1TBS
convention for function declarations. This style has been chosen for its
widespread familiarity and good readability. Indentation width is 4 spaces
(no tabs). Camel-casing is used for class and variable names, with
uppercase used for types and lowercase for instances.

You can use the [astyle][3] program to format your additions to MrsWatson.
Please run the script `scripts/format-code.sh` from the project's top-level
directory before submitting any pull requests.


Coding Conventions
------------------

MrsWatson is written in C, although there is a small amount of C++ code
used to communicate with VST plug-ins. Please do not expand the amount of
C++ code in the project unless strictly necessary (and the same goes for
other languages such as Obj-C).

That said, MrsWatson uses a python-like meta-class structure which you
should adhere to. Also, long and readable names are preferred (which is in
contrast to much C code on the internet).


Meta-Classes
------------

Classes in MrsWatson are simple structs with some associated functions that
are able to operate on them. A naming convention is used to associate the
class with the associated functions. Each of these functions takes in a
"self" argument as its first parameter, just like in Python. Also like
Python, there are no private members in the structs, so a leading underscore
is used to indicate that a member should not be directly accessed.

Instead of passing raw pointers throughout the source code, typedefs are
used to make the code easier to understand. Thus, a sample class might look
like this:

    typedef struct {
        int foo;
        char _bar;
        char* baz;
    } MyClassMembers;
    typedef MyClassMembers* MyClass;

Each class should provide a constructor function and a destructor function
so that the caller does not need to manually allocate and free the
associated memory. By convention, these functions should be prefixed with
"new" and "free". Continuing our example:

    MyClass newMyClass(void)
    {
        MyClass result = (MyClass)malloc(sizeof(MyClassMembers));
        result->foo = 0;
        result->_bar = 'a';
        result->baz = NULL;
        return result;
    }

    void freeMyClass(MyClass self)
    {
        if (self != NULL) {
            free(self->baz);
            free(self);
        }
    }

Any member functions for this class should begin with the class name. This
begins to get a little verbose, but at least it makes the code easy to
understand. Continuing our example:

    char myClassGetBar(MyClass self)
    {
        return self->_bar;
    }

    size_t myClassBazLength(MyClass self)
    {
        return self->baz != NULL ? strlen(self->baz) : 0;
    }

The result is a convention that allows one to write code like this:

    MyClass whatever = newMyClass();
    if(myClassBazLength(whatever)) {
        char ch = myClassGetBar(whatever);
    }
    freeMyClass(whatever);


[1]: TESTING.md
[2]: http://en.wikipedia.org/wiki/Indent_style#K.26R_style
[3]: http://astyle.sourceforge.net/astyle.html
[4]: https://github.com/teragonaudio/MrsWatson
[5]: http://valgrind.org/