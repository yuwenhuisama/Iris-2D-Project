#ifndef CPPDSTORUBYMACRO_H_INCLUDED
#define CPPDSTORUBYMACRO_H_INCLUDED

#ifdef MINGW_WITH_RUBY
#include <ruby.h>

// ------Class Macro
#define DECLAR_FRIEND_CLASS(cppclass) friend class cppclass##ToRuby;
#define DEFINE_RUBY_CLASS_ALLOC_FUNC(cppklass) \
    public:\
        static VALUE __c_alloc(VALUE klass){\
            cppklass *cObj = new (cppklass)();\
            VALUE obj = Data_Wrap_Struct(klass, 0, __cFree, cObj);\
            return obj;\
        }

#define REALIZE_RUBY_CLASS_BEGIN(cppclass) static void Init_##cppclass() {
#define REALIZE_RUBY_CLASS(cppklass) cppklass##ToRuby::__cObj = rb_define_class(#cppklass, rb_cObject);
#define REALIZE_RUBY_ALLOC_FUNC(cppclass) rb_define_alloc_func(cppclass##ToRuby::__cObj, cppclass##ToRuby::__c_alloc);
#define REALIZE_RUBY_METHOD_FUNC(cppclass, mdnm, argc) \
    rb_define_method(cppclass##ToRuby::__cObj, #mdnm, (RbFunc)cppclass##ToRuby::_c_##mdnm, argc);
#define REALIZE_RUBY_METHOD_FUNC_WITH_SINGBOL(cppclass, mdnm, sb, argc) \
    rb_define_method(cppclass##ToRuby::__cObj, #mdnm#sb, (RbFunc)cppclass##ToRuby::_c_##mdnm, argc);
#define REALIZE_RUBY_CLASS_END };

#define REALIZE_RUBY_ATTR_VARIABLE_BEGIN() VALUE vl;
#define REALIZE_RUBY_ATTR_VARIABLE(vbnm, initvl) \
    vl = rb_iv_set(self, #vbnm, initvl);
#define REALIZE_RUBY_ATTR_VARIABLE_END()

#define DEFINE_CONVER_METHOD(mdnm) static VALUE _c_##mdnm
#define DEFINE_CONVER_CLASS_BEGIN(cppklass) \
    class cppklass##ToRuby : public IrisToRubyBaseClass, public cppklass {
#define DEFINE_CONVER_CLASS_END };

#define DEFINE_CONVER_IV_GET(vmnm) return rb_iv_get(self, #vmnm);
#define DEFINE_CONVER_IV_SET(vmnm, value) \
    rb_iv_set(self, #vmnm, value);\
    return Qnil;


#define DEFINE_VARIABLE_GETTER(mdnm) static VALUE _getter_##mdnm
#define DEFINE_VARIABLE_SETTER(mdnm) static VALUE _setter_##mdnm

#define REALIZE_VARIABLE_SETTER(cppklass, vbnm) \
    rb_define_method(cppklass##ToRuby::__cObj, #vbnm"=", (RbFunc)cppklass##ToRuby::_setter_##vbnm, 1);
#define REALIZE_VARIABLE_GETTER(cppklass, vbnm) \
    rb_define_method(cppklass##ToRuby::__cObj, #vbnm, (RbFunc)cppklass##ToRuby::_getter_##vbnm, 0);

#define REALIZE_RUBY_VARIABLE_GETTER_SETTER(cppklass, vbnm) \
    REALIZE_VARIABLE_SETTER(cppklass, vbnm) \
    REALIZE_VARIABLE_GETTER(cppklass, vbnm)

#define MACRO_VARIABLE_GETTER(vbnm) \
    DEFINE_VARIABLE_GETTER(vbnm)(VALUE self){\
        DEFINE_CONVER_IV_GET(vbnm) \
    }
#define MACRO_VARIABLE_SETTER_WITH_OBJ(vbnm, cppklass1, cppklass2, exp) \
    DEFINE_VARIABLE_SETTER(vbnm)(VALUE self, VALUE v){ \
        cppklass1* cppobj; \
        Data_Get_Struct(self, cppklass1, cppobj); \
        cppklass2* robj; \
        Data_Get_Struct(v, cppklass2, robj); \
        exp; \
        DEFINE_CONVER_IV_SET(vbnm, v); \
    }

#define MACRO_VARIABLE_SETTER_WITH_QV(vbnm, cppklass, exp) \
    DEFINE_VARIABLE_SETTER(vbnm)(VALUE self, VALUE v){ \
        cppklass* cppobj; \
        Data_Get_Struct(self, cppklass, cppobj); \
        exp; \
        DEFINE_CONVER_IV_SET(vbnm, v); \
    }

#define INIT_RUBY_CLASS(cppklass) cppklass##ToRuby::Init_##cppklass();

// ------Module Macro

#define REALIZE_RUBY_MODULE_BEGIN(mdnm) static void Init_##mdnm() {
#define REALIZE_RUBY_MODULE(mdnm) mdnm##ToRuby::__mod = rb_define_module(#mdnm);
#define REALIZE_RUBY_SINGLETON_METHOD_FUNC(modname, mdnm, args) \
    rb_define_singleton_method(modname##ToRuby::__mod, #mdnm, (RbFunc)modname##ToRuby::_m_##mdnm, args);
#define REALIZE_RUBY_MODULE_END }

#define DEFINE_CONVER_SINGLETON_METHOD(mdnm) static VALUE _m_##mdnm
#define DEFINE_CONVER_MODULE_BEGIN(modname) \
    class modname##ToRuby : public IrisToRubyBaseModule , public modname{ \
    public:
#define DEFINE_CONVER_MODULE_END };

#define INIT_RUBY_MODULE(modname) modname##ToRuby::Init_##modname();

// ------Type-def
typedef VALUE (*RbFunc)(...);

// BaseClass
class IrisToRubyBaseClass {
    public :
        IrisToRubyBaseClass() {}
        ~IrisToRubyBaseClass() {}
        static void __cFree(IrisToRubyBaseClass *p){delete p;}
        static VALUE __cObj;
};

class IrisToRubyBaseModule {
    public :
        IrisToRubyBaseModule();
        virtual ~IrisToRubyBaseModule() = 0;
        static VALUE __mod;
};
#endif // MINGW_WITH_RUBY
#endif // CPPDSTORUBYMACRO_H_INCLUDED
